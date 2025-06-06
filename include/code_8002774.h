#ifndef GUARD_CODE_8002774_H
#define GUARD_CODE_8002774_H

#include "structs/str_position.h"

#define UNK_STRUCT_ARR_COUNT 4

struct S_sub
{
    u8 x0[UNK_STRUCT_ARR_COUNT];
};

struct S
{
    struct S_sub x0;
};

void sub_800290C(PixelPos *param_1, s32 param_2);
void sub_8002934(PixelPos *param_1, PixelPos *param_2, PixelPos *param_3, s32 param_4, s32 param_5);
s32 sub_8002A70(s32 a0, s32 a1, s32 a2);
s32 sub_8002B04(s32, s32);
s32 VecDirection8Radial(PixelPos *param_1);
s8 SizedDeltaDirection4(const PixelPos *r0, const PixelPos *r1, const PixelPos *r2, const PixelPos *r3);
s8 SizedDeltaDirection8(const PixelPos *r0, const PixelPos *r1, const PixelPos *r2, const PixelPos *r3);
struct S sub_80027A0(u16 a0);
u16 sub_8002774(struct S_sub s);

#endif // GUARD_CODE_8002774_H
