#include "global.h"
#include "dungeon_visibility.h"

#include "constants/status.h"
#include "dungeon_pokemon_attributes.h"
#include "dungeon_range.h"
#include "dungeon_util.h"

bool8 CanSeeTarget(struct Entity *entity, struct Entity *targetEntity)
{
    if (!EntityExists(entity) || !EntityExists(targetEntity) || !targetEntity->isVisible)
    {
        return FALSE;
    }
    if (targetEntity->type == ENTITY_MONSTER)
    {
        if (entity->type == ENTITY_MONSTER)
        {
            if (!CanSeeInvisibleMonsters(entity) && targetEntity->info->transformStatus == STATUS_INVISIBLE)
            {
                return FALSE;
            }
            if (entity->info->eyesightStatus == STATUS_BLINKER)
            {
                return FALSE;
            }
        }
        else if (targetEntity->info->transformStatus == STATUS_INVISIBLE)
        {
            return FALSE;
        }
    }
    return IsPositionActuallyInSight(&entity->pos, &targetEntity->pos);
}

bool8 CanTargetEntity(struct Entity *entity, struct Entity *targetEntity)
{
    if (!EntityExists(entity) || !EntityExists(targetEntity) || !targetEntity->isVisible)
    {
        return FALSE;
    }
    if (targetEntity->type == ENTITY_MONSTER)
    {
        if (entity->type == ENTITY_MONSTER)
        {
            if (!CanSeeInvisibleMonsters(entity) && targetEntity->info->transformStatus == STATUS_INVISIBLE)
            {
                return FALSE;
            }
            if (entity->info->eyesightStatus == STATUS_BLINKER)
            {
                return FALSE;
            }
        }
        else if (targetEntity->info->transformStatus == STATUS_INVISIBLE)
        {
            return FALSE;
        }
    }
    return IsPositionInSight(&entity->pos, &targetEntity->pos);
}

bool8 sub_8045A70(struct Entity *entity, struct Entity *targetEntity)
{
    if (EntityExists(entity) && EntityExists(targetEntity) && targetEntity->isVisible)
    {
         return IsPositionActuallyInSight(&entity->pos, &targetEntity->pos);
    }
   return FALSE;
}

bool8 sub_8045AAC(struct Entity *entity, struct Position *pos)
{
    return IsPositionActuallyInSight(&entity->pos, pos);
}

bool8 CanTargetPosition(struct Entity *entity, struct Position *pos)
{
    return IsPositionInSight(&entity->pos, pos);
}
