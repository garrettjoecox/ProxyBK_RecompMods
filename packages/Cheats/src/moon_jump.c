#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("baphysics_update")
void post_jump_baphysics_update(void) {
    if (bakey_held(BUTTON_L) && recomp_get_config_u32("moon_jump")) {
        baphysics_set_vertical_velocity(500.0f);
    }
}
