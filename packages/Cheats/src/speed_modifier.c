#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("baphysics_update")
void post_speed_baphysics_update(void) {
    if (bakey_held(BUTTON_R) && recomp_get_config_u32("speed_modifier")) {
        baphysics_set_target_horizontal_velocity(2000.0f);
    }
}
