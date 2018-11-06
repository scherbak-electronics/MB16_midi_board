/*
 * LFO RATE
 * 
 * Knob 3 action in mode number 1.
 */
#define Controller_Mode_1_Knob_3_Action(knobVal) {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Sequencer_SetTempo(knobVal + 1);\
    }\
}
