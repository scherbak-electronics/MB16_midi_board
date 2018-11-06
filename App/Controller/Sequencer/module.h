/*
 * Controller_Sequencer module
 * 
 * Sequencer Module
 * 16 steps pattern sequencer.
 */
#include "View/module.h"

#define CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER          0
#define CONTROLLER_SEQUENCER_FLAG_PLAY_PATTERN          1
#define CONTROLLER_SEQUENCER_FLAG_REC                   2

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
    BYTE editPatternStepNumber;
    BYTE structureNumber;
    struct SEQUENCER_VIEW_MODULE view;
    BYTE tempo;
    BYTE bpmTimer;
};

#define Controller_Sequencer_setStepTriggerFlag()                           set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)
#define Controller_Sequencer_clrStepTriggerFlag()                           clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)
#define Controller_Sequencer_isStepTriggerFlag()                            bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_STEP_TRIGGER)

#define Controller_Sequencer_setPlayPatternFlag()                           set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY_PATTERN)
#define Controller_Sequencer_clrPlayPatternFlag()                           clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY_PATTERN)
#define Controller_Sequencer_isPlayPatternFlag()                            bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_PLAY_PATTERN)

#define Controller_Sequencer_setRecFlag()                                   set_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)
#define Controller_Sequencer_clrRecFlag()                                   clr_bit(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)
#define Controller_Sequencer_isRecFlag()                                    bit_is_set(controller.sequencer.flags, CONTROLLER_SEQUENCER_FLAG_REC)

#define Controller_Sequencer_SetEditPatternNumber(num)                      controller.sequencer.editPatternNumber = num
#define Controller_Sequencer_GetEditPatternNumber()                         controller.sequencer.editPatternNumber
#define Controller_Sequencer_SetEditPatternStepNumber(num)                  controller.sequencer.editPatternStepNumber = num
#define Controller_Sequencer_GetEditPatternStepNumber()                     controller.sequencer.editPatternStepNumber

#define Controller_Sequencer_SetPatternStepNoteNumber(patt, pos, noteNum)   controller.sequencer.patterns[patt][pos].noteNumber = noteNum
#define Controller_Sequencer_SetPatternStepVelocity(patt, pos, velo)        controller.sequencer.patterns[patt][pos].velocity = velo
#define Controller_Sequencer_SetPatternStepGateTime(patt, pos, gate)        controller.sequencer.patterns[patt][pos].gateTime = gate
#define Controller_Sequencer_SetTempo(temp)                                 controller.sequencer.tempo = temp


/*
 * Module Initialization.
 */
#define Controller_Sequencer_Init() {\
    controller.sequencer.flags = 0;\
    controller.sequencer.structureNumber = 0;\
    controller.sequencer.playStepNumber = 0;\
    controller.sequencer.editPatternNumber = 0;\
    controller.sequencer.editPatternStepNumber = 0;\
    controller.sequencer.tempo = CONTROLLER_SEQUENCER_CFG_DEFAULT_TEMPO;\
    controller.sequencer.bpmTimer = controller.sequencer.tempo;\
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
            Controller_Sequencer_setStepTriggerFlag();\
            controller.sequencer.bpmTimer = controller.sequencer.tempo;\
        }\
    }\
}

/*
 * Play pattern positions Process.
 */
#define Controller_Sequencer_PlayProcess() {\
    if (Controller_Sequencer_isPlayPatternFlag() && Controller_Sequencer_isStepTriggerFlag()) {\
        Controller_Sequencer_clrStepTriggerFlag();\
        Controller_Sequencer_PlayPatternPosition(0, controller.sequencer.playStepNumber);\
        if (controller.sequencer.playStepNumber < CONTROLLER_SEQUENCER_CFG_PATTERN_LEN - 1) {\
            controller.sequencer.playStepNumber++;\
        } else {\
            controller.sequencer.playStepNumber = 0;\
        }\
    }\
}

/*
 * Play pattern position by pattern number and position number.
 */
#define Controller_Sequencer_PlayPatternPosition(patt, pos) {\
    if (controller.sequencer.patterns[patt][pos].noteNumber != CONTROLLER_NOTES_CFG_NOTE_OFF) {\
        controller.mode.mode1.lastNoteNumber = controller.sequencer.patterns[patt][pos].noteNumber;\
        Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.sequencer.patterns[patt][pos].velocity, controller.sequencer.patterns[patt][pos].gateTime);\
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

/*
 * Start sequencer playback.
 */
#define Controller_Sequencer_StartPlayback() {\
    if (!Controller_Sequencer_isPlayPatternFlag()) {\
        controller.sequencer.playStepNumber = 0;\
        Controller_Sequencer_setPlayPatternFlag();\
    }\
}

/*
 * Stop sequencer.
 */
#define Controller_Sequencer_StopPlayback() {\
    if (Controller_Sequencer_isPlayPatternFlag()) {\
        Controller_Sequencer_clrPlayPatternFlag();\
    }\
}
