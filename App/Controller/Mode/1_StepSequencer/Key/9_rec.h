/*
 * REC
 * key action handler
 * 
 * Key 9 action in mode number 1.
 * Sequencer record mode.
 */
#define Controller_Mode_1_Key_9_DownAction() {\
    Controller_Sequencer_setRecFlag();\
}

#define Controller_Mode_1_Key_9_UpAction() {\
    Controller_Sequencer_clrRecFlag();\
}
