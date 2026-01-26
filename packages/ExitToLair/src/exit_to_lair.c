#include "modding.h"
#include "functions.h"
#include "variables.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "bkextern.h"

// Level enum values for checking current location
#define LEVEL_6_LAIR 0x6
#define LEVEL_B_SPIRAL_MOUNTAIN 0xB
#define LEVEL_C_BOSS 0xC
#define LEVEL_D_CUTSCENE 0xD

typedef struct struct_1A_s {
    f32 delay;
    f32 unk4;
    u8 *str;
    s16 y;
    u8 portrait;
    u8 unkF;
} struct1As;

extern struct1As D_8036C4E0[4];

extern struct {
    u8          state;
    u8          menu;
    u8          selection; //menu page
    u8          exit_pause: 1;
    u8          unk3_6: 1; //busy?
    u8          unk3_5: 1;
    u8          unk3_4: 1;
    u8          left_joystick_visible: 1;
    u8          right_joystick_visible: 1;
    u8          b_button_visible: 1;
    u8          unk3_0: 1;
    s8          zoombox_opening_count;
    s8          zoombox_closing_count;
    u8          unk6;
    u8          unk7;
    s8          unk8; //header position
    s8          page;
    s8          joystick_frame;
    u8          joystick_frame_count;
    f32         unkC;
    GcZoombox  *zoombox[4];
    f32         unk20;
    BKSprite   *joystick_sprite;
    f32         unk28;
    BKSprite   *b_button_sprite;
    u8          b_button_frame;
    u8          b_button_frame_count;      //B-button total frames
    s16         b_button_alpha;      //B-button alpha
    s16         left_joystick_alpha;      //left joystick alpha
    s16         right_joystick_alpha;      //right joystick alpha
    u8          page_cnt;
    u8          sns_items;
    u8          sns_visible;
    // u8  pad3B[1];
    s16         sns_alpha; //sns opacity
    s16         unk3E[7];
    s16         unk4C[7];
    // u8 pad5A[0x3];
    BKModelBin *sns_egg_model; //SnS Egg Model
    BKModelBin *ice_key_model; //Ice key model
    u8          pad64[12];
    u32         unk70_31: 1;
    u32         unk70_30: 1;
    u32         return_to_lair_disabled: 1;
    u32         pad70_28: 29;
} D_80383010;

RECOMP_HOOK("gcdialog_incrementYPositionModifier")
void gcdialog_incrementYPositionModifier() {
    enum level_e current_level = level_get();
    int is_in_level = (current_level != LEVEL_6_LAIR && 
                       current_level != LEVEL_B_SPIRAL_MOUNTAIN &&
                       current_level != LEVEL_C_BOSS &&
                       current_level != LEVEL_D_CUTSCENE);
    
    if (is_in_level) {
        D_80383010.return_to_lair_disabled = FALSE;
        D_8036C4E0[0].y = 45;   // RETURN TO GAME
        D_8036C4E0[1].y = 75;   // EXIT TO WITCH'S LAIR
        D_8036C4E0[2].y = 105;  // VIEW TOTALS
        D_8036C4E0[3].y = 135;  // SAVE AND QUIT
    } else {
        D_80383010.return_to_lair_disabled = TRUE;

        D_8036C4E0[0].y = 55;
        D_8036C4E0[1].y = -100;
        D_8036C4E0[2].y = 90;
        D_8036C4E0[3].y = 125;
    }
}
