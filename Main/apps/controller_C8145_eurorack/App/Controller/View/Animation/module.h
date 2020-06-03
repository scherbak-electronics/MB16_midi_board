/*
 * Shows animated screen saver on 4-leds display.
 * User cannot interact while animation is in progress.
 */
#define CONTROLLER_VIEW_ANIMATION_FLAG_RUN          0

#define CONTROLLER_VIEW_ANIMATION_CFG_TICK_TIME     1

struct CONTROLLER_VIEW_ANIMATION_MODULE {
    BYTE flags;
    BYTE tickTimer;
    BYTE keyFrameCounter;
    BYTE type;
};

#define Controller_View_Animation_isRunFlag()       bit_is_set(controller.view.animation.flags, CONTROLLER_VIEW_ANIMATION_FLAG_RUN)
#define Controller_View_Animation_setRunFlag()       set_bit(controller.view.animation.flags, CONTROLLER_VIEW_ANIMATION_FLAG_RUN)
#define Controller_View_Animation_clrRunFlag()       clr_bit(controller.view.animation.flags, CONTROLLER_VIEW_ANIMATION_FLAG_RUN)

/*
 * Module Initialization.
 */
#define Controller_View_Animation_Init() {\
    controller.view.animation.flags = 0;\
    controller.view.animation.keyFrameCounter = 0;\
    controller.view.animation.tickTimer = 0;\
}

/*
 * Shows runing dot animation.
 */
#define Controller_View_Animation_ShowRuningDot() {\
    controller.view.animation.tickTimer = CONTROLLER_VIEW_ANIMATION_CFG_TICK_TIME;\
    controller.view.animation.keyFrameCounter = 4;\
    Controller_View_Animation_setRunFlag();\
}

/*
 * Module main loop.
 */
#define Controller_View_Animation_Process() {\
}

/*
 * System timer 100ms process alias.
 */
#define Controller_View_Animation_Timer100msProcess() {\
    Controller_View_Animation_TickTimerProcess();\
}

/*
 * Animation timer process.
 */
#define Controller_View_Animation_TickTimerProcess() {\
    if (Controller_View_Animation_isRunFlag()) {\
        if (controller.view.animation.tickTimer != 0) {\
            controller.view.animation.tickTimer--;\
            if (controller.view.animation.tickTimer == 0) {\
                controller.view.animation.tickTimer = CONTROLLER_VIEW_ANIMATION_CFG_TICK_TIME;\
                if (controller.view.animation.keyFrameCounter != 0) {\
                    controller.view.animation.keyFrameCounter--;\
                    Controller_View_Animation_RuningDotProcess();\
                } else {\
                    if (controller.view.animation.keyFrameCounter == 0) {\
                        Controller_View_Animation_clrRunFlag();\
                        Controller_View_CleanGreenPort();\
                        Controller_View_Animation_CompleteEvent();\
                    }\
                }\
            }\
        }\
    }\
}

/*
 * Runing dot animation process.
 */
#define Controller_View_Animation_RuningDotProcess() {\
    Controller_View_CleanGreenPort();\
    Controller_View_SetGreenLedsPortBit(controller.view.animation.keyFrameCounter);\
}

/*
 * Event fires when animation is complete. 
 * After last key frame displayed.
 */
#define Controller_View_Animation_CompleteEvent() {\
    Controller_Mode_EnableAllActions();\
}

