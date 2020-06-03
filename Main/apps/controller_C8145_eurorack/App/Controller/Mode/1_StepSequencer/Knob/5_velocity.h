/*
 * VELOCITY
 * 
 * Knob 5 action in mode number 1.
 */
#define Controller_Mode_1_Knob_5_Action(knobVal) {\
    Controller_Knob_StartMeasureSpeed(CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_5);\
    if (Controller_Mode_1_isAltLeftFlag()) {\
        Controller_Mode_1_Knob_5_SetNoteStepAction(knobVal);\
    } else {\
        Controller_Mode_1_Knob_5_TrigNoteVelocityAction(knobVal);\
    }\
}

/* 
 * Set note step action
 */
#define Controller_Mode_1_Knob_5_SetNoteStepAction(knobVal) {\
    if ((knobVal >> 4) < 13) {\
        controller.mode.mode1.trigNoteStep = (knobVal >> 4);\
    }\
    Controller_View_Param_Show(controller.mode.mode1.trigNoteStep);\
}

/* 
 * Set Trig note velocity action
 */
#define Controller_Mode_1_Knob_5_TrigNoteVelocityAction(knobVal) {\
    controller.notes.velocity = knobVal;\
    switch (Controller_Mode_1_GetTrigDirection()) {\
        case CONTROLLER_MODE_1_CFG_TRIG_DIR_ALL:\
        Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
        break;\
        case CONTROLLER_MODE_1_CFG_TRIG_DIR_FWD:\
        if (Controller_Knob_GetDirection(5, knobVal) == CONTROLLER_KNOB_CFG_DIR_FWD) {\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
        }\
        break;\
        case CONTROLLER_MODE_1_CFG_TRIG_DIR_BCK:\
        if (Controller_Knob_GetDirection(5, knobVal) == CONTROLLER_KNOB_CFG_DIR_BKD) {\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
        }\
        break;\
    }\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Sequencer_SetPatternStepData(\
            Controller_Sequencer_GetEditPatternNumber(), \
            Controller_Sequencer_GetEditStepNumber(), \
            controller.mode.mode1.lastNoteNumber, \
            controller.notes.velocity, \
            controller.notes.gateTime\
        );\
    }\
}

