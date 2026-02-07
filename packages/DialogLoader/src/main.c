#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

RECOMP_IMPORT(".", void DialogLoader_SetModsFolderPath(unsigned char* path));
RECOMP_IMPORT(".", void DialogLoader_RefreshAll());
RECOMP_IMPORT(".", void DialogLoader_RefreshDialog(s32 textId));
RECOMP_IMPORT(".", void DialogLoader_RefreshQuizQ(s32 quizQId));
RECOMP_IMPORT(".", bool DialogLoader_GetDialog(s32 textId, void* dest));
RECOMP_IMPORT(".", bool DialogLoader_GetQuizQ(s32 quizQId, void* dest));
RECOMP_IMPORT("bk_recomp_asset_expansion_pak", void bk_recomp_aep_register_replacement(enum asset_e asset_id, void *asset_data));
RECOMP_IMPORT("bk_recomp_asset_expansion_pak", void bk_recomp_aep_unregister_replacement(enum asset_e asset_id));

static enum asset_e replacedTextId = -1;
static char dialogBuffer[0x1000];
static char debugTextBuffer[32];

void format_hex(char* buffer, u32 value) {
    const char hex[] = "0123456789ABCDEF";
    buffer[0] = hex[(value >> 12) & 0xF];
    buffer[1] = hex[(value >> 8) & 0xF];
    buffer[2] = hex[(value >> 4) & 0xF];
    buffer[3] = hex[value & 0xF];
    buffer[4] = '\0';
}

RECOMP_CALLBACK("*", recomp_on_init)
void RecompOnInit() {
    unsigned char* modFolderPath = recomp_get_mod_folder_path();
    DialogLoader_SetModsFolderPath(modFolderPath);
    recomp_free(modFolderPath);

    DialogLoader_RefreshAll();
}

RECOMP_HOOK_RETURN("gczoombox_draw")
void post_gczoombox_draw(void) {
    if (recomp_get_config_u32("debug_mode") && g_Dialog.currentTextId != -1) {
        format_hex(debugTextBuffer, g_Dialog.currentTextId);
        print_dialog(50, 55, "TEXT:");
        print_dialog(50, 65, debugTextBuffer);
    }
}

RECOMP_HOOK("dialogBin_get")
void pre_dialogBin_get(enum asset_e text_id) {
    if (recomp_get_config_u32("debug_mode")) {
        DialogLoader_RefreshDialog(text_id);
    }

    recomp_printf("[ProxyBK_DialogLoader] Checking textId: 0x%04X (%d)\n", text_id, text_id);

    // Print the original first 1000 bytes of the dialog data for debugging purposes
    // u8* originalText = assetcache_get(text_id);
    // for (int i = 0; i < 221; i++) {
    //     recomp_printf("%02X ", originalText[i]);
    //     if ((i + 1) % 16 == 0) {
    //         recomp_printf("\n");
    //     }
    // }
    // recomp_printf("\n");
    // assetcache_release(originalText);

    // Clear the buffer before use
    for (int i = 0; i < sizeof(dialogBuffer); i++) {
        dialogBuffer[i] = 0;
    }

    if (DialogLoader_GetDialog(text_id, dialogBuffer)) {
        recomp_printf("[ProxyBK_DialogLoader] Found textId: 0x%04X (%d)\n", text_id, text_id);
        bk_recomp_aep_register_replacement(text_id, dialogBuffer);
        replacedTextId = text_id;

        // // Print the first 1000 bytes of the new dialog data for debugging purposes
        // for (int i = 0; i < 221; i++) {
        //     recomp_printf("%02X ", dialogBuffer[i]);
        //     if ((i + 1) % 16 == 0) {
        //         recomp_printf("\n");
        //     }
        // }
        // recomp_printf("\n");
    }
}

RECOMP_HOOK("dialogBin_release")
void pre_dialogBin_release(enum asset_e text_id) {
    if (replacedTextId != -1) {
        bk_recomp_aep_unregister_replacement(replacedTextId);
        replacedTextId = -1;
    }
}
