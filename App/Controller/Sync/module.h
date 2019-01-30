/*
 * Controller_Sync module
 * 
 * Sync Module
 * provides clock signal to all other modules.
 */
#define CONTROLLER_SYNC_FLAG_CLOCK_96               0
#define CONTROLLER_SYNC_FLAG_CLOCK_1BEAT            1
#define CONTROLLER_SYNC_FLAG_EXT_CLOCK              2
#define CONTROLLER_SYNC_FLAG_SEND_CLOCK             3
#define CONTROLLER_SYNC_FLAG_CLOCK_1STEP            4
#define CONTROLLER_SYNC_FLAG_CLOCK_96_EXT           5

#define CONTROLLER_SYNC_CFG_EXT_CLOCK_TIMEOUT        100
#define CONTROLLER_SYNC_CFG_CLOCK_96_TIME            21
#define CONTROLLER_SYNC_CFG_DEFAULT_TEMPO           120
#define CONTROLLER_SYNC_CFG_MAX_DIV_COUNTERS        10
#define CONTROLLER_SYNC_CFG_DIV_2_CNT_VAL           1
#define CONTROLLER_SYNC_CFG_DIV_3_CNT_VAL           2
#define CONTROLLER_SYNC_CFG_DIV_4_CNT_VAL           3
#define CONTROLLER_SYNC_CFG_DIV_6_CNT_VAL           5
#define CONTROLLER_SYNC_CFG_DIV_8_CNT_VAL           7
#define CONTROLLER_SYNC_CFG_DIV_12_CNT_VAL          11
#define CONTROLLER_SYNC_CFG_DIV_16_CNT_VAL          15
#define CONTROLLER_SYNC_CFG_DIV_24_CNT_VAL          23
#define CONTROLLER_SYNC_CFG_DIV_32_CNT_VAL          31
#define CONTROLLER_SYNC_CFG_DIV_48_CNT_VAL          47

struct SYNC_DIVIDER_COUNTER {
    BYTE flags;
    BYTE value;
};

struct SYNC_MODULE {
    BYTE flags;
    BYTE tempo;
    BYTE bpmTimer;
    BYTE clock96Time;
    BYTE clock96Timer;
    BYTE extClockTimeoutTimer;
    struct SYNC_DIVIDER_COUNTER clockDividerCounters[CONTROLLER_SYNC_CFG_MAX_DIV_COUNTERS];
};

#define Controller_Sync_setClock96Flag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96)
#define Controller_Sync_clrClock96Flag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96)
#define Controller_Sync_isClock96Flag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96)

#define Controller_Sync_setClock96ExtFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96_EXT)
#define Controller_Sync_clrClock96ExtFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96_EXT)
#define Controller_Sync_isClock96ExtFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_96_EXT)


#define Controller_Sync_setClock1StepFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1STEP)
#define Controller_Sync_clrClock1StepFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1STEP)
#define Controller_Sync_isClock1StepFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1STEP)

#define Controller_Sync_setClock1BeatFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1BEAT)
#define Controller_Sync_clrClock1BeatFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1BEAT)
#define Controller_Sync_isClock1BeatFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_CLOCK_1BEAT)

#define Controller_Sync_setExtClockFlag()                                   set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_CLOCK)
#define Controller_Sync_clrExtClockFlag()                                   clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_CLOCK)
#define Controller_Sync_isExtClockFlag()                                    bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_CLOCK)

#define Controller_Sync_setSendClockFlag()                                   set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_CLOCK)
#define Controller_Sync_clrSendClockFlag()                                   clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_CLOCK)
#define Controller_Sync_isSendClockFlag()                                    bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_CLOCK)
#define Controller_Sync_invSendClockFlag()                                    inv_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_CLOCK)



/*
 * Module Initialization.
 */
#define Controller_Sync_Init() {\
    controller.sync.flags = 0;\
    controller.sync.tempo = CONTROLLER_SYNC_CFG_DEFAULT_TEMPO;\
    controller.sync.clock96Time = 100;\
    controller.sync.clock96Timer = controller.sync.clock96Time;\
    controller.sync.extClockTimeoutTimer = 0;\
    Controller_Sync_ResetDividerCounters();\
}

#define Controller_Sync_ResetDividerCounters() {\
    system.var = 0;\
    for (; system.var < CONTROLLER_SYNC_CFG_MAX_DIV_COUNTERS; system.var++) {\
        controller.sync.clockDividerCounters[system.var].value = 0;\
        controller.sync.clockDividerCounters[system.var].flags = 0;\
    }\
}

#define Controller_Sync_SetTempo(bpm) {\
    controller.sync.tempo = bpm;\
    controller.sync.clock96Time = bpm;\
    controller.sync.clock96Timer = controller.sync.clock96Time;\
}

/*
 * Module main loop process..
 */
#define Controller_Sync_Process() {\
}

/*
 * Trig 1/96 timer Process.
 */
#define Controller_Sync_Clock96TimerProcess() {\
    if (controller.sync.clock96Timer != 0 && !Controller_Sync_isExtClockFlag()) {\
        controller.sync.clock96Timer--;\
        if (controller.sync.clock96Timer == 0) {\
            Controller_Sequencer_ClockDividerCounterProcess();\
            Controller_Sync_ClockDividerCountersProcess();\
            if (Controller_Sync_isSendClockFlag()) {\
            }\
            controller.sync.clock96Timer = controller.sync.clock96Time;\
        }\
    }\
}

/*
 * Trig Divider Counter Process.
 */
#define Controller_Sync_ClockDividerCountersProcess() {\
    Controller_Sync_IncrementClockDividerCounter(0, 48);\
    Controller_Sync_IncrementClockDividerCounter(1, 32);\
    Controller_Sync_IncrementClockDividerCounter(2, 24);\
    Controller_Sync_IncrementClockDividerCounter(3, 16);\
    Controller_Sync_IncrementClockDividerCounter(4, 12);\
    Controller_Sync_IncrementClockDividerCounter(5, 8);\
    Controller_Sync_IncrementClockDividerCounter(6, 6);\
    Controller_Sync_IncrementClockDividerCounter(7, 4);\
    Controller_Sync_IncrementClockDividerCounter(8, 3);\
    Controller_Sync_IncrementClockDividerCounter(9, 2);\
}

/*
 * Handle one of the divider counters by number.
 */
#define Controller_Sync_IncrementClockDividerCounter(counterNum, divRatio) {\
    if (controller.sync.clockDividerCounters[counterNum].value > CONTROLLER_SYNC_CFG_DIV_##divRatio##_CNT_VAL) {\
        controller.sync.clockDividerCounters[counterNum].value = 0;\
    }\
    if (controller.sync.clockDividerCounters[counterNum].value == 0) {\
        controller.sync.clockDividerCounters[counterNum].flags = 0b11111111;\
    }\
    controller.sync.clockDividerCounters[counterNum].value++;\
}

/*
 * External trigger event process 
 */
#define Controller_Sync_ExtClockProcess() {\
    if (Controller_Sequencer_isPlayingFlag()) {\
        Controller_Sequencer_ClockDividerCounterProcess();\
    }\
    Controller_Sync_ClockDividerCountersProcess();\
    Controller_Sync_setExtClockFlag();\
    controller.sync.extClockTimeoutTimer = CONTROLLER_SYNC_CFG_EXT_CLOCK_TIMEOUT;\
}

/*
 * Start sequencer playback.
 */
#define Controller_Sync_StartPlayback() {\
    Controller_Sequencer_StartPlayback();\
}

/*
 * Stop sequencer.
 */
#define Controller_Sync_StopPlayback() {\
    Controller_Sequencer_StopPlayback();\
}

/*
 * Start sequencer playback from external.
 */
#define Controller_Sync_ExtStartPlayback() {\
    Controller_Sync_setExtClockFlag();\
    controller.sync.extClockTimeoutTimer = CONTROLLER_SYNC_CFG_EXT_CLOCK_TIMEOUT;\
    Controller_Sequencer_StartPlayback();\
}

/*
 * Stop sequencer from external.
 */
#define Controller_Sync_ExtStopPlayback() {\
    Controller_Sync_clrExtClockFlag();\
    Controller_Sequencer_StopPlayback();\
}

/*
 * Ext Trig timeout timer Process.
 */
#define Controller_Sync_ExtClockTimeoutProcess() {\
    if (controller.sync.extClockTimeoutTimer != 0) {\
        controller.sync.extClockTimeoutTimer--;\
        if (controller.sync.extClockTimeoutTimer == 0) {\
            Controller_Sync_clrExtClockFlag();\
        }\
    }\
}
