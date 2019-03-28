/*
 * SHIFT RIGHT
 * Key 3 up/down actions in mode number 1.
 */
#define Controller_Mode_1_Key_3_DownAction() {\
    Controller_Mode_1_setShiftRightFlag();\
}

#define Controller_Mode_1_Key_3_UpAction() {\
    Controller_Mode_1_clrShiftRightFlag();\
}
