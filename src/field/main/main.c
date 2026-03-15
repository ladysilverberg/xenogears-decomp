#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"
#include "system/memory.h"
#include "system/controller.h"

extern int g_FrameDeltaTime;

void FieldInitializeControllers(void) {
    HeapChangeCurrentUser(8, 0);
    ArchiveSetIndex(4, 0);
    FieldInitializeControllersAndMouse();
}

void FieldRenderSync(void) {
    DrawSync(0);
    Vsync(0);
}

INCLUDE_ASM("asm/field/nonmatchings/main/main", FieldLoadUITextures);

extern s32 D_8004F34C;

void func_800777DC(void) {
    ArchiveCdDataSync(0);
    do {} while (func_8001B484((D_8004F34C & 0xFFF) << 1, 0));
}

void FieldUpdateDeltaTime(void) {
    g_FrameDeltaTime = Vsync(1);
}

void func_80077844(s16* dest, int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {
    dest[0] = v0;
    dest[1] = v1;
    dest[2] = v2;
    dest[3] = v3;
    dest[4] = v4;
    dest[5] = v5;
    dest[6] = v6;
    dest[7] = v7;
    dest[8] = v8;
}

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077884);

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077AB4);

void func_80077C60(void) {
    func_80077884();
    func_80077AB4();
}

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077C88);
/*
extern void* D_8005A414;
extern void* D_8005A418;
extern void* D_8005A41C;

void func_80077C88(void) {
    HeapChangeCurrentUser(HEAP_USER_YOSI, NULL);
    D_8005A414 = HeapAlloc(0x14000, 0);
    D_8005A418 = HeapAlloc(0x14000, 0);
    D_8005A41C = HeapAlloc(0x14000, 0);
    HeapPinBlock(D_8005A414);
    HeapPinBlock(D_8005A418);
    HeapPinBlock(D_8005A41C);
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077D2C);
/*
void func_80077D2C(void) {
    HeapUnpinBlock(D_8005A414);
    HeapUnpinBlock(D_8005A418);
    HeapUnpinBlock(D_8005A41C);
    HeapFree(D_8005A414);
    HeapFree(D_8005A418);
    HeapFree(D_8005A41C);
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077DAC);

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077E10);

INCLUDE_ASM("asm/field/nonmatchings/main/main", FieldMain);
