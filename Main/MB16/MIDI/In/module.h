/*
 * MIDI In Modeule
 * Accept incoming bytes from USART and parse them to MIDI messages.
 * Generates events by seting status register flags.
 */

/*
 * MIDI In Config
 */
#define MIDI_IN_CFG_MESSAGE_BUFFER_SIZE                         4
#define MIDI_IN_CFG_REALTIME_MESSAGE_BUFFER_SIZE                4
#define MIDI_IN_CFG_TIMEOUT_TIME                                200

/*
 * MIDI In Flags
 */
#define MIDI_IN_FLAG_TIMEOUT_ERROR                              0
#define MIDI_IN_FLAG_TIME_CLOCK                                 4
#define MIDI_IN_FLAG_START                                      5
#define MIDI_IN_FLAG_STOP                                       6
#define MIDI_IN_FLAG_CONTINUE                                   7

#define MIDI_In_isTimeoutErrorFlag()               bit_is_set(midi.in.flags, MIDI_IN_FLAG_TIMEOUT_ERROR)
#define MIDI_In_setTimeoutErrorFlag()              set_bit(midi.in.flags, MIDI_IN_FLAG_TIMEOUT_ERROR)
#define MIDI_In_clrTimeoutErrorFlag()              clr_bit(midi.in.flags, MIDI_IN_FLAG_TIMEOUT_ERROR)

#define MIDI_In_isTimeClockFlag()               bit_is_set(midi.in.flags, MIDI_IN_FLAG_TIME_CLOCK)
#define MIDI_In_setTimeClockFlag()              set_bit(midi.in.flags, MIDI_IN_FLAG_TIME_CLOCK)
#define MIDI_In_clrTimeClockFlag()              clr_bit(midi.in.flags, MIDI_IN_FLAG_TIME_CLOCK)

#define MIDI_In_isStartFlag()               bit_is_set(midi.in.flags, MIDI_IN_FLAG_START)
#define MIDI_In_setStartFlag()              set_bit(midi.in.flags, MIDI_IN_FLAG_START)
#define MIDI_In_clrStartFlag()              clr_bit(midi.in.flags, MIDI_IN_FLAG_START)

#define MIDI_In_isStopFlag()               bit_is_set(midi.in.flags, MIDI_IN_FLAG_STOP)
#define MIDI_In_setStopFlag()              set_bit(midi.in.flags, MIDI_IN_FLAG_STOP)
#define MIDI_In_clrStopFlag()              clr_bit(midi.in.flags, MIDI_IN_FLAG_STOP)

#define MIDI_In_isContinueFlag()               bit_is_set(midi.in.flags, MIDI_IN_FLAG_CONTINUE)
#define MIDI_In_setContinueFlag()              set_bit(midi.in.flags, MIDI_IN_FLAG_CONTINUE)
#define MIDI_In_clrContinueFlag()              clr_bit(midi.in.flags, MIDI_IN_FLAG_CONTINUE)

#define MIDI_In_isNewMessage()              (midi.in.msgBufferPointer != midi.in.msgBufferReadPointer)
#define MIDI_In_isNewRealTimeMessage()      (midi.in.rtmMsgBufferPointer != midi.in.rtmMsgBufferReadPointer)

struct MIDI_MESSAGE_BUFFER {
    BYTE status;
    BYTE data1;
    BYTE data2;
};

struct MIDI_IN_MODULE {
    BYTE flags;
    struct MIDI_MESSAGE_BUFFER msgBuffer[MIDI_IN_CFG_MESSAGE_BUFFER_SIZE];
    BYTE msgBufferPointer;
    BYTE msgBufferReadPointer;
    BYTE currentStatus;
    BYTE dataBytesExpected;
    BYTE dataBytesReceived;
    BYTE rtmMsgBuffer[MIDI_IN_CFG_REALTIME_MESSAGE_BUFFER_SIZE];
    BYTE rtmMsgBufferPointer;
    BYTE rtmMsgBufferReadPointer;
    BYTE timeoutTimer;
};

/*
 * MIDI In Initialization
 */
#define MIDI_In_Init() {\
    midi.in.msgBufferPointer = 0;\
    midi.in.msgBufferReadPointer = 0;\
    midi.in.dataBytesExpected = 0;\
    midi.in.dataBytesReceived = 0;\
    midi.in.rtmMsgBufferPointer = 0;\
    midi.in.rtmMsgBufferReadPointer = 0;\
    midi.in.timeoutTimer = 0;\
    midi.in.flags = 0;\
}

/*
 * Parse MIDI messages from USART rx buffer depending on currently received messages,
 * runing status, system exclusive mode, number of data bytes and midi module flags
 */
#define MIDI_In_ParseMessage() {\
    if (MIDI_isRealTimeMessage(system.usart.rxBuffer[system.usart.rxBufferReadPointer])) {\
        MIDI_In_ParseRealTimeMessage();\
    } else {\
        if (MIDI_isChannelVoiceMessage(system.usart.rxBuffer[system.usart.rxBufferReadPointer])) {\
            MIDI_In_ParseChannelVoiceMessage();\
        } else {\
            if (MIDI_isDataByte(system.usart.rxBuffer[system.usart.rxBufferReadPointer])) {\
                MIDI_In_ParseDataByte();\
            } else {\
                if (MIDI_isSysExMessage(system.usart.rxBuffer[system.usart.rxBufferReadPointer])) {\
                    MIDI_In_ParseSystemExclusiveMessage();\
                } else {\
                    if (system.usart.rxBuffer[system.usart.rxBufferReadPointer] == MIDI_STATUS_EOX_MSG) {\
                        MIDI_In_ExitSystemExclusiveMode();\
                    } else {\
                        MIDI_In_ParseSystemCommonMessage();\
                    }\
                }\
            }\
        }\
    }\
}

/*
 * Parse voice messages, note on/off, controller change, program change, etc.. 
 */
#define MIDI_In_ParseChannelVoiceMessage() {\
    if (midi.in.msgBufferPointer < MIDI_IN_CFG_MESSAGE_BUFFER_SIZE) {\
        switch (MIDI_getStatusByte(system.usart.rxBuffer[system.usart.rxBufferReadPointer])) {\
            case MIDI_STATUS_MASK_NOTE_ON_MSG:\
            case MIDI_STATUS_MASK_NOTE_OFF_MSG:\
            case MIDI_STATUS_MASK_CTRL_CHANGE_MSG:\
            case MIDI_STATUS_MASK_PITCH_MSG:\
            case MIDI_STATUS_MASK_AFTCH_MSG:\
            MIDI_In_setCurrentStatus(system.usart.rxBuffer[system.usart.rxBufferReadPointer]);\
            midi.in.dataBytesExpected = 2;\
            break;\
            case MIDI_STATUS_MASK_PROG_CHANGE_MSG:\
            case MIDI_STATUS_MASK_CHN_AFTCH_MSG:\
            MIDI_In_setCurrentStatus(system.usart.rxBuffer[system.usart.rxBufferReadPointer]);\
            midi.in.dataBytesExpected = 1;\
            break;\
        }\
    }\
}

/*
 * Get data bytes from USART buffer, put parsed MIDI message to message buffer
 * and set message event flag
 */
#define MIDI_In_ParseDataByte() {\
    if (midi.in.msgBufferPointer < MIDI_IN_CFG_MESSAGE_BUFFER_SIZE) {\
        if (midi.in.dataBytesExpected != midi.in.dataBytesReceived) {\
            if (midi.in.dataBytesReceived == 0) {\
                midi.in.msgBuffer[midi.in.msgBufferPointer].data1 = system.usart.rxBuffer[system.usart.rxBufferReadPointer];\
            } else {\
                if (midi.in.dataBytesReceived == 1) {\
                    midi.in.msgBuffer[midi.in.msgBufferPointer].data2 = system.usart.rxBuffer[system.usart.rxBufferReadPointer];\
                }\
            }\
            midi.in.dataBytesReceived++;\
            MIDI_In_SetTimeoutTimer();\
            if (midi.in.dataBytesExpected == midi.in.dataBytesReceived) {\
                midi.in.dataBytesReceived = 0;\
                midi.in.msgBufferPointer++;\
                MIDI_In_ClearTimeoutTimer();\
            }\
        }\
    }\
}

/*
 * Parse real time messages, external clock, play/stop, system reset..
 */
#define MIDI_In_ParseRealTimeMessage() {\
    if (midi.in.rtmMsgBufferPointer < MIDI_IN_CFG_REALTIME_MESSAGE_BUFFER_SIZE) {\
        switch (system.usart.rxBuffer[system.usart.rxBufferReadPointer]) {\
            case MIDI_STATUS_CLK_MSG:\
            MIDI_In_setCurrentRtmStatus(MIDI_STATUS_CLK_MSG);\
            MIDI_In_setTimeClockFlag();\
            break;\
            case MIDI_STATUS_CONTINUE_MSG:\
            MIDI_In_setCurrentRtmStatus(MIDI_STATUS_CONTINUE_MSG);\
            MIDI_In_setContinueFlag();\
            break;\
            case MIDI_STATUS_START_MSG:\
            MIDI_In_setCurrentRtmStatus(MIDI_STATUS_START_MSG);\
            MIDI_In_setStartFlag();\
            break;\
            case MIDI_STATUS_STOP_MSG:\
            MIDI_In_setCurrentRtmStatus(MIDI_STATUS_STOP_MSG);\
            MIDI_In_setStopFlag();\
            break;\
            case MIDI_STATUS_ACTIVE_SENS_MSG:\
            case MIDI_STATUS_RESET_MSG:\
            break;\
        }\
    }\
}

/*
 * System Common Messages
 */
#define MIDI_In_ParseSystemCommonMessage() {\
    switch (system.usart.rxBuffer[system.usart.rxBufferReadPointer]) {\
        case MIDI_STATUS_SONG_POS_MSG:\
        break;\
        case MIDI_STATUS_SONG_SEL_MSG:\
        break;\
        case MIDI_STATUS_TIMECODE_MSG:\
        break;\
        case MIDI_STATUS_TUNE_RQ_MSG:\
        break;\
    }\
}

#define MIDI_In_setCurrentStatus(byte) {\
    midi.in.currentStatus = byte;\
    midi.in.msgBuffer[midi.in.msgBufferPointer].status = midi.in.currentStatus;\
    midi.in.dataBytesReceived = 0;\
    MIDI_In_SetTimeoutTimer();\
}

#define MIDI_In_setCurrentRtmStatus(byte) {\
    midi.in.rtmMsgBuffer[midi.in.rtmMsgBufferPointer] = byte;\
    midi.in.rtmMsgBufferPointer++;\
}

#define MIDI_In_ResetMsgBuffer() {\
    midi.in.msgBufferPointer = 0;\
    midi.in.msgBufferReadPointer = 0;\
}

#define MIDI_In_ResetRtmMsgBuffer() {\
    midi.in.rtmMsgBufferPointer = 0;\
    midi.in.rtmMsgBufferReadPointer = 0;\
}

#define MIDI_In_SetTimeoutTimer() {\
    midi.in.timeoutTimer = MIDI_IN_CFG_TIMEOUT_TIME;\
}

#define MIDI_In_ClearTimeoutTimer() {\
    midi.in.timeoutTimer = 0;\
}

#define MIDI_In_TimeoutTimerProcess() {\
    if (midi.in.timeoutTimer != 0) {\
        midi.in.timeoutTimer--;\
        if (midi.in.timeoutTimer == 0) {\
            MIDI_In_ResetMsgBuffer();\
            MIDI_In_setTimeoutErrorFlag();\
        }\
    }\
}

/*
 * System Exclusive Messages, enter System Exclusive mode.
 */
#define MIDI_In_ParseSystemExclusiveMessage() {\
    MIDI_setSysExModeFlag();\
}

/*
 * Exit System Exclusive mode
 */
#define MIDI_In_ExitSystemExclusiveMode() {\
    MIDI_clrSysExModeFlag();\
}
