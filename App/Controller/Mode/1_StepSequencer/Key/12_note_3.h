/*
 * Button N3 / save / P3 (note play key num 2)
 * key action handler
 * 
 * Key 12 action in mode 1.
 * Play key note 3. Save pattern data if FN key is pressed.
 */

/*
 * Key down action. 
 */
#define Controller_Mode_1_Key_12_DownAction() {\
    if (Controller_Mode_1_isAltRightFlag()) {\
        if (Controller_Mode_1_isFunctionFlag()) {\
            /* assign prog to key */\
            Controller_Key_AssignProgramNumber(2, Controller_Program_GetLastUsedNumber());\
            Controller_Notes_On(controller.mode.mode1.lastNoteNumber, CONTROLLER_NOTES_CFG_DEFAULT_VELOCITY, CONTROLLER_NOTES_CFG_GATE_TIME_DEFAULT);\
        } else {\
            /* change the program to assigned */\
            MIDI_Out_SendProgramChange(Controller_Key_GetAssignedProgramNumber(2));\
        }\
    } else {\
        if (Controller_Memory_View_isSaveDialogVisible()) {\
            if (!Controller_Mode_1_isFunctionFlag()) {\
                Controller_Memory_SavePatternData();\
                Controller_Memory_View_ShowSaveProgressDialog();\
            } else {\
                Controller_Memory_View_HideSaveDialog();\
                Controller_Mode_EnableAllActions();\
            }\
        } else {\
            if (Controller_Mode_1_isFunctionFlag() && !Controller_Sequencer_isPlayingFlag()) {\
                Controller_Memory_View_ShowSaveDialog();\
                Controller_Mode_DisableAllActions();\
                Controller_Mode_EnableKeyAction(12);\
                Controller_Mode_EnableKeyAction(4);\
            } else {\
                if (Controller_Mode_1_isShiftRightFlag()) {\
                    Controller_LFO_SetRate(2);\
                    if (!Controller_LFO_isPlayingFlag()) {\
                        Controller_LFO_Play();\
                        Controller_Sync_ResetDividerCounters();\
                    }\
                } else {\
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
                }\
            }\
        }\
    }\
}

/*
 * Key up action. 
 */
#define Controller_Mode_1_Key_12_UpAction() {\
    if (!Controller_Mode_1_isFunctionFlag() && !Controller_Memory_View_isSaveDialogVisible()) {\
        if (Controller_Mode_1_isShiftRightFlag()) {\
            if (Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Stop();\
            }\
        } else {\
            MIDI_Out_SendNoteOff(controller.mode.mode1.keyNote[2].number, 0);\
        }\
    }\
}
