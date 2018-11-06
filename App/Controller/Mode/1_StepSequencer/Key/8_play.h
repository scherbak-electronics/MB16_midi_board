/*
 * Mode 1
 * Key number 8 up and down actions.
 */

/*  
 * Play sequencer. 
 * Start playing sequencer patterns according to selected tempo
 * and sequencer structure.
 */
#define Controller_Mode_1_Key_8_DownAction() {\
    Controller_Sequencer_StartPlayback();\
}

#define Controller_Mode_1_Key_8_UpAction() {\
    Controller_Sequencer_StopPlayback();\
}
