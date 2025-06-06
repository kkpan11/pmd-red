#ifndef GUARD_STRING_FORMAT_H
#define GUARD_STRING_FORMAT_H

#include "structs/menu.h"
#include "structs/rgb.h"
#include "structs/str_file_system.h"
#include "structs/str_mon_portrait.h"
#include "structs/str_text.h"

// TODO: once the files close to string_format.c are decompiled, check if these should be included here. Most likely, they should be declared elsewhere.
// code_80130A8.s
void sub_80140DC(void);
void sub_8014114(void);
s32 sub_80144A4(s32 *);
u32 sub_80154F0(void);
void sub_80155F0(void);

#define FORMAT_BUFFER_LEN 80
#define FRIEND_AREA_BUFFER_LEN 184

extern s32 gFormatArgs[10];
extern u8 gFormatBuffer_Items[4][FORMAT_BUFFER_LEN];
extern u8 gFormatBuffer_Monsters[10][FORMAT_BUFFER_LEN];
extern u8 gFormatBuffer_Names[10][FORMAT_BUFFER_LEN];
extern u8 gSpeakerNameBuffer[FORMAT_BUFFER_LEN];
extern u8 gFormatBuffer_FriendArea[FRIEND_AREA_BUFFER_LEN];

void sub_8014144(void);
void sub_801416C(s32 param_1,s32 param_2);
void CreateDialogueBoxAndPortrait(const u8 *text, void *param_2, MonPortraitMsg *monPortraitPtr, u16 flags);
void CreateYesNoDialogueBoxAndPortrait_DefaultYes(const u8 *text, MonPortraitMsg *monPortraitPtr, u16 flags);
void CreateYesNoDialogueBoxAndPortrait_DefaultNo(const u8 *text, MonPortraitMsg *monPortraitPtr, u16 flags);
void CreateMenuDialogueBoxAndPortrait(const u8 *text, void *a1, u32 r9, const MenuItem *menuItems, void *arg_0, u32 a5, u32 unknownUnused, MonPortraitMsg *monPortraitPtr, u16 flags);
void sub_8014490(void);
s32 sub_80144A4(s32 *a0);
void DrawDialogueBoxString(void);
const u8 *FormatString(const u8 *str, u8 *dst, u8 *dstMax, u16 flags);
void PrintFormattedStringOnWindow(s32 x, s32 y, const u8 *str, u32 windowId, u32 terminatingChr);
void PrintFormattedStringOnWindow2(s32 x, s32 y, const u8 *str, u32 windowId, u32 terminatingChr, s32 lineSpacing);

#endif // GUARD_STRING_FORMAT_H
