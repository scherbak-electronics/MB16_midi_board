/*
 * FUNCTION
 * Key 4 up/down actions in mode number 1.
 */
#define Controller_Mode_1_Key_4_DownAction() {\
    Controller_Mode_1_setFunctionFlag();\
    if (Controller_Memory_View_isSaveDialogVisible()) {\
        /* Canceling save operation */\
        Controller_Memory_View_HideSaveDialog();\
        Controller_Mode_EnableAllActions();\
    }\
}

#define Controller_Mode_1_Key_4_UpAction() {\
    Controller_Mode_1_clrFunctionFlag();\
}
