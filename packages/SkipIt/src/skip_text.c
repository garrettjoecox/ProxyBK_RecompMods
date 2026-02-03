#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

// Simulate holding A for speeding up text
bool simulateAPress = FALSE;
RECOMP_HOOK("gczoombox_update")
void pre_gczoombox_update(GcZoombox *this) {
    if (!this) return;

    if (recomp_get_config_u32("skip_text") == 1) {
        if (this->state == 2 && this->unk1A4_12) {
            this->unk190 = 1.0f / 30.0f;
            simulateAPress = TRUE;
        }
    } else {
        // Restore default speed
        this->unk190 = 1.0f / 15.0f;
    }
}

RECOMP_HOOK("controller_copyFaceButtons")
void pre_controller_copyFaceButtons(s32 controller_index, s32 dst[6]) {
    if (simulateAPress) {
        D_80281138[controller_index].face_button[FACE_BUTTON(BUTTON_A)] = 1;
        simulateAPress = FALSE;
    }
}

// L + R + B to skip dialog
RECOMP_PATCH s32 func_8024E5E8(s32 arg0, s32 arg1){
    int textId = gcdialog_getCurrentTextId();
    if (
        recomp_get_config_u32("skip_text") == 2 && arg1 == 3 &&
        textId != 0xC0A &&  // PRESS A TO RACE OR B TO BACK OUT.
        textId != 0xC6C &&  // WANT TO TRY AGAIN GREENY? PRESS A TO PLAY OR B TO RUN.
        textId != 0xC8D &&  // PRESS A TO ACCEPT OR B TO SLIDE OFF LIKE A SLUG!
        textId != 0xC09 &&  // PRESS A TO ACCEPT OR B TO CHICKEN OUT!
        textId != 0xC63 &&  // PRESS A TO ACCEPT OR B TO CHICKEN OUT!
        textId != 0xC90 &&  // HURR...GREENY GOT MORE TASTY LIVES FOR MR. VILE? PRESS A TO TRY AGAIN OR B TO HOP AWAY LIKE FROG!
        textId != 0xC91 &&  // GREENY FANCY CHANCES AGAIN, HUH? SAME DEAL, WIN 3 GAMES TO WIN 3 EXTRA LIVES! PRESS A TO ACCEPT OR B TO SLITHER OFF LIKE SNAKE!
        textId != 0xE38 &&  // BANJO! IF YOU USE A THIRD CHEAT CODE YOUR GAME PAK WILL BE ERASED! ARE YOU SURE YOU WANT TO DO THIS? PRESS A FOR YES OR B FOR NO...
        textId != 0x102C && // PRESS A TO TRY IT IF YOU DARE!
        textId != 0x1035    // PLEASE PRESS A TO TRY AGAIN!
    ) {
        return 1;
    }

    return D_802810E0[arg0][arg1];
}
