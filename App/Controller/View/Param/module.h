/*
 * Shows the parameter as a binary value.
 */
#define CONTROLLER_VIEW_PARAM_CFG_SHOW_TIME          100

struct CONTROLLER_VIEW_PARAM_MODULE {
    BYTE flags;
    BYTE showTimer;
};

/*
 * Module Initialization.
 */
#define Controller_View_Param_Init() {\
    controller.view.param.flags = 0;\
    controller.view.param.showTimer = 0;\
}

/*
 * Module main loop.
 */
#define Controller_View_Param_Process() {\
}

/*
 * System timer 100ms process alias.
 */
#define Controller_View_Param_Timer100msProcess() {\
    Controller_View_Param_ShowTimerProcess();\
}

/*
 * Parameter show timer process.
 */
#define Controller_View_Param_ShowTimerProcess() {\
    if (controller.view.param.showTimer != 0) {\
        controller.view.param.showTimer--;\
        if (controller.view.param.showTimer == 0) {\
            Controller_View_CleanGreenPort();\
            Controller_View_clrBusyFlag();\
        }\
    }\
}

/*
 * Runing dot animation process.
 */
#define Controller_View_Param_Show(value) {\
    Controller_View_setBusyFlag();\
    Controller_View_CleanGreenPort();\
    Controller_View_renderGreenLeds(value << 4);\
    controller.view.param.showTimer = 20;\
}
