/*
 * SEQUENCER STEPS
 * Knob 2 action in mode number 1.
 */
#define Controller_Mode_1_Knob_2_Action(knobVal) {\
    if (!Controller_Mode_1_isShiftLeftFlag()) {\
        Controller_Sequencer_SetEditStepNumber(knobVal >> 3);\
        if (Controller_Sequencer_IsEditStepNumberChanged()) {\
            Controller_Sequencer_RenewPreviousEditStepNumber();\
            if (Controller_Mode_1_isFunctionFlag()) {\
                Controller_Sequencer_PlayStep(\
                    Controller_Sequencer_GetEditPatternNumber(),\
                    Controller_Sequencer_GetEditStepNumber()\
                );\
            }\
            Controller_Sequencer_View_Show();\
        }\
    } else {\
        Controller_Mode_1_Knob_2_SetBaseNoteAction((knobVal >> 3));\
    }\
}

/*
 * Set Base Note Action.
 */
#define Controller_Mode_1_Knob_2_SetBaseNoteAction(knobVal) {\
    if (knobVal < 13) {\
        controller.mode.mode1.baseNoteNumber = knobVal;\
    }\
    Controller_View_Param_Show(controller.mode.mode1.baseNoteNumber);\
}
