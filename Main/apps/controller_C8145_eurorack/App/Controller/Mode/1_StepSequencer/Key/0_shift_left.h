/*
 * SHIFT LEFT
 * Key 0 up/down actions in mode number 1.
 */
#define Controller_Mode_1_Key_0_DownAction() {\
    Controller_Mode_1_setShiftLeftFlag();\
}

#define Controller_Mode_1_Key_0_UpAction() {\
    Controller_Mode_1_clrShiftLeftFlag();\
}
