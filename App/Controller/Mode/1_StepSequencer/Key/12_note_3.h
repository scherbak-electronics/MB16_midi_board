/*
 * N3
 * key action handler
 * 
 * Key 12 action in mode 1.
 * Play key note 3. Save pattern data if FN key is pressed.
 */
#define Controller_Mode_1_Key_12_DownAction() {\
    MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[2].number, controller.notes.velocity);\
    controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[2].number;\
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

#define Controller_Mode_1_Key_12_UpAction() {\
    MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[2].number, 0);\
}
