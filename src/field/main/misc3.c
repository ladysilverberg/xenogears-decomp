#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"

// Light data stuff
INCLUDE_ASM("asm/field/nonmatchings/main/misc3", func_8006FDEC);

void FieldLZSSDecompress(void* _unused, void* pCompressed, void* pDecompressed) {
    LZSSDecompress(pCompressed, pDecompressed);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc3", FieldFree);

void FieldLoadTIMWithClut(u_long *pTimData, short x, short y, short clutX, short clutY, short clutWidth, short clutHeight) {
    TIM_IMAGE* pTIM;
    TIM_IMAGE tim;   

    OpenTIM(pTimData);
    pTIM = ReadTIM(&tim);

    if (pTIM) {
        if (tim.caddr) {
            if (clutY != -1) {
                tim.crect->x = clutX;
                tim.crect->y = clutY;
            }

            if (clutWidth)
                tim.crect->w = clutWidth;
            
            if (clutHeight)
                tim.crect->h = clutHeight;

            LoadImage(tim.crect, tim.caddr);
        }

        if (tim.paddr) {
            tim.prect->x = x;
        }
        tim.prect->y = y;
        LoadImage(tim.prect, tim.paddr);
    }
}

extern s32 D_800ADB60;
extern void* D_800ADC14;
extern s32 D_8004F34C;

void func_80070488(void) {
    void* pStreamFile;

    if (D_800ADB60 == 0) {
        D_800ADB60 = 1;
        pStreamFile = ArchiveAllocStreamFile(4, 1);
        D_800ADC14 = pStreamFile;
        func_80029EB0(((D_8004F34C & 0xFFF) << 1) + 0xB9, pStreamFile, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

extern s32 D_800ADB60;
extern void* D_800ADC14;
extern void func_80078C5C(void);

void func_80070508(void) {
    if (D_800ADB60 == 1) {
        ArchiveCdDataSync(0);
        DrawSync(0);
        HeapFree(D_800ADC14);
        D_800ADB60 = 0;
    }
    func_80078C5C();
}

void func_80070560(s32* dest, s16* src) {
    dest[0] = src[0] << 16;
    dest[1] = src[1] << 16;
    dest[2] = src[2] << 16;
}

void func_80070594(MATRIX* dest) {
    SVECTOR rotation;

    rotation.vx = 0;
    rotation.vy = 0;
    rotation.vz = 0;
    RotMatrix(&rotation, dest);
    dest->t[2] = 0;
    dest->t[1] = 0;
    dest->t[0] = 0;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc3", func_800705DC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc3", func_80070C84);

INCLUDE_ASM("asm/field/nonmatchings/main/misc3", FieldLoad);

