/*
 * ALT LEFT
 * Key 1 up/down actions in mode number 1.
 */
#define Controller_Mode_1_Key_1_DownAction() {\
    Controller_Mode_1_setAltLeftFlag();\
}

#define Controller_Mode_1_Key_1_UpAction() {\
    Controller_Mode_1_clrAltLeftFlag();\
}
