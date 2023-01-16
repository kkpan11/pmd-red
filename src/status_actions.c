#include "global.h"
#include "status_actions.h"

#include "code_80521D0.h"
#include "code_8077274_1.h"
#include "code_808417C.h"
#include "charge_move.h"
#include "constants/ability.h"
#include "constants/move_id.h"
#include "constants/status.h"
#include "constants/type.h"
#include "constants/weather.h"
#include "dungeon_engine.h"
#include "dungeon_ai_targeting.h"
#include "dungeon_global_data.h"
#include "dungeon_items.h"
#include "dungeon_map_access.h"
#include "dungeon_pokemon_attributes.h"
#include "dungeon_util.h"
#include "dungeon_visibility.h"
#include "map.h"
#include "moves.h"
#include "number_util.h"
//#include "pokemon.h" // NOTE: overriding some of the funcs below... when fixed, uncomment this
#include "status.h"
#include "status_checks_1.h"
#include "team_inventory.h"
#include "text_util.h"
#include "tile_types.h"
#include "trap.h"
#include "weather.h"

extern void sub_807F43C(struct Entity *, struct Entity *);
extern void sub_8078F50(struct Entity *, struct Entity *);
extern void sub_807DC68(struct Entity *, struct Entity *);
extern void sub_8078A58(struct Entity *, struct Entity *, s16, u32);
extern u32 sub_803D73C(u32);
extern void sub_8045C28(struct Item *, u8 , u8 *);
extern void sub_80464C8(struct Entity *, struct Position *, struct Item *);
extern void sub_8068FE0(struct Entity *, u32, struct Entity *r2);
extern void sub_80522F4(struct Entity *r1, struct Entity *r2, const char []);
extern void sub_806F370(struct Entity *r0, struct Entity *r1, u32, u32, u8 *, u8, s32, u32, u32, u32);
extern void sub_807FC3C(struct Position *, u32, u32);
extern void sub_8042A64(struct Position *);
extern void sub_8040A84(void);
extern void sub_8049ED4(void);
extern void sub_80498A8(s32, s32);
extern void sub_806CF60();
extern void sub_8042A54(struct Position *);
extern void sub_8049BB0(s32, s32);
extern s16 sub_8057600(struct Move*, u32);
extern u32 sub_8055864(struct Entity *pokemon, struct Entity *target, struct Move *param_3, s32 param_4, s32 param_5);
extern void sub_807D148(struct Entity *pokemon, struct Entity *r1, u32 r2, struct Position *r3);
extern void sub_807FE04(u32 *, u32);
extern void sub_807DB74(struct Entity *);
extern void SetMessageArgument(char[], struct Entity*, u32);
extern void HandleLuminousOrbAction(struct Entity *pokemon);
extern void sub_807D510(struct Entity *, struct Entity *);
extern void sub_807DA14(struct Entity *, struct Entity *, s32);
extern s16 sub_803D970(u32);
extern u8 sub_806AA0C(s32, u32);
extern void sub_806BB6C(struct Entity *, s32);
extern void sub_8075C58(struct Entity *, struct Entity *, s32, s32);
extern void sub_807E254(struct Entity *, struct Entity *, u32);
extern bool8 sub_805727C(struct Entity * pokemon, struct Entity * target, s32 chance);
extern u32 sub_8055640(struct Entity *, struct Entity *, struct Move *, u32, u32);
extern void sub_806A6E8(struct Entity *);
extern void sub_807D3CC(struct Entity *, struct Entity *);
extern u8 sub_8069D18(struct Position *);
extern u8 sub_804AD34(struct Position *);
extern u8 sub_8057308(struct Entity *, u32);


// TODO include dungeon_ai.h when SqueezedStatusTarget is figured out
extern void LowerDefenseStageTarget(struct Entity *, struct Entity *, s32, s32, u8, bool8);
extern void RaiseAttackStageTarget(struct Entity *, struct Entity *, s32, s32);
extern void PoisonedStatusTarget(struct Entity *, struct Entity *, bool8);
extern void RaiseDefenseStageTarget(struct Entity *, struct Entity *, s32, s32);
extern void InfatuateStatusTarget(struct Entity *, struct Entity *, bool8);
extern void LowerAttackStageTarget(struct Entity *, struct Entity *, s32, s32, u8, bool8);
extern void PetrifiedStatusTarget(struct Entity *, struct Entity *);
extern void WrapTarget(struct Entity *, struct Entity *);

// TODO having matching issues when this isn't s32.. 
extern void SqueezedStatusTarget(struct Entity *, struct Entity *, s32, bool32);

extern void sub_806F324(struct Entity *, s32, u32, u32);
extern bool8 sub_805755C(struct Entity* pokemon,u16 moveID);
extern void sub_80783C4(struct Entity *, struct Entity *, u32);
extern bool8 sub_807FCD4(struct Position *, u32, u8);
extern void sub_807CD9C(struct Entity *, struct Entity *, u8 direction);


// NOTE: Override pokemon.c types for these two funcs
// GetSize is ok
extern u8 GetBodySize(s32 index);
extern void CopyCyanMonsterNametoBuffer(u8 *buffer, s32 index);
extern u32 GetSize(s16 index);

extern s16 gUnknown_80F55EC[];
extern s16 gUnknown_80F4DCE;
extern u8 *gUnknown_80FDD00[];
extern u8 *gUnknown_80FDCE4[];
extern u32 gUnknown_8106A50;
extern u8 *gPtrSleepingTargetOnlyMessage[];
extern u8 *gUnknown_80FAFF0[];
extern u32 gUnknown_80F4F58;
extern u32 gUnknown_8106A4C;
extern s16 gUnknown_80F4E74[];
extern u8 gAvailablePokemonNames[];
extern u8 *gUnknown_80FD450[];
extern u8 *gUnknown_80FD434[];
extern u8 gUnknown_202DFE8[];
extern s16 gUnknown_80F4F80;
extern u8 *gUnknown_80FF678[];
extern u8 *gUnknown_80FD0B8[];
extern u8 *gUnknown_80FD0B4[];
extern u8 *gUnknown_80FD454[];
extern s16 gUnknown_80F4FC6;
extern u8 *gUnknown_81004F0[];
extern u8 *gUnknown_80FD1CC[];
extern u8 *gUnknown_80FD1B0[];
extern u8 *gUnknown_80FD1EC[];
extern u8 *gUnknown_80FD4C4[];
extern u8 *gUnknown_80FD4DC[];
extern u8 *gUnknown_80FC920[];
extern u8 *gUnknown_80FC8F0[];
extern u8 *gUnknown_80FC614[];
extern u8 *gUnknown_80FC678[];
extern u8 *gUnknown_80FC654[];
extern u8 *gUnknown_80FD574[];
extern u8 *gUnknown_80FD430[];
extern u8 *gUnknown_80FD40C[];
extern u8 *gUnknown_80FD3F0[];
extern u32 gUnknown_8106A50;
extern s16 gUnknown_80F4DDC;
extern s16 gUnknown_80F4F7E;
extern u8 *gUnknown_80FDCA0[];
extern u8 *gUnknown_80FDC9C[];
extern s16 gUnknown_80F4DD8;
extern u32 gUnknown_202F224;
extern u32 gUnknown_8106A8C[];
extern s16 gUnknown_80F4F94[];
extern u8 *gUnknown_80FC5A8[];
extern u8 *gPtrForecastPreventsTypeSwitchMessage[];
extern u8 *gUnknown_80FEB08[];
extern u8 gUnknown_202DE58[];
extern s16 gUnknown_80F4E08;
extern u8 gDungeonCamouflageTypes[76];
extern u32 gUnknown_202F228;

struct Position_Alt
{
    union PositionAlt
    {
        struct Position norm;
        u32 full_bits;
    } temp;
};


extern s16 gUnknown_80F4DC6;
extern u8 *gUnknown_80FEFF4[];

extern u32 gUnknown_80F51C4[];

typedef bool8 (*MoveCallback)(struct Entity *pokemon, struct Entity *target, struct Move *move, s32 param_4);

struct NaturePowerMove
{
    s16 moveID;
    u16 unk2;
    MoveCallback move;
};
struct NaturePowerMove gUnknown_80F59C8[10];

bool8 sub_805AFA4(struct Entity * pokemon, struct Entity * target, struct Move *move, u32 param_4)
{
  s32 r0;
  s32 r2;
  s32 r1;
  bool8 flag;

#ifndef NONMATCHING
  register struct EntityInfo *entityInfo asm("r3");
#else
  struct EntityInfo *entityInfo;
#endif
  
  SendThawedMessage(pokemon, target);
  entityInfo = pokemon->info;
  r2 = entityInfo->maxHPStat;
  r0 = r2;
  if (r2 < 0) {
    r0 = r2 + 3;
  }
  if (entityInfo->HP <= r0 >> 2) {
    r2 = 0;
  }
  else if (r1 = entityInfo->HP, r1 <= r2 / 2) {
      r2 = 1;
  }
  else
  {
    r0 = r2 * 3;
    if (r0 < 0) {
        r0 = r0 + 3;
    }
    if (r0 >>= 2, r2 = 3, r1 <= r0) {
        r2 = 2;
    }
  }
  flag =  sub_8055640(pokemon,target,move,gUnknown_80F51C4[r2],param_4) ? TRUE : FALSE;
  return flag;
}

bool8 sub_805B028(struct Entity * pokemon,struct Entity * target,struct Move *move)
{ 
    ParalyzeStatusTarget(pokemon,target, TRUE);
    return TRUE;
}

bool8 TransformMoveAction(struct Entity * pokemon, struct Entity * target, struct Move *move)
{ 
  if (IsBossFight()) {
    sub_80522F4(pokemon,target,*gUnknown_80FEFF4);
    return FALSE;
  }
  else {
    move->PP = 0;
    sub_8078E18(pokemon,target);
    return TRUE;
  }
}

bool8 sub_805B074(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{ 
    bool8 uVar5;

    uVar5 = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        uVar5 = TRUE;
        if (sub_805727C(pokemon,target,gUnknown_80F4DC6) != 0) {
            PoisonedStatusTarget(pokemon,target,FALSE);
        }
    }
    return uVar5;
}

bool8 sub_805B0BC(struct Entity * pokemon, struct Entity * target)
{ 
    sub_807CD9C(pokemon, target, pokemon->info->action.direction);
    return TRUE;
}

bool8 HandleColorChange(struct Entity * pokemon, struct Entity * target)
{
    u8 newType;
    const char *typeString;
    struct EntityInfo *entityInfo;

    entityInfo = target->info;
    newType = gDungeonCamouflageTypes[gDungeon->tileset];
    if (HasAbility(target, ABILITY_FORECAST)) {
        sub_80522F4(pokemon,target,*gPtrForecastPreventsTypeSwitchMessage);
        return FALSE;
    }
    else {
        entityInfo->types[0] = newType;
        entityInfo->types[1] = TYPE_NONE;
        entityInfo->isColorChanged = TRUE;
        SetMessageArgument(gUnknown_202DFE8,target,0);
        typeString = GetUnformattedTypeString(newType);
        strcpy(gUnknown_202DE58, typeString);
        sub_80522F4(pokemon,target,*gUnknown_80FEB08);
        return TRUE;
    }
}

bool8 sub_805B164(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    RaiseAttackStageTarget(pokemon,target,gUnknown_8106A50, 2);
    return TRUE;
}

bool8 sub_805B17C(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    s32 uVar4;
    bool8 uVar5;

    uVar5 = FALSE;
    if (move->id == MOVE_FIRE_SPIN) {
        SendThawedMessage(pokemon,target);
        uVar4 = 0x13c;
    }
    else {
        uVar4 = 0x75;
        if ((move->id != MOVE_CLAMP) && (uVar4 = 0xf1, move->id == MOVE_BIND)) {
            uVar4 = 0x7e;
        }
    }
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        uVar5 = TRUE;
        if (sub_805727C(pokemon,target,gUnknown_80F4E08) != 0) {
            SqueezedStatusTarget(pokemon,target,uVar4,0);
        }
    }
    return uVar5;
}

bool8 PerishSongMoveAction(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    PerishSongTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805B214(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    WrapTarget(pokemon, target);
    return TRUE;
}

bool8 TrapperOrbAction(struct Entity * pokemon, struct Entity * target)
{
    bool8 trapLaid;
    u8 uVar2;
    bool8 isNotTeamMember;
    
    trapLaid = FALSE;
    isNotTeamMember = pokemon->info->isNotTeamMember;
    uVar2 = 1;
    
    if (isNotTeamMember) {
        uVar2 = 2;
    }
    if (sub_807FCD4(&pokemon->pos,0x13,uVar2) != 0) {
        trapLaid = TRUE;
    }
    else
    {
        sub_80522F4(pokemon,target,*gUnknown_80FC5A8); // A trap can't be laid here!
    }
    sub_8049ED4();
    return trapLaid;
}

bool8 sub_805B264(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    s32 r3;
    bool8 r6;
    s32 iVar5;
    struct EntityInfo *entityInfo;

    entityInfo = target->info;  
    r3 = gUnknown_202F224;
    r6 = FALSE;

    gDungeon->unk18200 = gUnknown_8106A8C[r3];
    gDungeon->unk18204 = 0;
    iVar5 = gUnknown_80F4F94[r3];
    if (entityInfo->chargingStatus == STATUS_DIGGING) {
        iVar5 *= 2;
    }
    r6 = sub_8055864(pokemon,target,move,iVar5,param_4) ? TRUE : FALSE;
    return r6;
}

bool8 MagicCoatMoveAction(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    MagicCoatStatusTarget(pokemon, target);
    return TRUE;
}

bool8 ProtectMoveAction(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    ProtectStatusTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805B2FC(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    RaiseDefenseStageTarget(pokemon,target,gUnknown_8106A4C,1);
    return TRUE;
}

bool8 sub_805B314(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{
    sub_80783C4(pokemon, target, 1);
    return TRUE;
}

bool8 sub_805B324(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{
    bool8 uVar3;

    uVar3 = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        uVar3 = TRUE;
        if (sub_805727C(pokemon,target,gUnknown_80F4DD8) != 0) {
            LowerAttackStageTarget(pokemon,target,gUnknown_8106A50,1,1,0);
        }
    }
    return uVar3;
}

bool8 DestinyBondMoveAction(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    DestinyBondStatusTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805B388(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    return (sub_8055640(pokemon,target,move,0x100,param_4)) ? TRUE : FALSE;
}

bool8 MirrorCoatMoveAction(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    MirrorCoatStatusTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805B3B4(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    u32 uVar1 = gUnknown_8106A50;
    RaiseAttackStageTarget(pokemon,target,uVar1,1);
    RaiseDefenseStageTarget(pokemon,target,uVar1,1);
    return TRUE;
}

bool8 sub_805B3E0(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4)
{ 
    sub_8055640(pokemon,target,move,0x100,param_4);
    return TRUE;
}

bool8 sub_805B3FC(struct Entity * pokemon,struct Entity * target,struct Move *move, s32 param_4, s32 param_5)
{
    struct EntityInfo *entityInfo;
    bool8 uVar4;

    uVar4 = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_5) != 0) {
        uVar4 = TRUE;
        if (sub_805727C(pokemon,pokemon,gUnknown_80F4DCE) != 0) {
            entityInfo = pokemon->info;
            RaiseAttackStageTarget(pokemon,pokemon,param_4,1);
            if (entityInfo->unkFB == 0) {
                entityInfo->unkFB = 1;
            }
        }
    }
    return uVar4;
}

bool8 sub_805B454(struct Entity * pokemon, struct Entity * target)
{
    InfatuateStatusTarget(pokemon, target, TRUE);
    return TRUE;
}

bool8 MimicMoveAction(struct Entity * pokemon, struct Entity * target)
{
    struct EntityInfo *entityInfo;
    struct EntityInfo *targetEntityInfo;
    struct Move *move;
    s32 moveCounter;
    s32 moveIndex;
    bool8 mimicSuccess;

    mimicSuccess = FALSE;
    entityInfo = pokemon->info;
    targetEntityInfo = target->info;
    moveCounter = 0;

    for(moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        move = &targetEntityInfo->moves[moveIndex];
        if (((move->moveFlags & MOVE_FLAG_EXISTS)) && !sub_805755C(pokemon,move->id)) {
            if ((move->id != MOVE_MIMIC) && (move->id != MOVE_ASSIST) && (move->id != MOVE_SKETCH) && (move->id != MOVE_MIRROR_MOVE) &&
                (move->id != MOVE_ENCORE) && ((move->moveFlags & MOVE_FLAG_LAST_USED))) {
                entityInfo->mimicMoveIDs[moveCounter] = move->id;
                moveCounter++;
            }
        }
    }
    SetMessageArgument(gAvailablePokemonNames,pokemon,0);
    if (moveCounter != 0) {
        if (entityInfo->unkFB == 0) {
            entityInfo->unkFB = 1;
        }
        sub_80522F4(pokemon,target,*gUnknown_80FDCE4);
        mimicSuccess = TRUE;
    }
    else {
        sub_80522F4(pokemon,target,*gUnknown_80FDD00);
    }
    return mimicSuccess;
}

bool8 sub_805B53C(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    s16 *r1;
    s32 index;
    s32 r5;
    s32 IQ;
    u8 local_24;
    struct EntityInfo *entityInfo;

    local_24 = 0;
    entityInfo = pokemon->info;
    r5 = 1;
    index = 0;
    if (0 <= gUnknown_80F55EC[0]) {
        IQ = entityInfo->IQ;
        for(r1 = &gUnknown_80F55EC[index]; (999 > index) && (*r1 >= 0); r1 = r1 + 2, index++)
            {
                if ((IQ < *r1)){
                    r5 = r1[1];
                    goto _0805B598;
                }
            }
    }
_0805B598:
    sub_806F370(pokemon,target,r5,1,&local_24, GetMoveType(move),sub_8057600(move,param_4),0,1,0);
    local_24 = local_24 == 0;
    return local_24;
}

bool8 LeechSeedMoveAction(struct Entity * pokemon, struct Entity * target)
{
    HandleLeechSeed(pokemon, target, TRUE);
    if (pokemon->info->unkFB == 0) {
        pokemon->info->unkFB = 1;
    }
    return TRUE;
}

bool8 sub_805B618(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
  bool8 flag;
  struct Move natureMove;
  u32 index;

  index = gUnknown_202F228;
  
  InitPokemonMove(&natureMove, gUnknown_80F59C8[index].moveID);
  flag = gUnknown_80F59C8[index].move(pokemon, target, &natureMove, param_4);
  return flag;
}

bool8 sub_805B668(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
  bool8 hasLiquidOoze;
  s32 iVar3;
  s32 iVar4;
  bool8 uVar5;
  
  uVar5 = FALSE;
  hasLiquidOoze = HasAbility(target, ABILITY_LIQUID_OOZE);
  if (IsSleeping(target)) {
    iVar3 = sub_8055640(pokemon,target,move,0x100,param_4);
    if (iVar3 != 0) {
      uVar5 = TRUE;
      iVar4 = iVar3 / 2;
      if (iVar4 < 1) {
        iVar4 = 1;
      }
      if (sub_8057308(pokemon,0) != 0) {
        if (pokemon->info->unkFB == 0) {
          pokemon->info->unkFB = 1;
        }
        if (sub_8057308(pokemon,0) != 0) {
          if (hasLiquidOoze) {
            sub_806F324(pokemon,iVar4,0xd,0x1fa);
          }
          else {
            HealTargetHP(pokemon,pokemon,iVar4,0,TRUE);
          }
        }
      }
    }
  }
  else {
    sub_80522F4(pokemon,target,*gPtrSleepingTargetOnlyMessage);
  }
  return uVar5;
}

bool8 sub_805B734(struct Entity * pokemon, struct Entity * target)
{
    SnatchStatusTarget(pokemon, target);
    return TRUE;
}

bool8 RecycleMoveAction(struct Entity * pokemon, struct Entity * target)
{
  struct Item *item;
  s32 index;
  struct EntityInfo *entityInfo;
  bool8 isTMRecycled;
  
  entityInfo = target->info;
  isTMRecycled = FALSE;
  if (!entityInfo->isNotTeamMember) {
    for(index = 0; index < INVENTORY_SIZE; index++)
    {
#ifdef NONMATCHING
    item = &gTeamInventory_203B460->teamItems[index];
#else
        register size_t offset asm("r1") = offsetof(struct TeamInventory, teamItems[index]);
        struct Item* p = gTeamInventory_203B460->teamItems;
        size_t addr = offset + (size_t)p;
        item = (struct Item*)addr;
#endif
        if ((item->flags & ITEM_FLAG_EXISTS) && ((item->flags & ITEM_FLAG_IN_SHOP) == 0))
            if(item->id == ITEM_TM_USED_TM) {
                xxx_init_itemslot_8090A8C(item, item->quantity + 0x7d,0);
                isTMRecycled = TRUE;
            }
        }
    if ((entityInfo->heldItem.flags & ITEM_FLAG_EXISTS) && (entityInfo->heldItem.id == ITEM_TM_USED_TM)) {
      xxx_init_itemslot_8090A8C(&entityInfo->heldItem,entityInfo->heldItem.quantity + 0x7D,0);
      isTMRecycled = TRUE;
    }
  }
  if (isTMRecycled) {
    sub_80522F4(pokemon,target,*gUnknown_80FDC9C); // The Used TM was recharged!
  }
  else {
    sub_80522F4(pokemon,target,*gUnknown_80FDCA0); // But nothing happened!
  }
  return isTMRecycled;
}

bool8 ReflectMoveAction(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    ReflectStatusTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805B808(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    u8 local_20;

    local_20 = 0;
    sub_806F370(pokemon,target,gUnknown_80F4F7E,1,&local_20,GetMoveType(move),sub_8057600(move,param_4),0,1,0);
    local_20 = (local_20 == 0);
    return local_20;
}

bool8 sub_805B884( struct Entity * pokemon, struct Entity * target)
{ 
    RaiseAttackStageTarget(pokemon, target, gUnknown_8106A4C, 1);
    RaiseMovementSpeedTarget(pokemon, target, 0, TRUE);
    return TRUE;
}

bool8 SkullBashMoveAction(struct Entity * pokemon, struct Entity * target, struct Move * move, s32 param_4)
{
    bool8 flag;

    if (MoveMatchesChargingStatus(pokemon,move)) {
        flag = sub_8055640(pokemon,target,move,gUnknown_80F4F58,param_4) != 0 ? 1 : 0;
        sub_8079764(pokemon);
    }
    else {
        SetChargeStatusTarget(pokemon,target,STATUS_SKULL_BASH,move,*gUnknown_80FAFF0);
        flag = TRUE;
    }
    return flag;
}

bool8 sub_805B910(struct Entity * pokemon, struct Entity * target, struct Move * move, s32 param_4)
{
    bool8 flag;

    flag = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        flag = TRUE;
        if(sub_805727C(pokemon, target, gUnknown_80F4DDC))
        {
            LowerDefenseStageTarget(pokemon, target, gUnknown_8106A50, 1, 1, 0);
        }
    }
    return flag;
}

bool8 sub_805B968(struct Entity * pokemon, struct Entity * target, struct Move * move, s32 param_4)
{
    s32 entityHP;
    s32 iVar5;
    bool8 flag;

    flag = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        flag = TRUE;
        if (sub_8057308(pokemon,0) != 0) {
            entityHP = pokemon->info->maxHPStat;
            if (entityHP < 0) {
                entityHP = entityHP + 3;
            }
            iVar5 = entityHP >> 2;
            if (iVar5 < 1) {
                iVar5 = 1;
            }
            sub_806F370(pokemon,pokemon,iVar5,0,0,0,sub_8057600(move,param_4),0,1,0);
        }
    }
    return flag;
}

bool8 RockSmashMoveAction(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    bool8 uVar3;
    struct Position pos;

#ifdef NONMATCHING
    struct Entity *temp;
    struct Entity *temp1;
#else
    register struct Entity *temp asm("r5");
    register struct Entity *temp1 asm("r4");
#endif

    temp = pokemon;
    temp1 = target;

    uVar3 = 0;
    if (sub_8069D18(&pos) != 0) {
        sub_80522F4(temp,temp1,*gUnknown_80FD430); // Can't use that diagonally!
    }
    else if (uVar3 = (sub_804AD34(&pos)), uVar3 != 0) {
        sub_80522F4(temp,temp1,*gUnknown_80FD3F0); // It dug the wall in front!
    }
    else {
        sub_80522F4(temp,temp1,*gUnknown_80FD40C); // Can't use that here!
    }
    return uVar3;
}

bool8 sub_805BA44(struct Entity * pokemon, struct Entity * target)
{
    sub_807D3CC(pokemon, target);
    return TRUE;
}

bool8 sub_805BA50(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    struct EntityInfo *iVar2;
    struct EntityInfo *iVar3;
    struct EntityInfo *iVar5;
    struct EntityInfo *iVar6;
    bool8 uVar6;
    struct Item *pokeItem;
    struct Item *targetItem;

    uVar6 = FALSE;
    if (sub_8055640(pokemon,target,move,0x100,param_4) != 0) {
        uVar6 = TRUE;
        if (sub_805727C(pokemon,target, 0) != 0) {
            iVar2 = pokemon->info;
            iVar3 = pokemon->info;
            iVar5 = target->info;
            iVar6 = target->info;
            SetMessageArgument(gAvailablePokemonNames, pokemon, 0);
            SetMessageArgument(gAvailablePokemonNames + 0x50, target, 0);
            if (HasAbility(target, ABILITY_STICKY_HOLD)) {
                return TRUE;
            }
            else if (HasHeldItem(target, ITEM_ALERT_SPECS)) {
                sub_80522F4(pokemon,target,*gUnknown_80FD574); // $m1 was protected by its Specs!
                return TRUE;
            }
            else {
                pokeItem = &iVar2->heldItem;
                targetItem = &iVar5->heldItem;
                if ((pokeItem->flags & ITEM_FLAG_EXISTS) != 0) {
                    sub_80522F4(pokemon,target,*gUnknown_80FC654); // $m0 has an item already!
                    return TRUE;
                }
                else if ((targetItem->flags & ITEM_FLAG_EXISTS) == 0) {
                    sub_80522F4(pokemon,target,*gUnknown_80FC678); // $m1 doesn't have anything
                    return TRUE;
                }
                else {
                    iVar3->heldItem = iVar6->heldItem;
                    targetItem->id = ITEM_NOTHING;
                    targetItem->quantity = 0;
                    targetItem->flags = 0;
                    sub_806A6E8(pokemon);
                    sub_806A6E8(target);
                    if (iVar3->unkFB == 0) {
                        iVar3->unkFB = 1;
                    }
                    sub_80522F4(pokemon,target,*gUnknown_80FC614); // Got $m1's item!
                }
            }
        }
    }
    return uVar6;
}

bool8 sub_805BB64(struct Entity * pokemon, struct Entity * target)
{
    sub_80797A0(pokemon, target, STATUS_MINI_COUNTER);
    return TRUE;
}

bool8 sub_805BB74(struct Entity * pokemon, struct Entity * target)
{
    if(pokemon->info->unkFB == 0)
    {
        pokemon->info->unkFB = 1;
    }
    sub_807E254(pokemon, target, 1);
    return TRUE;
}

bool8 sub_805BB98(struct Entity * pokemon, struct Entity * target)
{
    sub_807D148(pokemon, target, 1, NULL);
    return TRUE;
}

bool8 CleanseOrbAction(struct Entity * pokemon, struct Entity * target)
{
    struct Item *item;
    struct Entity *entity;
    struct EntityInfo *entityInfo;
    s32 index;
    bool8 isItemCleaned;

#ifdef NONMATCHING
    u8 flag;
#else
    register u8 flag asm("r2");
#endif

    entityInfo = target->info;
    isItemCleaned = FALSE;
    if (!entityInfo->isNotTeamMember) {
        for(index = 0; index < INVENTORY_SIZE; index++){
            // WTF why does this work...
            UNUSED struct Item* current = &gTeamInventory_203B460->teamItems[index];
            flag = index[gTeamInventory_203B460->teamItems].flags;
            if (((flag & ITEM_FLAG_EXISTS) != 0) && ((flag & ITEM_FLAG_IN_SHOP) == 0))
                if((flag & ITEM_FLAG_STICKY) != 0) {
                    gTeamInventory_203B460->teamItems[index].flags = flag & 0xf7;
                    isItemCleaned = TRUE;
                }
        }
        for(index = 0; index < MAX_TEAM_MEMBERS; index++)
            {
                entity = gDungeon->teamPokemon[index];
                if (EntityExists(entity)) {
                    item = &entity->info->heldItem;
                    if (((item->flags & ITEM_FLAG_EXISTS) != 0) && ((item->flags & ITEM_FLAG_STICKY) != 0)) {
                        item->flags &= 0xf7;
                        isItemCleaned = TRUE;
                    }
                }
            }
    }
    if (isItemCleaned) {
        sub_80522F4(pokemon,target,*gUnknown_80FC8F0);
    }
    else {
        sub_80522F4(pokemon,target,*gUnknown_80FC920);
    }
    return isItemCleaned;
}

bool8 sub_805BC70(struct Entity * pokemon, struct Entity * target)
{
    sub_8075C58(pokemon,target,CalculateStatusTurns(target, gUnknown_80F4E74, TRUE), TRUE);
    return TRUE;
}

bool8 sub_805BC98(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    struct EntityInfo *entityInfo;
    bool8 uVar3;
    s32 targetHP;
    s32 pokeHP;
    u8 local_28;
    u8 local_27;

    local_28 = 0;
    local_27 = 0;
    entityInfo = pokemon->info;
    targetHP = target->info->HP - 1;
    if (targetHP < 0) {
        targetHP = 0;
    }
    sub_806F370(pokemon,target,targetHP,0,&local_28,0,sub_8057600(move,param_4),0,0,0);
    pokeHP = entityInfo->HP / 2;
    if (pokeHP < 0) {
        pokeHP = 0;
    }
    sub_806F370(pokemon,pokemon,pokeHP,0,&local_27,0,sub_8057600(move,param_4),0,0,0);

    local_28 = (local_28 == 0);
    local_27 = (local_27 == 0);

    uVar3 = FALSE;
    if ((local_28 != 0) || (local_27 != 0)) {
        uVar3 = TRUE;
    }
    return uVar3;
}

bool8 SilenceOrbAction(struct Entity * pokemon, struct Entity * target)
{
    MuzzleTarget(pokemon, target);
    return TRUE;
}

bool8 ScannerOrbAction(struct Entity * pokemon, struct Entity * target)
{
    HandleScannerOrb(pokemon, target);
    return TRUE;
}

bool8 RadarOrbAction(struct Entity * pokemon, struct Entity * target)
{
    HandleRadarOrb(pokemon, target);
    return TRUE;
}

bool8 TransferOrbAction(struct Entity *pokemon, struct Entity * target)
{
    struct EntityInfo *entityInfo;
    s32 oldID; //r8
    s32 targetID; // r5
    s32 r6; // r6
    bool8 didTransfer;

    didTransfer = FALSE;
    if (target->info->isNotTeamMember) {
        entityInfo = target->info;
        targetID = entityInfo->id;
        oldID = entityInfo->id;
        SetMessageArgument(gAvailablePokemonNames,target,0);
        if (entityInfo->clientType != 0) {
            sub_80522F4(pokemon,target,*gUnknown_80FD450);
            return FALSE;
        }
        else
        {
            for (r6 = 0; r6 < 0x1E; r6++) {
                targetID = sub_803D970(0);
                if ((sub_806AA0C(targetID,0) != 0) && (oldID != targetID)) {
                    if (GetBodySize(oldID) == GetBodySize(targetID)) break;
                }
            }
            if ((r6 == 0x1e) || (entityInfo->id == targetID)) {
                sub_80522F4(pokemon,target,*gUnknown_80FD450);
            }
            else {
                CopyCyanMonsterNametoBuffer(gUnknown_202DFE8, targetID);
                sub_80522F4(pokemon,target,*gUnknown_80FD434);
                sub_806BB6C(target, targetID);
                didTransfer = TRUE;
            }
        }
    }
    else {
        SetMessageArgument(gAvailablePokemonNames,target,0);
        sub_80522F4(pokemon,target,*gUnknown_80FD450);
    }
    return didTransfer;
}

bool8 sub_805BE90(struct Entity *pokemon, struct Entity *target)
{
  LowerMovementSpeedTarget(pokemon, target, 1, TRUE);
  return TRUE;
}

bool8 LuminousOrbAction(struct Entity * pokemon, struct Entity * target)
{
    HandleLuminousOrbAction(pokemon);
    return TRUE;
}

bool8 sub_805BEAC(struct Entity * pokemon, struct Entity * target)
{
    PetrifiedStatusTarget(pokemon, target);
    return TRUE;
}

bool8 sub_805BEB8(struct Entity * pokemon, struct Entity * target)
{
    sub_807DA14(pokemon, target, 8);
    return TRUE;
}

bool8 sub_805BEC8(struct Entity * pokemon, struct Entity * target)
{
    sub_807D510(pokemon, target);
    return TRUE;
}

bool8 EscapeOrbAction(struct Entity * pokemon, struct Entity * target)
{
    SetMessageArgument(gAvailablePokemonNames,pokemon,0);
    if (gDungeon->unk66E != 0) {
        sub_80522F4(pokemon,target,*gUnknown_80FD4DC); // $m0 can't escape!
    }
    else {
        sub_80522F4(pokemon,target,*gUnknown_80FD4C4); // $m0 escaped!
        gDungeon->unk4 = 1;
        gDungeon->unk11 = 1;
    }
    return FALSE;
}

bool8 sub_805BF34(struct Entity * pokemon, struct Entity * target)
{
    sub_807DB74(pokemon);
    return TRUE;
}

bool8 TrapbustOrbAction(struct Entity * pokemon,struct Entity * target)
{
    struct Tile *tile;
    struct Entity *object;
    u8 *trapData;
    s32 bottomRightCornerX, bottomRightCornerY;
    s32 xCoord, yCoord;
    struct RoomData *room;
    s32 topLeftCornerX, topLeftCornerY;
    u32 sp;
    bool8 foundTrap = FALSE;
    tile = GetTileAtEntitySafe(target);
    if (IsBossFight()) {
        SendMessage(pokemon,*gUnknown_80FD1EC);
        return FALSE;
    }
    else
    {
        if (tile->room == 0xFF) {
            bottomRightCornerX    =   target->pos.x - gDungeon->visibilityRange;
            bottomRightCornerY    =   target->pos.y - gDungeon->visibilityRange;
            topLeftCornerX      =   bottomRightCornerX + gDungeon->visibilityRange;
            topLeftCornerY      =   bottomRightCornerY + gDungeon->visibilityRange;
        }
        else {
            room       =   &gDungeon->roomData[tile->room];
            bottomRightCornerX     =   room->bottomRightCornerX - 1;
            bottomRightCornerY     =   room->bottomRightCornerY - 1;
            topLeftCornerX       =   room->topLeftCornerX + 1;
            topLeftCornerY       =   room->topLeftCornerY + 1;
        }
        ++topLeftCornerY; --topLeftCornerY;
        for (xCoord = bottomRightCornerX; xCoord <= topLeftCornerX; xCoord++) {
            for (yCoord = bottomRightCornerY; yCoord <= topLeftCornerY; yCoord++) {
                object = GetTileSafe(xCoord, yCoord)->object;
                if (((object != 0) && (GetEntityType(object) == ENTITY_TRAP)) &&
                    (trapData = (u8*)GetTrapData(object), trapData[0] != 0x11)) {
                    sp = yCoord << 0x10 | (u16)xCoord;
                    sub_807FE04(&sp, 0);
                    foundTrap = TRUE;
                }
            }
        }
        if (foundTrap) {
            sub_80522F4(pokemon, target, *gUnknown_80FD1B0);
            sub_8040A84();
            sub_8049ED4();
        }
        else {
            sub_80522F4(pokemon, target, *gUnknown_80FD1CC);
        }
    }
    return foundTrap;
}

bool8 sub_805C080(struct Entity * pokemon, struct Entity *target)
{
    struct Entity **possibleTargets;
    s32 numPossibleTargets;
    struct Entity *targetEntity;
    bool8 foundTarget;
    s32 index;

    foundTarget = FALSE;
    if (pokemon->info->isNotTeamMember) {
        possibleTargets = gDungeon->wildPokemon;
        numPossibleTargets = DUNGEON_MAX_WILD_POKEMON;
    }
    else {
        possibleTargets = gDungeon->teamPokemon;
        numPossibleTargets = MAX_TEAM_MEMBERS;
    }
    for(index = 0; index < numPossibleTargets; index++){
        targetEntity = possibleTargets[index];
        if (((EntityExists(targetEntity)) && (pokemon != targetEntity)) &&
            (CanTarget(pokemon,targetEntity,1,FALSE) == 0)) {
            sub_807D148(pokemon,targetEntity,2,&pokemon->pos);
            foundTarget = TRUE;
        }
    }
    if (!foundTarget) {
        sub_80522F4(pokemon,target,*gUnknown_81004F0);
    }
    return foundTarget;
}

bool8 sub_805C128(struct Entity * pokemon, struct Entity * target)
{
    InvisibleStatusTarget(pokemon, pokemon);
    return TRUE;
}

bool8 sub_805C138(struct Entity * pokemon, struct Entity * target, struct Move *move, s32 param_4)
{
    u8 local_20;

    local_20 = 0;
    sub_806F370(pokemon,target,9999,1,&local_20,GetMoveType(move),sub_8057600(move,param_4),0,1,0);
    local_20 = (local_20 == 0);
    return local_20;
}

bool8 IdentifyOrbAction(struct Entity *pokemon, struct Entity *target)
{
    IdentityItemHolders(pokemon, target);
    return TRUE;
}

bool8 sub_805C1BC(struct Entity *pokemon, struct Entity *target, struct Move *move, s32 param_4)
{
    bool8 flag;

    flag = sub_8055864(pokemon, target, move, gUnknown_80F4F80, param_4) != 0 ? TRUE : FALSE;
    return flag;
}

bool8 sub_805C1E4(struct Entity *pokemon, struct Entity *target)
{
    sub_80522F4(pokemon, target, *gUnknown_80FD454);
    return FALSE;
}

bool8 ShockerOrbAction(struct Entity *pokemon, struct Entity *target)
{
    CowerStatusTarget(pokemon, target, TRUE);
    return TRUE;
}

bool8 sub_805C208(struct Entity *pokemon, struct Entity *target, struct Move *move, u32 param_4)
{
    u32 uVar3;
    u8 local_24;

    local_24 = 0;
    uVar3 = GetSize(target->info->apparentID);
    sub_806F370(pokemon,target,uVar3,1,&local_24,GetMoveType(move),sub_8057600(move,param_4),0,1,0);

    local_24 = local_24 == 0;
    return local_24;
}

bool8 sub_805C288(struct Entity *pokemon, struct Entity *target)
{
    sub_8078A58(pokemon, target, gUnknown_80F4FC6, 0);
    return TRUE;
}

bool8 sub_805C2A0(struct Entity *pokemon, struct Entity *target)
{
    sub_807DC68(pokemon, target);
    return TRUE;
}

bool8 FillInOrbAction(struct Entity *pokemon,struct Entity *target)
{
    struct Tile *tileToFill;
    struct EntityInfo *iVar5;
    int y;
    bool8 filledInTile;
    int x;
    u16 cast_x;
    u32 cast_y;
    struct Position_Alt tileCoords;

    filledInTile = FALSE;
    iVar5 = target->info;
    if (IsBossFight()) {
        SendMessage(pokemon,*gUnknown_80FD0B8);
        return FALSE;
    }
    else
    {
        // Calculate the coordinates of the tile in front of the user
        cast_x = target->pos.x + gAdjacentTileOffsets[iVar5->action.direction].x;
        tileCoords.temp.full_bits = (tileCoords.temp.full_bits & 0xffff0000) | cast_x;

        cast_y = ((u16)(target->pos.y + gAdjacentTileOffsets[iVar5->action.direction].y)) << 0x10;
        tileCoords.temp.full_bits = (tileCoords.temp.full_bits & 0x0000ffff) | cast_y;

        sub_8042A54((struct Position *)&tileCoords);
        tileToFill = GetTileSafe(tileCoords.temp.norm.x,tileCoords.temp.norm.y);
        if ((tileToFill->terrainType & (TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)) == TERRAIN_TYPE_SECONDARY) {
            tileToFill->terrainType = (tileToFill->terrainType & ~(TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)) | TERRAIN_TYPE_NORMAL;

            for(y = -1; y < 2; y++)
                for(x = -1; x < 2; x++)
                    sub_80498A8(tileCoords.temp.norm.x + x, tileCoords.temp.norm.y + y);
            filledInTile = TRUE;
            sub_806CF60();
        }

        for(y = 0; y < DUNGEON_MAX_SIZE_Y; y++)
            for(x = 0; x < DUNGEON_MAX_SIZE_X; x++)
                sub_8049BB0(x,y);

        if (filledInTile) {
            sub_8042A64((struct Position *)&tileCoords);
            sub_80522F4(pokemon,target,*gUnknown_80FD0B4);
        }
        else {
            sub_80522F4(pokemon,target,*gUnknown_80FD0B8);
        }
        sub_8040A84();
        sub_8049ED4();
        return filledInTile;
    }
}

bool8 sub_805C3DC(struct Entity *pokemon, struct Entity *target)
{
    u32 var;
    var = (target->info->isNotTeamMember ? 2 : 1);
    sub_807FC3C(&target->pos, 0x14, var);
    return TRUE;
}

bool8 sub_805C3F8(struct Entity *pokemon, struct Entity *target)
{
    struct Item stack;
    struct Position posStruct = target->pos;

    if(target->info->clientType != CLIENT_TYPE_NONE)
    {
        sub_80522F4(pokemon, target, *gUnknown_80FF678);
        return FALSE;
    }
    else
    {
        target->isVisible = FALSE;
        sub_8045C28(&stack, sub_803D73C(0), 0);
        sub_80464C8(pokemon, &posStruct, &stack);
        sub_8068FE0(target, 0x218, pokemon);
        return TRUE;
    }
}

bool8 sub_805C45C(struct Entity *pokemon, struct Entity *target)
{
    sub_807F43C(pokemon, target);
    return TRUE;
}

bool8 sub_805C468(struct Entity *pokemon, struct Entity *target)
{
    sub_8078F50(pokemon, target);
    return TRUE;
}

bool8 StairsOrbAction(struct Entity *pokemon, struct Entity *target)
{
    HandleStairsOrb(pokemon, target);
    return TRUE;
}

bool8 LongtossOrbAction(struct Entity *pokemon, struct Entity *target)
{
    LongTossStatusTarget(pokemon, target);
    return TRUE;
}

bool8 PierceOrbAction(struct Entity *pokemon, struct Entity *target)
{
    PierceStatusTarget(pokemon, target);
    return TRUE;
}