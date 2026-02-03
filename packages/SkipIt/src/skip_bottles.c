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
            if (!ability_isUnlocked(ability)) {
                ability_unlock(ability);
                if (ability == ABILITY_6_EGGS) {
                    item_adjustByDiffWithHud(ITEM_D_EGGS, 50);
                } else if (ability == ABILITY_9_FLIGHT) {
                    item_adjustByDiffWithHud(ITEM_F_RED_FEATHER, 25);
                } else if (ability == ABILITY_12_WONDERWING) {
                    item_adjustByDiffWithHud(ITEM_10_GOLD_FEATHER, 5);
                }
            }
        }
    }
}
