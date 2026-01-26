#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

enum volatile_flags_e flags[] = {
    VOLATILE_FLAG_97_SANDCASTLE_BOTTLES_BONUS_1,
    VOLATILE_FLAG_98_SANDCASTLE_BOTTLES_BONUS_2,
    VOLATILE_FLAG_99_SANDCASTLE_BOTTLES_BONUS_3,
    VOLATILE_FLAG_9A_SANDCASTLE_BOTTLES_BONUS_4,
    VOLATILE_FLAG_9B_SANDCASTLE_BOTTLES_BONUS_5,
    VOLATILE_FLAG_9C_SANDCASTLE_BOTTLES_BONUS_6,
    VOLATILE_FLAG_9D_SANDCASTLE_WISHY_WASHY,
};

RECOMP_HOOK("func_80295C14")
void post_silly_func_80295C14(void) {
    if (recomp_get_config_u32("silly_effect")) {
        for (int i = 0; i < 7; i++) {
            volatileFlag_set(flags[i], 0);
        }

        volatileFlag_set(VOLATILE_FLAG_78_SANDCASTLE_NO_BONUS, 1);
        volatileFlag_set(flags[recomp_get_config_u32("silly_effect") - 1], 1);
    } else {
        volatileFlag_set(VOLATILE_FLAG_78_SANDCASTLE_NO_BONUS, 0);
    }
}
