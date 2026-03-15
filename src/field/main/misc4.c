#include "common.h"
#include "field/actor.h"
#include "field/main.h"
#include "field/text_box.h"
#include "field/effects.h"
#include "system/memory.h"
#include "system/archive.h"
#include "system/sound.h"
#include "psyq/libetc.h"
#include "psyq/libcd.h"

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80078B5C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80078BC8);

extern s16 D_800B2344;
void func_80078C5C(void) {
    RECT rect;
    int i;
    u_int* pImage;

    if (D_800B2344 != 0) {
        g_FieldRenderContexts[0].drawEnvs[0].dtd = 0;
        g_FieldRenderContexts[1].drawEnvs[0].dtd = 0;
        pImage = HeapAlloc(0x4000, 0x0);
        rect.y = 0x1E0;
        rect.w = 0x100;
        rect.x = 0;
        rect.h = 0x20;
        StoreImage(&rect, pImage);
        DrawSync(0);

        // Process image before storing it back in VRAM
        for (i = 0; i < 0x1000; i++) {
            if (pImage[i] & 0xFFFF) {
                pImage[i] |= 0xC63;
            }
            if (pImage[i] & 0xFFFF0000) {
                pImage[i] |= 0x0C630000;
            }
        }
        
        LoadImage(&rect, pImage);
        DrawSync(0);
        HeapFree(pImage);
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80078D44);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80079288);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007954C);

void func_800796F4(void) {}

void FieldSwapRenderContext(void) {
    g_FieldCurRenderContextIndex = (g_FieldCurRenderContextIndex + 1) % 2;
    g_FieldCurRenderContext = &g_FieldRenderContexts[g_FieldCurRenderContextIndex];
    PutDispEnv(&g_FieldCurRenderContext->dispEnv);
    PutDrawEnv(&g_FieldCurRenderContext->drawEnvs[0]);
}

extern RECT D_800AFE4C;
extern TILE D_800AFE54[];
extern DR_MODE D_800AFE24[];
	
void func_80079784(int color) {
    FieldClearAndSwapOTag();
    setRGB(D_800AFE54[g_FieldCurRenderContextIndex], color * 4);
    addPrim(g_FieldCurRenderContext->ot1, &D_800AFE54[g_FieldCurRenderContextIndex]);
    addPrim(g_FieldCurRenderContext->ot1, &D_800AFE24[g_FieldCurRenderContextIndex]);
    FieldRenderSync();
    MoveImage(&D_800AFE4C, 0, g_FieldCurRenderContextIndex * 0x100);
    PutDispEnv(&g_FieldCurRenderContext->dispEnv);
    PutDrawEnv(&g_FieldCurRenderContext->drawEnvs[0]);
    DrawOTag(g_FieldCurRenderContext->ot1 + 1);
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800798BC);

void func_8007995C(short w, short h, short x, short y, int destX, int destY) {
    RECT rect;

    rect.w = w;
    rect.h = h;
    rect.x = x;
    rect.y = y;
    MoveImage(&rect, destX, destY);
    DrawSync(0);
}

void FieldRenderSyncAndFlush(void) {
    FieldRenderSync();
    EnterCriticalSection();
    FlushCache();
    ExitCriticalSection();
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800799D4);


// Quad rendering
// --------------------
void FieldClampPolyFT4UVs(POLY_FT4* poly, short u0, short v0, short u1, short v1, short u2, short v2, short u3, short v3) {
    if (u0 < 0) u0 = 0;
    if (u1 < 0) u1 = 0;
    if (u2 < 0) u2 = 0;
    if (u3 < 0) u3 = 0;
    if (v0 < 0) v0 = 0;
    if (v1 < 0) v1 = 0;
    if (v2 < 0) v2 = 0;
    if (v3 < 0) v3 = 0;
    
    if (u0 >= 0x100) u0 = 0xFF;
    if (u1 >= 0x100) u1 = 0xFF;
    if (u2 >= 0x100) u2 = 0xFF;
    if (u3 >= 0x100) u3 = 0xFF;
    if (v0 >= 0x100) v0 = 0xFF;
    if (v1 >= 0x100) v1 = 0xFF;
    if (v2 >= 0x100) v2 = 0xFF;
    if (v3 >= 0x100) v3 = 0xFF;

    poly->u0 = u0;
    poly->v0 = v0;
    poly->u1 = u1;
    poly->v1 = v1;
    poly->u2 = u2;
    poly->v2 = v2;
    poly->u3 = u3;
    poly->v3 = v3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007A5C4);

extern SVec4 D_800ADCE0[]; // X0 -> X3 positions
extern SVec4 D_800ADD28[]; // Y0 -> Y3 positions
extern SVec4 D_800ADD70[]; // U0 -> U3s
extern SVec4 D_800ADDB8[]; // V0 -> V3s

// Texture / Clut stuff
extern short D_800ADE00[];
extern short D_800ADE02[];
extern short D_800ADE04[];
extern short D_800ADE06[];
extern short D_800ADE08[];
extern short D_800ADE0A[];

// Compass primitive initialization?
void func_8007A7F4(Quad* pPart, int x, int y, int tex) {
    int nIndexTex;
    POLY_FT4* pNextPoly;
    char _pad[0x88];

    pNextPoly = &pPart->polys[1]; 
    SetPolyFT4(&pPart->polys[0]);
    
    nIndexTex = tex * 0x6,

    // Set Position 0, 1, 2, and 3
    pPart->vecs[0].vx = D_800ADCE0[x].x;
    pPart->vecs[0].vy = 0x0;
    pPart->vecs[0].vz = D_800ADD28[y].x;

    pPart->vecs[1].vx = D_800ADCE0[x].y;
    pPart->vecs[1].vy = 0;
    pPart->vecs[1].vz = D_800ADD28[y].y;

    pPart->vecs[2].vx = D_800ADCE0[x].z;
    pPart->vecs[2].vy = 0;
    pPart->vecs[2].vz = D_800ADD28[y].z;

    pPart->vecs[3].vx = D_800ADCE0[x].w;
    pPart->vecs[3].vy = 0;
    pPart->vecs[3].vz = D_800ADD28[y].w;
    
    setRGB0(&pPart->polys[0], 0x80, 0x80, 0x80);
    
    pPart->polys[0].tpage = GetTPage(
        D_800ADE00[nIndexTex], 
        D_800ADE02[nIndexTex], 
        D_800ADE04[nIndexTex], 
        D_800ADE06[nIndexTex]
    );
    
    pPart->polys[0].clut = GetClut(D_800ADE08[nIndexTex], D_800ADE0A[nIndexTex]);
    
    FieldClampPolyFT4UVs(&pPart->polys[0], 
        D_800ADD70[x].x, D_800ADDB8[y].x, 
        D_800ADD70[x].y, D_800ADDB8[y].y, 
        D_800ADD70[x].z, D_800ADDB8[y].z, 
        D_800ADD70[x].w, D_800ADDB8[y].w
    );

    *pNextPoly = pPart->polys[0];
}

// Actor primitive initialization
void func_8007AA44(Quad* pQuad) {
    POLY_FT4* pPoly;
    POLY_FT4* pPoly2;

    pPoly = &pQuad->polys[0];
    pPoly2 = &pQuad->polys[1];
    
    SetPolyFT4(pPoly);
    pQuad->vecs[3].vx = -0x18;
    pQuad->vecs[3].vz = -0x18;
    pQuad->vecs[3].vy = 0;

    pQuad->vecs[2].vx = 0x18;
    pQuad->vecs[2].vy = 0;
    pQuad->vecs[2].vz = -0x18;

    pQuad->vecs[1].vx = -0x18;
    pQuad->vecs[1].vy = 0;
    pQuad->vecs[1].vz = 0x18;

    pQuad->vecs[0].vx = 0x18;
    pQuad->vecs[0].vy = 0;
    pQuad->vecs[0].vz = 0x18;

    setRGB0(pPoly, 0x80, 0x80, 0x80);
    pPoly->tpage = GetTPage(0, 2, 0x280, 0x1E0);
    pPoly->clut = GetClut(0x100, 0xF3);
    SetSemiTrans(pPoly, 1);

    pPoly->v0 = 0xE0;
    pPoly->v1 = 0xE0;
    pPoly->u0 = 0;
    pPoly->u1 = 0xF;
    pPoly->u2 = 0;
    pPoly->v2 = 0xEF;
    pPoly->u3 = 0xF;
    pPoly->v3 = 0xEF;
    
    *pPoly2 = *pPoly;
}

// Draw Quad / Actor primitive
void func_8007AB6C(u_long* ot, Quad* pQuad, MATRIX* matrix, int renderContext) {
    long nInterpolation;
    long nFlag;
    POLY_FT4* pPoly;

    pPoly = &pQuad->polys[renderContext];
    PushMatrix();
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    RotAverage4(
        &pQuad->vecs[0], &pQuad->vecs[1], &pQuad->vecs[2], &pQuad->vecs[3], 
        &pPoly->x0, &pPoly->x1, &pPoly->x2, &pPoly->x3, 
        &nInterpolation, &nFlag
    );
    addPrim(ot + 1, pPoly);
    PopMatrix();
}

void func_8007AC58(u_long* ot, Quad* pQuad, MATRIX* matrix, int renderContext) {
    int nInterpolation;
    int nFlag;
    int nPosY;
    int nPosX1;
    POLY_FT4* pPoly;
    int nPosX2;

    pPoly = &pQuad->polys[renderContext];
    PushMatrix();
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    RotAverage4(
        &pQuad->vecs[0], &pQuad->vecs[1], &pQuad->vecs[2], &pQuad->vecs[3], 
        &pPoly->x0, &pPoly->x1, &pPoly->x2, &pPoly->x3, 
        &nInterpolation, &nFlag
    );
    
    nPosX1 = (pPoly->x3 + pPoly->x2) / 2;
    nPosY = pPoly->y3;

    nPosX2 = nPosX1 + 8;
    nPosX1 = nPosX1 - 8;
    setXY4(pPoly,
        nPosX1, nPosY - 10,
        nPosX2, nPosY - 10,
        nPosX1, nPosY,
        nPosX2, nPosY
    );
    
    addPrim(ot + 1, pPoly);
    PopMatrix();
}


// Controller stuff
// --------------------
extern s32 g_pFieldControllerBuffer1;
extern s32 g_pFieldControllerBuffer2;

extern u_short g_FieldMouseSpeedX;
extern u_short g_FieldMouseSpeedY;
extern s32 D_800C3A44;
extern s32 D_800C3A4C;
extern s32 D_800C3A50;
extern s32 D_800C3A54;
extern int g_FieldMousePositionsX[2];
extern int g_FieldMousePositionsY[2];

void FieldSetControllerBuffers(void* controllerBuffer1, void* controllerBuffer2) {
    g_pFieldControllerBuffer1 = controllerBuffer1;
    g_pFieldControllerBuffer2 = controllerBuffer2;
}

void func_8007ADA4(int arg0, int arg1, int arg2, int arg3) {
    D_800C3A44 = arg0 * g_FieldMouseSpeedX;
    D_800C3A50 = arg1 * g_FieldMouseSpeedX;
    D_800C3A4C = arg2 * g_FieldMouseSpeedY;
    D_800C3A54 = arg3 * g_FieldMouseSpeedY;
}

void FieldSetMouseSpeed(u_short xSpeed, u_short ySpeed) {
    g_FieldMouseSpeedX = xSpeed;
    g_FieldMouseSpeedY = ySpeed;
}

void FieldSetMousePosition(int mouseIndex, int xMovement, int yMovement) {
    g_FieldMousePositionsX[mouseIndex] = xMovement * g_FieldMouseSpeedX;
    g_FieldMousePositionsY[mouseIndex] = yMovement * g_FieldMouseSpeedY;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007AE78);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007AF74);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B07C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B1C4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B478);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B614);

int func_8007B694(s32* ptr) {
    return (-func_8004B32C(ptr[2], ptr[0])) & 0xFFF;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B6C4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007B814);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007BAC0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007BEF4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007C670);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007C694);

extern s32 D_800ADC10;

void* func_8007CD3C(int size) {
    s32 offset = D_800ADC10;
    D_800ADC10 = offset + size;
    return (void*)((offset << 2) + (u32)PSX_SCRATCH);
}

extern s32 D_800ADC10;

void func_8007CD60(int value) {
    D_800ADC10 -= value;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007CD80);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007D3D4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007D818);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007D8B4);

// Fade Effect
// --------------------
void FieldFadeInitializePrimitives(int index) {
    SetTile(&g_FieldEffects.fades[index].tiles[0]);
    SetSemiTrans(&g_FieldEffects.fades[index].tiles[0], 1);
    g_FieldEffects.fades[index].tiles[0].w = 0x140;
    g_FieldEffects.fades[index].tiles[0].h = 0xE0;
    g_FieldEffects.fades[index].tiles[0].x0 = 0x0;
    g_FieldEffects.fades[index].tiles[0].y0 = 0x0;
    g_FieldEffects.fades[index].tiles[1] = g_FieldEffects.fades[index].tiles[0];
    g_FieldEffects.fades[index].isVisible = 0;
    g_FieldEffects.fades[index].duration = 0;
    setRGB(g_FieldEffects.fades[index], 0x0);
    g_FieldEffects.fades[index].semitransparency = 2;
}

extern RECT D_800AFE3C[];
void FieldFadeDraw(u_long* ot, int renderContext) {
    int i;
    int ctx;

    for (i = 0; i < 2; i++) {
        if (g_FieldEffects.fades[i].isVisible) {
            D_800AFE3C[i].w = 0x140;
            D_800AFE3C[i].x = 0x0;
            D_800AFE3C[i].y = 0x0;
            D_800AFE3C[i].h = 0xE0;

            SetDrawMode(
                &g_FieldEffects.fades[i].drawModes[renderContext], 
                0, 0, 
                GetTPage(0, g_FieldEffects.fades[i].semitransparency, 0, 0), 
                &D_800AFE3C[i]
            );

            setRGB0(&g_FieldEffects.fades[i].tiles[renderContext],
                g_FieldEffects.fades[i].r0 >> 8,
                g_FieldEffects.fades[i].g0 >> 8, 
                g_FieldEffects.fades[i].b0 >> 8
            );

            ctx = (i == 1);
            addPrim(ot + ctx, &g_FieldEffects.fades[i].tiles[renderContext]);
            addPrim(ot + ctx, &g_FieldEffects.fades[i].drawModes[renderContext]);

            if (
                (g_FieldEffects.fades[i].r0 >> 8 == 0) && 
                (g_FieldEffects.fades[i].g0 >> 8 == 0) &&
                (g_FieldEffects.fades[i].b0 >> 8 == 0)
            ) {
                g_FieldEffects.fades[i].isVisible = 0;
                g_FieldEffects.fades[i].duration = 0;
            }
        }
    }
}


// Text Box stuff
// --------------------
INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007DCF8);

// https://decomp.me/scratch/NE0tE
INCLUDE_ASM("asm/field/nonmatchings/main/misc4", FieldTextBoxInitialize);

// _pad[0x4A] is possibly a RECT?
void func_8007E114(int index, int arg1, int arg2, int arg3, s32 arg4) {
    g_FieldTextBoxes[index]._pad[0x4A] = arg1;
    g_FieldTextBoxes[index]._pad[0x4B] = arg2;
    g_FieldTextBoxes[index]._pad[0x4C] = arg3;
    g_FieldTextBoxes[index]._pad[0x4D] = arg4;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007E16C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007E1C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", FieldTextBoxInitializePrimitives);
/*
extern u8 D_800594D4;
extern u8 D_800594D5;
extern u8 D_800594D6;
extern RECT D_800ADE9C[];
extern RECT D_800ADEDC;
extern RECT D_800ADF04;

void FieldTextBoxInitializePrimitives(int index) {
    int i;
    RECT rect;
    POLY_FT4* pPoly;
    POLY_FT4* pPoly2;
    TILE* pBackgroundTile;
    TILE* pBackgroundTile2;
    SPRT* pBorderSprite1;
    SPRT* pBorderSprite2;
    SPRT* pArrowSprite;
    SPRT* pArrowSprite2;
    SPRT* pCursorSprite2;
    u16* pWidth;
    u16* pHeight;

    FieldTextBoxBackground* pBackground;
    FieldTextBoxCursor* pCursor;
    FieldTextBoxContinueArrow* pArrow;
    FieldTextBoxBorders* pBorders;
    FieldTextBoxPortrait* pPortrait;

    // Background
    pBackground = &g_FieldTextBoxes[index].background;
    SetDrawMode(&pBackground->drawModes[0], NULL, 0, GetTPage(0, 2, 0x280, 0x1F0), NULL);
    SetDrawMode(&pBackground->drawModes[1], NULL, 0, GetTPage(0, 2, 0x280, 0x1F0), NULL);
    pBackgroundTile = &pBackground->tiles[0];
    SetTile(pBackgroundTile);
    setRGB0(pBackgroundTile, D_800594D4, D_800594D5, D_800594D6);
    SetSemiTrans(pBackgroundTile, 1);
    pBackgroundTile2 =  &pBackground->tiles[1];
    *pBackgroundTile2 = *pBackgroundTile;

    // Arrow
    pArrow = &g_FieldTextBoxes[index].continueArrow;
    rect.x = D_800ADF04.x;
    rect.y = D_800ADF04.y;
    rect.w = D_800ADF04.w;
    rect.h = D_800ADF04.h;
    SetDrawMode(&pArrow->drawModes[0], NULL, 0, GetTPage(0, 0, 0x298, 0x1C0), &rect);
    SetDrawMode(&pArrow->drawModes[1], NULL, 0, GetTPage(0, 0, 0x298, 0x1C0), &rect);
    SetSprt(&pArrow->sprites[0]);
    pArrowSprite = &pArrow->sprites[0];
    setRGB0(pArrowSprite, 0x80, 0x80, 0x80);
    setWH0(pArrowSprite, 0xC, 0x8);
    pArrowSprite->clut = GetClut(0x100, 0xF6);
    pArrowSprite2 = &pArrow->sprites[1];
    setUV0(pArrowSprite, 0x80, 0xC0);
    setXY0(pArrowSprite, 0x0, 0x0);
    *pArrowSprite2 = *pArrowSprite;

    // Cursor
    pCursor = &g_FieldTextBoxes[index].cursor;
    rect.x = D_800ADEDC.x;
    rect.y = D_800ADEDC.y;
    rect.w = D_800ADEDC.w;
    rect.h = D_800ADEDC.h;
    SetDrawMode(&pCursor->drawModes[0], NULL, 0, GetTPage(0, 0, 0x288, 0x1C0), &rect);
    SetDrawMode(&pCursor->drawModes[1], NULL, 0, GetTPage(0, 0, 0x288, 0x1C0), &rect);
    SetSprt(&pCursor->sprites[0]);
    setRGB0(&pCursor->sprites[0], 0x80, 0x80, 0x80);
    pCursor->sprites[0].clut = GetClut(0x100, 0xF6);
    pCursorSprite2 = &pCursor->sprites[1];
    setWH0(&pCursor->sprites[0], 0x8, 0xC);
    setUV0(&pCursor->sprites[0], 0x80, 0xC0);
    setXY0(&pCursor->sprites[0], 0x0, 0x0);
    *pCursorSprite2 = pCursor->sprites[0];
    g_FieldTextBoxes[index].continueArrowTimer = 2;

    // Borders
    pBorders = &g_FieldTextBoxes[index].borders;
    for (i = 0; i < 8; i++) {
        pWidth = &D_800ADE9C[i].w;
        pHeight = &D_800ADE9C[i].h;
        
        rect.x = D_800ADE9C[i].x;
        rect.y = D_800ADE9C[i].y;
        rect.w = *pWidth;
        rect.h = *pHeight;
        
        SetDrawMode(&pBorders->drawModes1[i], NULL, 0, GetTPage(0, 2, 0x280, 0x1F0), &rect);
        SetDrawMode(&pBorders->drawModes2[i], NULL, 0, GetTPage(0, 2, 0x280, 0x1F0), &rect);
        pBorderSprite1 = &pBorders->sprites1[i];
        SetSprt(pBorderSprite1);
        setRGB0(pBorderSprite1, 0x80, 0x80, 0x80);
        pBorderSprite1->clut = GetClut(0x100, 0xF4);
        SetSemiTrans(pBorderSprite1, 1);
        setUV0(pBorderSprite1, 0x80, 0xC0);
        setWH0(pBorderSprite1, *pWidth, *pHeight);
        setXY0(pBorderSprite1, 0x0, 0x0);
        pBorderSprite2 =  &pBorders->sprites2[i];
        *pBorderSprite2 = *pBorderSprite1;
    }

    // Portrait
    pPortrait = &g_FieldTextBoxes[index].portrait;
    rect.y = 0;
    rect.x = 0;
    rect.h = 0xFF;
    rect.w = 0xFF;
    SetDrawMode(&pPortrait->drawModes[0], NULL, 0, GetTPage(1, 0, 0x2C0, 0x100), &rect);
    SetDrawMode(&pPortrait->drawModes[1], NULL, 0, GetTPage(1, 0, 0x2C0, 0x100), &rect);
    pPoly = &pPortrait->polys[0];
    SetPolyFT4(pPoly);
    setRGB0(pPoly, 0x80, 0x80, 0x80);
    pPoly->clut = GetClut(0, 0xE0);
    pPoly2 = &pPortrait->polys[1];
    pPoly->tpage = GetTPage(1, 0, 0x2C0, 0x100);
    *pPoly2 = *pPoly;
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007F5AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007F6F8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007F814);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8007F8DC);

void func_8007FFE8(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (!g_FieldTextBoxes[i].visibility) {
            func_8007F6F8((s16) i); // TODO: Clean up cast w/ function sig
        }
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8008004C);

void func_800805F4(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (!g_FieldTextBoxes[i].visibility) {
            // TODO: _pad[0x8] is probably a short holding some flags
            if (g_FieldTextBoxes[i].windowOpenTimer == 0 && !(g_FieldTextBoxes[i]._pad[0x8] & 4)) {
                func_8007F6F8( (i*0x10000) >> 0x10);
            }
            if (g_FieldTextBoxes[i].status == 0) {
                func_8007F6F8( (i*0x10000) >> 0x10);
            }
            if (g_FieldTextBoxes[i].windowOpenTimer) {
                g_FieldTextBoxes[i].windowOpenTimer--;
            }
        }
    }
}

// Get index of textbox with order 0
int func_800806E4(void) {
    int i;
    
    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].order == 0) {
            return i;
        }
    }
    return TEXT_BOX_UNINITIALIZED;
}


// Is textbox free to use?
int func_80080720(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].order == TEXT_BOX_UNINITIALIZED) {
            return 0;
        }
    }
    return -1;
}

// Get index of textbox with lowest order
int func_80080760(void) {
    int i;
    int nResult;
    int lowestOrder;
    
    lowestOrder = 0; // 0 = Top
    nResult = 0xFFFF;
    
    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].order != 0xFFFF && g_FieldTextBoxes[i].order >= lowestOrder) {
            lowestOrder = g_FieldTextBoxes[i].order;
            nResult = i;
        }
    }
    return nResult;
}

// Update textbox order
int func_800807B4(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].order != TEXT_BOX_UNINITIALIZED) {
            g_FieldTextBoxes[i].order++;
        }
    }

    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].order == TEXT_BOX_UNINITIALIZED) {
            g_FieldTextBoxes[i].order = 0;
            return i;
        }
    }

    return TEXT_BOX_UNINITIALIZED;
}

extern int D_800ADBFC;
void func_8008083C(int actorIndex) {
    ActorData* pActor;

    if (actorIndex < D_800ADBFC) {
        pActor = g_FieldActors[actorIndex].pActorData;
        if (pActor->flags134 & 0x80) {
            HeapFree(pActor->unk110);
        }
        if (pActor->flags12C_0xD) {
            HeapFree(pActor->unk114);
        }
        if (g_FieldActors[actorIndex].status & 0x2000) {
            HeapFree(pActor->unk118);
        }
        if (pActor->unk124 != -1) {
            HeapFree(pActor->unk120);
        }
        HeapFree(pActor);
        HeapFree(g_FieldActors[actorIndex].pShadow);
        func_800230A8(g_FieldActors[actorIndex].pSpriteData);
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80080968);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800809D0);

extern s32 D_800ADB58;
extern s32 D_800ADB5C;

int func_80080A18(void) {
    ActorData* pActor = g_FieldActors[D_800ADB58].pActorData;
    int index = D_800ADB5C;
    D_800ADB5C = index + 1;
    return ((s32*)pActor->unk118)[index];
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80080A74);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80080F44);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8008110C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800815F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80081C54);

int func_80081F5C(u32* ptr) {
    u32 a = (ptr[0] >> 9) & 3;
    u32 b = ptr[5] >> 3;
    return -(int)((a & b) != 0);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80081F80);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800821F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8008237C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80082494);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800825AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80082620);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80082BB8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80083178);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800831D0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800831F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80083288);

void func_80083994(void) {
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8008399C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80084158);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_8008492C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80084A40);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800854D0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085560);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800855C8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085634);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085678);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085738);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085788);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085890);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085988);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800859DC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085B20);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085C3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80085C90);

extern void* D_8004F2FC;

void func_80085EEC(void) {
    if (D_8004F2FC) {
        func_80039C4C(D_8004F2FC);
        func_800399D4(D_8004F2FC);
        D_8004F2FC = 0;
    }
}

extern s32 D_8004F364;
extern s32 D_8004F368;
extern s16 D_8004F384;
extern s32 D_80059560;
extern SoundWDSEntry* D_8006251C;
extern void* D_800B00E0; // WDS File Buffer

int func_80085F30(void) {
    void* pWdsEntry;

    if (ArchiveDataSync()) {
        return -1;
    }
    
    pWdsEntry = SoundLoadWdsFile(D_800B00E0, 0);
    D_8006251C = pWdsEntry;
    D_80059560 = pWdsEntry;
    func_8003BDFC(0x10);
    HeapFree(D_800B00E0);
    D_8004F364 = 1;
    D_8004F384 = 0;
    D_8004F368 = 0;
    return 0;
}

void func_80085FB8(void) {
    void* pWdsFileBuffer;

    ArchiveSetIndex(0x1C, 0x0);
    pWdsFileBuffer = HeapAlloc(ArchiveDecodeAlignedSize(3), 1);
    D_800B00E0 = pWdsFileBuffer;
    ArchiveReadFileToBuffer(3, pWdsFileBuffer, 0, CdlModeSpeed);
    ArchiveSetIndex(4, 0);
    D_8004F364 = 0x80;
}

void func_80086024(void) {
    if (D_8004F368 == 0) {
        D_8004F384 = 1;
        SoundFreeWdsEntry(D_8006251C);
        D_8004F368 = 1;
    }
    D_8004F364 = 0;
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086078);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800860F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086200);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800862CC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800863E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086470);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800864B4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800864F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086590);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086908);

// Call function from second handler table
INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_800869B8);
/*
void func_800869B8(void) {
    u_short handlerIndex;

    handlerIndex = g_FieldScriptVMCurActor->scriptInstructionPointer + 1;
    g_FieldScriptVMCurActor->scriptInstructionPointer = handlerIndex;
    &gEventHandlers2[g_FieldScriptVMCurScriptData + handlerIndex]();
}
*/

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086A1C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086BA8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc4", func_80086C34);

void func_80086D4C(void) {
    GameSoftReset();
    D_800B00C0 = 1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}
