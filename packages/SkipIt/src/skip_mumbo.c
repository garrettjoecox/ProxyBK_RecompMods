#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("chMumbo_update") 
void chMumbo_update(Actor *this) {
    if (recomp_get_config_u32("skip_mumbo")) {
        if (!this->initialized) {
            // Skip Mumbo's initial dialog
            this->has_met_before = TRUE;
            fileProgressFlag_set(FILEPROG_11_HAS_MET_MUMBO, TRUE);
            fileProgressFlag_set(FILEPROG_12_HAS_TRANSFORMED_BEFORE, TRUE);
            fileProgressFlag_set(FILEPROG_DC_HAS_HAD_ENOUGH_TOKENS_BEFORE, TRUE);
        }

        // Speed up Mumbo's animations
        if (this->state == 4 || this->state == 5) {
            anctrl_setDuration(this->anctrl, 7.5f / 4.0f);
        }
    }
}

// Speed up transformations
RECOMP_HOOK_RETURN("__bsdronexform_setState") 
void __bsdronexform_setState() {
    if (recomp_get_config_u32("skip_mumbo")) {
        // This may be problematic in the future... should probably add a state check
        if (batimer_isGreaterThan(0, 0.2f)) {
            batimer_set(0, 0.2f);
        }
    }
}
