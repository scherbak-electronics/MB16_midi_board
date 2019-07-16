/*
 * Mode 0.
 * Key 4 asigned to mapping selecting.
 * Select Next Mode key up/down actions
 */
#define Controller_Mode_0_Key_4_DownAction() {\
    Controller_Knob_SetAlterMapping();\
    Controller_Key_SetAlterMapping();\
}

#define Controller_Mode_0_Key_4_UpAction() {\
    Controller_Knob_SetDefaultMapping();\
    Controller_Key_SetDefaultMapping();\
}
