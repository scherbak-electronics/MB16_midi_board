/*
 * Mode 1
 * Key number 11 up and down actions.
 * Play/Stop key note 2
 * NOTE: keyNote array has zero based index. 
 */

/*  
 * Play key note 2. 
 * sends note on MIDI message. Note number depends on...
 */
#define Controller_Mode_1_Key_11_DownAction() {\
    MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[1].number, controller.notes.velocity);\
    controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[1].number;\
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
 * Stop play key note 2.
 * sends note off MIDI message.
 */
#define Controller_Mode_1_Key_11_UpAction() {\
    MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[1].number, 0);\
}
