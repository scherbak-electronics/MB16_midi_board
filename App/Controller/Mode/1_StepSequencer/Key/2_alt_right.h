/*
 * ALT RIGHT
 * Key 2 up/down actions in mode number 1.
 */
#define Controller_Mode_1_Key_2_DownAction() {\
    Controller_Mode_1_setAltRightFlag();\
}

#define Controller_Mode_1_Key_2_UpAction() {\
    Controller_Mode_1_clrAltRightFlag();\
}
