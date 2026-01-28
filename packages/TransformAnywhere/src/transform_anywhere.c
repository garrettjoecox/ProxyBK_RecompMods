#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("func_80295C14")
void pre_func_80295C14(void) {
    // Prevent transforming while entering/exiting drone state
    if ((bsDroneEnterSubstate != 0 && bsDroneEnterSubstate != 3) || (D_8037D468 != 0 && D_8037D468 != 3)) {
        return;
    }

    bool requiresL = recomp_get_config_u32("require_l_to_transform");

    bool anyDpadHeld = 
        bakey_held(BUTTON_D_UP) || 
        bakey_held(BUTTON_D_DOWN) || 
        bakey_held(BUTTON_D_LEFT) || 
        bakey_held(BUTTON_D_RIGHT);
    bool anyDpadPressed = 
        bakey_pressed(BUTTON_D_UP) || 
        bakey_pressed(BUTTON_D_DOWN) || 
        bakey_pressed(BUTTON_D_LEFT) || 
        bakey_pressed(BUTTON_D_RIGHT);

    if ((bakey_held(BUTTON_L) || !requiresL) && anyDpadHeld && ((!requiresL && bakey_pressed(BUTTON_L)) || anyDpadPressed)) {
        u32 currentForm = player_getTransformation();
        u32 targetForm = currentForm;

        if (bakey_pressed(BUTTON_D_UP)) {
            targetForm = currentForm == TRANSFORM_1_BANJO ? TRANSFORM_7_WISHWASHY : TRANSFORM_1_BANJO;
        } else if (bakey_pressed(BUTTON_D_DOWN)) {
            targetForm = currentForm == TRANSFORM_5_CROC ? TRANSFORM_4_WALRUS : TRANSFORM_5_CROC;
        } else if (bakey_pressed(BUTTON_D_LEFT)) {
            targetForm = currentForm == TRANSFORM_6_BEE ? TRANSFORM_1_BANJO : TRANSFORM_6_BEE;
        } else if (bakey_pressed(BUTTON_D_RIGHT)) {
            targetForm = currentForm == TRANSFORM_2_TERMITE ? TRANSFORM_3_PUMPKIN : TRANSFORM_2_TERMITE;
        }

        if (targetForm != currentForm) {
            enum asset_e sp34;
            f32 sp30;

            func_802BB3DC(2, 80.0f, 0.85f);
            func_8030E6D4(SFX_147_GRUNTY_SPELL_ATTACK_2);
            if(targetForm == TRANSFORM_7_WISHWASHY){
                yaw_setIdeal(yaw_get() + 180.0f);
                yaw_applyIdeal();
            }
            player_setTransformation(targetForm);
            baModel_updateModel();
            bs_setState(bs_getIdleState());
        }
    }
}
