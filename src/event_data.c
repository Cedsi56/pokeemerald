#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "constants/items.h"

#define SPECIAL_FLAGS_SIZE  (NUM_SPECIAL_FLAGS / 8)  // 8 flags per byte
#define TEMP_FLAGS_SIZE     (NUM_TEMP_FLAGS / 8)
#define DAILY_FLAGS_SIZE    (NUM_DAILY_FLAGS / 8)
#define TEMP_VARS_SIZE      (NUM_TEMP_VARS * 2)      // 1/2 var per byte

EWRAM_DATA u16 gSpecialVar_0x8000 = 0;
EWRAM_DATA u16 gSpecialVar_0x8001 = 0;
EWRAM_DATA u16 gSpecialVar_0x8002 = 0;
EWRAM_DATA u16 gSpecialVar_0x8003 = 0;
EWRAM_DATA u16 gSpecialVar_0x8004 = 0;
EWRAM_DATA u16 gSpecialVar_0x8005 = 0;
EWRAM_DATA u16 gSpecialVar_0x8006 = 0;
EWRAM_DATA u16 gSpecialVar_0x8007 = 0;
EWRAM_DATA u16 gSpecialVar_0x8008 = 0;
EWRAM_DATA u16 gSpecialVar_0x8009 = 0;
EWRAM_DATA u16 gSpecialVar_0x800A = 0;
EWRAM_DATA u16 gSpecialVar_0x800B = 0;
EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;
EWRAM_DATA u16 gSpecialVar_Unused_0x8014 = 0;
EWRAM_DATA static u8 sSpecialFlags[SPECIAL_FLAGS_SIZE] = {0};

extern u16 *const gSpecialVars[];

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, sizeof(gSaveBlock1Ptr->flags));
    memset(gSaveBlock1Ptr->vars, 0, sizeof(gSaveBlock1Ptr->vars));
    memset(sSpecialFlags, 0, sizeof(sSpecialFlags));
}

void ClearTempFieldEventData(void)
{
    memset(&gSaveBlock1Ptr->flags[TEMP_FLAGS_START / 8], 0, TEMP_FLAGS_SIZE);
    memset(&gSaveBlock1Ptr->vars[TEMP_VARS_START - VARS_START], 0, TEMP_VARS_SIZE);
    FlagClear(FLAG_SYS_ENC_UP_ITEM);
    FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_CTRL_OBJ_DELETE);
    FlagClear(FLAG_NURSE_UNION_ROOM_REMINDER);
}

void ClearDailyFlags(void)
{
    memset(&gSaveBlock1Ptr->flags[DAILY_FLAGS_START / 8], 0, DAILY_FLAGS_SIZE);
}

void DisableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0;
    *nationalDexVar = 0;
    FlagClear(FLAG_SYS_NATIONAL_DEX);
}

void EnableNationalPokedex(void)
{
    u16 *nationalDexVar = GetVarPointer(VAR_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0xDA;
    *nationalDexVar = 0x302;
    FlagSet(FLAG_SYS_NATIONAL_DEX);
    gSaveBlock2Ptr->pokedex.mode = DEX_MODE_NATIONAL;
    gSaveBlock2Ptr->pokedex.order = 0;
    ResetPokedexScrollPositions();
}

bool32 IsNationalPokedexEnabled(void)
{
    if (gSaveBlock2Ptr->pokedex.nationalMagic == 0xDA && VarGet(VAR_NATIONAL_DEX) == 0x302 && FlagGet(FLAG_SYS_NATIONAL_DEX))
        return TRUE;
    else
        return FALSE;
}

void DisableMysteryEvent(void)
{
    FlagClear(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void EnableMysteryEvent(void)
{
    FlagSet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

bool32 IsMysteryEventEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_EVENT_ENABLE);
}

void DisableMysteryGift(void)
{
    FlagClear(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void EnableMysteryGift(void)
{
    FlagSet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

bool32 IsMysteryGiftEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_GIFT_ENABLE);
}

void ClearMysteryGiftFlags(void)
{
    FlagClear(FLAG_MYSTERY_GIFT_DONE);
    FlagClear(FLAG_MYSTERY_GIFT_1);
    FlagClear(FLAG_MYSTERY_GIFT_2);
    FlagClear(FLAG_MYSTERY_GIFT_3);
    FlagClear(FLAG_MYSTERY_GIFT_4);
    FlagClear(FLAG_MYSTERY_GIFT_5);
    FlagClear(FLAG_MYSTERY_GIFT_6);
    FlagClear(FLAG_MYSTERY_GIFT_7);
    FlagClear(FLAG_MYSTERY_GIFT_8);
    FlagClear(FLAG_MYSTERY_GIFT_9);
    FlagClear(FLAG_MYSTERY_GIFT_10);
    FlagClear(FLAG_MYSTERY_GIFT_11);
    FlagClear(FLAG_MYSTERY_GIFT_12);
    FlagClear(FLAG_MYSTERY_GIFT_13);
    FlagClear(FLAG_MYSTERY_GIFT_14);
    FlagClear(FLAG_MYSTERY_GIFT_15);
}

void ClearMysteryGiftVars(void)
{
    VarSet(VAR_GIFT_PICHU_SLOT, 0);
    VarSet(VAR_GIFT_UNUSED_1, 0);
    VarSet(VAR_GIFT_UNUSED_2, 0);
    VarSet(VAR_GIFT_UNUSED_3, 0);
    VarSet(VAR_GIFT_UNUSED_4, 0);
    VarSet(VAR_GIFT_UNUSED_5, 0);
    VarSet(VAR_GIFT_UNUSED_6, 0);
    VarSet(VAR_GIFT_UNUSED_7, 0);
}

void DisableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0);
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);
}

void EnableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0x920);
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);
}

bool32 CanResetRTC(void)
{
    if (FlagGet(FLAG_SYS_RESET_RTC_ENABLE) && VarGet(VAR_RESET_RTC_ENABLE) == 0x920)
        return TRUE;
    else
        return FALSE;
}

u16 *GetVarPointer(u16 id)
{
    if (id < VARS_START)
        return NULL;
    else if (id < SPECIAL_VARS_START)
        return &gSaveBlock1Ptr->vars[id - VARS_START];
    else
        return gSpecialVars[id - SPECIAL_VARS_START];
}

u16 VarGet(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return id;
    return *ptr;
}

bool8 VarSet(u16 id, u16 value)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return FALSE;
    *ptr = value;
    return TRUE;
}

u8 VarGetObjectEventGraphicsId(u8 id)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + id);
}

u8 *GetFlagPointer(u16 id)
{
    if (id == 0)
        return NULL;
    else if (id < SPECIAL_FLAGS_START)
        return &gSaveBlock1Ptr->flags[id / 8];
    else
        return &sSpecialFlags[(id - SPECIAL_FLAGS_START) / 8];
}

u8 FlagSet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 FlagClear(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 FlagGet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}

int GetNbBadges(void){
    return FlagGet(FLAG_BADGE01_GET) + 
                FlagGet(FLAG_BADGE02_GET) +
                FlagGet(FLAG_BADGE03_GET) +
                FlagGet(FLAG_BADGE04_GET) +
                FlagGet(FLAG_BADGE05_GET) +
                FlagGet(FLAG_BADGE06_GET) +
                FlagGet(FLAG_BADGE07_GET) +
                FlagGet(FLAG_BADGE08_GET);
}

u8 GetLevelToUse(u16 heldItem){
    u8 ret;
    u8 levelPlusFlat = 0;
    u8 levelMinusFlat = 0;
    u8 baseLevel;
    int nbBadges;



    nbBadges = GetNbBadges();

    switch (heldItem)
    {
        case ITEM_POKE_BALL:
            levelMinusFlat = 2;
            break;
        case ITEM_GREAT_BALL:
            levelMinusFlat = 1;
            break;
        case ITEM_ULTRA_BALL:
            levelPlusFlat = 1;
            break;
        case ITEM_MASTER_BALL:
            levelPlusFlat = 2;
            break;
        case ITEM_SAFARI_BALL:
            if (nbBadges == 0){
                levelPlusFlat = 6;
            } else {
                levelPlusFlat = 5 + nbBadges;
            }
            break;
        case ITEM_NET_BALL:
            if (nbBadges == 0){
                levelPlusFlat = 5;
            } else {
                levelPlusFlat = 4 + nbBadges;
            }
            break;
        case ITEM_NEST_BALL:
            if (nbBadges == 0){
                levelPlusFlat = 4;
            } else {
                levelPlusFlat = 3 + nbBadges;
            }
            break;
        case ITEM_REPEAT_BALL:
            if (nbBadges == 0){
                levelPlusFlat = 3;
            } else {
                levelPlusFlat = 2 + nbBadges;
            }
            break;
        case ITEM_TIMER_BALL:
            if (nbBadges == 0){
                levelPlusFlat = 2;
            } else {
                levelPlusFlat = 1 + nbBadges;
            }
            break;
        case ITEM_ORAN_BERRY:
            if (nbBadges == 0){
                levelPlusFlat = 4;
            } else {
                levelPlusFlat = 3 + nbBadges;
            }
            break;
        case ITEM_PECHA_BERRY:
            if (nbBadges == 0){
                levelPlusFlat = 5;
            } else {
                levelPlusFlat = 4 + nbBadges;
            }
            break;
        case ITEM_CHERI_BERRY:
            if (nbBadges == 0){
                levelPlusFlat = 6;
            } else {
                levelPlusFlat = 5 + nbBadges;
            }
            break;
        case ITEM_SHELL_BELL:
            if (nbBadges == 0){
                levelPlusFlat = 7;
            } else {
                levelPlusFlat = 6 + nbBadges;
            }
            break;
        case ITEM_SITRUS_BERRY:
            if (nbBadges == 0){
                levelPlusFlat = 8;
            } else {
                levelPlusFlat = 7 + nbBadges;
            }
            break;
        case ITEM_LEFTOVERS:
            if (nbBadges == 0){
                levelPlusFlat = 8;
            } else {
                levelPlusFlat = 7 + nbBadges;
            }
            break;
    }

    if (nbBadges == 0){
        baseLevel = 5;
    } else {
        baseLevel = 6 + 6 * nbBadges;
    }


    ret = baseLevel + levelPlusFlat - levelMinusFlat;

    return ret;
}
