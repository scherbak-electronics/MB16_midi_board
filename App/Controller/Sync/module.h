/*
 * Controller_Sync module
 * 
 * Sync Module
 * 16 steps pattern sequencer.
 */
#define CONTROLLER_SYNC_FLAG_TRIG_96          0
#define CONTROLLER_SYNC_FLAG_TRIG_1BEAT          1
#define CONTROLLER_SYNC_FLAG_EXT_TRIG                   2
#define CONTROLLER_SYNC_FLAG_SEND_TRIG               3
#define CONTROLLER_SYNC_FLAG_TRIG_1STEP          4
#define CONTROLLER_SYNC_FLAG_TRIG_96_EXT        5

#define CONTROLLER_SYNC_CFG_EXT_TRIG_TIMEOUT            100
#define CONTROLLER_SYNC_CFG_TRIG_96_TIME          21
#define CONTROLLER_SYNC_CFG_DEFAULT_TEMPO          120


struct SYNC_MODULE {
    BYTE flags;
    BYTE tempo;
    BYTE bpmTimer;
    BYTE trig96Time;
    BYTE trig96Timer;
    BYTE stepTriggerDividerCounter;
    BYTE extTrigTimeoutTimer;
};

#define Controller_Sync_setTrig96Flag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96)
#define Controller_Sync_clrTrig96Flag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96)
#define Controller_Sync_isTrig96Flag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96)

#define Controller_Sync_setTrig96ExtFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96_EXT)
#define Controller_Sync_clrTrig96ExtFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96_EXT)
#define Controller_Sync_isTrig96ExtFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_96_EXT)


#define Controller_Sync_setTrig1StepFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1STEP)
#define Controller_Sync_clrTrig1StepFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1STEP)
#define Controller_Sync_isTrig1StepFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1STEP)

#define Controller_Sync_setTrig1BeatFlag()                           set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1BEAT)
#define Controller_Sync_clrTrig1BeatFlag()                           clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1BEAT)
#define Controller_Sync_isTrig1BeatFlag()                            bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_TRIG_1BEAT)

#define Controller_Sync_setExtTrigFlag()                                   set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_TRIG)
#define Controller_Sync_clrExtTrigFlag()                                   clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_TRIG)
#define Controller_Sync_isExtTrigFlag()                                    bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_EXT_TRIG)

#define Controller_Sync_setSendTrigFlag()                                   set_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_TRIG)
#define Controller_Sync_clrSendTrigFlag()                                   clr_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_TRIG)
#define Controller_Sync_isSendTrigFlag()                                    bit_is_set(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_TRIG)
#define Controller_Sync_invSendTrigFlag()                                    inv_bit(controller.sync.flags, CONTROLLER_SYNC_FLAG_SEND_TRIG)



/*
 * Module Initialization.
 */
#define Controller_Sync_Init() {\
    controller.sync.flags = 0;\
    controller.sync.tempo = CONTROLLER_SYNC_CFG_DEFAULT_TEMPO;\
    controller.sync.trig96Time = 100;\
    controller.sync.trig96Timer = controller.sync.trig96Time;\
    controller.sync.extTrigTimeoutTimer = 0;\
    controller.sync.stepTriggerDividerCounter = 0;\
}

#define Controller_Sync_SetTempo(bpm) {\
    controller.sync.tempo = bpm;\
    controller.sync.trig96Time = bpm;\
    controller.sync.trig96Timer = controller.sync.trig96Time;\
}

/*
 * Module Main Process.
 */
#define Controller_Sync_Process() {\
}


/*
 * Trig 1/96 timer Process.
 */
#define Controller_Sync_Trig96TimerProcess() {\
    if (controller.sync.trig96Timer != 0 && !Controller_Sync_isExtTrigFlag()) {\
        controller.sync.trig96Timer--;\
        if (controller.sync.trig96Timer == 0) {\
            Controller_Sync_StepTrigDividerCounterProcess();\
            if (Controller_Sync_isSendTrigFlag()) {\
            }\
            controller.sync.trig96Timer = controller.sync.trig96Time;\
        }\
    }\
}

/*
 * When diivider counter reach target value 
 * sequencer position will be triggered
 */
#define Controller_Sync_StepTrigDividerCounterProcess() {\
    if (controller.sync.stepTriggerDividerCounter > 5) {\
        controller.sync.stepTriggerDividerCounter = 0;\
    }\
    if (controller.sync.stepTriggerDividerCounter == 0) {\
        Controller_Sequencer_setStepTriggerFlag();\
    }\
    controller.sync.stepTriggerDividerCounter++;\
}

/*
 * Ext Trig timeout timer Process.
 */
#define Controller_Sync_ExtTrigTimeoutProcess() {\
    if (controller.sync.extTrigTimeoutTimer != 0) {\
        controller.sync.extTrigTimeoutTimer--;\
        if (controller.sync.extTrigTimeoutTimer == 0) {\
            Controller_Sync_clrExtTrigFlag();\
        }\
    }\
}

/*
 * External trigger event process 
 */
#define Controller_Sync_ExtTrigProcess() {\
    if (!Controller_Sequencer_isPlayingFlag()) {\
        Controller_Sync_StartPlayback();\
        Controller_Sequencer_StartPlayback();\
    }\
    Controller_Sync_setExtTrigFlag();\
    Controller_Sync_StepTrigDividerCounterProcess();\
    controller.sync.extTrigTimeoutTimer = CONTROLLER_SYNC_CFG_EXT_TRIG_TIMEOUT;\
}

/*
 * Start sequencer playback.
 */
#define Controller_Sync_StartPlayback() {\
    if (!Controller_Sequencer_isPlayingFlag()) {\
        controller.sync.stepTriggerDividerCounter = 0;\
        Controller_Sequencer_StartPlayback();\
    }\
}

/*
 * Stop sequencer.
 */
#define Controller_Sync_StopPlayback() {\
    controller.sync.stepTriggerDividerCounter = 0;\
    Controller_Sequencer_StopPlayback();\
}

/*
 * Start sequencer playback from external.
 */
#define Controller_Sync_ExtStartPlayback() {\
    if (!Controller_Sequencer_isPlayingFlag()) {\
        Controller_Sync_setExtTrigFlag();\
        controller.sync.stepTriggerDividerCounter = 0;\
        controller.sync.extTrigTimeoutTimer = CONTROLLER_SYNC_CFG_EXT_TRIG_TIMEOUT;\
        Controller_Sequencer_StartPlayback();\
    }\
}

/*
 * Stop sequencer from external.
 */
#define Controller_Sync_ExtStopPlayback() {\
    Controller_Sync_clrExtTrigFlag();\
    controller.sync.stepTriggerDividerCounter = 0;\
    Controller_Sequencer_StopPlayback();\
}
