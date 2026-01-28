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
        textId != 3081 && // Boggy Second Race 
        textId != 3171 // Vile Challenge 
    ) {
        return 1;
    }

    return D_802810E0[arg0][arg1];
}
