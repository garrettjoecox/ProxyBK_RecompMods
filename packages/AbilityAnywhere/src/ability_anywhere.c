#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

static int pressedAFrames = 0;

RECOMP_HOOK("func_80295C14")
void pre_func_80295C14(void) {
    if (
        D_8037D160 == BS_1_IDLE ||
        D_8037D160 == BS_2_WALK_SLOW ||
        D_8037D160 == BS_WALK ||
        D_8037D160 == BS_4_WALK_FAST ||
        D_8037D160 == BS_WALK_CREEP
    ) {
        if (bakey_held(BUTTON_L) && bakey_pressed(BUTTON_A)) {
            pressedAFrames++;
        }
    }

    if (pressedAFrames > 0) {
        if (bakey_held(BUTTON_A)) {
            pressedAFrames++;
            if (pressedAFrames == 6) {
                if (ability_isUnlocked(ABILITY_D_SHOCK_JUMP) || !recomp_get_config_u32("require_unlock")) {
                    bs_setState(BS_BSHOCK_CHARGE);
                }
                pressedAFrames = 0;
            }
        } else if (bakey_newlyReleased(BUTTON_A)) {
            if (pressedAFrames < 6 && (ability_isUnlocked(ABILITY_9_FLIGHT) || !recomp_get_config_u32("require_unlock"))) {
                bs_setState(BS_23_FLY_ENTER);
            }
            pressedAFrames = 0;
        }
    }
}
