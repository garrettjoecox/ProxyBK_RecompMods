#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_PATCH void cutscenetrigger_check(s32 cs_map, s32 arg1, s32 return_map, s32 return_exit, bool (* condFunc)(void)){
    if(map_get() != cs_map)
        return;

    if((condFunc && condFunc()) || mapSpecificFlags_get(arg1) || recomp_get_config_u32("skip_cutscenes")){
        mapSpecificFlags_set(arg1, 0);
        transitionToMap(return_map, (return_exit == -1)? 0: return_exit, 1);
    }
}
