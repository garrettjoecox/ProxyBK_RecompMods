#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

#define EXTEND_DRAW_DISTANCE (\
    recomp_get_config_u32("extend_draw_distance") && \
    !in_demo_playback_game_mode() \
)

#define EXTEND_UPDATE_DISTANCE (\
    recomp_get_config_u32("extend_draw_distance") && \
    recomp_get_config_u32("extend_update_distance") && \
    !in_demo_playback_game_mode() \
)

// @recomp Check whether the game is currently on a mode that uses demo playback instead of the player's inputs.
bool in_demo_playback_game_mode() {
    switch (getGameMode()) {
        case GAME_MODE_2_UNKNOWN:
        case GAME_MODE_6_FILE_PLAYBACK:
        case GAME_MODE_7_ATTRACT_DEMO:
        case GAME_MODE_8_BOTTLES_BONUS:
        case GAME_MODE_A_SNS_PICTURE:
        case GAME_MODE_9_BANJO_AND_KAZOOIE:
            return TRUE;
        default:
            return FALSE;
    }
}

RECOMP_PATCH bool viewport_cube_isInFrustum2(Cube *cube) {
    if (EXTEND_DRAW_DISTANCE) {
        return TRUE;
    }

    f32 min[3];
    f32 max[3];
    f32 rel_pos[3];

    if (cube->x == -16) {
        return TRUE;
    }

    rel_pos[0] = (f32) ((cube->x * 1000) + 500) - sViewportPosition[0];
    rel_pos[1] = (f32) ((cube->y * 1000) + 500) - sViewportPosition[1];
    rel_pos[2] = (f32) ((cube->z * 1000) + 500) - sViewportPosition[2];

    if (LENGTH_SQ_VEC3F(rel_pos) > 1.6e7f) {
        return FALSE;
    }

    min[0] = (f32) ((cube->x * 1000) - 150);
    min[1] = (f32) ((cube->y * 1000) - 150);
    min[2] = (f32) ((cube->z * 1000) - 150);

    max[0] = min[0] + 1300.0f;
    max[1] = min[1] + 1300.0f;
    max[2] = min[2] + 1300.0f;

    return viewport_isBoundingBoxInFrustum(min, max);
}

// Makes actors update
RECOMP_PATCH bool func_803296D8(Actor *this, s32 dist){
    if (EXTEND_UPDATE_DISTANCE) {
        return TRUE;
    }

    if(!this->unk124_7){
        return TRUE;
    }
    else{
        return subaddie_playerIsWithinSphereAndActive(this, dist);
    }
}

int frustum_checks_enabled = TRUE;
int hook_func_80339124 = FALSE;

RECOMP_FORCE_PATCH bool viewport_func_8024DB50(f32 pos[3], f32 distance) {
    if (!frustum_checks_enabled || EXTEND_DRAW_DISTANCE) {
        return TRUE;
    }
    f32 delta[3];
    s32 i;

    delta[0] = pos[0] - sViewportPosition[0];
    delta[1] = pos[1] - sViewportPosition[1];
    delta[2] = pos[2] - sViewportPosition[2];

    for(i = 0; i < 4; i++) {
        if(distance <= ml_vec3f_dot_product(delta, sViewportFrustumPlanes[i])) {
            return FALSE;
        }
    }

    return TRUE;
}

RECOMP_HOOK("func_80344138")
void pre_func_80344138(BKSpriteDisplayData *self, s32 frame, s32 mirrored, f32 position[3], f32 scale[3], Gfx **gfx, Mtx **mtx) {
    if (EXTEND_DRAW_DISTANCE) {
        D_803858B0 = TRUE;
    }
}

RECOMP_HOOK("modelRender_draw")
BKModelBin *pre_modelRender_draw(Gfx **gfx, Mtx **mtx, f32 position[3], f32 rotation[3], f32 scale, f32*arg5, BKModelBin* model_bin){
    if (EXTEND_DRAW_DISTANCE) {
        D_80383710 = FALSE;
        D_8038370C = 1e30f;
        D_80383708 = 1e30f;
    }
    hook_func_80339124 = TRUE;
}

RECOMP_HOOK_RETURN("modelRender_draw")
BKModelBin *post_modelRender_draw() {
    hook_func_80339124 = FALSE;
}

RECOMP_HOOK("func_80339124")
BKModelBin *pre_func_80339124(Gfx ** gfx, Mtx ** mtx, BKGeoList *geo_list){
    if (hook_func_80339124) {
        frustum_checks_enabled = FALSE;
    }
}

RECOMP_HOOK_RETURN("func_80339124")
BKModelBin *post_func_80339124() {
    if (hook_func_80339124) {
        frustum_checks_enabled = TRUE;
    }
}

RECOMP_PATCH void func_80302C94(Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    f32 vp_position[3];
    s32 vp_cube_indices[3];
    f32 vp_rotation[3];
    s32 i;
    s32 sp44[3];
    s32 sp38[3];
    f32 temp_f18;

    if (!mapSpecificFlags_validateCRC1())
        return;

    func_8032D3A8();
    viewport_getPosition_vec3f(vp_position);
    viewport_getRotation_vec3f(vp_rotation);
    func_80256664(vp_rotation);
    cube_positionToIndices(vp_cube_indices, vp_position);
    vp_cube_indices[0] -= sCubeList.min[0];\
    vp_cube_indices[1] -= sCubeList.min[1];\
    vp_cube_indices[2] -= sCubeList.min[2];
    func_80308EC8();
    sp44[0] = sp44[1] = sp44[2] = 0;
    sp38[0] = sCubeList.width[0] - 1;\
    sp38[1] = sCubeList.width[1] - 1;\
    sp38[2] = sCubeList.width[2] - 1;
    if ((vp_rotation[0]> 250.0f) && (vp_rotation[0]< 290.0f)) {
        if ((vp_rotation[1] >= 225.0f) && (vp_rotation[1] <= 315.0f)) {
            sp44[0] = (vp_cube_indices[0] > sp44[0]) ? vp_cube_indices[0] - 1 : sp44[0];
        } else {
            if ((vp_rotation[1] >= 45.0f) && (vp_rotation[1] <= 135.0f)) {
                sp38[0] = vp_cube_indices[0];
            }
        }

        if ((vp_rotation[0]>= 45.0f) && (vp_rotation[0]<= 135.0f)) {
            sp44[1] = vp_cube_indices[1];
        } else if ((vp_rotation[0]>= 225.0f) && (vp_rotation[0]<= 315.0f)) {
            sp38[1] = vp_cube_indices[1];
        }
        if ((vp_rotation[1] >= 135.0f) && (vp_rotation[1] <= 225.0f)) {
            sp44[2] = (vp_cube_indices[2] > sp44[2]) ? vp_cube_indices[2] - 1 : sp44[2];
        } else if ((315.0f <= vp_rotation[1]) || (vp_rotation[1] <= 45.0f)) {
            sp38[2] = vp_cube_indices[2];
        }
    } else {
        if ((vp_rotation[1] >= 225.0f) && (vp_rotation[1] <= 315.0f)) {
            sp44[0] = vp_cube_indices[0];
        } else {
            if ((vp_rotation[1] >= 45.0f) && (vp_rotation[1] <= 135.0f)) {
                sp38[0] = vp_cube_indices[0];
            }
        }

        if ((vp_rotation[0]>= 45.0f) && (vp_rotation[0]<= 135.0f)) {
            sp44[1] = vp_cube_indices[1];
        } else if ((vp_rotation[0]>= 225.0f) && (vp_rotation[0]<= 315.0f)) {
            sp38[1] = vp_cube_indices[1];
        }
        
        if ((vp_rotation[1] >= 135.0f) && (vp_rotation[1] <= 225.0f)) {
            sp44[2] = vp_cube_indices[2];
        } else if ((315.0f <= vp_rotation[1]) || (vp_rotation[1] <= 45.0f)) {
            sp38[2] = vp_cube_indices[2];
        }
    }

    for(i = 0; i < 3; i++){
        int width = EXTEND_DRAW_DISTANCE ? sCubeList.width[i] : 4;
        if(vp_cube_indices[i] - sp44[i] > width){
            sp44[i] = vp_cube_indices[i] - width;
        }
        if(sp38[i] - vp_cube_indices[i] > width){
            sp38[i] = vp_cube_indices[i] + width;
        }
    }
    if (sCubeList.unk3C != NULL) {
        func_8032D510(sCubeList.unk3C, gfx, mtx, vtx);
    }

    if (sCubeList.unk40 != NULL) {
        func_8032D510(sCubeList.unk40, gfx, mtx, vtx);
    }
    if (((45.0f <= vp_rotation[1]) && (vp_rotation[1] <= 135.0f)) || ((225.0f <= vp_rotation[1]) && (vp_rotation[1] <= 315.0f))) {
        func_80301F50(gfx, mtx, vtx, vp_cube_indices, sp44, sp38);
    } else {
        func_80302634(gfx, mtx, vtx, vp_cube_indices, sp44, sp38);
    }
    func_80308D2C(gfx, mtx, vtx);
}
