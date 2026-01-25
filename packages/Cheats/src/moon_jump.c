#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK("baphysics_update")
void post_jump_baphysics_update(void) {
    // Not using bakey_held since all buttons are zeroed out when L + R are held
    if ((pfsManagerContPadData[0].button & 0x0020) && recomp_get_config_u32("moon_jump")) {
        baphysics_set_vertical_velocity(500.0f);
    }
}
