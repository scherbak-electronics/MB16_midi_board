/*
 * Button N2 (note play key num 1)
 * Key number 11 up and down actions.
 * Play/Stop key note 2
 * NOTE: keyNote array has zero based index. 
 */

/*  
 * Play key note 2. 
 * sends note on MIDI message. Note number depends on...
 */
#define Controller_Mode_1_Key_11_DownAction() {\
    if (Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isFunctionFlag()) {\
            /* assign prog to key */\
            Controller_Key_AssignProgramNumber(1, Controller_Program_GetLastUsedNumber());\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY, CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT);\
        } else {\
            /* change the program to assigned */\
            MIDI_Out_SendProgramChange(Controller_Key_GetAssignedProgramNumber(1));\
        }\
    } else {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            Controller_LFO_SetRate(1);\
            if (!Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Play();\
                Controller_Sync_ResetDividerCounters();\
            }\
        } else {\
            if (Controller_Mode_1_isFunctionFlag()) {\
                if (!Controller_LFO_isPlayingFlag()) {\
                    /* Read pattern data from eeprom */\
                    Controller_View_Animation_ShowRuningDot();\
                    Controller_Mode_DisableAllActions();\
                    Controller_Memory_ReadPatternData();\
                }\
            } else {\
                MIDI_Out_SendNoteOn(controller.mode.mode1.keyNote[1].number, controller.notes.velocity);\
                controller.mode.mode1.lastNoteNumber = controller.mode.mode1.keyNote[1].number;\
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
    }\
}

/* 
 * Stop play key note 2.
 * sends note off MIDI message.
 */
#define Controller_Mode_1_Key_11_UpAction() {\
    if (!Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            if (Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Stop();\
            }\
        } else {\
            MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[1].number, 0);\
        }\
    }\
}
