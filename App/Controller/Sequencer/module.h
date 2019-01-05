/*
 * Controller_Sequencer module
 * 
 * Sequencer Module
 * 16 steps pattern sequencer.
 */
#include "View/module.h"

#define CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER          0
#define CONTROLLER_SEQUENCER_FLAG_PLAY          1
#define CONTROLLER_SEQUENCER_FLAG_REC                   2
#define CONTROLLER_SEQUENCER_FLAG_OVERDUB               3

#define CONTROLLER_SEQUENCER_CFG_PATTERN_LEN            16
#define CONTROLLER_SEQUENCER_CFG_PATTERS_COUNT          4
#define CONTROLLER_SEQUENCER_CFG_DEFAULT_TEMPO          50

struct PATTERN_STEP_DATA {
    BYTE noteNumber;
    BYTE velocity;
    BYTE gateTime;
};

struct SEQUENCER_MODULE {
    BYTE flags;
    struct PATTERN_STEP_DATA patterns[CONTROLLER_SEQUENCER_CFG_PATTERS_COUNT][CONTROLLER_SEQUENCER_CFG_PATTERN_LEN];
    BYTE playStepNumber;
    BYTE editPatternNumber;
    BYTE editStepNumber;
    BYTE editStepNumberPrev;
    BYTE structureNumber;
    struct SEQUENCER_VIEW_MODULE view;
    BYTE tempo;
    BYTE bpmTimer;
    BYTE gateTime;
    BYTE programNumber;
    BYTE stepTriggerDividerCounter;
};

#define Controller_Sequencer_setStepTriggerFlag()                           set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)
#define Controller_Sequencer_clrStepTriggerFlag()                           clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)
#define Controller_Sequencer_isStepTriggerFlag()                            bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)

#define Controller_Sequencer_setPlayingFlag()                           set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY)
#define Controller_Sequencer_clrPlayingFlag()                           clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY)
#define Controller_Sequencer_isPlayingFlag()                            bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY)

#define Controller_Sequencer_setRecFlag()                                   set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)
#define Controller_Sequencer_clrRecFlag()                                   clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)
#define Controller_Sequencer_isRecFlag()                                    bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)

#define Controller_Sequencer_setOverdubFlag()                                   set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_OVERDUB)
#define Controller_Sequencer_clrOverdubFlag()                                   clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_OVERDUB)
#define Controller_Sequencer_isOverdubFlag()                                    bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_OVERDUB)
#define Controller_Sequencer_invOverdubFlag()                                    inv_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_OVERDUB)


#define Controller_Sequencer_SetEditPatternNumber(num)                      controller.sequencer.editPatternNumber = num
#define Controller_Sequencer_GetEditPatternNumber()                         controller.sequencer.editPatternNumber
#define Controller_Sequencer_SetEditStepNumber(num)                         controller.sequencer.editStepNumber = num
#define Controller_Sequencer_GetEditStepNumber()                            controller.sequencer.editStepNumber
#define Controller_Sequencer_IsEditStepNumberChanged()                      (controller.sequencer.editStepNumber != controller.sequencer.editStepNumberPrev)
#define Controller_Sequencer_RenewPreviousEditStepNumber(num)               controller.sequencer.editStepNumberPrev = controller.sequencer.editStepNumber

#define Controller_Sequencer_SetStepNoteNumber(patt, pos, noteNum)          controller.sequencer.patterns[patt][pos].noteNumber = noteNum
#define Controller_Sequencer_SetStepVelocity(patt, pos, velo)               controller.sequencer.patterns[patt][pos].velocity = velo
#define Controller_Sequencer_SetStepGateTime(patt, pos, gate)               controller.sequencer.patterns[patt][pos].gateTime = gate
//#define Controller_Sequencer_SetTempo(temp)                                 controller.sequencer.tempo = temp
#define Controller_Sequencer_SetTempo(temp)                                 Controller_Sync_SetTempo(temp)
#define Controller_Sequencer_GetCurrentEditStep(stepNum)                    controller.sequencer.patterns[controller.sequencer.editPatternNumber][stepNum]


/*
 * Module Initialization.
 */
#define Controller_Sequencer_Init() {\
    controller.sequencer.flags = 0;\
    controller.sequencer.structureNumber = 0;\
    controller.sequencer.playStepNumber = 0;\
    controller.sequencer.editPatternNumber = 0;\
    controller.sequencer.editStepNumber = 0;\
    controller.sequencer.editStepNumberPrev = 0;\
    controller.sequencer.tempo = CONTROLLER_SEQUENCER_CFG_DEFAULT_TEMPO;\
    controller.sequencer.bpmTimer = controller.sequencer.tempo;\
    controller.sequencer.gateTime = 1;\
    controller.sequencer.programNumber = 0;\
    controller.sequencer.stepTriggerDividerCounter = 0;\
    system.var = 0;\
    for (; system.var < CONTROLLER_SEQUENCER_CFG_PATTERN_LEN; system.var++) {\
        controller.sequencer.patterns[0][system.var].noteNumber = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.patterns[0][system.var].velocity = 0;\
        controller.sequencer.patterns[0][system.var].gateTime = 1;\
        controller.sequencer.patterns[1][system.var].noteNumber = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.patterns[1][system.var].velocity = 0;\
        controller.sequencer.patterns[1][system.var].gateTime = 1;\
        controller.sequencer.patterns[2][system.var].noteNumber = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.patterns[2][system.var].velocity = 0;\
        controller.sequencer.patterns[2][system.var].gateTime = 1;\
        controller.sequencer.patterns[3][system.var].noteNumber = CONTROLLER_NOTES_CFG_NOTE_OFF;\
        controller.sequencer.patterns[3][system.var].velocity = 0;\
        controller.sequencer.patterns[3][system.var].gateTime = 1;\
    }\
    Controller_Sequencer_View_Init();\
}

/*
 * Module Main Process.
 */
#define Controller_Sequencer_Process() {\
    Controller_Sequencer_PlayProcess();\
}

/*
 * BPM timer Process.
 */
#define Controller_Sequencer_BPMTimerProcess() {\
    if (controller.sequencer.bpmTimer != 0) {\
        controller.sequencer.bpmTimer--;\
        if (controller.sequencer.bpmTimer == 0) {\
            /*Controller_Sequencer_setStepTriggerFlag();*/\
            controller.sequencer.bpmTimer = controller.sequencer.tempo;\
        }\
    }\
}

/*
 * Start sequencer playback.
 */
#define Controller_Sequencer_StartPlayback() {\
    controller.sequencer.playStepNumber = 0;\
    controller.sequencer.stepTriggerDividerCounter = 0;\
    Controller_Sequencer_setPlayingFlag();\
    Controller_Sequencer_clrStepTriggerFlag();\
}

/*
 * Stop sequencer.
 */
#define Controller_Sequencer_StopPlayback() {\
    Controller_Sequencer_clrPlayingFlag();\
    controller.sequencer.stepTriggerDividerCounter = 0;\
}

/*
 * When diivider counter reach target value 
 * sequencer position will be triggered
 */
#define Controller_Sequencer_StepTrigDividerCounterProcess() {\
    if (Controller_Sequencer_isPlayingFlag()) {\
        if (controller.sequencer.stepTriggerDividerCounter > 5) {\
            controller.sequencer.stepTriggerDividerCounter = 0;\
        }\
        if (controller.sequencer.stepTriggerDividerCounter == 0) {\
            Controller_Sequencer_setStepTriggerFlag();\
        }\
        controller.sequencer.stepTriggerDividerCounter++;\
    }\
}

/*
 * Play pattern positions Process.
 */
#define Controller_Sequencer_PlayProcess() {\
    if (Controller_Sequencer_isPlayingFlag() && Controller_Sequencer_isStepTriggerFlag()) {\
        System_Led_Blink(0);\
        Controller_Sequencer_clrStepTriggerFlag();\
        Controller_Sequencer_PlayStep(\
            controller.sequencer.editPatternNumber,\
            controller.sequencer.playStepNumber\
        );\
        if (Controller_Sequencer_isOverdubFlag()) {\
            Controller_Sequencer_SetEditStepNumber(controller.sequencer.playStepNumber);\
            Controller_Sequencer_View_Show();\
        }\
        if (controller.sequencer.playStepNumber < (CONTROLLER_SEQUENCER_CFG_PATTERN_LEN - 1)) {\
            controller.sequencer.playStepNumber++;\
        } else {\
            controller.sequencer.playStepNumber = 0;\
        }\
    }\
}

/*
 * Play pattern step by pattern number and step number.
 */
#define Controller_Sequencer_PlayStep(patt, stepNum) {\
    if (controller.sequencer.patterns[patt][stepNum].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        controller.mode.mode1.lastNoteNumber = controller.sequencer.patterns[patt][stepNum].noteNumber;\
        if (controller.sequencer.programNumber != controller.program.number) {\
            controller.sequencer.programNumber = controller.program.number;\
            MIDI_Out_SendProgramChange(controller.sequencer.programNumber);\
        }\
        if (controller.sequencer.gateTime != controller.notes.gateTime) {\
            controller.sequencer.gateTime = controller.notes.gateTime;\
            Controller_Notes_OnMono(\
                0,\
                controller.mode.mode1.lastNoteNumber,\
                controller.sequencer.patterns[patt][stepNum].velocity,\
                controller.sequencer.gateTime\
            );\
        } else {\
            Controller_Notes_On(\
                controller.mode.mode1.lastNoteNumber,\
                controller.sequencer.patterns[patt][stepNum].velocity,\
                controller.sequencer.patterns[patt][stepNum].gateTime\
            );\
        }\
    }\
}

/*
 * Sets play cursor to zero step.
 */
#define Controller_Sequencer_ResetPlayPosition() {\
    controller.sequencer.playStepNumber = 0;\
}

/*
 * Select sequencer structure 
 */
#define Controller_Sequencer_SelectStructure(structNum) {\
    controller.sequencer.structureNumber = structNum;\
    if (controller.sequencer.structureNumber) {\
    }\
}

/*
 * Set pattern data by pattern number and position number.
 */
#define Controller_Sequencer_SetPatternStepData(patt, pos, noteNum, velo, gate) {\
    controller.sequencer.patterns[patt][pos].noteNumber = noteNum;\
    controller.sequencer.patterns[patt][pos].velocity = velo;\
    controller.sequencer.patterns[patt][pos].gateTime = gate;\
}

#define Controller_Sequencer_ClearStepData(patt, pos) {\
    controller.sequencer.patterns[patt][pos].noteNumber = CONTROLLER_NOTES_CFG_NOTE_OFF;\
    controller.sequencer.patterns[patt][pos].velocity = 0;\
    controller.sequencer.patterns[patt][pos].gateTime = 1;\
}
