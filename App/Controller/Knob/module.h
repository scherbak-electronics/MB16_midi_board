/*
 * Controller_Knob
 * 
 * Knobs Module
 * provides processing of ADC values to which variable resistors should be connected.
 */
#define CONTROLLER_KNOB_CFG_KNOBS_COUNT             ADC_CFG_CHANNELS_COUNT
#define CONTROLLER_KNOB_CFG_SPEED_TIMERS_COUNT      2
#define CONTROLLER_KNOB_CFG_MAX_MEASURE_TIME        127
#define CONTROLLER_KNOB_CFG_DIR_FWD                 0b00000010
#define CONTROLLER_KNOB_CFG_DIR_BKD                 0b00000001
#define CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_4  0
#define CONTROLLER_KNOB_CFG_SPEED_TIMER_NUM_KNOB_5  1

struct KNOB_SPEED_TIMER {
    BYTE timer;
    BYTE value;
};

struct KNOB_MODULE {
    BYTE mapping[CONTROLLER_KNOB_CFG_KNOBS_COUNT];
    struct KNOB_SPEED_TIMER speed[CONTROLLER_KNOB_CFG_SPEED_TIMERS_COUNT];
};

#define Controller_Knob_GetCCNumber(knobNum)                controller.knob.mapping[knobNum]
#define Controller_Knob_GetDirection(knobNum, knobVal)      (((system.adc.values[knobNum] < knobVal) << 1) | (system.adc.values[knobNum] > knobVal))

/*
 * Module Initialization.
 */
#define Controller_Knob_Init() {\
    Controller_Knob_SetDefaultMapping();\
    system.var = 0;\
    for (; system.var < CONTROLLER_KNOB_CFG_SPEED_TIMERS_COUNT; system.var++) {\
        controller.knob.speed[system.var].timer = 0;\
        controller.knob.speed[system.var].value = 0;\
    }\
}

/*
 * Initialize default mapping table
 */
#define Controller_Knob_SetDefaultMapping() {\
    controller.knob.mapping[0] = 25;\
    controller.knob.mapping[1] = 26;\
    controller.knob.mapping[2] = 27;\
    controller.knob.mapping[3] = 28;\
    controller.knob.mapping[4] = 29;\
    controller.knob.mapping[5] = 30;\
    controller.knob.mapping[6] = 31;\
    controller.knob.mapping[7] = 85;\
}

/*
 * Initialize alternatve mapping table
 */
#define Controller_Knob_SetAlterMapping() {\
    controller.knob.mapping[0] = 25;\
    controller.knob.mapping[1] = 26;\
    controller.knob.mapping[2] = 27;\
    controller.knob.mapping[3] = 28;\
    controller.knob.mapping[4] = 13;\
    controller.knob.mapping[5] = 70;\
    controller.knob.mapping[6] = 71;\
    controller.knob.mapping[7] = 72;\
}


/*
 * Module Main Process.
 */
#define Controller_Knob_Process() {\
    Controller_Knob_SpeedTimersProcess(0);\
    Controller_Knob_SpeedTimersProcess(1);\
}

/*
 * Speed Measure Timer Process.
 */
#define Controller_Knob_SpeedTimersProcess(knobNum) {\
    if (controller.knob.speed[knobNum].timer != 0) {\
        controller.knob.speed[knobNum].timer--;\
        if (controller.knob.speed[knobNum].timer == 0) {\
            controller.knob.speed[knobNum].value = 0;\
        }\
    }\
}

/*
 * Start measure knob speed.
 */
#define Controller_Knob_StartMeasureSpeed(knobNum) {\
    if (controller.knob.speed[knobNum].timer != 0) {\
        controller.knob.speed[knobNum].value = controller.knob.speed[knobNum].timer;\
    } else {\
        controller.knob.speed[knobNum].value = 0;\
    }\
    controller.knob.speed[knobNum].timer = CONTROLLER_KNOB_CFG_MAX_MEASURE_TIME;\
}
