/*
 * Controller_LFO
 * 
 * LFO Module
 * Note trigger LFO with sync to external/internal clock
 */
#define CONTROLLER_LFO_CFG_DEFAULT_GATE_TIME        10
#define CONTROLLER_LFO_CFG_NOTE_OFF                 CONTROLLER_NOTES_CFG_NOTE_OFF

#define CONTROLLER_LFO_FLAG_CLOCK_EVENT              0
#define CONTROLLER_LFO_FLAG_PLAY                    0

struct LFO_MODULE {
    BYTE flags;
    BYTE note;
    BYTE gateTimer;
    BYTE rate;
};

#define Controller_LFO_setPlayingFlag()                           set_bit(controller.lfo.flags, CONTROLLER_LFO_FLAG_PLAY)
#define Controller_LFO_clrPlayingFlag()                           clr_bit(controller.lfo.flags, CONTROLLER_LFO_FLAG_PLAY)
#define Controller_LFO_isPlayingFlag()                            bit_is_set(controller.lfo.flags, CONTROLLER_LFO_FLAG_PLAY)

/*
 * Module Initialization.
 */
#define Controller_LFO_Init() {\
    controller.lfo.note = CONTROLLER_LFO_CFG_NOTE_OFF;\
}

/*
 * Set LFO rate.
 * please make sure that rate value in the range 0 - 9.
 * LFO rate will be used to select one of the divider counters, 
 * and will be actually converted to divider counter number
 */
#define Controller_LFO_SetRate(lfoRate) {\
    controller.lfo.rate = (lfoRate);\
}

/*
 * LFO module main loop process.
 */
#define Controller_LFO_Process() {\
    if (Controller_LFO_isPlayingFlag()) {\
        if (Controller_LFO_IsClockEventFlag(controller.lfo.rate)) {\
            Controller_LFO_ResetClockEventFlags();\
            if (Controller_LFO_IsNoteOn()) {\
                Controller_LFO_TrigNoteOff();\
            }\
            Controller_LFO_TrigNoteOn();\
        }\
    }\
}

/*
 * Gate timer Process.
 */
#define Controller_LFO_GateTimerProcess() {\
    if (controller.lfo.gateTimer != 0) {\
        controller.lfo.gateTimer--;\
        if (controller.lfo.gateTimer == 0) {\
            Controller_LFO_TrigNoteOff();\
        }\
    }\
}

/*
 * Start playing.
 * Begins Low Frequency Oscilations at current rate.
 */
#define Controller_LFO_Play() {\
    Controller_LFO_setPlayingFlag();\
}

/*
 * Stop playing.
 * Ends Low Frequency Oscilations.
 */
#define Controller_LFO_Stop() {\
    Controller_LFO_clrPlayingFlag();\
}

/*
 * Is LFO note currently on.
 */
#define Controller_LFO_IsNoteOn() (controller.lfo.note != CONTROLLER_LFO_CFG_NOTE_OFF)

/*
 * Send Note On MIDI message and re-init note gate timer.
 */
#define Controller_LFO_TrigNoteOn() {\
    controller.lfo.gateTimer = controller.notes.gateTime;\
    controller.lfo.note = controller.mode.mode1.lastNoteNumber;\
    MIDI_Out_SendNoteOn(controller.lfo.note, controller.notes.velocity);\
}

/*
 * Sending note off MIDI message.
 */
#define Controller_LFO_TrigNoteOff() {\
    MIDI_Out_SendNoteOff(controller.lfo.note, 0);\
    controller.lfo.note = CONTROLLER_LFO_CFG_NOTE_OFF;\
}

/*
 * Checking clock divider counter flag by counter number.
 */
#define Controller_LFO_IsClockEventFlag(counterNum) (bit_is_set(controller.sync.clockDividerCounters[counterNum].flags, CONTROLLER_LFO_FLAG_CLOCK_EVENT))

/*
 * Reset trig divider counter flag by counter number.
 */
#define Controller_LFO_ResetClockEventFlag(counterNum) {\
    clr_bit(controller.sync.clockDividerCounters[counterNum].flags, CONTROLLER_LFO_FLAG_CLOCK_EVENT);\
}

/*
 * Reset all trig divider counters flag.
 */
#define Controller_LFO_ResetClockEventFlags() {\
    system.var = 0;\
    for (; system.var < CONTROLLER_SYNC_CFG_MAX_DIV_COUNTERS; system.var++) {\
        clr_bit(controller.sync.clockDividerCounters[system.var].flags, CONTROLLER_LFO_FLAG_CLOCK_EVENT);\
    }\
}
