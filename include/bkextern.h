#include "functions.h"
#include "variables.h"
#include "core2/ba/physics.h"
#include "core2/abilityprogress.h"
#include "core2/commonParticle.h"


typedef struct GcZoombox {
    u8 unk0[0x30];  //string1
    u8 unk30[0x30]; //string2
    u8 unk60[0x30];
    u8 unk90[0x20];
    u8 unkB0[0x40];
    BKModelBin *model;
    AnimCtrl *anim_ctrl;
    BKSprite *unkF8;
    BKSpriteDisplayData *unkFC;
    BKSprite *unk100;
    BKSpriteDisplayData *unk104;
    u8  unk108[5];  //sfx_indexes
    u8  pad10D[3];
    f32  unk110[5]; //sfx_???
    s16 unk124[5];  //sfx_???
    s16 unk12E;
    void (*callback)(s32 portrait_id, s32 state);
    u8  unk134;
    u8  state;
    u8  portrait_id; //0x136
    u8  str_cnt; //string_cnt
    u8  current_str_index; //current_string
    u8  unk139;
    u8  unk13A;
    u8  sfx_count;
    char *raw_str[8]; //string_ptrs
    u8 unk15C;
    u8 unk15D;
    u8 unk15E;
    u8 pad15F[0x1];
    u8 *unk160;
    s16 unk164;
    s16 unk166; //top_transparency???
    s16 unk168; //rgb???
    s16 unk16A; //x_pos
    s16 unk16C; //y1_pos
    s16 unk16E; //y2_pos
    s16 unk170;
    s16 unk172;
    s16 unk174;
    s8  unk176;
    s8  unk177;
    s8  unk178;
    s8  unk179;
    u8  pad17A[0x2];
    f32 unk17C;
    s8  unk180;
    s8  unk181;
    u8  unk182;
    u8  unk183;
    u8 unk184;
    u8 unk185;
    s8 unk186;
    u8 unk187;
    u8 frame_count; //sprite frame count
    u8 unk189;
    u8 unk18A;
    u8 prev_sfx;      //next_sfx
    f32 unk18C;
    f32 unk190;
    f32 unk194;
    f32 unk198;
    f32 unk19C;
    f32 unk1A0;
    u32 unk1A4_31:1;
    u32 unk1A4_30:1;
    u32 unk1A4_29:1;
    u32 unk1A4_28:1;
    u32 unk1A4_27:1;
    u32 unk1A4_26:1;
    u32 unk1A4_25:1;
    u32 unk1A4_24:1;
    u32 unk1A4_23:1;
    u32 unk1A4_22:1;
    u32 unk1A4_21:1;
    u32 unk1A4_20:1;
    u32 unk1A4_19:1;
    u32 highlighted:1;
    u32 unk1A4_17:1;
    u32 unk1A4_16:1;
    u32 unk1A4_15:1;
    u32 unk1A4_14:1;
    u32 unk1A4_13:1;
    u32 unk1A4_12:1;
    u32 unk1A4_11:1;
    u32 unk1A4_10:1;
    u32 pad1A4_9:10;
} GcZoombox; //size 0x1A8

typedef struct{
    s16 teach_text_id;
    s16 refresher_text_id;
    s8 camera_node;
    s8 ability;
} ChMoleDescription;

extern struct {
    Cube *cubes;
    f32 margin;
    s32 min[3];
    s32 max[3];
    s32 stride[2];
    s32 cubeCnt; 
    s32 unk2C;
    s32 width[3];
    Cube *unk3C; // fallback cube?
    Cube *unk40; // some other fallback cube?
    s32 unk44; // index of some sort
} sCubeList;

extern struct{
    f32 position[3]; //first_person_position
    f32 rotation[3];
    f32 zoomed_in_position[3];
    f32 zoomed_in_rotation[3];
    f32 zoomed_out_position[3];
    f32 zoomed_out_rotation[3];
    f32 transistion_timer;
    u8 state;
} D_8037DC60;


void func_80315C90(GcZoombox *this, s32 arg1);
s32 globalTimer_getTime(void);
bool gameFile_anyNonEmpty(void);
void __chSmBottles_skipIntroTutorial(void);
extern s32 gBootMap;
s32 mapSpecificFlags_get(s32);
enum map_e map_get(void);
s32 item_getCount(enum item_e item);
void item_set(s32 item, s32 val);
void item_setMaxCount(s32 item);
int chmole_learnAbility(Actor *this);
bool fileProgressFlag_get(enum file_progress_e index);
enum level_e level_get(void);
s32 getGameMode(void);
void player_setTransformation(s32 transformation);
void baModel_updateModel(void);
enum transformation_e func_80294A4C(void);
void func_8029BD44(enum asset_e *anim_id, f32 *anim_duration);
enum bs_e bs_getIdleState(void);
int bakey_newlyReleased(s32 button_indx);
int bakey_released(s32 button_indx);
int ability_isUnlocked(enum ability_e uid);
void fileProgressFlag_set(enum file_progress_e, bool);
int gcdialog_getCurrentTextId(void);
int gctransition_done(void);
bool player_isDead(void);
void func_80302634(Gfx **gfx, Mtx **mtx, Vtx **vtx, s32 arg3[3], s32 arg4[3], s32 arg5[3]);
void func_80308D2C(Gfx **gfx, Mtx **mtx, Vtx **vtx);
void cube_positionToIndices(s32 arg0[3], f32 arg1[3]);
void func_80308EC8(void);
void func_8032D510(Cube *, Gfx **, Mtx **, Vtx **);
s32 mapSpecificFlags_validateCRC1(void);
void func_8032D3A8(void);
void func_80301F50(Gfx **gfx, Mtx **mtx, Vtx **vtx, s32 arg3[3], s32 arg4[3], s32 arg5[3]);
s32 getGameMode(void);
bool subaddie_playerIsWithinSphereAndActive(Actor *this, s32 dist);
void func_802A1B88(void);
s32 fileProgressFlag_getAndSet(enum file_progress_e index, s32 set);
bool func_8028FB88(enum transformation_e xform_id);
s32 item_adjustByDiffWithHud(enum item_e item, s32 diff);
void __chMumbo_textCallback(ActorMarker *caller, enum asset_e text_id, s32 arg2);
void func_8028F918(s32);
void gcpausemenu_80314AC8(s32);
void func_8025A7DC(enum comusic_e);
void chMumbo_func_802D1B8C(Actor *this, enum transformation_e transform_id);
enum file_progress_e __bkProgId_from_transformationId(enum transformation_e trans_id);
void * osPhysicalToVirtual(u32);
s32 can_egg(void);
void ability_use(enum ability_used ability);
s32 item_empty(enum item_e item);
int commonParticle_new(enum common_particle_e particle_id, int arg1);
void item_dec(enum item_e item);
void fxegg_collide(s32 arg0, ActorMarker *marker, s32 arg2);
u8 func_8033E93C(void);
ActorMarker *func_8033E840(void);
void func_803300B8(ActorMarker *marker, MarkerCollisionFunc method);
void func_8033EA40(s32, f32);
void func_80244D94(f32[3], f32[3], f32[3], u32, f32);
f32 func_8033EA14(s32);
void projectile_getPosition(u8 indx, f32 position[3]);
void commonParticle_stashCurrentIndex(void);
void func_803541C0(s32 arg0);
void func_803541CC(s32 arg0);
void func_80354030(f32[3], f32);
void commonParticle_applyIndexStash(void);
s32 func_803531C8(u8 projectile_indx, s32 arg1);
void func_80344E7C(u8 index, f32 dst[3]);
void fxegg_shatter(u8 projectile_indx);
s32 func_80344EC0(u8 index);
void func_8032320C(void);
bool fxegg_isCollidingWithPlayer(f32 arg0[3]);
s32 chCollectible_collectEgg(ActorProp *arg0);

extern ChMoleDescription moleTable[];
extern PfsManagerControllerData D_80281138[4];
extern s32 D_802810E0[4][5];
extern OSContPad pfsManagerContPadData[4];
extern s32 D_8037D160;
extern s32 D_8037D164;
extern s32 gameNumber;
extern u8 bsDroneEnterSubstate;
extern u8 D_8037D468;
extern s32 D_80383710;
extern f32 D_8038370C;
extern f32 D_80383708;
extern f32 sViewportFrustumPlanes[4][4];
extern f32 sViewportPosition[3];
extern u8 D_803858B0;
extern u8 sHasWarnedBanjoAboutDetransform;
extern u8 D_8037DDF3;
extern u8 D_8037DDF1;
extern u8 D_8037DDF0;
extern AnimSpriteStep D_803726A0[10];
