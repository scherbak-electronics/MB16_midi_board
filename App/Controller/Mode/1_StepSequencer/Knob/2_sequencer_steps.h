/*
 * SEQUENCER STEPS
 * Knob 2 action in mode number 1.
 */
#define Controller_Mode_1_Knob_2_Action(knobVal) {\
    Controller_Sequencer_SetEditPatternStepNumber(knobVal >> 3);\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Sequencer_PlayPatternPosition( \
            Controller_Sequencer_GetEditPatternNumber(), \
            Controller_Sequencer_GetEditPatternStepNumber() \
        );\
    }\
    Controller_Sequencer_View_MoveCursor(Controller_Sequencer_GetEditPatternStepNumber());\
}
