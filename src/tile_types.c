#include "global.h"
#include "tile_types.h"
#include "code_806CD90.h"
#include "structs/str_dungeon.h"
#include "dungeon_map.h"
#include "dungeon_map_access.h"
#include "dungeon_util.h"

const u8 gDungeonWaterType[76] = {
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_WATER,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_WATER,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_LAVA,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_LAVA,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_LAVA,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_LAVA,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
    DUNGEON_WATER_TYPE_NONE,
};

extern void sub_8049BB0(s32, s32);
void sub_8042A14(DungeonPos *);

bool8 PosHasItem(DungeonPos *pos)
{
  const Tile *tile;
  Entity *entity;

  tile = GetTile(pos->x,pos->y);
  entity = tile->object;
  if ((entity != NULL) && (GetEntityType(entity) == ENTITY_ITEM)) {
    return TRUE;
  }
  return FALSE;
}

Entity *GetMonsterAtPos(DungeonPos *pos)
{
  const Tile *tile;
  Entity *entity;

  tile = GetTile(pos->x,pos->y);
  entity = tile->monster;
  if ((entity != NULL) && (entity->type == ENTITY_MONSTER)) {
    return entity;
  }
  return NULL;
}

bool8 sub_804AD34(DungeonPos *pos)
{
  Tile *tile;
  s32 x;
  Entity * entity;
  s32 y;
  bool8 iVar8;
  s32 index;

  iVar8 = 0;
  tile = GetTileMut(pos->x,pos->y);
  if (!(tile->terrainType & (TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)))
    if(!(tile->terrainType & (TERRAIN_TYPE_UNBREAKABLE | TERRAIN_TYPE_IMPASSABLE_WALL))){
    iVar8 = 1;
    tile->terrainType = (tile->terrainType & ~(TERRAIN_TYPE_SECONDARY | TERRAIN_TYPE_NORMAL)) | TERRAIN_TYPE_NORMAL;

    for(y = -1; y < 2; y++)
    {
      for(x = -1; x < 2; x++)
      {
        sub_80498A8(x + pos->x, y + pos->y);
        sub_8049BB0(x + pos->x, y + pos->y);
        ShowDungeonMapAtPos(x + pos->x, y + pos->y);
      }
    }
  }
  if (iVar8 != 0) {
    for(index = 0; index < DUNGEON_MAX_POKEMON; index++)
    {
      entity = gDungeon->activePokemon[index];
      if (EntityIsValid(entity)) {
        sub_806CF98(entity);
      }
    }
    sub_8049ED4();
    sub_8042A14(pos);
  }
  return iVar8;
}

bool8 sub_804AE08(DungeonPos *pos)
{
  Tile *tile;
  s32 x;
  s32 y;
  bool8 uVar6;

  uVar6 = FALSE;
  tile = GetTileMut(pos->x,pos->y);

  if (!(tile->terrainType & (TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)))
    if(!(tile->terrainType & (TERRAIN_TYPE_UNBREAKABLE | TERRAIN_TYPE_IMPASSABLE_WALL))) {
        uVar6 = TRUE;
        tile->terrainType = (tile->terrainType & ~(TERRAIN_TYPE_SECONDARY | TERRAIN_TYPE_NORMAL)) | TERRAIN_TYPE_NORMAL;
        tile->spawnOrVisibilityFlags = tile->spawnOrVisibilityFlags | 0x10;

        for(y = -1; y < 2; y++)
        {
            for(x = -1; x < 2; x++)
            {
                sub_8049BB0(x + pos->x, y + pos->y);
            }
        }
    }
  return uVar6;
}

void sub_804AE84(DungeonPos *pos)
{
  Tile *tile;
  s32 x;
  Entity * entity;
  s32 index;
  s32 y;

  tile = GetTileMut(pos->x,pos->y);
  if ((tile->spawnOrVisibilityFlags & 0x10) != 0) {
    tile->spawnOrVisibilityFlags &= 0xffef;

    for(y = -1; y < 2; y++)
    {
      for(x = -1; x < 2; x++)
      {
        sub_80498A8(x + pos->x, y + pos->y);
        ShowDungeonMapAtPos(x + pos->x, y + pos->y);
      }
    }

    for(index = 0; index < DUNGEON_MAX_POKEMON; index++)
    {
      entity = gDungeon->activePokemon[index];
      if (EntityIsValid(entity)) {
        sub_806CF98(entity);
      }
    }
    sub_8049ED4();
    sub_8042A14(pos);
  }
}

bool8 IsTileGround(Tile *tile)
{
    bool8 isGround = FALSE;
    if (IsWaterTileset())
    {
        if (!(tile->terrainType & (TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)))
        {
            isGround = TRUE;
        }
    }
    else if ((tile->terrainType & (TERRAIN_TYPE_NORMAL | TERRAIN_TYPE_SECONDARY)) != TERRAIN_TYPE_SECONDARY ||
        gDungeonWaterType[gDungeon->tileset] == DUNGEON_WATER_TYPE_LAVA)
    {
        isGround = TRUE;
    }
    return isGround;
}

bool8 IsWaterTileset()
{
    if (gDungeon->tileset == 0 ||
        gDungeon->tileset == 0x31 ||
        gDungeon->tileset == 0x20 ||
        gDungeon->tileset == 0x21 ||
        gDungeon->tileset == 0x36)
    {
        return TRUE;
    }
    return FALSE;
}
