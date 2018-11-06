/*
 * NOTE TRIG
 * key action handler
 * 
 * Knob 4 action in mode number 1.
 */
#define Controller_Mode_1_Knob_4_Action(knobVal) {\
    Controller_Knob_StartMeasureSpeed(CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_4);\
    if (Controller_Mode_1_isShiftLeftFlag()) {\
        Controller_Mode_1_Knob_4_ShiftLeftAction(knobVal);\
    } else {\
        controller.mode.mode1.lastNoteNumber = (BYTE)(knobVal * controller.mode.mode1.trigNoteStep) & 0b01111111;\
        switch (Controller_Mode_1_GetTrigDirection()) {\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_ALL:\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            break;\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_FWD:\
            if (Controller_Knob_GetDirection(4, knobVal) == CONTROLLER_KNOB_CFG_DIR_FWD) {\
                Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            }\
            break;\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_BCK:\
            if (Controller_Knob_GetDirection(4, knobVal) == CONTROLLER_KNOB_CFG_DIR_BKD) {\
                Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            }\
            break;\
        }\
    }\
    if (Controller_Mode_1_isKeyNoteDown(CONTROLLER_MODE_1_CFG_KEY_NOTE_1_NUM) && Controller_Mode_1_isFunctionFlag()) {\
        MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[0].number, 0);\
        controller.mode.mode1.keyNote[0].number = controller.mode.mode1.lastNoteNumber;\
    }\
    if (Controller_Mode_1_isKeyNoteDown(CONTROLLER_MODE_1_CFG_KEY_NOTE_2_NUM) && Controller_Mode_1_isFunctionFlag()) {\
        MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[1].number, 0);\
        controller.mode.mode1.keyNote[1].number = controller.mode.mode1.lastNoteNumber;\
    }\
    if (Controller_Mode_1_isKeyNoteDown(CONTROLLER_MODE_1_CFG_KEY_NOTE_3_NUM) && Controller_Mode_1_isFunctionFlag()) {\
        MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[2].number, 0);\
        controller.mode.mode1.keyNote[2].number = controller.mode.mode1.lastNoteNumber;\
    }\
    if (Controller_Mode_1_isKeyNoteDown(CONTROLLER_MODE_1_CFG_KEY_NOTE_4_NUM) && Controller_Mode_1_isFunctionFlag()) {\
        MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[3].number, 0);\
        controller.mode.mode1.keyNote[3].number = controller.mode.mode1.lastNoteNumber;\
    }\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Sequencer_SetPatternStepData(\
            Controller_Sequencer_GetEditPatternNumber(), \
            Controller_Sequencer_GetEditPatternStepNumber(), \
            controller.mode.mode1.lastNoteNumber, \
            controller.notes.velocity, \
            controller.notes.gateTime\
        );\
    }\
}

/* 
 * Knob 4 action when left shift is on
 */
#define Controller_Mode_1_Knob_4_ShiftLeftAction(knobVal) {\
    if ((controller.mode.mode1.lastNoteNumber & 0b00011111) != (knobVal >> 2)) {\
        controller.mode.mode1.lastNoteNumber = (knobVal >> 2) + (controller.mode.mode1.lastNoteNumber & 0b01100000);\
        Controller_Notes_On(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
    }\
}
