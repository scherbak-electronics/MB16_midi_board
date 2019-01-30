/*
 * LFO RATE
 * 
 * Knob 3 action in mode number 1.
 */
#define Controller_Mode_1_Knob_3_Action(knobVal) {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        Controller_Sequencer_SetTempo(knobVal + 1);\
    } else {\
        if ((knobVal > 1) && (knobVal < 78)) {\
            Controller_LFO_SetRate(knobVal >> 3);\
            if (!Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Play();\
                Controller_Sync_ResetDividerCounters();\
            }\
        } else {\
            if (Controller_LFO_isPlayingFlag()) {\
                Controller_LFO_Stop();\
            }\
        }\
    }\
}
