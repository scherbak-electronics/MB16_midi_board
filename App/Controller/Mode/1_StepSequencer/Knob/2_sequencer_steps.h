/*
 * SEQUENCER STEPS
 * Knob 2 action in mode number 1.
 */
#define Controller_Mode_1_Knob_2_Action(knobVal) {\
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
}
