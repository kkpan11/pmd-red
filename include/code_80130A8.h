#ifndef GUARD_CODE_80130A8_H
#define GUARD_CODE_80130A8_H

#include "file_system.h"
#include "structs/menu.h"
#include "structs/str_text.h"

// code_80130A8.s
extern void sub_8013E54(void);
extern void sub_8013F84(void);
extern void sub_80140B4(UnkTextStruct2 *);
extern void sub_80140DC(void);
extern void sub_8014114(void);
extern void xxx_info_box_80141B4(const u8 *, u32, OpenedFile **, u16);
extern void sub_8014248(const u8 *, u32, u32, const MenuItem *, void *, u32, u32, OpenedFile **, u32);
extern s32 sub_80144A4(s32 *);
extern void sub_80151C0(u32, u8 *);
extern u32 sub_80154F0(void);
extern void sub_80155F0(void);
extern void xxx_draw_string_80144C4(void);
extern void PrintFormatStringOnWindow(u32, u32, const u8 *, u32 windowId, u32);
extern void xxx_format_string(const u8 *, u8 *, u8 *, u32);

#endif // GUARD_CODE_80130A8_H
