#include "common.h"
#include "main/game.h"
#include "field/script_vm.h"
#include "field/actor.h"
#include "field/text_box.h"

extern void func_80076AC0(s32, s32, void*, s32, s32, s32, s32);
extern void func_800A0C94();
extern s32 D_800AFD1C; // Current actor index

void FieldScriptVMHandlerDisableDialogActivation(void) {
    g_FieldScriptVMCurActor->scriptFlags_0xA = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void FieldScriptVMHandlerEnableDialogActivation(void) {
    g_FieldScriptVMCurActor->scriptFlags_0xA = 0x0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009DA70(void) {
    g_FieldScriptVMCurActor->scriptFlags_0x16 = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009DA98(void) {
    g_FieldScriptVMCurActor->scriptFlags_0x16 = 0;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009DAC4(void) {
    int nTextBoxIndex;
    ActorData* pActor;
    FieldActor* pFieldActor;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pActor = g_FieldActors[FieldScriptVMGetActorIndex(1)].pActorData;
        pActor->scriptFlags_0x0 = 0x1;
        pActor->flags |= 0x100000;
        pFieldActor = &g_FieldActors[FieldScriptVMGetActorIndex(1)];
        pFieldActor->status |= ACTOR_STATUS_INVISIBLE;
        if (func_8009CD18(&nTextBoxIndex) == 0) {
            g_FieldTextBoxes[nTextBoxIndex].status = 0;
        }
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void FieldScriptVMHandlerEnableActorVM(void) {
    ActorData* pActor;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pActor = g_FieldActors[FieldScriptVMGetActorIndex(1)].pActorData;
        pActor->scriptFlags_0x0 = 0;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void func_8009DC4C(void) {
    ActorData* pActor;
    int nTextBoxIndex;
    short nNewRotation;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pActor = g_FieldActors[FieldScriptVMGetActorIndex(1)].pActorData;
        pActor->moveModified.vx = 0;
        pActor->moveModified.vy = 0;
        pActor->moveModified.vz = 0;
        pActor->move.vx = 0;
        pActor->move.vy = 0;
        pActor->move.vz = 0;
        pActor->scriptFlags_0x0 = 1;
        nNewRotation = pActor->rotationX | 0x8000;
        pActor->rotationY = nNewRotation;
        pActor->rotationX = nNewRotation;
        if (func_8009CD18(&nTextBoxIndex) == 0) {
            g_FieldTextBoxes[nTextBoxIndex].status = 0;
        }
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void FieldScriptVMHandlerSleep(void) {
    u_char nScriptId;

    nScriptId = g_FieldScriptVMCurActor->curScriptIndex;

    // Initialize the value with the argument as the time to sleep, else count down
    if (g_FieldScriptVMCurActor->scripts[nScriptId].waitTimer == 0) {
        g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].waitTimer = FieldScriptVMGetArgument(1);
    } else {
        g_FieldScriptVMCurActor->scripts[nScriptId].waitTimer--;
    }
    
    // When the timer has reached 0, we move to the next instruction
    if (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].waitTimer == 0) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
    }

    D_800B00C0 = 1;
}

void FieldScriptVMHandlerShowActorById(void) {
    FieldActor* pFieldActor;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pFieldActor = &g_FieldActors[FieldScriptVMGetActorIndex(1)];
        if (!(pFieldActor->pActorData->flags & 0x100000)) {
            pFieldActor->status &= ~ACTOR_STATUS_INVISIBLE;
            pFieldActor->pActorData->flags &= ~0x2000000;
        }
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void FieldScriptVMHandlerHideActorById(void) {
    FieldActor* pFieldActor;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pFieldActor = &g_FieldActors[FieldScriptVMGetActorIndex(1)];
        pFieldActor->status |= ACTOR_STATUS_INVISIBLE;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void FieldScriptVMHandlerShowActor(void) {
    FieldActor* pActor = &g_FieldActors[D_800AFD1C];
    pActor->status &= ~ACTOR_STATUS_INVISIBLE;
    g_FieldScriptVMCurActor->curAnimationId = 0xFF;
    g_FieldScriptVMCurActor->flags &= 0xFDFFFFFF;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009DF78(void) {
    FieldActor* pFieldActor;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        pFieldActor = &g_FieldActors[FieldScriptVMGetActorIndex(1)];
        pFieldActor->pActorData->flags |= 0x02000000;
        pFieldActor->pActorData->flags |= 0x800;
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void func_8009E014(void) {
    g_FieldScriptVMCurActor->flags |= 0x02000800;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void FieldScriptVMHandlerHideActor(void) {
    FieldActor* pActor = &g_FieldActors[D_800AFD1C];
    pActor->status |=  ACTOR_STATUS_INVISIBLE;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

// Update sprite movement or animation speed?
void func_8009E094(void) {
    unsigned short nMoveSpeed;

    nMoveSpeed = FieldScriptVMGetArgument(1);
    g_FieldScriptVMCurActor->moveSpeed = nMoveSpeed;
    func_80021BCC(g_FieldActors[D_800AFD1C].pSpriteData, nMoveSpeed);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009E10C);
/*
Matches when scriptFlags is a u32, not bitfields.

void func_8009E10C(void) {
    int nValue;
    int nUnkFlags;

    nValue = FieldScriptVMGetArgument(1);
    nUnkFlags = (nValue & 0x1) << 7; // if (nValue & 0x1) nUnkFlags |= 0x80;
    if (nValue & 0x4) nUnkFlags |= 0x20;
    if (nValue & 0x8) nUnkFlags |= 0x10;
    if (nValue & 0x10) nUnkFlags |= 8;
    if (nValue & 0x20) nUnkFlags |= 4;
    if (nValue & 0x40) nUnkFlags |= 0x08000000;
    
    g_FieldScriptVMCurActor->scriptFlags &= 0xF7FFFF43;
    g_FieldScriptVMCurActor->scriptFlags |= nUnkFlags;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}
*/

void func_8009E1A0(void) {
    u32 nValue;

    nValue = SCRIPT_READ_U8_REL(1) & 7;
    g_FieldScriptVMCurActor->flags &= ~7;
    g_FieldScriptVMCurActor->flags |= nValue;
    
    nValue = (SCRIPT_READ_U8_REL(1) >> 1) & 0x38;
    g_FieldScriptVMCurActor->flags &= ~0x38;
    g_FieldScriptVMCurActor->flags |= nValue;
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void func_8009E208(void) {
    g_FieldScriptVMCurActor->unkEC = 0;
    g_FieldScriptVMCurActor->scriptFlags_0x10 = 0x0;
    g_FieldScriptVMCurActor->scriptFlags_0x15 = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
    g_FieldScriptVMCurActor->curYPos = g_FieldScriptVMCurActor->position.vy >> 0x10;
}

void func_8009E248(void) {
    func_8009E574(
        FieldScriptVMGetInstructionArgumentS16(1),
        FieldScriptVMGetInstructionArgumentS16(3)
    );
    func_8009E810(FieldScriptVMGetInstructionArgumentS16(5));
    g_FieldScriptVMCurActor->scriptFlags_0x10 = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
}

void func_8009E2C8(void) {
    func_8009E810(func_8009CF78(1, SCRIPT_READ_U8_REL(3)));
    g_FieldScriptVMCurActor->scriptFlags_0x10 = 0x1;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 4;
}

// Read short from bytecode, absolute offset
short func_8009E330(int offset) {
    return SCRIPT_READ_U8(offset) + (SCRIPT_READ_U8(offset + 1) << 8);
}

void func_8009E35C(void) {
    g_FieldScriptVMCurActor->walkmeshId = SCRIPT_READ_U8_REL(5);
    func_8009E574(
        func_8009CF78(1, SCRIPT_READ_U8_REL(6)), 
        func_8009CFBC(3, SCRIPT_READ_U8_REL(6))
    );
    g_FieldScriptVMCurActor->flags &= ~0x200000;
    g_FieldScriptVMCurActor->scriptFlags_0xX = 0x0;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 7;
}

void func_8009E428(void) {
    ActorData* pActor;

    g_FieldScriptVMCurActor->walkmeshId = SCRIPT_READ_U8_REL(1);
    pActor = g_FieldActors[D_800AFD1C].pActorData;
    func_8009E574(pActor->position.vx >> 0x10, pActor->position.vz >> 0x10);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

void func_8009E4BC(void) {
    func_8009E574(
        func_8009CF78(1, SCRIPT_READ_U8_REL(5)), 
        func_8009CFBC(3, SCRIPT_READ_U8_REL(5))
    );
    g_FieldScriptVMCurActor->flags &= ~0x200000;
    g_FieldScriptVMCurActor->scriptFlags_0xX = 0x0;
    g_FieldScriptVMCurActor->scriptInstructionPointer += 6;
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009E574);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009E810);

void func_8009E83C(void) {
    unsigned char width;
    unsigned char zWidth;
    unsigned char height;
    unsigned char solidRange;

    width = SCRIPT_READ_U8_REL(1);
    if (width) {
        g_FieldScriptVMCurActor->width = width * 2;
    }
    
    zWidth = SCRIPT_READ_U8_REL(2);
    if (zWidth) {
        g_FieldScriptVMCurActor->zWidth = zWidth * 2;
    }
    
    height = SCRIPT_READ_U8_REL(3);
    if (height) {
        g_FieldScriptVMCurActor->height = height * 2;
    }
    
    solidRange = SCRIPT_READ_U8_REL(4);
    if (solidRange) {
        g_FieldScriptVMCurActor->solidRange = SCRIPT_READ_U8_REL(4) * 2;
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 5;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009E91C);
/*
Matches, but awaits being compiled in until unk114 struct has been better recovered.


typedef struct {
    u16 f0, f1, f2, f3, f4, f5, f6, f7;
} Tmp;

void func_8009E91C(void) {
    if (!(g_FieldScriptVMCurActor->flags12C & 0x1000)) {
        g_FieldScriptVMCurActor->unk114 = HeapAlloc(0x10, 0x0);
    }
    g_FieldScriptVMCurActor->flags12C |= 0x1000;
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f0 = func_8009CF78(0x1, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f1 = func_8009CFBC(0x3, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f2 = func_8009D000(0x5, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f3 = func_8009D044(0x7, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f4 = func_8009D088(0x9, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f5 = func_8009D0CC(0xB, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f6 = func_8009D110(0xD, SCRIPT_READ_U8_REL(0x11));
    ((Tmp*)g_FieldScriptVMCurActor->unk114)->f7 = func_8009D154(0xF, SCRIPT_READ_U8_REL(0x11));
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 0x12;
}
*/

// -1: Actor has a script slot occupied w/ target ID
//  0: Actor has no script slot w/ target ID
int FieldActorGetScriptStatus(ActorData* pActor, int targetId) {
    int i;

    for (i = 0; i < ACTOR_MAX_NUM_SCRIPTS; i++) {
        if (targetId == pActor->scripts[i].scriptId) {
            return -1;
        }
    }
    return 0;
}

void func_8009EB78(void) {
    ActorData* pActor;
    int actorIndex;
    int i;
    int curScriptId;

    if (FieldScriptVMGetActorIndex(1) != 0xFF) {
        actorIndex = FieldScriptVMGetActorIndex(1);
        pActor = g_FieldActors[actorIndex].pActorData;
        if (pActor->flags & 0x100000) {
            curScriptId = g_FieldScriptVMCurActor->curScriptIndex;
            g_FieldScriptVMCurActor->scripts[curScriptId].state = SCRIPT_STATE_IDLE;
            pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 0;
        } else if (FieldActorGetScriptStatus(pActor, SCRIPT_READ_U8_REL(2) & 0x1F) != ACTOR_SCRIPT_EXISTS) {
            for (i = 0; i < ACTOR_MAX_NUM_SCRIPTS; i++) {
                if (pActor->scripts[i].flags_0x12 != 0xF || pActor->scripts[i].isInUse) {
                    continue;
                }
                
                pActor->scripts[i].currentIP = FieldScriptGetBytecodeOffset(actorIndex, SCRIPT_READ_U8_REL(2) & 0x1F);
                pActor->scripts[i].flags_0x12 = SCRIPT_READ_U8_REL(2) >> 0x5;
                pActor->scripts[i].scriptId = SCRIPT_READ_U8_REL(2) & 0x1F;
                g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
                return;
            }
            return;
        }
    }
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_8009ED68(void) {
    ActorData* pActor;
    int actorIndex;
    int i;

    if (FieldScriptVMGetActorIndex(1) == 0xFF) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
        return;
    }
    
    actorIndex = FieldScriptVMGetActorIndex(1);
    pActor = g_FieldActors[actorIndex].pActorData;
    if (pActor->flags & 0x100000) {
        g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = SCRIPT_STATE_IDLE;
        pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 0;
    } else {
        switch (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state) {
        case 0:
            if (FieldActorGetScriptStatus(pActor, SCRIPT_READ_U8_REL(2) & 0x1F) == ACTOR_SCRIPT_EXISTS) {
                break;
            }
            
            for (i = 0; i < ACTOR_MAX_NUM_SCRIPTS; i++) {
                if (pActor->scripts[i].flags_0x12 != 0xF || pActor->scripts[i].isInUse) {
                    continue;
                }
                pActor->scripts[i].currentIP = FieldScriptGetBytecodeOffset(actorIndex, SCRIPT_READ_U8_REL(2) & 0x1F);
                pActor->scripts[i].flags_0x12 = SCRIPT_READ_U8_REL(2) >> 5;
                pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 1;
                pActor->scripts[i].scriptId = SCRIPT_READ_U8_REL(2) & 0x1F;
                g_FieldScriptVMCurActor->unkCF = i;
                g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = 1;
                break;
            }
            return;
        case 1:
            if ((pActor->curScriptIndex == g_FieldScriptVMCurActor->unkCF) || pActor->scripts[g_FieldScriptVMCurActor->unkCF].flags_0x12 == 0xF) {
                g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
                g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = SCRIPT_STATE_IDLE;
                pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 0;
            } else {
                D_800B00C0 = g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state;
            }
            return;
        default:
            return;
        }
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_8009F0A0(void) {
    ActorData* pActor;
    s32 actorIndex;
    int i;

    if (FieldScriptVMGetActorIndex(1) == 0xFF) {
        g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
        return;
    }
    
    actorIndex = FieldScriptVMGetActorIndex(1);
    pActor = g_FieldActors[actorIndex].pActorData;
    if (pActor->flags & 0x100000) {
        g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = SCRIPT_STATE_IDLE;
        pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 0;
    } else {
        switch (g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state) {
        case 0:
            if (FieldActorGetScriptStatus(pActor, SCRIPT_READ_U8_REL(2) & 0x1F) == ACTOR_SCRIPT_EXISTS) {
                g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
                break;
            }
            
            for (i = 0; i < ACTOR_MAX_NUM_SCRIPTS; i++) {
                if (pActor->scripts[i].flags_0x12 != 0xF || pActor->scripts[i].isInUse) {
                    continue;
                }
                pActor->scripts[i].currentIP = FieldScriptGetBytecodeOffset(actorIndex, SCRIPT_READ_U8_REL(2) & 0x1F);
                pActor->scripts[i].flags_0x12 = SCRIPT_READ_U8_REL(2) >> 5;
                pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 1;
                g_FieldScriptVMCurActor->unkCF = i;
                g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = 1;
                pActor->scripts[i].scriptId = SCRIPT_READ_U8_REL(2) & 0x1F;
                return;
            }
            break;
        case 1:
            if ((pActor->curScriptIndex == g_FieldScriptVMCurActor->unkCF) || pActor->scripts[g_FieldScriptVMCurActor->unkCF].flags_0x12 == 0xF) {
                g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = 2;
                return;
            }
            D_800B00C0 = 1;
            break;
        case 2:
            if (pActor->scripts[g_FieldScriptVMCurActor->unkCF].flags_0x12 == 0xF) {
                g_FieldScriptVMCurActor->scripts[g_FieldScriptVMCurActor->curScriptIndex].state = SCRIPT_STATE_IDLE;
                pActor->scripts[g_FieldScriptVMCurActor->unkCF].isInUse = 0;
                g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
                return;
            }
            D_800B00C0 = 1;
            break;
        }
        return;
    }
    
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

// Randomize X rotation
void func_8009F424(void) {
    int nRotation;
    
    nRotation = g_FieldScriptVMCurActor->rotationY;
    g_FieldScriptVMCurActor->unk102++;
    if (!(g_FieldScriptVMCurActor->unk102 & 0xF)) {
        if (!(rand() & 0x1)) {
            nRotation = (g_FieldScriptVMCurActor->rotationY + 0x200) & 0xFFF;
        } else {
            nRotation = (g_FieldScriptVMCurActor->rotationY - 0x200) & 0xFFF;
        }
    }
    D_800B00C0 = 1;
    g_FieldScriptVMCurActor->rotationX = nRotation;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009F4CC(void) {
    short nSpecialRotation;
    int nRotation;
    int nRand;
    int nDeltaRotation;

    nRotation = g_FieldScriptVMCurActor->rotationY;
    g_FieldScriptVMCurActor->unk102++;
    if (!(g_FieldScriptVMCurActor->unk102 & 0xF)) {
        nRand = rand();
        if (nRand & 0x30) {
            nSpecialRotation = g_FieldScriptVMCurActor->rotationY | ~0x7FFF;
            nRotation = nSpecialRotation;
            g_FieldScriptVMCurActor->rotationY = nSpecialRotation;
        } else {
            if (!(nRand & 1)) {
                nDeltaRotation = g_FieldScriptVMCurActor->rotationY + 0x200;
            } else {
                nDeltaRotation = g_FieldScriptVMCurActor->rotationY - 0x200;
            }
            nRotation = nDeltaRotation & 0xFFF;
        }
    }
    D_800B00C0 = 1;
    g_FieldScriptVMCurActor->rotationX = nRotation;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

void func_8009F5A8(void) {
    unsigned short nStoredIP = g_FieldScriptVMCurActor->scriptInstructionPointer;
    func_8009F5F4(); // Do Encounter
    D_800B00C0 = 1;
    g_FieldScriptVMCurActor->scriptInstructionPointer = nStoredIP;
}


INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009F5F4);

int FieldCharacterIdToPartyId(int characterId) {
    int i;

    if (characterId == CHARACTER_ID_NONE) {
        return -1;
    }
    
    for (i = 0; i < 3; i++) {
        if (g_GamePartyMembers[i] == CHARACTER_ID_NONE)
            return -1;
        
        if (g_GamePartyMembers[i] == characterId) {
            return i;
        }
    }

    return -1;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009FA54);

extern s32 D_8004F34C;
extern s32 D_800B2268[];

void func_8009FB98(void) {
    D_8004F34C |= 0xC000;
    GameWaitForCdData();
    GamePartySyncSkinData();
    GamePartySyncStreamedData();
    D_800B2268[0] = SCRIPT_READ_U8_REL(1);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 2;
}

extern s32 D_8006F990[];
int func_8009FC10(int arg0) {
    int i;

    for (i = 0; i < 3; i++) {
        if (D_8006F990[i] == arg0) {
            return i;
        }
    }
    
    return 0xFF;
}


void func_8009FC48(void) {
    int index = FieldScriptVMGetArgument(1);
    if (index >= 3) {
        index = 2;
    }
    *((u8*)g_GameState + index + 0x22B1) = 1;
    func_8009FD10(index);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

void func_8009FCAC(void) {
    int index = FieldScriptVMGetArgument(1);
    if (index >= 3) {
        index = 2;
    }
    *((u8*)g_GameState + index + 0x22B1) = 0;
    func_8009FD10(index);
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

extern int D_8004F34C;
void func_8009FD10(int arg0) {
    switch (arg0) { 
        case 0:
            FieldScriptMemoryWriteU16(0x2A, D_8004F34C & 0xFFF);
            FieldScriptMemoryWriteU16(0x2C, 0);
            FieldScriptMemoryWriteU16(0x2E, 0);
            break;
        case 1:
            FieldScriptMemoryWriteU16(0x30, D_8004F34C & 0xFFF);
            FieldScriptMemoryWriteU16(0x32, 0);
            FieldScriptMemoryWriteU16(0x34, 0);
            break;
        case 2:
            FieldScriptMemoryWriteU16(0x36, D_8004F34C & 0xFFF);
            FieldScriptMemoryWriteU16(0x38, 0);
            FieldScriptMemoryWriteU16(0x3A, 0);
            break;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009FDD4);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009FE4C);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_8009FEE4);

void func_800A0158(s32 arg0, s32* arg1, s32* arg2, s32* arg3) {
    switch (arg0) {
        case 0:
            *arg1 = FieldScriptVMGetVariableValue(0x2A);
            *arg2 = FieldScriptVMGetVariableValue(0x2C);
            *arg3 = FieldScriptVMGetVariableValue(0x2E);
            break;
        case 1:
            *arg1 = FieldScriptVMGetVariableValue(0x30);
            *arg2 = FieldScriptVMGetVariableValue(0x32);
            *arg3 = FieldScriptVMGetVariableValue(0x34);
            break;
        case 2:
            *arg1 = FieldScriptVMGetVariableValue(0x36);
            *arg2 = FieldScriptVMGetVariableValue(0x38);
            *arg3 = FieldScriptVMGetVariableValue(0x3A);
            break;
    }
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0228);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0524);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A06E8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A08B8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0C4C);

// FieldResetActorPosition, set translation and sprite position of actor based on current actor data position
INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0C94);

void func_800A0D3C(void) {
    func_80076AC0(D_800AFD1C, 0, (void*)((*(s32*)(g_FieldSpriteData + 4)) + (s32)g_FieldSpriteData), 0, 0, 0x80, 1);
    func_800A0C94();
    g_FieldScriptVMCurActor->scriptFlags_0x8 = 0x1;
    g_FieldScriptVMCurActor->flags |= 0x800;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0DC0);

void func_800A0DFC(void) {
    int addr = FieldScriptVMGetInstructionArgument(1) & 0xFFFF;
    FieldScriptMemoryWriteU16(addr, ArchiveGetDiscNumber());
    g_FieldScriptVMCurActor->scriptInstructionPointer += 3;
}

extern s32 D_800ADB74;

void func_800A0E54(void) {
    if (D_800ADB74 == 0) {
        g_FieldScriptVMCurActor->scriptInstructionPointer++;
    } else {
        g_FieldScriptVMCurActor->scriptInstructionPointer--;
    }
    D_800B00C0 = 1;
}

extern s32 D_800ADB84;

void func_800A0EB0(void) {
    D_800B00C0 = 1;
    D_800ADB84++;
    g_FieldScriptVMCurActor->scriptInstructionPointer++;
}

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0EE8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A0FD8);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A1364);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A14F0);

INCLUDE_ASM("asm/field/nonmatchings/main/misc6", func_800A1624);
