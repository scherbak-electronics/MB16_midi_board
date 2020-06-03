/*
 * Mode 1
 * Key number 6 up and down actions.
 */

/*  
 * Trigger direction select down action.
 */
#define Controller_Mode_1_Key_6_DownAction() {\
    if (Controller_Mode_1_isFunctionFlag()) {\
        if (Controller_View_IsParamVisible()) {\
            Controller_Mode_1_NextTrigDirection();\
        }\
        Controller_Mode_1_View_ShowTrigDirection(Controller_Mode_1_GetTrigDirection());\
    }\
}

/* 
 * Trigger direction select swith Up action.
 */
#define Controller_Mode_1_Key_6_UpAction() {\
}
