#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("chSmBottles_update") 
void chSmBottles_update(Actor *this) {
    if (recomp_get_config_u32("skip_bottles")) {
        if (!this->initialized && this->actorTypeSpecificField == 1) {
            __chSmBottles_skipIntroTutorial();
        }
    }
}

RECOMP_HOOK("chmole_update") 
void chmole_update(Actor *this) {
    if (recomp_get_config_u32("skip_bottles")) {
        if (!this->initialized) {
            this->has_met_before = TRUE;
            s8 ability = moleTable[this->actorTypeSpecificField-9].ability;
            ability_unlock(ability);
            if (ability == ABILITY_6_EGGS) {
                item_set(ITEM_D_EGGS, 50);
            } else if (ability == ABILITY_9_FLIGHT) {
                item_set(ITEM_F_RED_FEATHER, 25);
            } else if (ability == ABILITY_12_WONDERWING) {
                item_set(ITEM_10_GOLD_FEATHER, 5);
            }
        }
    }
}

// For debugging

// RECOMP_HOOK("__chSmBottles_setState")
// void __chSmBottles_setState(Actor *this, s32 next_state) {
//     recomp_printf("__chSmBottles_setState(%d) (%d)\n", next_state, this->actorTypeSpecificField);
// }

// RECOMP_HOOK("mapSpecificFlags_set") 
// void mapSpecificFlags_set(s32 i, s32 val) {
//     recomp_printf("mapSpecificFlags_set(%d, %d)\n", i, val);
// }

// RECOMP_HOOK("ability_setLearned") 
// void ability_setLearned(enum ability_e ability, bool hasLearned) {
//     recomp_printf("ability_setLearned(%d, %d)\n", ability, hasLearned);
// }
