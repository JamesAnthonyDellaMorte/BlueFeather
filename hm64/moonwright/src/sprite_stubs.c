#include "common.h"

// Stubs for sprite/bitmap functions that need PC implementations

void* advanceBitmapMetadataPtr(void* ptr, s32 offset) {
    return (void*)((u8*)ptr + offset);
}

void calculateSceneNodePosition(void) {
    // TODO: Implement scene graph node position calculation
}

void* getAnimationFrameMetadataPtrFromFrame(void* sprite, s32 frame) {
    // TODO: Implement frame metadata lookup
    return NULL;
}

void setAnimationFrameMetadata(void* dst, void* src, s32 count) {
    // TODO: Implement frame metadata copy
}

void setBitmapBlendModeDisplayList(void* bitmap, u8 blendMode) {
    // TODO: Implement blend mode setting
}

void setBitmapMetadata(void* dst, void* src) {
    // TODO: Implement bitmap metadata copy
}

// Cutscene stub
u16 cutsceneUpdateValue(u16 current, u16 target, u16 step) {
    // Simple linear interpolation towards target
    if (current < target) {
        u16 newVal = current + step;
        return (newVal > target) ? target : newVal;
    } else if (current > target) {
        u16 newVal = current - step;
        return (newVal < target) ? target : newVal;
    }
    return current;
}
