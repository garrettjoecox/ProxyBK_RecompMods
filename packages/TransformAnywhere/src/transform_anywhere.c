#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

enum allowed_transformations_e {
    ALLOWED_TRANSFORMATIONS_ALL = 0,
    ALLOWED_TRANSFORMATIONS_CURRENT_WORLD = 1,
    ALLOWED_TRANSFORMATIONS_BANJO = 2,
    ALLOWED_TRANSFORMATIONS_NONE = 3,
};

bool can_transform_to(enum transformation_e trans_id) {
    if (!recomp_get_config_u32("token_payment")) {
        return TRUE;
    }

    return fileProgressFlag_get((trans_id - TRANSFORM_2_TERMITE) + FILEPROG_90_PAID_TERMITE_COST);
}

bool check_button(s32 button_indx) {
    if (recomp_get_config_u32("button_mode") == 0) {
        return bakey_pressed(button_indx);
    } else {
        return (bakey_held(button_indx) && bakey_pressed(BUTTON_L)) || (bakey_pressed(button_indx) && bakey_held(BUTTON_L));
    }
}

RECOMP_HOOK("func_80295C14")
void pre_func_80295C14(void) {
    // Prevent transforming while entering/exiting drone state
    if ((bsDroneEnterSubstate != 0 && bsDroneEnterSubstate != 3) || (D_8037D468 != 0 && D_8037D468 != 3)) {
        return;
    }

    // Prevent transforming while dying
    if (
        bs_getState() == BS_41_DIE ||
        bs_getState() == BS_4E_PUMPKIN_DIE ||
        bs_getState() == BS_BEE_DIE ||
        bs_getState() == BS_CROC_DIE ||
        bs_getState() == BS_WALRUS_DIE ||
        bs_getState() == BS_43_ANT_DIE
    ) {
        return;
    }

    if (recomp_get_config_u32("allowed_transformations") == ALLOWED_TRANSFORMATIONS_NONE) {
        return;
    }

    u8 transformations_available[4][3] = {
        { TRANSFORM_1_BANJO, TRANSFORM_1_BANJO, TRANSFORM_1_BANJO }, // D-pad Up
        { TRANSFORM_1_BANJO, TRANSFORM_1_BANJO, TRANSFORM_1_BANJO }, // D-pad Down
        { TRANSFORM_1_BANJO, TRANSFORM_1_BANJO, TRANSFORM_1_BANJO }, // D-pad Left
        { TRANSFORM_1_BANJO, TRANSFORM_1_BANJO, TRANSFORM_1_BANJO }, // D-pad Right
    };

    if (recomp_get_config_u32("allowed_transformations") == ALLOWED_TRANSFORMATIONS_ALL) {
        if (can_transform_to(TRANSFORM_2_TERMITE)) {
            transformations_available[3][0] = TRANSFORM_2_TERMITE;
        }
        if (can_transform_to(TRANSFORM_3_PUMPKIN)) {
            transformations_available[3][1] = TRANSFORM_3_PUMPKIN;
        }
        if (can_transform_to(TRANSFORM_4_WALRUS)) {
            transformations_available[1][1] = TRANSFORM_4_WALRUS;
        }
        if (can_transform_to(TRANSFORM_5_CROC)) {
            transformations_available[1][0] = TRANSFORM_5_CROC;
        }
        if (can_transform_to(TRANSFORM_6_BEE)) {
            transformations_available[2][0] = TRANSFORM_6_BEE;
        }
        if (can_transform_to(TRANSFORM_7_WISHWASHY)) {
            transformations_available[0][2] = TRANSFORM_7_WISHWASHY;
        }
    } else if (recomp_get_config_u32("allowed_transformations") == ALLOWED_TRANSFORMATIONS_CURRENT_WORLD) {
        switch (map_get()) {
            case MAP_E_MM_MUMBOS_SKULL:
            case MAP_C_MM_TICKERS_TOWER:
            case MAP_2_MM_MUMBOS_MOUNTAIN:
                if (can_transform_to(TRANSFORM_2_TERMITE)) {
                    transformations_available[0][0] = TRANSFORM_2_TERMITE;
                }
                break;
            case MAP_1B_MMM_MAD_MONSTER_MANSION:
            case MAP_1C_MMM_CHURCH:
            case MAP_1D_MMM_CELLAR:
            case MAP_24_MMM_TUMBLARS_SHED:
            case MAP_25_MMM_WELL:
            case MAP_26_MMM_NAPPERS_ROOM:
            case MAP_28_MMM_EGG_ROOM:
            case MAP_29_MMM_NOTE_ROOM:
            case MAP_2A_MMM_FEATHER_ROOM:
            case MAP_2B_MMM_SECRET_CHURCH_ROOM:
            case MAP_2C_MMM_BATHROOM:
            case MAP_2D_MMM_BEDROOM:
            case MAP_2E_MMM_HONEYCOMB_ROOM:
            case MAP_2F_MMM_WATERDRAIN_BARREL:
            case MAP_30_MMM_MUMBOS_SKULL:
            case MAP_8D_MMM_INSIDE_LOGGO:
                if (can_transform_to(TRANSFORM_3_PUMPKIN)) {
                    transformations_available[0][0] = TRANSFORM_3_PUMPKIN;
                }
                break;
            case MAP_27_FP_FREEZEEZY_PEAK:
            case MAP_7F_FP_WOZZAS_CAVE:
            case MAP_48_FP_MUMBOS_SKULL:
            case MAP_41_FP_BOGGYS_IGLOO:
            case MAP_53_FP_CHRISTMAS_TREE:
                if (can_transform_to(TRANSFORM_4_WALRUS)) {
                    transformations_available[0][0] = TRANSFORM_4_WALRUS;
                }
                break;
            case MAP_D_BGS_BUBBLEGLOOP_SWAMP:
            case MAP_10_BGS_MR_VILE:
            case MAP_47_BGS_MUMBOS_SKULL:
            case MAP_11_BGS_TIPTUP:
                if (can_transform_to(TRANSFORM_5_CROC)) {
                    transformations_available[0][0] = TRANSFORM_5_CROC;
                }
                break;
            case MAP_40_CCW_HUB:
            case MAP_43_CCW_SPRING:
            case MAP_44_CCW_SUMMER:
            case MAP_45_CCW_AUTUMN:
            case MAP_46_CCW_WINTER:
            case MAP_4A_CCW_SPRING_MUMBOS_SKULL:
            case MAP_4B_CCW_SUMMER_MUMBOS_SKULL:
            case MAP_4C_CCW_AUTUMN_MUMBOS_SKULL:
            case MAP_4D_CCW_WINTER_MUMBOS_SKULL:
            case MAP_5A_CCW_SUMMER_ZUBBA_HIVE:
            case MAP_5B_CCW_SPRING_ZUBBA_HIVE:
            case MAP_5C_CCW_AUTUMN_ZUBBA_HIVE:
            case MAP_5E_CCW_SPRING_NABNUTS_HOUSE:
            case MAP_5F_CCW_SUMMER_NABNUTS_HOUSE:
            case MAP_60_CCW_AUTUMN_NABNUTS_HOUSE:
            case MAP_61_CCW_WINTER_NABNUTS_HOUSE:
            case MAP_62_CCW_WINTER_HONEYCOMB_ROOM:
            case MAP_63_CCW_AUTUMN_NABNUTS_WATER_SUPPLY:
            case MAP_64_CCW_WINTER_NABNUTS_WATER_SUPPLY:
            case MAP_65_CCW_SPRING_WHIPCRACK_ROOM:
            case MAP_66_CCW_SUMMER_WHIPCRACK_ROOM:
            case MAP_67_CCW_AUTUMN_WHIPCRACK_ROOM:
            case MAP_68_CCW_WINTER_WHIPCRACK_ROOM:
                if (can_transform_to(TRANSFORM_6_BEE)) {
                    transformations_available[0][0] = TRANSFORM_6_BEE;
                }
                break;
        }
    }

    u32 currentForm = player_getTransformation();
    u32 targetForm = currentForm;

    const s32 dpad_buttons[4] = { BUTTON_D_UP, BUTTON_D_DOWN, BUTTON_D_LEFT, BUTTON_D_RIGHT };
    for (u32 row = 0; row < 4; row++) {
        // Only check dpad up unless all transformations are allowed
        if (row > 0 && recomp_get_config_u32("allowed_transformations") != ALLOWED_TRANSFORMATIONS_ALL) {
            continue;
        }

        if (!check_button(dpad_buttons[row])) {
            continue;
        }

        u32 currentFormIndex = 2;
        for (u32 i = 0; i < 3; i++) {
            if (transformations_available[row][i] == currentForm) {
                currentFormIndex = i;
            }
        }

        targetForm = transformations_available[row][(currentFormIndex + 1) % 3];
        break;
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

RECOMP_PATCH void chMumbo_detransformWarn(NodeProp *arg0, ActorMarker *arg1){
    if (recomp_get_config_u32("allowed_transformations") == ALLOWED_TRANSFORMATIONS_ALL) {
        return;
    }

    s32 xform;
    xform = player_getTransformation();
    if(xform == TRANSFORM_1_BANJO || xform  == TRANSFORM_7_WISHWASHY || sHasWarnedBanjoAboutDetransform)
        return;
    
    sHasWarnedBanjoAboutDetransform++;
    if(D_8037DDF3)
        return;
    
    gcdialog_showDialog(fileProgressFlag_getAndSet(FILEPROG_83_MAGIC_GET_WEAK_TEXT, TRUE) ? ASSET_F5C_DIALOG_MUMBO_MAGIC_GET_WEAK_ABREV : ASSET_F5B_DIALOG_MUMBO_MAGIC_GET_WEAK_FULL, 0xe, NULL, NULL, NULL, NULL);
}

RECOMP_PATCH void chMumbo_detransformTrigger(NodeProp *arg0, ActorMarker *arg1){
    if (recomp_get_config_u32("allowed_transformations") == ALLOWED_TRANSFORMATIONS_ALL) {
        return;
    }
    
    s32 xform;
    xform = player_getTransformation();
    if(xform == TRANSFORM_1_BANJO || xform  == TRANSFORM_7_WISHWASHY || D_8037DDF1)
        return;
    gcdialog_showDialog(fileProgressFlag_getAndSet(FILEPROG_84_MAGIC_ALL_GONE_TEXT, TRUE) ? ASSET_F5E_DIALOG_MUMBO_MAGIC_RUN_OUT_ABREV: ASSET_F5D_DIALOG_MUMBO_MAGIC_RUN_OUT_FULL, 0xe, NULL, NULL, NULL, NULL);
    D_8037DDF1++;
    func_8028FB88(TRANSFORM_1_BANJO);
}
