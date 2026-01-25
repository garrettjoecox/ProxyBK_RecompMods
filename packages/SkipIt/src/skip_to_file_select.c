#include "modding.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_HOOK_RETURN("setBootMap")
void post_setBootMap(enum map_e map_id){
    if (recomp_get_config_u32("skip_to_file_select")) {
        gBootMap = MAP_91_FILE_SELECT;
    }
}
