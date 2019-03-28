/*
 * Button N4 (note play key num 3)
 * key action handler
 * 
 * Key 13 action in mode number 1.
 * Play key note 4. Clear pattern data if FN key is pressed.
 */
#define Controller_Mode_1_Key_13_DownAction() {\
    if (Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isFunctionFlag()) {\
            /* assign prog to key */\
            Controller_Key_AssignProgramNumber(3, Controller_Program_GetLastUsedNumber());\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY, CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT);\
        } else {\
            /* play assigned prog */\
            MIDI_Out_SendProgramChange(Controller_Key_GetAssignedProgramNumber(3));\
        }\
    } else {\
        if (Controller_Mode_1_isFunctionFlag()) {\
            Controller_Sequencer_ClearStepData(\
                Controller_Sequencer_GetEditPatternNumber(), \
                Controller_Sequencer_GetEditStepNumber()\
            );\
        } else {\
            if (Controller_Mode_1_isShiftRightFlag()) {\
                Controller_LFO_SetRate(3);\
                if (!Controller_LFO_isPlayingFlag()) {\
                    Controller_LFO_Play();\
                    Controller_Sync_ResetDividerCounters();\
                }\
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
        }\
    }\
}

#define Controller_Mode_1_Key_13_UpAction() {\
    if (!Controller_Mode_1_isFunctionFlag()) {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            if (Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Stop();\
            }\
        } else {\
            MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[3].number, 0);\
        }\
    }\
}
