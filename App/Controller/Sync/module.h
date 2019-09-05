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
#define CONTROLLER_SYNC_CFG_CLK96_DEFAULT_TIME      20
#define CONTROLLER_SYNC_CFG_TEMPO_ADJ_CONST         2000 /* tempo convert to time ms adj const */
#define CONTROLLER_SYNC_CFG_MAX_DIV_COUNTERS        10
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_2           1
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_3           2
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_4           3
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_6           5
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_8           7
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_12          11
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_16          15
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_24          23  /* one beat, quarter note */
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_32          31
#define CONTROLLER_SYNC_CFG_DIV_CNT_VAL_48          47

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
    controller.sync.clock96Time = CONTROLLER_SYNC_CFG_CLK96_DEFAULT_TIME;\
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
    if (controller.sync.tempo < 10) {\
        controller.sync.tempo = 10;\
    }\
    controller.sync.clock96Time = CONTROLLER_SYNC_CFG_TEMPO_ADJ_CONST / controller.sync.tempo;\
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
            Controller_Sync_Clock96TimerEvent();\
            if (Controller_Sync_isSendClockFlag()) {\
            }\
            controller.sync.clock96Timer = controller.sync.clock96Time;\
        }\
    }\
}

/*
 * Sync 1/96 clock timer event.
 */
#define Controller_Sync_Clock96TimerEvent() {\
    Controller_Sequencer_ClockDividerCounterProcess();\
    Controller_Sequencer_ShuffleTimerProcess();\
    Controller_Sync_ClockDividerCountersProcess();\
}

/*
 * Trig Divider Counter Process.
 * NOTE: this is the mapping of actual rate to the value range 0 - 9.
 * This value range represents clock divider timer number. 
 */
#define Controller_Sync_ClockDividerCountersProcess() {\
    Controller_Sync_IncrementClockDividerCounter(0, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_24);\
    Controller_Sync_IncrementClockDividerCounter(1, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_16);\
    Controller_Sync_IncrementClockDividerCounter(2, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_12);\
    Controller_Sync_IncrementClockDividerCounter(3, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_8);\
    Controller_Sync_IncrementClockDividerCounter(4, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_6);\
    Controller_Sync_IncrementClockDividerCounter(5, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_4);\
    Controller_Sync_IncrementClockDividerCounter(6, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_3);\
    Controller_Sync_IncrementClockDividerCounter(7, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_2);\
    Controller_Sync_IncrementClockDividerCounter(8, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_32);\
    Controller_Sync_IncrementClockDividerCounter(9, CONTROLLER_SYNC_CFG_DIV_CNT_VAL_48);\
}

/*
 * Handle one of the divider counters by number.
 */
#define Controller_Sync_IncrementClockDividerCounter(counterNum, divRatio) {\
    if (controller.sync.clockDividerCounters[counterNum].value > divRatio) {\
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
