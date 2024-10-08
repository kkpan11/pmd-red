#ifndef GUARD_CODE_800E9A8_H
#define GUARD_CODE_800E9A8_H

typedef struct unkStruct_800EAE4
{
    s16 unk0;
    s16 unk2;
} unkStruct_800EAE4;

struct unkStruct_203B0CC_sub
{
    // size: 0xD0
    u32 unk0;
    s32 unk4;
    s32 unk8;
    u8 fillc[0x18 - 0x0c];
    s32 unk18;
    unkStruct_800EAE4 unk1c;
    s32 unk20;
    s32 unk24;
    u8 fill28[0x32 - 0x28];
    u32 unk34;
    u32 unk38;
    u8 fill3C[0x4C - 0x3C];
    u32 unk4C;
    s32 unk50;
    u8 unk54;
    u8 fill55[0xB8 - 0x55];
    u32 unkB8;
    u8 fillBC[0xCC - 0xBC];
    u32 unkCC;
};

struct unkStruct_203B0CC
{
    // size: 0x1A18
    struct unkStruct_203B0CC_sub unk0[0x20];
    u32 unk1A00;
    /* 0x1A04 */ u32 fileSelection;
    u32 unk1A08;
    u32 unk1A0C;
    u32 unk1A10;
    u8 fill1A14[0x1A18 - 0x1A14];
};

bool8 sub_800E9A8(s32 a0);
bool8 sub_800E9E4(u32);
bool8 sub_800E9FC(u8 a0);

#endif
