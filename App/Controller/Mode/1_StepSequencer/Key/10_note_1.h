/*
 * N1
 * Key 10 action handler.
 * Play/Stop key note 1
 * NOTE: keyNote array has zero based index. 
 */

/*  
 * Play key note 1. 
 * sends note on MIDI message. Note number depends on...
 */
#define Controller_Mode_1_Key_10_DownAction() {\
    MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[0].number, controller.notes.velocity);\
    controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[0].number;\
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
 * Stop play key note 1.
 * sends note off MIDI message.
 */
#define Controller_Mode_1_Key_10_UpAction() {\
    MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[0].number, 0);\
}
