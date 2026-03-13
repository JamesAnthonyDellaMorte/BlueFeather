#include "nualstl_n.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <libultraship/bridge/audiobridge.h>
#include <ship/Context.h>
#include <ship/audio/Audio.h>
#include <ship/audio/AudioPlayer.h>
#include <ship/resource/ResourceManager.h>

#include "generated/runtime_archive_rom_table.h"

extern "C" {
#include "player.h"
}

namespace {

constexpr size_t kOtrHeaderSize = 64;
constexpr uint32_t kBlobResourceType = 0x4F424C42;
constexpr int kSequencePlayerCount = 4;
constexpr int kNativeSampleRate = NU_AU_OUTPUT_RATE;

struct HostSongData {
    std::vector<uint8_t> raw;
    std::vector<char*> channelData;
    std::vector<char*> volumeData;
    std::vector<char*> pitchBendData;
    std::vector<unsigned long> drumData;
    song_t song = {};
};

struct HostPointerBankData {
    ptr_bank_t bank = {};
    std::vector<uint8_t> baseNotes;
    std::vector<float> detunes;
    std::vector<ALWaveTable*> waveList;
    std::vector<std::unique_ptr<ALWaveTable>> waves;
    std::vector<std::unique_ptr<ALADPCMloop>> adpcmLoops;
    std::vector<std::unique_ptr<ALRawLoop>> rawLoops;
    std::vector<std::unique_ptr<uint8_t[]>> adpcmBooks;
};

struct SeqPlayerState {
    std::unique_ptr<HostSongData> songData;
};

struct DecodedWave {
    std::vector<int16_t> pcm;
    std::vector<int16_t> loopPcm;
};

ALPlayer* s_player = nullptr;
std::vector<ALVoice*> s_voices;
std::unordered_map<const ALWaveTable*, DecodedWave> s_waveCache;
std::unordered_map<std::string, std::shared_ptr<std::vector<char>>> s_archiveBlobCache;
std::vector<uint8_t> s_audioHeapStorage;
SeqPlayerState s_seqPlayers[kSequencePlayerCount];
std::unique_ptr<HostPointerBankData> s_currentBank;
ALHeap s_audioHeap = {};
bool s_audioInitialized = false;
double s_outputSampleAccumulator = 0.0;
std::mutex s_audioMutex;

uint32_t ReadLittleU32(const std::vector<char>& buffer, size_t offset) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset])) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 1])) << 8) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 2])) << 16) |
           (static_cast<uint32_t>(static_cast<uint8_t>(buffer[offset + 3])) << 24);
}

uint16_t ReadBigU16(const uint8_t* data, size_t offset, size_t size) {
    if (offset + sizeof(uint16_t) > size) {
        return 0;
    }

    return static_cast<uint16_t>(static_cast<uint16_t>(data[offset]) << 8) |
           static_cast<uint16_t>(data[offset + 1]);
}

uint32_t ReadBigU32(const uint8_t* data, size_t offset, size_t size) {
    if (offset + sizeof(uint32_t) > size) {
        return 0;
    }

    return (static_cast<uint32_t>(data[offset]) << 24) | (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) | static_cast<uint32_t>(data[offset + 3]);
}

int8_t DecodeSignedU8(uint8_t value) {
    return (value & 0x80) ? static_cast<int8_t>(value - 0x100) : static_cast<int8_t>(value);
}

std::shared_ptr<std::vector<char>> LoadArchiveBlob(const char* path) {
    auto cached = s_archiveBlobCache.find(path);
    if (cached != s_archiveBlobCache.end()) {
        return cached->second;
    }

    auto context = Ship::Context::GetInstance();
    auto resourceManager = context ? context->GetResourceManager() : nullptr;
    if (resourceManager == nullptr) {
        return nullptr;
    }

    auto file = resourceManager->LoadFileProcess(path);
    if (file == nullptr || !file->IsLoaded || file->Buffer == nullptr) {
        return nullptr;
    }

    if (file->Buffer->size() >= (kOtrHeaderSize + sizeof(uint32_t))) {
        const uint32_t resourceType = ReadLittleU32(*file->Buffer, 4);
        if (resourceType == kBlobResourceType) {
            const uint32_t payloadSize = ReadLittleU32(*file->Buffer, kOtrHeaderSize);
            const size_t payloadOffset = kOtrHeaderSize + sizeof(uint32_t);
            if (payloadOffset <= file->Buffer->size() && payloadSize <= (file->Buffer->size() - payloadOffset)) {
                file->Buffer = std::make_shared<std::vector<char>>(file->Buffer->begin() + payloadOffset,
                                                                   file->Buffer->begin() + payloadOffset + payloadSize);
            } else {
                return nullptr;
            }
        }
    }

    s_archiveBlobCache.emplace(path, file->Buffer);
    return file->Buffer;
}

std::shared_ptr<std::vector<char>> LoadRuntimeRange(uintptr_t romAddr, size_t size, size_t* offsetOut) {
    for (const auto& entry : kMWRuntimeArchiveRomRanges) {
        if (romAddr < entry.Start || romAddr >= entry.End) {
            continue;
        }
        const size_t offset = romAddr - entry.Start;
        if (size > (entry.End - romAddr)) {
            return nullptr;
        }

        auto blob = LoadArchiveBlob(entry.Path);
        if (blob == nullptr || offset > blob->size() || size > (blob->size() - offset)) {
            return nullptr;
        }

        if (offsetOut != nullptr) {
            *offsetOut = offset;
        }
        return blob;
    }

    return nullptr;
}

bool CopyRomRange(uintptr_t romAddr, size_t size, std::vector<uint8_t>& out) {
    out.assign(size, 0);
    if (size == 0) {
        return true;
    }

    nuPiReadRom(romAddr, out.data(), static_cast<u32>(size));
    return true;
}

char* OffsetToRawPtr(std::vector<uint8_t>& raw, uint32_t offset) {
    if (offset == 0 || offset >= raw.size()) {
        return nullptr;
    }
    return reinterpret_cast<char*>(raw.data() + offset);
}

std::unique_ptr<HostSongData> BuildHostSongData(uintptr_t romAddr, size_t seqSize) {
    auto songData = std::make_unique<HostSongData>();
    if (!CopyRomRange(romAddr, seqSize, songData->raw) || songData->raw.size() < 0x18) {
        return nullptr;
    }

    const auto* raw = songData->raw.data();
    const size_t rawSize = songData->raw.size();
    const uint32_t channelCount = ReadBigU32(raw, 0x00, rawSize);
    const uint32_t trackTableOffset = ReadBigU32(raw, 0x04, rawSize);
    const uint32_t volumeTableOffset = ReadBigU32(raw, 0x08, rawSize);
    const uint32_t pitchTableOffset = ReadBigU32(raw, 0x0C, rawSize);
    const uint32_t drumTableOffset = ReadBigU32(raw, 0x10, rawSize);
    const uint32_t adsrOffset = ReadBigU32(raw, 0x14, rawSize);

    if (channelCount == 0 || channelCount > 64) {
        return nullptr;
    }

    songData->channelData.assign(channelCount, nullptr);
    songData->volumeData.assign(channelCount, nullptr);
    songData->pitchBendData.assign(channelCount, nullptr);
    songData->drumData.assign(256, 0);

    for (uint32_t i = 0; i < channelCount; i++) {
        songData->channelData[i] = OffsetToRawPtr(songData->raw, ReadBigU32(raw, trackTableOffset + (i * 4), rawSize));
        songData->volumeData[i] = OffsetToRawPtr(songData->raw, ReadBigU32(raw, volumeTableOffset + (i * 4), rawSize));
        songData->pitchBendData[i] =
            OffsetToRawPtr(songData->raw, ReadBigU32(raw, pitchTableOffset + (i * 4), rawSize));
    }

    if (drumTableOffset != 0 && drumTableOffset < adsrOffset && adsrOffset <= rawSize) {
        const size_t drumCount = (std::min<size_t>)(256, (adsrOffset - drumTableOffset) / sizeof(uint32_t));
        for (size_t i = 0; i < drumCount; i++) {
            songData->drumData[i] = ReadBigU32(raw, drumTableOffset + (i * 4), rawSize);
        }
    }

    songData->song.number_of_channels = channelCount;
    songData->song.ChannelData = songData->channelData.data();
    songData->song.VolumeData = songData->volumeData.data();
    songData->song.PitchBendData = songData->pitchBendData.data();
    songData->song.EnvelopeData = OffsetToRawPtr(songData->raw, adsrOffset);
    songData->song.DrumData = songData->drumData.data();
    return songData;
}

std::unique_ptr<HostPointerBankData> BuildHostPointerBank(uintptr_t pbkRomAddr, size_t pbkSize, uintptr_t wbkRomAddr) {
    auto bankData = std::make_unique<HostPointerBankData>();
    std::vector<uint8_t> raw;
    if (!CopyRomRange(pbkRomAddr, pbkSize, raw) || raw.size() < 0x30) {
        return nullptr;
    }

    const uint32_t count = ReadBigU32(raw.data(), 0x20, raw.size());
    const uint32_t baseNoteOffset = ReadBigU32(raw.data(), 0x24, raw.size());
    const uint32_t detuneOffset = ReadBigU32(raw.data(), 0x28, raw.size());
    const uint32_t waveListOffset = ReadBigU32(raw.data(), 0x2C, raw.size());
    if (count == 0 || count > 512) {
        return nullptr;
    }

    bankData->baseNotes.resize(count);
    bankData->detunes.resize(count);
    bankData->waveList.assign(count, nullptr);
    bankData->waves.reserve(count);
    bankData->adpcmLoops.reserve(count);
    bankData->rawLoops.reserve(count);
    bankData->adpcmBooks.reserve(count);

    for (uint32_t i = 0; i < count; i++) {
        const uint8_t baseNote = (baseNoteOffset + i < raw.size()) ? raw[baseNoteOffset + i] : 48;
        const uint8_t detuneByte = (detuneOffset + (i * 4) < raw.size()) ? raw[detuneOffset + (i * 4)] : 0;
        bankData->baseNotes[i] = baseNote;
        bankData->detunes[i] = static_cast<float>(DecodeSignedU8(detuneByte)) / 100.0f +
                               static_cast<float>(DecodeSignedU8(static_cast<uint8_t>(baseNote - 48)));

        const uint32_t waveOffset = ReadBigU32(raw.data(), waveListOffset + (i * 4), raw.size());
        if (waveOffset == 0 || waveOffset + 20 > raw.size()) {
            continue;
        }

        auto wave = std::make_unique<ALWaveTable>();
        wave->base = reinterpret_cast<u8*>(static_cast<uintptr_t>(wbkRomAddr + ReadBigU32(raw.data(), waveOffset, raw.size())));
        wave->len = static_cast<s32>(ReadBigU32(raw.data(), waveOffset + 4, raw.size()));
        wave->type = raw[waveOffset + 8];
        wave->flags = 1;

        if (wave->type == AL_ADPCM_WAVE) {
            const uint32_t loopOffset = ReadBigU32(raw.data(), waveOffset + 12, raw.size());
            const uint32_t bookOffset = ReadBigU32(raw.data(), waveOffset + 16, raw.size());

            if (loopOffset != 0 && loopOffset + 44 <= raw.size()) {
                auto loop = std::make_unique<ALADPCMloop>();
                loop->start = ReadBigU32(raw.data(), loopOffset + 0, raw.size());
                loop->end = ReadBigU32(raw.data(), loopOffset + 4, raw.size());
                loop->count = ReadBigU32(raw.data(), loopOffset + 8, raw.size());
                for (size_t stateIndex = 0; stateIndex < ADPCMFSIZE; stateIndex++) {
                    loop->state[stateIndex] =
                        static_cast<int16_t>(ReadBigU16(raw.data(), loopOffset + 12 + (stateIndex * 2), raw.size()));
                }
                wave->waveInfo.adpcmWave.loop = loop.get();
                bankData->adpcmLoops.push_back(std::move(loop));
            } else {
                wave->waveInfo.adpcmWave.loop = nullptr;
            }

            if (bookOffset != 0 && bookOffset + 8 <= raw.size()) {
                const int32_t order = static_cast<int32_t>(ReadBigU32(raw.data(), bookOffset + 0, raw.size()));
                const int32_t npredictors = static_cast<int32_t>(ReadBigU32(raw.data(), bookOffset + 4, raw.size()));
                const size_t coeffCount = static_cast<size_t>(8) * static_cast<size_t>(order) * static_cast<size_t>(npredictors);
                const size_t allocSize = sizeof(ALADPCMBook) + ((coeffCount > 0 ? coeffCount - 1 : 0) * sizeof(int16_t));
                auto bookBytes = std::make_unique<uint8_t[]>(allocSize);
                auto* book = reinterpret_cast<ALADPCMBook*>(bookBytes.get());
                book->order = order;
                book->npredictors = npredictors;
                for (size_t coeffIndex = 0; coeffIndex < coeffCount; coeffIndex++) {
                    book->book[coeffIndex] = static_cast<int16_t>(
                        ReadBigU16(raw.data(), bookOffset + 8 + (coeffIndex * 2), raw.size()));
                }
                wave->waveInfo.adpcmWave.book = book;
                bankData->adpcmBooks.push_back(std::move(bookBytes));
            } else {
                wave->waveInfo.adpcmWave.book = nullptr;
            }
        } else {
            const uint32_t loopOffset = ReadBigU32(raw.data(), waveOffset + 12, raw.size());
            if (loopOffset != 0 && loopOffset + 12 <= raw.size()) {
                auto loop = std::make_unique<ALRawLoop>();
                loop->start = ReadBigU32(raw.data(), loopOffset + 0, raw.size());
                loop->end = ReadBigU32(raw.data(), loopOffset + 4, raw.size());
                loop->count = ReadBigU32(raw.data(), loopOffset + 8, raw.size());
                wave->waveInfo.rawWave.loop = loop.get();
                bankData->rawLoops.push_back(std::move(loop));
            } else {
                wave->waveInfo.rawWave.loop = nullptr;
            }
        }

        bankData->waveList[i] = wave.get();
        bankData->waves.push_back(std::move(wave));
    }

    std::memcpy(bankData->bank.header_name, raw.data(), sizeof(bankData->bank.header_name));
    bankData->bank.flags = PTRFLAG_REMAPPED;
    for (size_t i = 0; i < 3; i++) {
        bankData->bank.wbk_name[i] = ReadBigU32(raw.data(), 20 + (i * 4), raw.size());
    }
    bankData->bank.count = static_cast<int>(count);
    bankData->bank.basenote = bankData->baseNotes.data();
    bankData->bank.detune = bankData->detunes.data();
    bankData->bank.wave_list = bankData->waveList.data();
    return bankData;
}

static inline int32_t InnerProduct(int32_t length, const int32_t* v1, const int32_t* v2) {
    int32_t out = 0;
    for (int32_t i = 0; i < length; i++) {
        out += v1[i] * v2[i];
    }
    int32_t dout = out / (1 << 11);
    int32_t fiout = dout * (1 << 11);
    return dout - (out - fiout < 0);
}

std::vector<std::vector<std::vector<int32_t>>> ExpandCodebook(const ALADPCMBook* book) {
    const int order = book->order;
    const int npredictors = book->npredictors;
    std::vector<std::vector<std::vector<int32_t>>> table(
        npredictors, std::vector<std::vector<int32_t>>(8, std::vector<int32_t>(order + 8, 0)));

    const int16_t* bookData = book->book;
    for (int i = 0; i < npredictors; i++) {
        auto& entry = table[i];
        for (int j = 0; j < order; j++) {
            for (int k = 0; k < 8; k++) {
                entry[k][j] = *(bookData++);
            }
        }
        for (int k = 1; k < 8; k++) {
            entry[k][order] = entry[k - 1][order - 1];
        }
        entry[0][order] = 1 << 11;
        for (int k = 1; k < 8; k++) {
            int j = 0;
            for (; j < k; j++) {
                entry[j][k + order] = 0;
            }
            for (; j < 8; j++) {
                entry[j][k + order] = entry[j - k][order];
            }
        }
    }
    return table;
}

void DecodeVAdpcmFrame(const uint8_t* frame, int32_t* state, int16_t* out, const ALADPCMBook* book) {
    const int order = book->order;
    const auto coefTable = ExpandCodebook(book);
    const uint8_t header = frame[0];
    const int32_t scale = 1 << ((header >> 4) & 0xF);
    const int32_t predictor = header & 0xF;

    int32_t ix[16];
    for (int i = 0; i < 16; i += 2) {
        const uint8_t c = frame[1 + i / 2];
        ix[i + 0] = (c >> 4) & 0xF;
        ix[i + 1] = c & 0xF;
    }

    for (int i = 0; i < 16; i++) {
        if (ix[i] >= 8) {
            ix[i] -= 16;
        }
        ix[i] *= scale;
    }

    const auto& coefPage = coefTable[predictor];
    for (int half = 0; half < 2; half++) {
        int32_t inVec[16] = {};
        for (int i = 0; i < order; i++) {
            inVec[i] = state[(2 - half) * 8 - order + i];
        }
        for (int i = 0; i < 8; i++) {
            const int ind = half * 8 + i;
            inVec[order + i] = ix[ind];
            state[ind] = InnerProduct(order + i, coefPage[i].data(), inVec) + ix[ind];
        }
    }

    for (int i = 0; i < 16; i++) {
        out[i] = static_cast<int16_t>(std::clamp(state[i], -32768, 32767));
    }
}

std::vector<int16_t> DecodeWaveSlice(const ALWaveTable* wave, uintptr_t baseAddr, size_t byteOffset, size_t byteLength,
                                     const int16_t* initialState, uint32_t sampleSkip, uint32_t sampleLimit) {
    size_t blobOffset = 0;
    auto blob = LoadRuntimeRange(baseAddr + byteOffset, byteLength, &blobOffset);
    if (blob == nullptr) {
        return {};
    }

    const uint8_t* data = reinterpret_cast<const uint8_t*>(blob->data() + blobOffset);
    const size_t frameCount = byteLength / 9;
    std::vector<int16_t> decoded;
    decoded.reserve(frameCount * 16);

    int32_t state[16] = {};
    if (initialState != nullptr) {
        for (int i = 0; i < 16; i++) {
            state[i] = initialState[i];
        }
    }

    for (size_t frame = 0; frame < frameCount; frame++) {
        int16_t out[16];
        DecodeVAdpcmFrame(data + (frame * 9), state, out, wave->waveInfo.adpcmWave.book);
        decoded.insert(decoded.end(), std::begin(out), std::end(out));
    }

    if (sampleSkip >= decoded.size()) {
        return {};
    }

    auto begin = decoded.begin() + sampleSkip;
    auto end = decoded.end();
    if (sampleLimit != 0 && sampleSkip + sampleLimit < decoded.size()) {
        end = begin + sampleLimit;
    }
    return std::vector<int16_t>(begin, end);
}

DecodedWave DecodeWave(ALWaveTable* wave) {
    DecodedWave result;
    const uintptr_t baseAddr = reinterpret_cast<uintptr_t>(wave->base);

    if (wave->type == AL_RAW16_WAVE) {
        size_t blobOffset = 0;
        auto blob = LoadRuntimeRange(baseAddr, wave->len, &blobOffset);
        if (blob == nullptr) {
            return result;
        }
        const uint8_t* src = reinterpret_cast<const uint8_t*>(blob->data() + blobOffset);
        result.pcm.resize(wave->len / 2);
        for (size_t i = 0; i < result.pcm.size(); i++) {
            result.pcm[i] = static_cast<int16_t>((src[i * 2] << 8) | src[i * 2 + 1]);
        }
        return result;
    }

    result.pcm = DecodeWaveSlice(wave, baseAddr, 0, static_cast<size_t>(wave->len), nullptr, 0, 0);

    auto* loop = wave->waveInfo.adpcmWave.loop;
    if (loop != nullptr && loop->end > loop->start) {
        const size_t loopStartFrame = loop->start / 16;
        const size_t loopStartSkip = loop->start % 16;
        const size_t loopFrameOffset = loopStartFrame * 9;
        const size_t loopByteLength = static_cast<size_t>(wave->len) > loopFrameOffset
                                          ? static_cast<size_t>(wave->len) - loopFrameOffset
                                          : 0;
        const uint32_t loopSampleLength = loop->end - loop->start;
        if (loopByteLength != 0) {
            result.loopPcm = DecodeWaveSlice(wave, baseAddr, loopFrameOffset, loopByteLength, loop->state, loopStartSkip,
                                             loopSampleLength);
        }
    }

    return result;
}

DecodedWave& GetDecodedWave(ALWaveTable* wave) {
    auto it = s_waveCache.find(wave);
    if (it == s_waveCache.end()) {
        it = s_waveCache.emplace(wave, DecodeWave(wave)).first;
    }
    return it->second;
}

int GetOutputSampleRate() {
    auto context = Ship::Context::GetInstance();
    auto audio = context ? context->GetAudio() : nullptr;
    auto player = audio ? audio->GetAudioPlayer() : nullptr;
    return player ? player->GetSampleRate() : 44100;
}

int GetOutputChannels() {
    auto context = Ship::Context::GetInstance();
    auto audio = context ? context->GetAudio() : nullptr;
    auto player = audio ? audio->GetAudioPlayer() : nullptr;
    return player ? player->GetNumOutputChannels() : 2;
}

void MixAudioTickLocked() {
    if (!s_audioInitialized || s_player == nullptr || s_player->handler == nullptr) {
        return;
    }

    s_player->handler(s_player->clientData);

    const int outputRate = GetOutputSampleRate();
    const int channels = (std::max)(2, GetOutputChannels());
    s_outputSampleAccumulator += static_cast<double>(outputRate) / 60.0;
    const int sampleCount = static_cast<int>(s_outputSampleAccumulator);
    s_outputSampleAccumulator -= sampleCount;

    if (sampleCount <= 0) {
        return;
    }

    std::vector<int32_t> mix(sampleCount * channels, 0);
    for (ALVoice* voice : s_voices) {
        if (voice == nullptr || !voice->active || voice->wave == nullptr) {
            continue;
        }

        auto& decoded = GetDecodedWave(voice->wave);
        if (decoded.pcm.empty()) {
            continue;
        }

        const double step = (std::max)(0.0, static_cast<double>(voice->pitch) * kNativeSampleRate / outputRate);
        if (step <= 0.0) {
            continue;
        }

        const double leftGain = (voice->volume / 32767.0) * ((127.0 - voice->pan) / 127.0);
        const double rightGain = (voice->volume / 32767.0) * (voice->pan / 127.0);

        for (int sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
            int16_t sampleValue = 0;
            const size_t pos = static_cast<size_t>(voice->cursor);
            if (pos < decoded.pcm.size()) {
                sampleValue = decoded.pcm[pos];
            } else if (!decoded.loopPcm.empty()) {
                const size_t loopPos = (pos - decoded.pcm.size()) % decoded.loopPcm.size();
                sampleValue = decoded.loopPcm[loopPos];
            } else {
                voice->active = 0;
                break;
            }

            mix[sampleIndex * channels + 0] += static_cast<int32_t>(sampleValue * leftGain);
            mix[sampleIndex * channels + 1] += static_cast<int32_t>(sampleValue * rightGain);
            for (int ch = 2; ch < channels; ch++) {
                mix[sampleIndex * channels + ch] += 0;
            }
            voice->cursor += step;
        }
    }

    std::vector<int16_t> pcm(sampleCount * channels);
    for (size_t i = 0; i < pcm.size(); i++) {
        pcm[i] = static_cast<int16_t>(std::clamp(mix[i], -32768, 32767));
    }
    AudioPlayerPlayFrame(reinterpret_cast<const uint8_t*>(pcm.data()), pcm.size() * sizeof(int16_t));
}

} // namespace

extern "C" {

ALGlobals auGlobal = {};
ALHeap nuAuHeap = {};

void alHeapInit(ALHeap* hp, u8* base, s32 len) {
    hp->base = base;
    hp->cur = base;
    hp->len = len;
    hp->count = 0;
}

void* alHeapDBAlloc(u8* file, s32 line, ALHeap* hp, s32 num, s32 size) {
    (void)file;
    (void)line;
    const size_t total = static_cast<size_t>(num) * static_cast<size_t>(size);
    const uintptr_t aligned = (reinterpret_cast<uintptr_t>(hp->cur) + 7u) & ~uintptr_t(7u);
    const uintptr_t end = aligned + total;
    const uintptr_t limit = reinterpret_cast<uintptr_t>(hp->base) + hp->len;
    if (end > limit) {
        return nullptr;
    }
    hp->cur = reinterpret_cast<u8*>(end);
    hp->count++;
    std::memset(reinterpret_cast<void*>(aligned), 0, total);
    return reinterpret_cast<void*>(aligned);
}

void alSynAddPlayer(ALSynth* drvr, ALPlayer* player) {
    (void)drvr;
    s_player = player;
}

void alSynRemovePlayer(ALSynth* drvr, ALPlayer* player) {
    (void)drvr;
    if (s_player == player) {
        s_player = nullptr;
    }
}

void alSynAllocVoice(ALSynth* drvr, ALVoice* voice, ALVoiceConfig* config) {
    (void)drvr;
    (void)config;
    if (voice == nullptr) {
        return;
    }
    std::memset(voice, 0, sizeof(*voice));
    voice->pitch = 1.0f;
    voice->volume = 0;
    voice->pan = 64;
    s_voices.push_back(voice);
}

void alSynStartVoice(ALSynth* drvr, ALVoice* voice, ALWaveTable* wave) {
    (void)drvr;
    if (voice == nullptr) {
        return;
    }
    voice->wave = wave;
    voice->cursor = 0.0;
    voice->active = (wave != nullptr);
}

void alSynStopVoice(ALSynth* drvr, ALVoice* voice) {
    (void)drvr;
    if (voice == nullptr) {
        return;
    }
    voice->active = 0;
    voice->cursor = 0.0;
}

void alSynSetVol(ALSynth* drvr, ALVoice* voice, u32 volume, ALMicroTime delta) {
    (void)drvr;
    (void)delta;
    if (voice != nullptr) {
        voice->volume = volume;
    }
}

void alSynSetPan(ALSynth* drvr, ALVoice* voice, ALPan pan) {
    (void)drvr;
    if (voice != nullptr) {
        voice->pan = pan;
    }
}

void alSynSetPitch(ALSynth* drvr, ALVoice* voice, float pitch) {
    (void)drvr;
    if (voice != nullptr) {
        voice->pitch = pitch;
    }
}

void alSynSetFXMix(ALSynth* drvr, ALVoice* voice, u8 fxmix) {
    (void)drvr;
    if (voice != nullptr) {
        voice->fxMix = fxmix;
    }
}

void nuAuStlInit(musConfig* config) {
    std::lock_guard<std::mutex> lock(s_audioMutex);

    s_audioHeapStorage.assign(NU_AU_HEAP_SIZE, 0);
    alHeapInit(&s_audioHeap, s_audioHeapStorage.data(), static_cast<s32>(s_audioHeapStorage.size()));
    nuAuHeap = s_audioHeap;
    s_currentBank.reset();
    s_waveCache.clear();

    config->channels = NU_AU_SYN_PVOICE_MAX;
    config->thread_priority = 12;
    MusInitialize(config);

    for (int i = 0; i < kSequencePlayerCount; i++) {
        s_seqPlayers[i].songData.reset();
    }

    s_audioInitialized = true;
}

void nuAuStlBankSet(u8* pbk_addr, u32 pbk_size, u8* wbk_addr) {
    std::lock_guard<std::mutex> lock(s_audioMutex);
    s_currentBank = BuildHostPointerBank(reinterpret_cast<uintptr_t>(pbk_addr), pbk_size, reinterpret_cast<uintptr_t>(wbk_addr));
    s_waveCache.clear();
}

void nuAuStlSeqPlayerDataSet(u8 player_no, u8* seq_addr, u32 seq_size) {
    std::lock_guard<std::mutex> lock(s_audioMutex);

    if (player_no >= kSequencePlayerCount) {
        return;
    }

    if (seq_size & 1) {
        seq_size++;
    }
    s_seqPlayers[player_no].songData = BuildHostSongData(reinterpret_cast<uintptr_t>(seq_addr), seq_size);
}

musHandle nuAuStlSeqPlayerPlay2(u8 player_no) {
    std::lock_guard<std::mutex> lock(s_audioMutex);
    if (player_no >= kSequencePlayerCount || s_seqPlayers[player_no].songData == nullptr) {
        return 0;
    }
    if (s_currentBank != nullptr) {
        return MusBankStartSong(&s_currentBank->bank, &s_seqPlayers[player_no].songData->song);
    }
    return MusStartSong(&s_seqPlayers[player_no].songData->song);
}

u32 nuAuStlSndPlayerPlay(u32 sndNo) {
    std::lock_guard<std::mutex> lock(s_audioMutex);
    if (s_currentBank != nullptr) {
        return MusBankStartEffect(&s_currentBank->bank, sndNo);
    }
    return MusStartEffect(sndNo);
}

u32 nuAuStlSndPlayerPlay2(u32 sndNo, s32 volume, s32 pan, s32 restartflag, s32 priority) {
    std::lock_guard<std::mutex> lock(s_audioMutex);
    if (s_currentBank != nullptr) {
        return MusBankStartEffect2(&s_currentBank->bank, sndNo, volume, pan, restartflag, priority);
    }
    return MusStartEffect2(sndNo, volume, pan, restartflag, priority);
}

void nuAuStlTick(void) {
    std::lock_guard<std::mutex> lock(s_audioMutex);
    MixAudioTickLocked();
}

} // extern "C"
