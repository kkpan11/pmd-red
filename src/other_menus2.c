#include "global.h"
#include "globaldata.h"
#include "code_8094F88.h"
#include "constants/communication_error_codes.h"
#include "constants/dungeon.h"
#include "main_menu1.h"
#include "memory.h"
#include "other_menus1.h"
#include "other_menus2.h"
#include "pokemon.h"
#include "save.h"
#include "menu_input.h"
#include "structs/str_dungeon.h"

typedef struct unkStruct_800D670
{
    u8 buffer[16];
    u32 unk10;
} unkStruct_800D670;

// rescue_password_menu.c
extern s32 gCommsTimeout; // Counts to 100 and then errors if other player hasn't connected

EWRAM_DATA static s32 gUnknown_202EC38 = 0;
UNUSED EWRAM_DATA static u8 sUnused = 0;
EWRAM_DATA static s32 gUnknown_202EC40[2] = {0};
EWRAM_DATA static s32 gUnknown_202EC48 = 0;

extern struct UnkStruct_203B184 *gUnknown_203B184;

#include "data/other_menus2.h"

// code_800D090.s
extern s32 sub_800D33C(void);
extern void sub_800D494(void);
extern void sub_800D510(void);
extern void sub_800D520(void);
extern void sub_800D570(void);
extern u8 sub_800D588(void);
extern void sub_800D59C(void *, u32);
extern u8 sub_800D600(void);
extern void sub_800D670(s32 idx, void *dst, s32 size);
extern void sub_800D68C(u32);
void sub_800D414(void);

// Inline needed for 8-bit return cast
static inline bool8 IsNotChunsoft(unkStruct_800D670 *unk)
{
    return strcmp(unk->buffer, sChunsoft) != 0;
}

bool8 sub_8037A48(void)
{
    bool8 found;
    unkStruct_800D670 stack;
    unkStruct_800D670 stack_1;
    s32 i;

    found = TRUE;
    sub_800D670(0, &stack, sizeof(unkStruct_800D670));
    sub_800D670(1, &stack_1, sizeof(unkStruct_800D670));

    for (i = 0; i < 2; i++)
        gUnknown_202EC40[i] = 8;

     gUnknown_202EC40[0] = stack.unk10;
     gUnknown_202EC40[1] = stack_1.unk10;

    if (IsNotChunsoft(&stack) || IsNotChunsoft(&stack_1))
        return FALSE;

    if ((stack.unk10 == 0 && stack_1.unk10 == 1)
        || (stack.unk10 == 1 && stack_1.unk10 == 0)) {
        //found = TRUE;
        }
    else if ((stack.unk10 == 2 && stack_1.unk10 == 3)
        || (stack.unk10 == 3 && stack_1.unk10 == 2)) {
        //found = TRUE;
        }
    else if ((stack.unk10 == 9 && stack_1.unk10 == 10)
        || (stack.unk10 == 10 && stack_1.unk10 == 9)) {
        //found = TRUE;
        }
    else if ((stack.unk10 == 4 && stack_1.unk10 == 5)
        || (stack.unk10 == 5 && stack_1.unk10 == 4)) {
        //found = TRUE;
        }
    else if ((stack.unk10 == 6 && stack_1.unk10 == 7)
        || (stack.unk10 == 7 && stack_1.unk10 == 6)) {
        //found = TRUE;
        }
    else {
        found = FALSE;
    }

    return found;
}

static inline void InitUnk(unkStruct_800D670 *dst, const u8 *chunsoft, s32 mode)
{
    MemoryFill8(dst, 0, sizeof(unkStruct_800D670));
    strcpy(dst->buffer, chunsoft);
    dst->unk10 = mode;
}

s32 sub_8037B28(s32 mode)
{
    s32 i;
    s32 ret;
    unkStruct_800D670 stack;
    s32 r5 = 0;

    sub_800D414();
    gUnknown_202EC38 = 0;
    InitUnk(&stack, sChunsoft, mode);
    sub_800D59C(&stack, sizeof(unkStruct_800D670));

    while (TRUE) {
        for (i = 0; i < 1; i++) {
            sub_80373C4();
            switch (GetMenuInput()) {
                case 2:
                case 3:
                    sub_800D520();
                    sub_800D510();
                    return 1;
            }
        }

        r5 = sub_800D33C();
        sub_800D570();

        if (r5 == 2) {
            break;
        }
        else if (r5 == 3) {
            sub_800D520();
            sub_800D510();
            return 2;
        }
        else if (r5 == 4) {
            sub_800D520();
            sub_800D510();
            return 3;
        }
        else if (r5 == 5) {
            sub_800D520();
            sub_800D510();
            return 1;
        }

        if (gUnknown_202EC38 < 1800) {
            gUnknown_202EC38++;
        }
        else {
            sub_800D520();
            sub_800D510();
            return COMMS_NOT_READY;
        }
    }

    if (sub_800D600() != 0) {
        if (sub_8037A48() == 0) {
            ret = 4;
            sub_800D520();
            sub_800D510();
        }
        else {
            ret = 0;
        }
    }
    else {
        ret = 5;
        sub_800D520();
        sub_800D510();
    }
    return ret;
}

s32 sub_8037C10(bool8 a0)
{
    s32 ret;

    if (a0) {
        if (sub_800D588())
            ret = gUnknown_202EC40[0];
        else
            ret = gUnknown_202EC40[1];
    }
    else {
        if (sub_800D588())
            ret = gUnknown_202EC40[1];
        else
            ret = gUnknown_202EC40[0];
    }

    return ret;
}

static void sub_8037C44(s32 mode, void *data)
{
    s32 i;

    for (i = 0; i < 2; i++)
        sub_800D68C(i);

    switch (mode) {
        case 0:
        case 1:
            sub_800D59C(data, sizeof(unkStruct_8035D94));
            break;
        case 2:
        case 3:
        case 6:
        case 7:
            sub_800D59C(data, sizeof(unkStruct_203B480));
            break;
        case 4:
        case 5:
            sub_800D59C(data, sizeof(WonderMailStruct_203B2C0_sub));
            break;
        case 9:
        case 10:
            sub_800D59C(data, 0xB4);
            break;
    }
}

static void sub_8037CC4(s32 mode, void *param_2, void *param_3)
{
    switch (mode) {
        case 0:
        case 1:
            sub_800D670(0, param_2, sizeof(unkStruct_8035D94));
            sub_800D670(1, param_3, sizeof(unkStruct_8035D94));
            break;
        case 2:
        case 3:
        case 6:
        case 7:
            sub_800D670(0, param_2, sizeof(unkStruct_203B480));
            sub_800D670(1, param_3, sizeof(unkStruct_203B480));
            break;
        case 4:
        case 5:
            sub_800D670(0, param_2, sizeof(WonderMailStruct_203B2C0_sub));
            sub_800D670(1, param_3, sizeof(WonderMailStruct_203B2C0_sub));
            break;
        case 9:
        case 10:
            sub_800D670(0, param_2, 0xB4);
            sub_800D670(1, param_3, 0xB4);
            break;
    }
}

s32 sub_8037D64(u32 mode, void * param_2, void *param_3)
{
    s32 iVar2 = 0;
    s32 linkStatus = 0;

    gUnknown_202EC48 = 0;
    sub_800D494();
    sub_8037C44(mode, param_2);

    while (1) {
        sub_80373C4();
        iVar2 = sub_800D33C();
        sub_800D570();

        if (iVar2 == 2) {
            break;
        }

        if (iVar2 == 3 || iVar2 == 4 || iVar2 == 5) {
            sub_800D520();
            sub_800D510();
            return 1;
        }
        else {

            if (gUnknown_202EC48 < 100)
                gUnknown_202EC48++;
            else {
                sub_800D520();
                sub_800D510();
                return COMMS_NOT_READY;
            }
        }
    }

    if (sub_800D600() != 0) {
        linkStatus = 0;
    }
    else {
        sub_800D520();
        sub_800D510();
        linkStatus = 5;
    }

    sub_8037CC4(mode, param_2, param_3);
    return linkStatus;
}

static s32 sub_8037DF0(void)
{
    s32 linkStatus;
    s32 iStack_10;
    s32 iStack_c;

    linkStatus = COMMS_GOOD;
    sub_800D670(0, &iStack_10, 4);
    sub_800D670(1, &iStack_c, 4);
    if ((iStack_10 != 0) || (iStack_c != 0)) {
        linkStatus = (!sub_800D588()) ? iStack_c : iStack_10;
        if (linkStatus == COMMS_GOOD) {
            linkStatus = 0xe;
        }
    }
    return linkStatus;
}

static void sub_8037E38(unkStruct_8035D94 *param_1,unkStruct_8035D94 *param_2)
{
    unkStruct_8035D94 *r3;
    unkStruct_8035D94 *r4;
    u32 load;

    r4 = sub_800D588() == 0 ? param_2 : param_1;
    r3 = sub_800D588() == 0 ? param_1 : param_2;

    if (r4->itemIndex == r3->itemIndex) {
         load = gTeamInventoryRef->teamStorage[r4->itemIndex];
         load += r3->numItems;
         gTeamInventoryRef->teamStorage[r4->itemIndex] = load;
    }
    else {
        load = gTeamInventoryRef->teamStorage[r3->itemIndex];
        load += r3->numItems;
        gTeamInventoryRef->teamStorage[r3->itemIndex] = load;
    }
}

static void sub_8037E90(unkStruct_203B480 *param_1, unkStruct_203B480 *param_2)
{
    if(sub_800D588() == 0)
    {
        param_2 = param_1;
    }
    param_2->mailType = 2;
    sub_80951BC(param_2);
    sub_8095274(param_2->unk10.unk10);
}

static void nullsub_53(void *param_1, void *param_2)
{
}

static void sub_8037EBC(WonderMailStruct_203B2C0_sub  *param_1, WonderMailStruct_203B2C0_sub *param_2)
{
    unkStruct_203B480 *mail;
    WonderMailStruct_203B2C0_sub *puVar2;

    if(sub_800D588() == 0)
    {
        puVar2 = param_1;
    }
    else
    {
        puVar2 = param_2;
    }
    mail = GetMailatIndex(GetMailIndex(1, (puVar2->mail).unk10.unk10));
    *mail = (*puVar2).mail;
    mail->mailType = 5;
    sub_80951FC(mail);
    mail->mailType = 7;

    if(puVar2->pokemon.speciesNum != MONSTER_NONE)
    {
        gUnknown_203B484->unk0 = puVar2->mail.unk10.unk10;
        gUnknown_203B484->unk4 = puVar2->pokemon;
        gUnknown_203B484->unk4.dungeonLocation.id = DUNGEON_UNKNOWN_WORLD;
        gUnknown_203B484->unk4.dungeonLocation.floor = 1;
    }
    else
    {
        MemoryFill8(gUnknown_203B484, 0, sizeof(unkStruct_203B484));
        gUnknown_203B484->unk4.speciesNum = MONSTER_NONE;
    }
}

static void sub_8037F4C(unkStruct_203B480 *param_1, unkStruct_203B480 *param_2)
{
    unkStruct_203B480 *mail;
    MainMenu1Work *mainMenu;

    if(sub_800D588() == 0)
    {
        param_2 = param_1;
    }
    mail = GetMailatIndex(GetMailIndex(4, param_2->unk10.unk10));
    *mail = *param_2;
    mail->mailType = 6;
    mainMenu = GetMainMenu();
    if(mainMenu)
    {
        mainMenu->unk3A = 1;
    }
}

static void sub_8037F9C(u32 mode, void *param_2, void *param_3)
{
    switch(mode)
    {
        case 0:
        case 1:
            sub_8037E38(param_2, param_3);
            break;
        case 7:
            sub_8037F4C(param_2, param_3);
            break;
        case 3:
            sub_8037E90(param_2, param_3);
            break;
        case 5:
            sub_8037EBC(param_2, param_3);
            break;
        case 10:
            nullsub_53(param_2, param_3);
            break;
    }
}

static s32 sub_8038014(unkStruct_8035D94 *param_1,unkStruct_8035D94 *param_2)
{
    s32 linkStatus;
    s32 r2;
    unkStruct_8035D94 *r3;
    unkStruct_8035D94 *r4;

    r4 = sub_800D588() == 0 ? param_2 : param_1;
    r3 = sub_800D588() == 0 ? param_1 : param_2;

    if (r4->itemIndex == r3->itemIndex) {
        r2 = gTeamInventoryRef->teamStorage[r4->itemIndex];
        r2 += r3->numItems;
        if (r2 > 999) {
            linkStatus = COMMS_NO_ROOM_STORAGE;
        }
        else
            linkStatus = COMMS_GOOD;
    }
    else {
        r2 = gTeamInventoryRef->teamStorage[r3->itemIndex];
        r2 += r3->numItems;
        if (r2 > 999) {
            linkStatus = COMMS_NO_ROOM_STORAGE;
        }
        else
            linkStatus = COMMS_GOOD;

    }
    return linkStatus;
}

static s32 sub_8038078(unkStruct_203B480 *param_1,unkStruct_203B480 *param_2)
{
    u32 uVar2;
    u32 uVar3;

    if (sub_800D588() == 0) {
        param_2 = param_1;
    }
    uVar3 = (param_2->unk10).unk10;
    if (gUnknown_203B184 != NULL) {
        uVar2 = gUnknown_203B184->unk050;
    }
    else {
        uVar2 = sub_8011C34();
    }
    if (HasMail(4,uVar3) && (param_2->unk28 == uVar2)) {
        return COMMS_GOOD;
    }
    else {
        return COMMS_NOT_ELIGIBLE_2;
    }
}

static s32 sub_80380C4(unkStruct_203B480 *param_1,unkStruct_203B480 *param_2)
{
    u32 uVar2;
    unkStruct_203B480 *mail;

    if (sub_800D588() == 0) {
        mail = param_1;
    }
    else
        mail = param_2;

    uVar2 = mail->unk10.unk10;
    if (HasMail(2,uVar2) || HasMail(4,uVar2) || HasMail(6,uVar2))
    {
        return COMMS_DUPLICATE_MAIL;
    }
    if(sub_8095298(mail->unk10.unk10))
    {
        return COMMS_DUPLICATE_MAIL;
    }
    else if (FindOpenMailSlot() == -1)
    {
        return COMMS_NO_ROOM_MAIL;
    }
    else
    {
        return COMMS_GOOD;
    }
}

static s32 sub_803812C(unkStruct_203B480 *param_1, unkStruct_203B480 *param_2)
{
    if (sub_800D588() == 0) {
        param_2 = param_1;
    }
    if (HasMail(1, (param_2->unk10).unk10)) {
        return COMMS_GOOD;
    }
    else {
        return COMMS_NOT_ELIGIBLE_1;
    }
}

static s32 sub_8038158(void *param_1, void *param_2)
{
    return COMMS_GOOD;
}

static s32 sub_803815C(u32 mode, void *param_2, void *param_3)
{
    s32 linkStatus;

    linkStatus = COMMS_GOOD;
    switch(mode) {
        case 0:
        case 1:
            linkStatus = sub_8038014(param_2, param_3);
            break;
        case 7:
            linkStatus = sub_8038078(param_2, param_3);
            break;
        case 3:
            linkStatus = sub_80380C4(param_2, param_3);
            break;
        case 5:
            linkStatus = sub_803812C(param_2, param_3);
            break;
        case 10:
            linkStatus = sub_8038158(param_2, param_3);
            break;
    }
    return linkStatus;
}

UNUSED static void sub_80381DC(u32 mode, void * param_2, void * param_3)
{
    sub_8037F9C(mode, param_2, param_3);
}

UNUSED static s32 sub_80381E8(u32 mode, void * param_2, void * param_3)
{
    return sub_803815C(mode, param_2, param_3);
}

s32 sub_80381F4(u32 mode, void *param_2, void *param_3)
{
    s32 iVar2 = 0;
    s32 linkStatus = sub_803815C(mode, param_2, param_3);
    gCommsTimeout = 0;
    sub_800D494();
    sub_800D59C(&linkStatus, 4);

    while (1) {
        sub_80373C4();
        iVar2 = sub_800D33C();
        sub_800D570();
        if (iVar2 == 2) {
            break;
        }

        if (iVar2 == 3 || iVar2 == 4 || iVar2 == 5) {
            sub_800D520();
            sub_800D510();
            return 1;
        }

        if (gCommsTimeout < 100) {
            gCommsTimeout++;
        }
        else
        {
            sub_800D520();
            sub_800D510();
            return COMMS_NOT_READY;
        }
    }

    if (sub_800D600() != 0) {
        linkStatus = sub_8037DF0();
    }
    else {
        sub_800D520();
        sub_800D510();
        linkStatus = 5;
    }

    if (linkStatus == COMMS_GOOD) {
        sub_8037F9C(mode, param_2, param_3);
    }
    else {
        sub_800D520();
        sub_800D510();
    }

    sub_800D520();
    return linkStatus;
}
