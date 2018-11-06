/*
 * VELOCITY
 * 
 * Knob 5 action in mode number 1.
 */
#define Controller_Mode_1_Knob_5_Action(knobVal) {\
    Controller_Knob_StartMeasureSpeed(CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_5);\
    if (Controller_Mode_1_isAltLeftFlag()) {\
        Controller_Mode_1_Knob_5_AltLeftAction(knobVal);\
    } else {\
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
    }\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Sequencer_SetPatternStepVelocity(\
            Controller_Sequencer_GetEditPatternNumber(), \
            controller.sequencer.editPatternStepNumber, \
            controller.notes.velocity \
        );\
    }\
}

/* 
 * Knob 4 action when left shift is on
 */
#define Controller_Mode_1_Knob_5_AltLeftAction(knobVal) {\
    controller.mode.mode1.trigNoteStep = ((knobVal + 1) % 12);\
}
