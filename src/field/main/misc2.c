#include "common.h"
#include "field/main.h"
#include "field/actor.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"

void FieldMatrixResetTranslation(MATRIX *matrix) {
    matrix->t[2] = 0;
    matrix->t[1] = 0;
    matrix->t[0] = 0;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80072150);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80072254);

extern MATRIX D_800AFA64;

void func_800722F4(void) {
    func_80072150();
    SetRotMatrix(&D_800AFA64);
    SetTransMatrix(&D_800AFA64);
    if (g_FieldSystemMode == 0) {
        func_802815B0();
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_8007234C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80072398);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800723E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_8007254C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800726E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80072A38);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80072D74);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073230);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073684);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073734);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073750);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073930);

extern s32 D_800ADC18;

int func_80073988(int unused, int angle) {
    if (D_800ADC18) {
        return angle & 0xFFF;
    }
    return func_80073930();
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800739C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80073E38);

void FieldClearAndSwapOTagInternal(void) {
    if (g_FieldSystemMode == SYSTEM_MODE_PC_HDD)
        asm("break 0x400");

    g_FieldCurRenderContextIndex = (g_FieldCurRenderContextIndex + 1) % 2;
    g_FieldCurRenderContext = &g_FieldRenderContexts[g_FieldCurRenderContextIndex];
    ClearOTagR(g_FieldCurRenderContext->ot3, 0x8);
}

void FieldClearAndSwapOTag(void) {
    FieldClearAndSwapOTagInternal();
    ClearOTagR(g_FieldCurRenderContext->ot1, 0x1000);
    if (g_FieldRenderContextUseOT2) {
        ClearOTagR(g_FieldCurRenderContext->ot2, 0x1000);
    }
}

void FieldMatrixCopy(MATRIX* dest, MATRIX* source) {
    FieldMatrixCopyTransform(dest, source);
    FieldMatrixCopyTranslation(dest, source);
}

void FieldMatrixCopyTranslation(MATRIX* dest, MATRIX* source) {
    dest->t[0] = source->t[0];
    dest->t[1] = source->t[1];
    dest->t[2] = source->t[2];
}

void FieldMatrixCopyTransform(MATRIX* dest, MATRIX* source) {
    dest->m[0][0] = source->m[0][0];
    dest->m[0][1] = source->m[0][1];
    dest->m[0][2] = source->m[0][2];
    dest->m[1][0] = source->m[1][0];
    dest->m[1][1] = source->m[1][1];
    dest->m[1][2] = source->m[1][2];
    dest->m[2][0] = source->m[2][0];
    dest->m[2][1] = source->m[2][1];
    dest->m[2][2] = source->m[2][2];
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80074108);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_8007469C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", FieldPollControllers);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800748E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_8007520C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800752C8);

void func_80075458(u_long* ot, u_long* pPrimList, int size) {
    AddPrims(ot, pPrimList + size, pPrimList);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80075484);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_8007554C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80075910);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800759E4);

extern s16 D_800B218E;

void func_80075B08(void* spriteData, u8* color) {
    if (D_800B218E == 0) {
        SpriteSetColor(spriteData, color[0], color[1], color[2]);
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80075B44);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800764B4);

void func_80076A74(void* ptr) {
    void* inner = *(void**)((u8*)ptr + 0x7C);
    s16 entityId = *(s16*)((u8*)inner + 0x14);
    g_FieldActors[entityId].pActorData->flags |= 0x10000;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80076AC0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_800771B0);

void FieldLoadTIM(u_long* pTimData) {
    TIM_IMAGE timImage;

    OpenTIM(pTimData);
    while (ReadTIM(&timImage) ) {
        if (timImage.caddr != NULL) {
            LoadImage(timImage.crect, timImage.caddr);
        }
        if (timImage.paddr != NULL) {
            LoadImage(timImage.prect, timImage.paddr);
        }
    }
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80077268);

INCLUDE_ASM("asm/field/nonmatchings/main/misc2", func_80077544);
