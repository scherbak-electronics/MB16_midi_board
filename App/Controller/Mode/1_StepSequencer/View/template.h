/*
 * Controller_Mode_1_View template
 * 
 * Mode_1 specific view.
 * each controller mode may (or may not) have its own specific parameters view.
 */

/*
 * Show step sequencer mode default view.
 * Displaing current selected pattern positions.
 */
#define Controller_Mode_1_View_Show() {\
    Controller_Sequencer_View_Show();\
}

/* 
 * Show Trig direction status (number).
 */
#define Controller_Mode_1_View_ShowTrigDirection(trigDir) {\
    Controller_View_ShowParam(trigDir);\
}

/*
 * 
 */
#define Controller_Mode_1_View_Clean() {\
    Controller_Sequencer_View_HideCursor();\
    Controller_View_CleanGreenBuffer();\
    Controller_View_ShowBuffer();\
}
