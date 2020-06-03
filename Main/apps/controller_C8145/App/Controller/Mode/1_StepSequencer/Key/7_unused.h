/*
 * Mode 1
 * Key number 7 up and down actions.
 */

/*
 * Key unused.
 */
#define Controller_Mode_1_Key_7_DownAction() {\
    Controller_Sequencer_setOverdubFlag();\
}

/*
 * Key unused.
 */
#define Controller_Mode_1_Key_7_UpAction() {\
    Controller_Sequencer_clrOverdubFlag();\
}
