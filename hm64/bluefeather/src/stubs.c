#include "common.h"
#include "game/gameFile.h"
#include "game/level.h"
#include "game/namingScreen.h"
#include "game/overlayScreens.h"
#include "game/shop.h"
#include "game/tv.h"

/*
 * Thin compatibility/data layer.
 *
 * Golden-image rule:
 * real HM64 gameplay/runtime logic belongs in hm64/src,
 * not in this file.
 */

u8 wateringCanUses = 0;
u8 chickenFeedQuantity = 0;
u8 flowerShopPoints = 0;

void cowInfoScreenCallback(void) {}
void chickenInfoScreenCallback(void) {}
void albumScreenEndCallback(void) {}
void recordingMenuScreenCallback(void) {}
void itemCheckScreenCallback(void) {}
void farmNameScreenCallback(void) {}
void birthdayScreenCallback(void) {}
void dateScreenCallback(void) {}
void animalNameScreenCallback(void) {}
void fileSelectScreenCallback(void) {}

TVContext tvContext = { 0 };
u8 gCurrentGameIndex = 0;
LoadGameScreenContext loadGameScreenContext = { 0 };
OverlayScreenTable overlayScreenTable = { 0 };
NamingScreenContext namingScreenContext = { 0 };
ShopContext shopContext = { 0 };

void initializeLoadGameScreen(bool controllerPakEnabled) {
    (void)controllerPakEnabled;
}

bool saveGameToSram(u8 gameSlot) {
    (void)gameSlot;
    return FALSE;
}

void initializeNamingScreen(u8* name, u8 type) {
    (void)name;
    (void)type;
}

u8 D_801890E8[31] = { 0 };
u8 D_80189108[5][7] = { { 0 } };
u8 D_80237420[31] = { 0 };
u32 D_80205204 = 0;

u32 albumBits = 0;
u32 blueMistFlowerPlot = 0;
u8 blueMistSeedsQuantity = 0;
u8 cabbageSeedsQuantity = 0;
u8 cornSeedsQuantity = 0;
u8 eggplantSeedsQuantity = 0;
u8 grassSeedsQuantity = 0;
u8 greenPepperSeedsQuantity = 0;
u8 moondropFlowerSeedsQuantity = 0;
u8 peanutSeedsQuantity = 0;
u8 pinkCatMintFlowerSeedsQuantity = 0;
u8 potatoSeedsQuantity = 0;
u8 pumpkinSeedsQuantity = 0;
u8 strawberrySeedsQuantity = 0;
u8 tomatoSeedsQuantity = 0;
u8 turnipSeedsQuantity = 0;
u32 totalCabbageShipped = 0;
u32 totalCornShipped = 0;
u32 totalEggplantsShipped = 0;
u32 totalGreenPeppersShipped = 0;
u32 totalMoondropFlowersShipped = 0;
u32 totalPeanutsShipped = 0;
u32 totalPinkCatmintShipped = 0;
u32 totalPotatoesShipped = 0;
u32 totalPumpkinsShipped = 0;
u32 totalStrawberriesShipped = 0;
u32 totalTomatoesShipped = 0;
u32 totalTurnipsShipped = 0;
u32 totalBlueMistFlowersShipped = 0;

u8 toolUse = 0;

u8 D_801594E0 = 0;
u8 D_801594E6 = 0;
u8 D_8016F6E0 = 0;
u8 D_8016FB00 = 0;
u8 D_80170268 = 0;
u8 D_8017044B = 0;
void* D_801806C8 = NULL;

void* gameStatus = NULL;
u8 farmName[6] = { 0 };
void* sprPlayer = NULL;

u8 D_80114E50[4] = { 0 };
u8 D_80115030[4] = { 0 };
u8 D_80115210[4] = { 0 };
u8 D_801153F0[4] = { 0 };
u8 D_801155D0[4] = { 0 };
u8 D_801157B0[4] = { 0 };
u8 D_80115990[4] = { 0 };
u8 D_80115B70[4] = { 0 };
u8 D_80115D50[4] = { 0 };
u8 D_80115F30[4] = { 0 };
u8 D_80116110[4] = { 0 };

u32 acquiredPowerNutBits = 0;
u8 anniversaryDate = 0;
u8 anniversarySeason = 0;
u8 babyBirthdayDate = 0;
u8 babyBirthdaySeason = 0;
u8 bakeryCardPoints = 0;
u32 dailyShippingBinValue = 0;
u8 deadAnimalCount = 0;
void* dogInfo = NULL;
void* farmFieldTiles = NULL;
u8 gBabyAge = 0;
s16 gCowFestivalEnteredCowIndex = -1;
u8 gDayOfMonth = 1;
u8 gDayOfWeek = 0;
void* gFarmAnimals = NULL;
u8 gFlowerFestivalGoddess = 0;
u8 gForecast = 0;
s16 gHappiness = 0;
u8 gHarvestCoinFinder = 0;
u8 gHarvestKing = 0;
u8 gHour = 6;
u8 gHouseExtensionSelection = 0;
u8 gItemBeingHeld = 0;
u8 gNamingScreenIndex = 0;
u8 gSeason = 0;
s16 gSelectedAnimalIndex = 0;
u8 gSickDays = 0;
u16 gTotalCropsShipped = 0;
u16 gTotalEggsShipped = 0;
u16 gTotalMilkShipped = 0;
u8 gWeather = 0;
u8 gWife = 0;
u8 gWifePregnancyCounter = 0;
u16 gYear = 1;
void* horseInfo = NULL;
void* mineFieldTiles = NULL;
void* npcAffection = NULL;
void* pondFieldTiles = NULL;
u8 previousLightingRGBA[4] = { 255, 255, 255, 255 };
u8 selectedAnimalType = 0;
u16 totalFishCaught = 0;

void setForecast(void) {}

Vec4f setWeatherLighting(u8 weather) {
    (void)weather;
    return (Vec4f){ 255.0f, 255.0f, 255.0f, 255.0f };
}

void addRecipe(u16 bitIndex) {
    (void)bitIndex;
}

u32 checkRecipe(u16 bitIndex) {
    (void)bitIndex;
    return FALSE;
}

u8 checkCanPickUpShopItem(u8 index) {
    (void)index;
    return FALSE;
}

bool checkShopItemShouldBeDisplayed(u16 itemIndex) {
    (void)itemIndex;
    return FALSE;
}

void deactivateShopItemMapObject(u8 index) {
    (void)index;
}

void handlePickUpShopItem(u8 index) {
    (void)index;
}

bool func_800CE714(u8 arg0) {
    (void)arg0;
    return FALSE;
}

bool func_800CE828(u8 arg0) {
    (void)arg0;
    return FALSE;
}

void incrementVarietyShowCounter(void) {}

void initializeMapAdditionsForLevel(u16 levelIndex) {
    (void)levelIndex;
}

void setAdditionalMapAdditionsForLevel(u16 mapIndex) {
    (void)mapIndex;
}

void initializeRaceContext(void) {}

void initializeTVAssets(void) {}

void intializeShopDialogue(u8 storeItemIndex) {
    (void)storeItemIndex;
}

void loadShopItemSprite(u8 index) {
    (void)index;
}

void loadTVCButtonIcons(void) {}

void setBarnFodderSprite(u8 itemIndex) {
    (void)itemIndex;
}

void setChickenFeedSprite(u8 itemIndex) {
    (void)itemIndex;
}

void updateDogRaceContext(void) {}

void updateHorseRaceContext(void) {}
