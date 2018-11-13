/*
 * N4
 * key action handler
 * 
 * Key 13 action in mode number 1.
 * Play key note 4. Clear pattern data if FN key is pressed.
 */
#define Controller_Mode_1_Key_13_DownAction() {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Sequencer_ClearStepData(\
            Controller_Sequencer_GetEditPatternNumber(), \
            Controller_Sequencer_GetEditStepNumber()\
        );\
    } else {\
        MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[3].number, controller.notes.velocity);\
        controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[3].number;\
        if (Controller_Sequencer_isRecFlag()) {\
            Controller_Sequencer_SetPatternStepData(\
                Controller_Sequencer_GetEditPatternNumber(), \
                Controller_Sequencer_GetEditStepNumber(), \
                controller.mode.mode1.lastNoteNumber, \
                controller.notes.velocity, \
                controller.notes.gateTime\
            );\
        }\
    }\
}

#define Controller_Mode_1_Key_13_UpAction() {\
    if (!Controller_Mode_1_isFunctionFlag()) {\
        MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[3].number, 0);\
    }\
}
