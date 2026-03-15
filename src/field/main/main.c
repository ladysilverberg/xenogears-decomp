#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"
#include "system/memory.h"
#include "system/controller.h"

extern int g_FrameDeltaTime;

INCLUDE_ASM("asm/field/nonmatchings/main/main", FieldInitializeControllers);
/*
void FieldInitializeControllers(void) {
    FieldSetControllerBuffers(&g_C1Buffer, &g_C2Buffer);
    func_8007AE14(3, 4);
    func_8007ADA4(0, 0x140, 0, 0xE0);
    func_8007AE2C(0, 0x50, 100);
    func_8007AE2C(1, 0xFA, 100);
    func_8007ADA4(0, 300, 10, 0xDC);
}
*/

void FieldRenderSync(void) {
    DrawSync(0);
    Vsync(0);
}

INCLUDE_ASM("asm/field/nonmatchings/main/main", FieldLoadUITextures);

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_800777DC);

void FieldUpdateDeltaTime(void) {
    g_FrameDeltaTime = Vsync(1);
}

INCLUDE_ASM("asm/field/nonmatchings/main/main", func_80077844);

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
