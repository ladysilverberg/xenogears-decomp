#include "common.h"
#include "main/game.h"
#include "field/main.h"
#include "field/actor.h"
#include "field/script_vm.h"
#include "field/text_box.h"

void FieldScriptMemoryWriteU16(int, int);

extern int rcos(int);
extern int rsin(int);

extern s32 D_8005A444;
extern s32 D_8005A448;
extern s32 D_8005A44C;
extern s32 D_800AFD1C;

void FieldSetScreenDimensions(void) {
    g_FieldRenderContexts[0].dispEnv.screen.x = 0;
    g_FieldRenderContexts[0].dispEnv.screen.y = 10;
    g_FieldRenderContexts[0].dispEnv.screen.w = 0x100;
    g_FieldRenderContexts[0].dispEnv.screen.h = 0xd8;
    g_FieldRenderContexts[1].dispEnv.screen.x = 0;
    g_FieldRenderContexts[1].dispEnv.screen.y = 10;
    g_FieldRenderContexts[1].dispEnv.screen.w = 0x100;
    g_FieldRenderContexts[1].dispEnv.screen.h = 0xd8;
}

extern u8 D_800B2358[]; // Is pause disabled?

void func_80086DE0(void) {
    D_800B2358[0] = SCRIPT_READ_U8_REL(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

extern s16 D_800ADB54;

void func_80086E1C(void) {
    RECT rect;
    switch (FieldScriptVMGetArgument(1)) {
        case 0:
            rect.w = 0x500;
            rect.x = 0;
            rect.y = 0;
            rect.h = 0x200;
            ClearImage(&rect, 0x0, 0x0, 0x0);
            DrawSync(0);
            Vsync(0);
            SetDefDrawEnv(g_FieldRenderContexts[0].drawEnvs, 0, 0, 0x280, 0xE0);
            SetDefDrawEnv(g_FieldRenderContexts[1].drawEnvs, 0, 0x100, 0x280, 0xE0);
            SetDefDispEnv(&g_FieldRenderContexts[0].dispEnv, 0, 0x100, 0x280, 0xE0);
            SetDefDispEnv(&g_FieldRenderContexts[1].dispEnv, 0, 0, 0x280, 0xE0);
            FieldSetScreenDimensions();
            break;
        case 1:
            D_800ADB54 = 0x1;
            break;
        case 2:
            D_800ADB54 = 0x0;
            break;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

// Set model animation for actor
void func_80086F7C(void) {
    g_FieldScriptVMCurActor->modelAnimation = (FieldScriptVMGetArgument(1) << 0xC) | FieldScriptVMGetArgument(3);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
}

void func_80086FD0(void) {
    switch (SCRIPT_READ_U8_REL(1)) {
        case 0:
            // Initialize Sprite List
            func_800AAC08();
            g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
            return;
        case 2:
            // Free Sprite List
            func_800AABD8();
            g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
            return;
        case 1:
            // Set X, Y of Sprite and add it to OT for drawing
            func_800AAE4C(
                FieldScriptVMGetArgument(2), // Sprite Index
                FieldScriptVMGetArgument(4), // X
                FieldScriptVMGetArgument(6), // Y
                FieldScriptVMGetArgument(8)  // Sprite type
            );
            g_FieldScriptVMCurActor->scriptInstructionPointer += 0xA;
            return;
        case 3:
            // Set Sprite Color
            func_800AADC8(
                FieldScriptVMGetArgument(2), // Sprite Index
                FieldScriptVMGetArgument(4), // Red
                FieldScriptVMGetArgument(6), // Green
                FieldScriptVMGetArgument(8)  // Blue
            );
            g_FieldScriptVMCurActor->scriptInstructionPointer += 0xA;
            return;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087148);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800871B0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800873C4);

void func_80087420(void) {
    int arg1, arg2, arg3, arg4, arg5, arg6;
    int value1, value2;

    arg1 = FieldScriptVMGetArgument(1);
    arg2 = FieldScriptVMGetArgument(3);
    arg3 = FieldScriptVMGetArgument(5);
    arg4 = FieldScriptVMGetArgument(7);
    arg5 = FieldScriptVMGetArgument(9);
    arg6 = FieldScriptVMGetArgument(0xB);

    value1 = ((arg5 << 0x10) / arg3 * arg1) >> 0x10;
    value2 = ((arg6 << 0x10) / arg4 * arg2) >> 0x10;
    
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(0xD) & 0xFFFF, 
        value1
    );
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(0xF) & 0xFFFF, 
        value2
    );
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 0x11;
}

void func_8008752C(void) {
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008754C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087580);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008764C);

extern u8 D_80050622;

void func_80087800(void) {
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(1) & 0xFFFF, 
        D_80050622
    );
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087848);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087960);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800879D0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087A40);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087A7C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087AB8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087B5C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087C0C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087C34);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087D30);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087D80);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087DE0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087E5C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087E98);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087FA4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80087FD4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008800C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088198);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800881E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008825C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800882B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088360);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800883D4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008848C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800884CC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088508);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008861C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088674);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088790);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800888A4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800889BC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088B68);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088C1C);

void func_80088CF8(void) {
    func_80088D38(0);
}

void func_80088D18(void) {
    func_80088D38(4);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80088D38);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089004);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089174);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089374);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089574);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800896D4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089880);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089A80);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089AE4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089B54);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089BF0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089DCC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089F18);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089F54);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089F94);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80089FD0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A08C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A148);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A244);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A2A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A2E8);

void func_8008A4E0(void) {}
void func_8008A4E8(void) {}
void func_8008A4F0(void) {}
void func_8008A4F8(void) {}
void func_8008A500(void) {}
void func_8008A508(void) {}
void func_8008A510(void) {}
void func_8008A518(void) {}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A520);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A558);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A5A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A604);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A640);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A6E0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A790);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A7DC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A93C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A974);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008A9AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008AA60);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008AACC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008ACE8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008AE5C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008AEC8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008AFD8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B0E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B144);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B180);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B210);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B248);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B2F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B328);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B45C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B518);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B5D4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B894);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008B978);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008BC80);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008BDD8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008BF38);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008C180);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008C334);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008C7D8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008C84C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008C938);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CA60);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CB4C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CC74);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CD48);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CDD4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CE64);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CED0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CF3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CF9C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008CFEC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D078);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D0F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D180);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D230);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D26C);

void func_8008D2D8(void) {
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D2E0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D30C);

static inline void CopySpriteFieldS32(FieldActor* actors, int dstId, int srcId, int offset) {
    void* dst = actors[dstId].pSpriteData;
    void* src = actors[srcId].pSpriteData;
    *(s32*)((u8*)dst + offset) = *(s32*)((u8*)src + offset);
}

static inline void CopySpriteFieldU16(FieldActor* actors, int dstId, int srcId, int offset) {
    void* dst = actors[dstId].pSpriteData;
    void* src = actors[srcId].pSpriteData;
    *(u16*)((u8*)dst + offset) = *(u16*)((u8*)src + offset);
}

static inline void CopyActorFieldS32(FieldActor* base, int dstId, int srcId, int offset) {
    *(s32*)((u8*)&base[dstId] + offset) = *(s32*)((u8*)&base[srcId] + offset);
}

void FieldActorCopyPlacement(int dstActorId, int srcActorId) {
    FieldActor* actors = g_FieldActors;
    ActorData* dstActor;
    ActorData* srcActor;
    int i;

    srcActor = actors[srcActorId].pActorData;
    dstActor = actors[dstActorId].pActorData;

    for (i = 0; i < 4; i++) {
        dstActor->walkmeshTriIds[i] = srcActor->walkmeshTriIds[i];
    }
    {
      s16 walkmeshId = srcActor->walkmeshId;
      dstActor->walkmeshId = walkmeshId;
    }
    dstActor->curTriNormal.vx = srcActor->curTriNormal.vx;
    dstActor->curTriNormal.vy = srcActor->curTriNormal.vy;
    dstActor->curTriNormal.vz = srcActor->curTriNormal.vz;
    dstActor->position.vx = srcActor->position.vx;
    dstActor->position.vy = srcActor->position.vy;
    dstActor->position.vz = srcActor->position.vz;
    dstActor->unkEC = srcActor->unkEC;
    dstActor->curYPos = srcActor->curYPos;
    dstActor->curWalkmeshTriMaterial = srcActor->curWalkmeshTriMaterial;

    CopySpriteFieldU16(g_FieldActors, dstActorId, srcActorId, offsetof(SpriteData, field_0x84));
    CopySpriteFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(SpriteData, position.x));
    CopySpriteFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(SpriteData, position.y));
    CopySpriteFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(SpriteData, position.z));

    CopyActorFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(FieldActor, transformMatrix.t[0]));
    CopyActorFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(FieldActor, transformMatrix.t[1]));
    CopyActorFieldS32(g_FieldActors, dstActorId, srcActorId, offsetof(FieldActor, transformMatrix.t[2]));
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D570);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D5C8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D604);

void func_8008D684(void) {
    int mask;
    unsigned int slotIndex;

    slotIndex = (unsigned int) (FieldScriptVMGetInstructionArgument(1) & 0xFFFF) >> 4;
    mask = 1 << (FieldScriptVMGetInstructionArgument(1) & 0xF);
    FieldScriptMemoryWriteU16(slotIndex, FieldScriptVMGetVariableValue(slotIndex) | mask);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_8008D700(void) {
    int mask;
    unsigned int slotIndex;

    slotIndex = (unsigned int) (FieldScriptVMGetInstructionArgument(1) & 0xFFFF) >> 4;
    mask = 1 << (FieldScriptVMGetInstructionArgument(1) & 0xF);
    FieldScriptMemoryWriteU16(slotIndex, FieldScriptVMGetVariableValue(slotIndex) & ~mask);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_8008D780(void) {
    short destination;
    int mask;
    unsigned int slotIndex;

    slotIndex = (unsigned int) (FieldScriptVMGetInstructionArgument(1) & 0xFFFF) >> 4;
    mask = 1 << (FieldScriptVMGetInstructionArgument(1) & 0xF);
    if (FieldScriptVMGetVariableValue(slotIndex) & mask) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
    } else {
        destination = FieldScriptVMGetInstructionArgument(3);
        g_FieldScriptVMCurActor->scriptInstructionPointer = destination;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008D808);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DA04);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DAFC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DB2C);


int FieldPartyMemberIncreaseGearHp(int partyMemberIndex, unsigned int amount) {
    int gearId;
    unsigned int maxHp;
    unsigned int newHp;

    gearId = GameCharacterGetGearID(g_GamePartyMembers[partyMemberIndex]);
    if (gearId != CHARACTER_ID_NONE) {
        maxHp = g_GameState->gears[gearId].maxHp;
        newHp = g_GameState->gears[gearId].hp + amount;
        g_GameState->gears[gearId].hp = newHp;
        if (maxHp < newHp) {
            g_GameState->gears[gearId].hp = maxHp;
        }
    }
}

int FieldPartyMemberDecreaseGearHp(int partyMemberIndex, unsigned int amount) {
    int gearId;
    int newHp;

    gearId = GameCharacterGetGearID(g_GamePartyMembers[partyMemberIndex]);
    if (gearId != CHARACTER_ID_NONE) {
        newHp = g_GameState->gears[gearId].hp - amount;
        if (newHp <= 0) {
            newHp = 1;
        }
        g_GameState->gears[gearId].hp = newHp;
    }
}

extern s16 g_FieldNumPartyMembersMasks[4];

void FieldScriptVMHandlerIncreasePartyGearHp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberIncreaseGearHp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerDecreasePartyGearHp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberDecreaseGearHp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DE64);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DEBC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DF44);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008DFCC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E054);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E0DC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E148);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E1B4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E298);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E2EC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E340);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E394);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E3E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E414);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E440);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E46C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E498);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E4EC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E518);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E544);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E570);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E59C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E718);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E85C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E8C8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008E9F8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EA58);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EC30);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EE14);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EF5C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EFA0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008EFE4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F070);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F0B4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F1C8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F2D8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F348);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F394);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F3D0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F444);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F4A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F4FC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F558);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F5E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F668);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F6AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F724);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F76C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F7B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008F90C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FA38);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FABC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FB28);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FB98);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FC4C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FD40);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FDD0);

extern VECTOR D_800AF8F0; // Override target position for camera?
void func_8008FE2C(void) {
    D_800AF8F0.vx = func_8009CF78(1, SCRIPT_READ_U8_REL(7)) << 0x10;
    D_800AF8F0.vz = func_8009CFBC(3, SCRIPT_READ_U8_REL(7)) << 0x10; 
    D_800AF8F0.vy = func_8009D000(5, SCRIPT_READ_U8_REL(7)) << 0x10;
    g_FieldScriptMaxInstructionCount += 1;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

extern VECTOR g_FieldCameraTargetPosition;
void FieldScriptVMHandlerSetCameraTargetToActor(void) {
    ActorData* pActor = g_FieldActors[func_8009CD7C(1)].pActorData;
    g_FieldCameraTargetPosition.vx = pActor->position.vx;
    g_FieldCameraTargetPosition.vy = pActor->position.vy;
    g_FieldCameraTargetPosition.vz = pActor->position.vz;  
    g_FieldScriptMaxInstructionCount += 1;    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8008FF90);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090068);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800900C4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009019C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090228);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090300);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800903BC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090A10);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090A94);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090B18);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090B9C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090C20);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090CB8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090D50);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090DEC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80090E70);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091008);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800910C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091318);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800915C4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091720);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091944);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091A08);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091A78);

void func_80091AD4(void) {
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091ADC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091BBC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091E00);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091E98);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80091F84);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092044);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800920D8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092148);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800921E8);

void func_800923E4(void) {
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80092404(void) {
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092424);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800924D4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800925A0);

void FieldScriptVMHandlerSetControllerBtnMask(void) {
    g_FieldControl.controllerBtnMask = FieldScriptVMGetInstructionArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092664);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800926C8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092768);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092808);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092894);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092C20);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092DFC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092EA0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092F44);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80092FB4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093014);

void func_800931F8(void) {
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093200);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800932D0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800933F8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093568);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093664);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800936E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093740);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093790);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800937E0);

extern s32 D_8004F350;
extern s8 D_80059171;
extern s32 D_800ADB64;

void func_80093824(void) {
    D_80059171 = FieldScriptVMGetArgument(1);
    D_800ADB64 = 0x3;
    D_800B00C0 = 1;
    D_8004F350++;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093888);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80093930);

void func_800939A0(void) {
    D_80059171 = FieldScriptVMGetArgument(1);
    D_800ADB64 = 0x4;
    D_800B00C0 = 1;
    D_8004F350++;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_80093A04(void) {
    D_80059171 = FieldScriptVMGetArgument(1);
    D_800ADB64 = 0x5;
    D_800B00C0 = 1;
    D_8004F350++;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}


// Random encounter stuff

// These are likely part of a struct
extern s8 D_800B21D0[];
extern s8 D_800B21D1[];
extern s32 D_800AF9D8[];

extern s32 D_800ADBDC;
extern s32 D_800ADBE4;
extern s32 D_800B00C0;

void func_80093A68(void) {
    D_800AF9D8[0] &= 0x7FFF;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093A98(void) {
    D_800AF9D8[0] |= 0x8000;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093AC8(void) {
    g_FieldControl.isRandomEncountersEnabled = 0;
    D_800B21D0[0] = 0;
    D_800B21D1[0] = 0;
    D_800AF9D8[0] &= 0x3FFF;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093B10(void) {
    g_FieldControl.isRandomEncountersEnabled = -1;
    D_800B21D0[0] = 1;
    D_800B21D1[0] = 1;
    D_800AF9D8[0] |= 0xC000;
    if ((D_800ADBDC == 0) || (D_800ADBE4 == 0)) {
        D_800B00C0 = 1; // Stop script VM execution?
        g_FieldScriptVMCurActor->scriptInstructionPointer--;
        return;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093BB0(void) {
    D_800B21D0[0] = 0x0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093BD4(void) {
    D_800B21D0[0] = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093BFC(void) {
    D_800B21D1[0] = 0x0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093C20(void) {
    D_800B21D1[0] = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void FieldScriptVMHandlerDisableRandomEncounters(void) {
    g_FieldControl.isRandomEncountersEnabled = 0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_80093C6C(void) {
    if (D_800ADBDC == 0 || D_800ADBE4 == 0) {
        D_800B00C0 = 1;
        return;
    }
    g_FieldControl.isRandomEncountersEnabled = -1;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 1;
}
// End of random encounter stuff


// Write U8 Handler
// Arg1 + Arg3 = Offset to U8 value in script
// Arg2 = Write address
void func_80093CD0(void) {
    unsigned short offset;
    unsigned short arg1;

    arg1 = FieldScriptVMGetInstructionArgument(1);
    offset = arg1 + FieldScriptVMGetArgument(5);
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(3) & 0xFFFF, 
        SCRIPT_READ_U8(offset)
    );
    g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
}

// Write U16/S16 handler
// Arg1 + Arg3 = Offset in script to short to write
// Arg3: Write address
void func_80093D48(void) {
    int arg1;
    int nAddress;
    unsigned short nOffset;
    int nValue;
    int arg3;

    arg1 = FieldScriptVMGetInstructionArgument(1);
    nOffset = arg1 + FieldScriptVMGetArgument(5);
    if (SCRIPT_READ_U8_REL(7) == 0) {
        // W/O carry
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(3) & 0xFFFF,
            SCRIPT_READ_U8(nOffset) | (SCRIPT_READ_U8(nOffset + 1) << 8)
        );
    } else {
        // With carry
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(3) & 0xFFFF,
            (short)(SCRIPT_READ_U8(nOffset) + (SCRIPT_READ_U8(nOffset + 1) << 8))
        );
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

// The two functions seems to be related to handling room transitions
void func_80093E30(void) {
    if (!g_FieldScriptVMCurActor->scriptFlags_0x13) {
        if (!(g_FieldScriptVMCurActor->flags12C_0x5)) {
            g_FieldScriptVMCurActor->flags12C_0x5 = 1;
            g_FieldScriptVMCurActor->curDoorStep = 0;
            func_80085634(8, 3);
        } else {
            g_FieldScriptVMCurActor->curDoorStep++;
            if (g_FieldScriptVMCurActor->curDoorStep < 0x1F) {
                if (SCRIPT_READ_U8_REL(1) == 0) {
                    g_FieldActors[D_800AFD1C].rotation.y += 0x20;
                } else {
                    g_FieldActors[D_800AFD1C].rotation.y -= 0x20;
                }
            } else {
                g_FieldScriptVMCurActor->scriptFlags_0x13 = 0x1;
                g_FieldScriptVMCurActor->flags12C_0x5 = 0;
                g_FieldScriptVMCurActor->curDoorStep = 0;
                g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
            }
        }
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
    }
    
    func_80072254(D_800AFD1C);
}

void func_80093FC0(void) {
    if (g_FieldScriptVMCurActor->scriptFlags_0x13) {
        if (!(g_FieldScriptVMCurActor->flags12C_0x5)) {
            g_FieldScriptVMCurActor->flags12C_0x5 = 1;
            g_FieldScriptVMCurActor->curDoorStep = 0;
            func_80085634(8, 3);
        } else {
            g_FieldScriptVMCurActor->curDoorStep++;
            if (g_FieldScriptVMCurActor->curDoorStep < 0x1F) {
                if (SCRIPT_READ_U8_REL(1) == 0) {
                    g_FieldActors[D_800AFD1C].rotation.y -= 0x20;
                } else {
                    g_FieldActors[D_800AFD1C].rotation.y += 0x20;
                }
            } else {
                g_FieldScriptVMCurActor->scriptFlags_0x13 = 0;
                g_FieldScriptVMCurActor->flags12C_0x5 = 0;
                g_FieldScriptVMCurActor->curDoorStep = 0;
                g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
            }
        }
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
    }
    func_80072254(D_800AFD1C);
}

extern void func_80072254(int);
extern void func_80085634(int,int);
extern s32 D_800AFD1C;
extern ActorData* D_800B06B8;

void func_80094158() {
    ActorData* pActor;
    int angle;

    if (!g_FieldScriptVMCurActor->scriptFlags_0x13) {
        if (!g_FieldScriptVMCurActor->flags12C_0x5) {
            g_FieldScriptVMCurActor->flags12C_0x5 = 0x1;
            g_FieldScriptVMCurActor->curDoorStep = 0;
            func_80085634(8, 3);
            g_FieldScriptVMCurActor->unkD0.vx = g_FieldScriptVMCurActor->position.vx;
            g_FieldScriptVMCurActor->unkD0.vy = g_FieldScriptVMCurActor->position.vy;
            g_FieldScriptVMCurActor->unkD0.vz = g_FieldScriptVMCurActor->position.vz;
        } else {
            g_FieldScriptVMCurActor->curDoorStep++;
            if (g_FieldScriptVMCurActor->curDoorStep < FieldScriptVMGetArgument(3)) {
                switch (FieldScriptVMGetArgument(5)) { 
                    case 0x1000:
                        g_FieldScriptVMCurActor->unkD0.vy -= FieldScriptVMGetArgument(1) * 0x10;
                        D_800B06B8->position.vy = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                    case 0x1001:
                        g_FieldScriptVMCurActor->unkD0.vy += FieldScriptVMGetArgument(1) * 0x10;
                        D_800B06B8->position.vy = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                    default:
                        angle = (D_800B06B8->curTriNormal.vx >> 0x10) + FieldScriptVMGetArgument(5) - 0x400;
                        g_FieldScriptVMCurActor->unkD0.vx += rsin(angle) * FieldScriptVMGetArgument(1);
                        g_FieldScriptVMCurActor->unkD0.vz -= rcos(angle) * FieldScriptVMGetArgument(1);
                        D_800B06B8->position.vx = g_FieldScriptVMCurActor->unkD0.vx >> 0x10;
                        D_800B06B8->position.vz = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                }
            } else {
                g_FieldScriptVMCurActor->scriptFlags_0x13 = 1;
                g_FieldScriptVMCurActor->flags12C_0x5 = 0;
                g_FieldScriptVMCurActor->curDoorStep = 0;   
                g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
            }
        }
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
    }
    func_80072254(D_800AFD1C);
}

void func_800943AC(void) {
    ActorData* temp_a1;
    int angle;
    
    if (g_FieldScriptVMCurActor->scriptFlags_0x13) {
        if (!g_FieldScriptVMCurActor->flags12C_0x5) {
            g_FieldScriptVMCurActor->flags12C_0x5 = 0x1;
            g_FieldScriptVMCurActor->curDoorStep = 0x0;
            func_80085634(8, 3);
        } else {
            g_FieldScriptVMCurActor->curDoorStep++;
            if (g_FieldScriptVMCurActor->curDoorStep < FieldScriptVMGetArgument(3)) {
                switch (FieldScriptVMGetArgument(5)) {
                    case 0x1000:
                        g_FieldScriptVMCurActor->unkD0.vy -= FieldScriptVMGetArgument(1) * 0x10;
                        D_800B06B8->position.vy = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                    case 0x1001:
                        g_FieldScriptVMCurActor->unkD0.vy += FieldScriptVMGetArgument(1) * 0x10;
                        D_800B06B8->position.vy = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                    default:
                        angle = (D_800B06B8->curTriNormal.vx >> 0x10) + FieldScriptVMGetArgument(5) - 0x400;
                        g_FieldScriptVMCurActor->unkD0.vx -= rsin(angle) * FieldScriptVMGetArgument(1);
                        g_FieldScriptVMCurActor->unkD0.vz += rcos(angle) * FieldScriptVMGetArgument(1);
                        D_800B06B8->position.vx = g_FieldScriptVMCurActor->unkD0.vx >> 0x10;
                        D_800B06B8->position.vz = g_FieldScriptVMCurActor->unkD0.vz >> 0x10;
                        break;
                }
            } else {
                g_FieldScriptVMCurActor->scriptFlags_0x13 = 0x0;
                g_FieldScriptVMCurActor->flags12C_0x5 = 0x0;
                g_FieldScriptVMCurActor->curDoorStep = 0;
                g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
            }
        }
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
    }
    func_80072254(D_800AFD1C);
}

extern s32 D_8004F318;
extern s32 D_8004F328;

void func_800945D4(void) {
    D_8004F318 = 0;
    D_8004F328 = 0xFF;
    FieldScriptMemoryWriteU16(
        0xA, 
        ((FieldScriptVMGetArgument(1) << 8) & 0xFF00) | (FieldScriptVMGetArgument(3) & 0xFF)
    );
    g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
}

void func_80094650(void) {
    D_8004F328 = SCRIPT_READ_U8_REL(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void func_8009468C(void) {
    D_8004F318 = 0;
    D_8004F328 = 0xFF;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_800946BC(void) {
    g_FieldScriptVMCurActor->flags12C_0 = 0x1;
    g_FieldScriptVMCurActor->unk70 = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_80094710(void) {
    g_FieldScriptVMCurActor->flags12C_0 = 0x2;
    g_FieldScriptVMCurActor->unk70 = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_80094764(void) {
    g_FieldScriptVMCurActor->flags12C_0 = 0x3;
    g_FieldScriptVMCurActor->unk70 = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

extern void func_80072254(int);

void func_800947B0(void) {
    FieldActor* pActor;

    if (FieldScriptVMGetActorIndex(2) != 0xFF) {
        pActor = &g_FieldActors[FieldScriptVMGetActorIndex(2)];
        switch (SCRIPT_READ_U8_REL(1)) {
            case 0:
                pActor->rotation.x += FieldScriptVMGetArgument(3);
                break;
            case 1:
                pActor->rotation.x -= FieldScriptVMGetArgument(3);
                break;
            case 2:
                pActor->rotation.y += FieldScriptVMGetArgument(3);
                break;
            case 3:
                pActor->rotation.y -= FieldScriptVMGetArgument(3);
                break;
            case 4:
                pActor->rotation.z += FieldScriptVMGetArgument(3);
                break;
            case 5:
                pActor->rotation.z -= FieldScriptVMGetArgument(3);
                break;
        }
        func_80072254(FieldScriptVMGetActorIndex(2));
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
}

// Set X, Y or Z rotaiton of Actor D_800AFD1C
void func_80094918(void) {
    switch (SCRIPT_READ_U8_REL(3)) { 
        case 0:
            g_FieldActors[D_800AFD1C].rotation.x = FieldScriptVMGetArgument(1);
            break;
        case 1:
            g_FieldActors[D_800AFD1C].rotation.y = FieldScriptVMGetArgument(1);
            break;
        case 2:
            g_FieldActors[D_800AFD1C].rotation.z = FieldScriptVMGetArgument(1);
            break;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
    func_80072254(D_800AFD1C);
}

// Increase X Rotation of Actor D_800AFD1C
void func_80094A5C(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.x += FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

// Decrease X Rotation of Actor D_800AFD1C
void func_80094ACC(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.x -= FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

// Increase Y Rotation of Actor D_800AFD1C
void func_80094B3C(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.y += FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

// Decrease Y Rotation of Actor D_800AFD1C
void func_80094BAC(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.y -= FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

// Increase Z Rotation of Actor D_800AFD1C
void func_80094C1C(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.z += FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

// Decrease Z Rotation of Actor D_800AFD1C
void func_80094C8C(void) {
    (&g_FieldActors[D_800AFD1C])->rotation.z -= FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    func_80072254(D_800AFD1C);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094CFC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094D4C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094D9C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094DEC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094E3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094E8C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094EDC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094F2C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094F7C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80094FCC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009501C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800950A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095124);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800951B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009524C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095284);

void func_80095300(void) {
    g_FieldControl.unkAngle = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009533C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095520);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095734);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800958C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095A7C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095B3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095C00);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095CC4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095D6C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095E48);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095F24);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80095FB8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009601C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", FieldScriptVMCheckControllerInput);
/*
void FieldScriptVMCheckControllerInput(u_short buttonState) {
    u_short nButtonMask;
    
    nButtonMask = FieldScriptVMGetInstructionArgument(1);
    if (buttonState & nButtonMask) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer = FieldScriptVMGetInstructionArgument(3);
    }
}
*/

void func_800960E4(int value) {
    u_short nArgument;

    nArgument = FieldScriptVMGetInstructionArgument(1);
    if (nArgument == (u_short) value) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer = FieldScriptVMGetInstructionArgument(3);
    }
}


extern u16 D_800AFE9C;
extern u16 D_800AFC6C;

void func_80096150(void) {
    func_800960E4(D_800AFE9C);
}

void func_80096178(void) {
    func_800960E4(D_800AFC6C);
}

// Is button pressed handler
void func_800961A0(void) {
    FieldScriptVMCheckControllerInput(D_800AFE9C);
}

void func_800961C8(void) {
    FieldScriptVMCheckControllerInput(D_800AFC6C);
}

void func_800961F0(void) {
    D_800AFC6C = 0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096214);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800962C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009631C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009635C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009640C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800964B0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096534);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800965A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800965F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096644);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800966B4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096724);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096790);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800967E8);

void FieldPartyMemberIncreaseHp(int i, int amount) {
    g_GameState->characters[g_GamePartyMembers[i]].hp += amount;
    if (g_GameState->characters[g_GamePartyMembers[i]].maxHp < g_GameState->characters[g_GamePartyMembers[i]].hp) {
        g_GameState->characters[g_GamePartyMembers[i]].hp = g_GameState->characters[g_GamePartyMembers[i]].maxHp;
    }
}

void FieldPartyMemberDecreaseHp(int partyMemberIndex, int amount) {
    int newHp;
    int characterId = g_GamePartyMembers[partyMemberIndex];
    newHp = g_GameState->characters[characterId].hp - amount;
    if (newHp <= 0) {
        newHp = 1;
    }
    g_GameState->characters[characterId].hp = newHp;
}

void FieldPartyMemberIncreaseMp(int i, int amount) {
    g_GameState->characters[g_GamePartyMembers[i]].mp += amount;
    if (g_GameState->characters[g_GamePartyMembers[i]].maxMp < g_GameState->characters[g_GamePartyMembers[i]].mp) {
        g_GameState->characters[g_GamePartyMembers[i]].mp = g_GameState->characters[g_GamePartyMembers[i]].maxMp;
    }
}

void FieldPartyMemberDecreaseMp(int partyMemberIndex, int amount) {
    int newMp;
    int characterId = g_GamePartyMembers[partyMemberIndex];
    newMp = g_GameState->characters[characterId].mp - amount;
    if (newMp <= 0) {
        newMp = 1;
    }
    g_GameState->characters[characterId].mp = newMp;
}

extern s16 g_FieldNumPartyMembersMasks[4];

void FieldScriptVMHandlerDecreasePartyHp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberDecreaseHp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80096AF4);

void FieldScriptVMHandlerWritePartyMemberHp(void) {
    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != CHARACTER_ID_NONE) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(1) & 0xFFFF, 
            g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(3)]].hp
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerWritePartyMemberMp(void) {
    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != CHARACTER_ID_NONE) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(1) & 0xFFFF, 
            g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(3)]].mp
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

// Sets the HP of a character to a target amount, but only if we have a full party
void FieldScriptVMHandlerSetPartyMemberHp(void) {
    int targetHp;
    int characterHp;

    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != 0xFF) {
        targetHp = FieldScriptVMGetArgument(2);
        characterHp = g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].maxHp;
        if (characterHp < targetHp) {
            targetHp = characterHp;
        }
        g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].hp = targetHp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

// Sets the MP of a character to a target amount, but only if we have a full party
void FieldScriptVMHandlerSetPartyMemberMp(void) {
    int targetMp;
    int characterMp;

    if (g_GamePartyMembers[SCRIPT_READ_U8_REL(3)] != 0xFF) {
        targetMp = FieldScriptVMGetArgument(2);
        characterMp = g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].maxMp;
        if (characterMp < targetMp) {
            targetMp = characterMp;
        }
        g_GameState->characters[g_GamePartyMembers[SCRIPT_READ_U8_REL(1)]].mp = targetMp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerIncreasePartyMp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberIncreaseMp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

void FieldScriptVMHandlerDecreasePartyMp(void) {
    int mask;
    int amount;
    int i;

    amount = func_8009CF78(1, SCRIPT_READ_U8_REL(3));
    mask = g_FieldNumPartyMembersMasks[SCRIPT_READ_U8_REL(3) & 0x3];

    for (i = 0; i < MAX_PARTY_MEMBERS; i++) {
        if ((g_GamePartyMembers[i] != CHARACTER_ID_NONE) && (mask & 1)) {
            FieldPartyMemberDecreaseMp(i, amount);
        }
        mask >>= 1;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097108);

void FieldScriptVMHandlerRestoreCharacterHpAndMp(void) {
    int id = FieldScriptVMGetArgument(1);
    g_GameState->characters[id].hp = g_GameState->characters[id].maxHp;
    g_GameState->characters[id].mp = g_GameState->characters[id].maxMp;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void FieldScriptVMHandlerRestoreHp(void) {
    int i;
    for (i = 0; i < MAX_GAME_CHARACTERS; i++) {
        g_GameState->characters[i].hp = g_GameState->characters[i].maxHp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void FieldScriptVMHandlerRestoreMp(void) {
    int i;
    for (i = 0; i < MAX_GAME_CHARACTERS; i++) {
        g_GameState->characters[i].mp = g_GameState->characters[i].maxMp;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800972F4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009731C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097364);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800973A4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097410);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009744C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009749C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800975C0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800976A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800977A4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097864);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097954);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800979F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80097A50);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098038);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800980FC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098184);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098274);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098370);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098430);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800984EC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800985BC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009861C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098738);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800988B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009899C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_800989F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098A7C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098C00);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098C3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80098CAC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099214);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099980);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099A04);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099A4C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099A8C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099AC0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099EF8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_80099F48);

void FieldScriptVMHandlerGetActorFacingAngle(void) {
    FieldScriptMemoryWriteU16(
        FieldScriptVMGetInstructionArgument(1) & 0xFFFF,
        ((g_FieldScriptVMCurActor->rotationY + 0x100 >> 9) + 2) & 7 // What
    );
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void FieldScriptVMHandlerGetActorPosition(void) {
    int nActorIndex = FieldScriptVMGetActorIndex(1);
    if (nActorIndex != 0xFF) {
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(2) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[0]
        );
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(4) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[2]
        );
        FieldScriptMemoryWriteU16(
            FieldScriptVMGetInstructionArgument(6) & 0xFFFF, 
            g_FieldActors[nActorIndex].childMatrix.t[1]
        );
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A0FC);

void FieldScriptVMHandlerPlayAnimation(void) {
    unsigned char animationID;
    
    g_FieldScriptVMCurActor->flags &= 0xFEFFFFFF;
    animationID = *(u8*)&g_FieldScriptVMCurScriptData[g_FieldScriptVMCurActor->scriptInstructionPointer + 1];
    g_FieldScriptVMCurActor->unkAnimationId = animationID;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A174);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A1AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A1E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A2A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A34C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A420);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A490);

extern s16 D_800AF98C;

int func_8009A514(void) {
    return (7 - ((D_800AF98C - 0x100) >> 9)) & 7;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A534);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A58C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A5E0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A634);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A670);

// Write cosine of angle to script memory?
void func_8009A6AC(void) {
    int nValue;
    int angle;
    int nFactor;
    int nVariableAddress;

    nVariableAddress = FieldScriptVMGetInstructionArgument(1) & 0xFFFF;
    angle = func_8009CFBC(3, SCRIPT_READ_U8_REL(7));
    nFactor = func_8009D000(5,  SCRIPT_READ_U8_REL(7)); // ?
    nValue = rcos(angle) * nFactor;
    FieldScriptMemoryWriteU16(nVariableAddress, nValue >> 0xC);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

// Write sine of angle to script memory?
void func_8009A768(void) {
    int nValue;
    int angle;
    int nFactor;
    int nVariableAddress;

    nVariableAddress = FieldScriptVMGetInstructionArgument(1) & 0xFFFF;
    angle = func_8009CFBC(3, SCRIPT_READ_U8_REL(7));
    nFactor = func_8009D000(5,  SCRIPT_READ_U8_REL(7));
    nValue = rsin(angle) * nFactor;
    FieldScriptMemoryWriteU16(nVariableAddress, nValue >> 0xC);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 8;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A824);

// Get 8-directional movement direction based on Y Rotation of current actor?
s32 func_8009A8DC(void) {
    return (((g_FieldScriptVMCurActor->rotationY + 0x100) >> 9) + 2) & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS;
}

extern s32 D_800ADB1C; // Is current actor a 2D actor (0) maybe?
void FieldSetCurrentActorRotation(int rotation) {
    short rotationValue2D;
    short rotationValue3D;

    if (D_800ADB1C == 0) {
        rotationValue3D = rotation | 0x8000;
        g_FieldScriptVMCurActor->rotationX = rotationValue3D;
        g_FieldScriptVMCurActor->rotationY = rotationValue3D;
        g_FieldScriptVMCurActor->rotationZ = rotationValue3D;
    }
    rotationValue2D = rotation | 0x8000;
    g_FieldScriptVMCurActor->rotationX = rotationValue2D;
    g_FieldScriptVMCurActor->rotationY = rotationValue2D;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009A958);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AA00);

extern s16 D_800AF98C;
void func_8009AB08(int rotation) {
    short rotationValue;

    rotationValue = ((rotation - D_800AF98C) & 0xFFF) | 0x8000;
    g_FieldScriptVMCurActor->rotationX = rotationValue;
    g_FieldScriptVMCurActor->rotationY = rotationValue;

    // 3D Actor?
    if (D_800ADB1C == 0) {
        g_FieldScriptVMCurActor->rotationZ = rotationValue;
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

extern u16 D_800AEA34[]; // 8-directional movement rotation value table?

// Set Current Actor Rotation (Clockwise)
void func_8009AB5C(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[nRotationLUTIndex + func_8009A8DC() & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS]);
}

// Set Current Actor Rotation (Counter-clockwise)
void func_8009ABAC(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[func_8009A8DC() - nRotationLUTIndex & MASK_8DIR_MOVEMENT_NUM_DIRECTIONS]);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009ABFC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AC34);

void FieldScriptVMHandlerSetCurActorRotation(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    FieldSetCurrentActorRotation(D_800AEA34[nRotationLUTIndex]);
}

void func_8009ACB4(void) {
    int nRotationLUTIndex = FieldScriptVMGetArgument(1);
    func_8009AB08(D_800AEA34[nRotationLUTIndex]);
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009ACEC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AD6C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009ADDC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AE0C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AE3C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009AEE0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B15C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B184);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B210);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B338);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B398);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B664);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B6AC);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B708);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B7A8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B824);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B884);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B8E4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009B9A0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009BA0C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009BA7C);

void func_8009BB0C(void) {
    int nTextBoxIndex;
    u32 lowerFlags;
    u32 upperFlags;

    // Check if there's no visible textbox owned by current actor
    if (func_8009CD18(&nTextBoxIndex) == -1) {
        g_FieldScriptMaxInstructionCount += 8;
        FieldScriptMemoryWriteU16(0x14, g_FieldScriptVMCurActor->unk81);
        g_FieldScriptVMCurActor->scriptInstructionPointer += 1;
        return;
    }
    
    if (g_FieldActors[g_FieldTextBoxes[nTextBoxIndex].talkingActorID].pActorData->flags & 0x200) {
        upperFlags = g_FieldScriptVMCurActor->dialogFlags >> 0x10;
        if (g_FieldScriptVMCurActor->dialogFlags >> 0x10 == 0) {
            lowerFlags = g_FieldScriptVMCurActor->dialogFlags & 0xFFFF;
        } else {
            lowerFlags = upperFlags & 0xFFFF;
        }
        
        if (!(lowerFlags & 0x1)) {
            if (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].flags_0x12 != 7) {
                func_800A1B70();
            }
            g_FieldTextBoxes[nTextBoxIndex].status = 0;
        }
    }
    D_800B00C0 = 1;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009BC98);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009BE58);

// Reset text box?
void func_8009BE9C(void) {
    int index;
    
    if (SCRIPT_READ_U8_REL(1) == 0) {
        if (func_8009CD18(&index) == 0) {
            g_FieldTextBoxes[index].status = 0;
            g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
        } else {
            g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
        }
    } else {
        g_FieldScriptVMCurActor->dialogPixelWidth = 0;
        g_FieldScriptVMCurActor->dialogPixelHeight = 0;
        g_FieldScriptVMCurActor->dialogWidth = 0;
        g_FieldScriptVMCurActor->dialogHeight = 0;
        g_FieldScriptVMCurActor->dialogFlags = 0;
        g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
    }
    D_800B00C0 = 1;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009BF8C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009C01C);

void func_8009C0B4(void) {
    func_8009C5A8(D_800AFD1C, 0);
}

void func_8009C0DC(void) {
    func_8009C5A8(D_800AFD1C, 1);
}

void func_8009C104(void) {
    func_8009C5A8(D_800AFD1C, 2);
}

void func_8009C12C(void) {
    func_8009C5A8(D_800AFD1C, 3);
}

// https://decomp.me/scratch/tL6mE
INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009C154);

// Check if there is a portrait w/ targetId that's free to use?
int func_8009C538(int targetId) {
    int i;
    
    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].visibility || g_FieldTextBoxes[i].portrait.shouldRenderPortrait != 1) {
            continue;
        }
        
        if (g_FieldTextBoxes[i].portrait.portraitID == targetId) {
            return -1;
        }
    }

    return 0;
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc", func_8009C5A8);

extern u16 D_800B2174[];

void func_8009CCF8(int arg0) {
    D_800B2174[0] |= 1 << arg0;
}

int func_8009CD18(int* pTextBoxIndex) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_FieldTextBoxes[i].ownerActorID == D_800AFD1C && g_FieldTextBoxes[i].visibility == 0) {
            *pTextBoxIndex = i;
            return 0;
        }
    }

    return -1;
}

u32 func_8009CD7C(int bytecodeOffset) {
    u32 nActorIndex = FieldScriptVMGetActorIndex(bytecodeOffset);
    if (nActorIndex == 0xFF) {
        return D_8005A444;
    }
    return nActorIndex;
}

u32 FieldScriptVMGetActorIndex(int bytecodeOffset) {
    u32 actorID = *(u8*)&g_FieldScriptVMCurScriptData[g_FieldScriptVMCurActor->scriptInstructionPointer + bytecodeOffset];
    if (actorID == 0xFF) {
        actorID = D_8005A444;  
    } else if (actorID == 0xFE) {
        actorID = D_8005A448;
    } else if (actorID == 0xFD) {
        actorID = D_8005A44C;
    } else if (actorID == 0xFB) {
        actorID = D_800AFD1C;
    }
    return actorID;
}


// Set up dialog window / text box
void func_8009CE48(void) {
    g_FieldScriptVMCurActor->dialogPixelWidth = SCRIPT_READ_U8_REL(1) * 2;
    g_FieldScriptVMCurActor->dialogPixelHeight = SCRIPT_READ_U8_REL(2);
    g_FieldScriptVMCurActor->dialogWidth = SCRIPT_READ_U8_REL(3) * 3;
    g_FieldScriptVMCurActor->dialogHeight = SCRIPT_READ_U8_REL(4);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
}


// Set up dialog window / text box
void func_8009CEE0(void) {
    g_FieldScriptVMCurActor->dialogPixelWidth = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->dialogPixelHeight = FieldScriptVMGetArgument(3);
    g_FieldScriptVMCurActor->dialogWidth = FieldScriptVMGetArgument(5) * 3;
    g_FieldScriptVMCurActor->dialogHeight = FieldScriptVMGetArgument(7);
    g_FieldScriptVMCurActor->dialogFlags = FieldScriptVMGetArgument(9);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 0xB;
}