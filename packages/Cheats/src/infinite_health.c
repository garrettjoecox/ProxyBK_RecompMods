#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("func_80295C14")
void post_health_func_80295C14(void) {
    if (recomp_get_config_u32("infinite_health")) {
        s32 max_health = item_getCount(ITEM_15_HEALTH_TOTAL);
        if (item_getCount(ITEM_14_HEALTH) < max_health) item_set(ITEM_14_HEALTH, max_health);
    }
}
