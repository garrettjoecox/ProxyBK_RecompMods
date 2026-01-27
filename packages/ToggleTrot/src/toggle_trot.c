#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "core2/statetimer.h"
#include "bkextern.h"

int framesSinceTrotStarted = 0;
bool holdingZ = FALSE;

RECOMP_HOOK("bs_setState")
void bs_setState(s32 state_id) {
    if (state_id == 20) { // trot enter
        framesSinceTrotStarted = 0;
        holdingZ = FALSE;
    }
}

RECOMP_PATCH int func_802A8C60(void) {
    framesSinceTrotStarted++;

    if (stateTimer_isActive(STATE_TIMER_3_TURBO_TALON)) {
        return 0;
    }

    if (framesSinceTrotStarted < 10) {
        return 0;
    }

    if (!holdingZ && bakey_held(BUTTON_Z)) {
        holdingZ = TRUE;
    }

    if (holdingZ && !bakey_held(BUTTON_Z)) {
        return 1;
    }

    return 0;
}
