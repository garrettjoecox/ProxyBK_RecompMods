#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("func_80295C14")
void post_cheats_func_80295C14(void) {
    if (recomp_get_config_u32("infinite_ammo")) {
        if (item_getCount(ITEM_D_EGGS) < 100) item_setMaxCount(ITEM_D_EGGS);
        if (item_getCount(ITEM_F_RED_FEATHER) < 50) item_setMaxCount(ITEM_F_RED_FEATHER);
        if (item_getCount(ITEM_10_GOLD_FEATHER) < 10) item_setMaxCount(ITEM_10_GOLD_FEATHER);
    }
}
