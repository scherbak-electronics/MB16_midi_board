/*
 * Button N1 (note play key num 0)
 * Key 10 action handler.
 * Play/Stop key note 1
 * NOTE: keyNote array has zero based index. 
 */

/*  
 * Play key note 1. 
 * sends note on MIDI message. Note number depends on...
 */
#define Controller_Mode_1_Key_10_DownAction() {\
    if (Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isFunctionFlag()) {\
            /* assign prog to key */\
            Controller_Key_AssignProgramNumber(0, Controller_Program_GetLastUsedNumber());\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY, CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT);\
        } else {\
            /* change the program to assigned */\
            MIDI_Out_SendProgramChange(Controller_Key_GetAssignedProgramNumber(0));\
        }\
    } else {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            Controller_LFO_SetRate(0);\
            if (!Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Play();\
                Controller_Sync_ResetDividerCounters();\
            }\
        } else {\
            controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[0].number + controller.mode.mode1.baseNoteNumber + Controller_Notes_GetOctaveNoteNumber();\
            controller.mode.mode1.keyNote[0].actualNumber = controller.mode.mode1.lastNoteNumber;\
            MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[0].actualNumber, controller.notes.velocity);\
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
    }\
}

/* 
 * Stop play key note 1.
 * sends note off MIDI message.
 */
#define Controller_Mode_1_Key_10_UpAction() {\
    if (!Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            if (Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Stop();\
            }\
        } else {\
            MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[0].actualNumber, 0);\
        }\
    }\
}
