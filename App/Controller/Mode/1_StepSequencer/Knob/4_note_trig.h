/*
 * NOTE TRIG
 * Knob 4 action in mode number 1.
 * Action name substituted in Controller_Mode module.
 */
#define Controller_Mode_1_Knob_4_Action(knobVal) {\
    Controller_Knob_StartMeasureSpeed(CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_4);\
    controller.mode.mode1.lastNoteNumber = controller.mode.mode1.lastNoteNumber >> controller.mode.mode1.noteTrigResolution;\
    controller.mode.mode1.lastNoteNumber = ((BYTE)(knobVal * controller.mode.mode1.trigNoteStep) & 0b01111111);\
    controller.mode.mode1.lastNoteNumber = \
        Controller_Notes_Scale_GetNote(controller.mode.mode1.lastNoteNumber) + \
        controller.mode.mode1.lastNoteNumber + \
        controller.mode.mode1.baseNoteNumber + \
        Controller_Notes_GetOctaveNoteNumber();\
    Controller_Mode_1_Knob_4_NoteTrigDefaultAction(knobVal);\
    /* Controller_Mode_1_Knob_4_NoteAssignmentAction(knobVal); */\
    if (Controller_Sequencer_isRecFlag()) {\
        Controller_Mode_1_Knob_4_SequencerRecAction(knobVal);\
    }\
}

/*
 * Default action for note triggering
 */
#define Controller_Mode_1_Knob_4_NoteTrigDefaultAction(knobVal) {\
    if (!Controller_LFO_isPlayingFlag()) {\
        switch (Controller_Mode_1_GetTrigDirection()) {\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_ALL:\
            Controller_Notes_OnSingle(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            break;\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_FWD:\
            if (Controller_Knob_GetDirection(4, knobVal) == CONTROLLER_KNOB_CFG_DIR_FWD) {\
                Controller_Notes_OnSingle(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            }\
            break;\
            case CONTROLLER_MODE_1_CFG_TRIG_DIR_BCK:\
            if (Controller_Knob_GetDirection(4, knobVal) == CONTROLLER_KNOB_CFG_DIR_BKD) {\
                Controller_Notes_OnSingle(controller.mode.mode1.lastNoteNumber, controller.notes.velocity, controller.notes.gateTime);\
            }\
            break;\
        }\
    }\
}

/*
 * Note assignment action.
 */
#define Controller_Mode_1_Knob_4_NoteAssignmentAction(knobVal) {\
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
}

/*
 * Sequencer record action
 * When REC switch is on
 */
#define Controller_Mode_1_Knob_4_SequencerRecAction(knobVal) {\
    Controller_Sequencer_SetPatternStepData(\
        Controller_Sequencer_GetEditPatternNumber(), \
        Controller_Sequencer_GetEditStepNumber(), \
        controller.mode.mode1.lastNoteNumber, \
        controller.notes.velocity, \
        controller.notes.gateTime\
    );\
}

