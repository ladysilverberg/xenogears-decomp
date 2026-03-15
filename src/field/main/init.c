#include "common.h"

#include "field/main.h"
#include "system/controller.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"
#include "psyq/libetc.h"

extern void FieldSetControllerBuffers(u_char*, u_char*);
extern void FieldSetMouseSpeed(int, int);
extern void func_8007ADA4(int, int, int, int);
extern void FieldSetMousePosition(int, int, int);

void FieldInitializeControllersAndMouse(void) {
    FieldSetControllerBuffers(g_C1Buffer, g_C1Buffer + CONTROLLER_BUFFER_SIZE);
    FieldSetMouseSpeed(3, 4);
    func_8007ADA4(0, 0x140, 0, 0xE0);
    FieldSetMousePosition(0, 0x50, 0x64);
    FieldSetMousePosition(1, 0xFA, 0x64);
    func_8007ADA4(0, 0x12C, 0xA, 0xDC);
}

void FieldSetClipDimensions(short x, short y, short w, short h) {
    g_FieldRenderContexts[0].drawEnvs[0].clip.y = y;
    g_FieldRenderContexts[0].drawEnvs[0].clip.x = x;
    g_FieldRenderContexts[0].drawEnvs[0].clip.w = w;
    g_FieldRenderContexts[0].drawEnvs[0].clip.h = h;
    g_FieldRenderContexts[1].drawEnvs[0].clip.x = x;
    g_FieldRenderContexts[1].drawEnvs[0].clip.y = y + 0x100;
    g_FieldRenderContexts[1].drawEnvs[0].clip.w = w;
    g_FieldRenderContexts[1].drawEnvs[0].clip.h = h;
}

void FieldInitializeRenderContexts(void) {
    D_80059198 = 1;
    DrawSync(0);
    Vsync(0);
    InitGeom();
    SetGeomOffset(0xA0, 0x70);
    SetDefDrawEnv(&g_FieldRenderContexts[0].drawEnvs[0], 0, 0, 0x140, 0xE0);
    SetDefDrawEnv(&g_FieldRenderContexts[1].drawEnvs[0], 0, 0x100, 0x140, 0xE0);
    SetDefDrawEnv(&g_FieldRenderContexts[0].drawEnvs[1], 0, 0, 0x140, 0xE0);
    SetDefDrawEnv(&g_FieldRenderContexts[1].drawEnvs[1], 0, 0x100, 0x140, 0xE0);
    SetDefDispEnv(&g_FieldRenderContexts[0].dispEnv, 0, 0x100, 0x140, 0xE0);
    SetDefDispEnv(&g_FieldRenderContexts[1].dispEnv, 0, 0, 0x140, 0xE0);
    FieldSetClipDimensions(0x0, 0x0, 0x140, 0xE0);
    FieldSetScreenDimensions();

    g_FieldRenderContexts[0].drawEnvs[0].r0 = 0;
    g_FieldRenderContexts[0].drawEnvs[0].g0 = 0;
    g_FieldRenderContexts[0].drawEnvs[0].b0 = 0;
    g_FieldRenderContexts[1].drawEnvs[0].r0 = 0;
    g_FieldRenderContexts[1].drawEnvs[0].g0 = 0;
    g_FieldRenderContexts[1].drawEnvs[0].b0 = 0;
    g_FieldRenderContexts[0].drawEnvs[0].dtd = 1;
    g_FieldRenderContexts[1].drawEnvs[0].dtd = 1;
    
    Vsync(0);
    PutDispEnv(&g_FieldRenderContexts[1].dispEnv);
    PutDrawEnv(&g_FieldRenderContexts[1].drawEnvs[0]);
    func_8002DFF0(0x140, 0xF0);
}
