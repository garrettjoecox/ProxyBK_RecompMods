#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("func_80295C14")
void post_infinite_func_80295C14(void) {
    if (recomp_get_config_u32("infinite_health")) {
        s32 max_health = item_getCount(ITEM_15_HEALTH_TOTAL);
        if (item_getCount(ITEM_14_HEALTH) < max_health) item_set(ITEM_14_HEALTH, max_health);
        if (!volatileFlag_get(VOLATILE_FLAG_77_SANDCASTLE_SET_HEALTH_TO_MAX)) {
            volatileFlag_set(VOLATILE_FLAG_77_SANDCASTLE_SET_HEALTH_TO_MAX, 1);
        }
    }

    if (recomp_get_config_u32("infinite_life")) {
        if (item_getCount(ITEM_16_LIFE) < 3) item_set(ITEM_16_LIFE, 3);
        if (!volatileFlag_get(VOLATILE_FLAG_73_SANDCASTLE_INFINITE_LIVES)) {
            volatileFlag_set(VOLATILE_FLAG_73_SANDCASTLE_INFINITE_LIVES, 1);
        }
    }

    if (recomp_get_config_u32("infinite_ammo")) {
        if (item_getCount(ITEM_D_EGGS) < 100) item_setMaxCount(ITEM_D_EGGS);
        if (!volatileFlag_get(VOLATILE_FLAG_74_SANDCASTLE_INFINITE_EGGS)) {
            volatileFlag_set(VOLATILE_FLAG_74_SANDCASTLE_INFINITE_EGGS, 1);
        }

        if (item_getCount(ITEM_F_RED_FEATHER) < 50) item_setMaxCount(ITEM_F_RED_FEATHER);
        if (!volatileFlag_get(VOLATILE_FLAG_75_SANDCASTLE_INFINITE_RED_FEATHERS)) {
            volatileFlag_set(VOLATILE_FLAG_75_SANDCASTLE_INFINITE_RED_FEATHERS, 1);
        }

        if (item_getCount(ITEM_10_GOLD_FEATHER) < 10) item_setMaxCount(ITEM_10_GOLD_FEATHER);
        if (!volatileFlag_get(VOLATILE_FLAG_76_SANDCASTLE_INFINITE_GOLD_FEATHERS)) {
            volatileFlag_set(VOLATILE_FLAG_76_SANDCASTLE_INFINITE_GOLD_FEATHERS, 1);
        }
    }

    if (recomp_get_config_u32("infinite_air")) {
        if (item_getCount(ITEM_17_AIR) < 3600) item_set(ITEM_17_AIR, 3600);
        if (!volatileFlag_get(VOLATILE_FLAG_96_SANDCASTLE_INFINITE_AIR)) {
            volatileFlag_set(VOLATILE_FLAG_96_SANDCASTLE_INFINITE_AIR, 1);
        }
    }
}
