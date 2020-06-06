/*
 * Instrument_Gates module
 * 
 * Converts note on/off messages to gate open/close signals
 * at GPIO outputs.
 */
#define INSTRUMENT_GATES_CFG_MAX_POLYPHONY                      8

#define INSTRUMENT_GATES_FLAG_GATE_OPEN                         0

struct GATE_DATA {
    BYTE flags;
    BYTE noteNumber;
    BYTE timeoutTimer;
};

struct GATES_MODULE {
    BYTE flags;
    struct GATE_DATA activeGates[INSTRUMENT_GATES_CFG_MAX_POLYPHONY];
    BYTE gateNumberTmp;
};

#define Instrument_Gates_isFlagGateOpen(gateNum)		            !bit_is_set(instrument.gates.activeGates[gateNum].flags, INSTRUMENT_GATES_FLAG_GATE_OPEN)
#define Instrument_Gates_setFlagGateOpen(gateNum)		            clr_bit(instrument.gates.activeGates[gateNum].flags, INSTRUMENT_GATES_FLAG_GATE_OPEN)
#define Instrument_Gates_clrFlagGateOpen(gateNum)		            set_bit(instrument.gates.activeGates[gateNum].flags, INSTRUMENT_GATES_FLAG_GATE_OPEN)


#define Instrument_Gates_Init() {\
    instrument.gates.flags = 0;\
}

#define Instrument_Gates_TimeoutTimersProcess() {\
}\

/* 
 * Handle Note On message by opening gate 
 * Note number is a gate number
 */
#define Instrument_Gates_NoteOn(noteNum, velocity) {\
    instrument.gates.gateNumberTmp = noteNum % INSTRUMENT_GATES_CFG_MAX_POLYPHONY;\
    if (!Instrument_Gates_isFlagGateOpen(instrument.gates.gateNumberTmp)) {\
        Instrument_Gates_setFlagGateOpen(instrument.gates.gateNumberTmp);\
    }\
    Instrument_Gates_OpenGateByNumber(instrument.gates.gateNumberTmp);\
}

/* 
 * Handle Note Off message by closing gate 
 * Note number is a gate number
 */
#define Instrument_Gates_NoteOff(noteNum) {\
    instrument.gates.gateNumberTmp = noteNum % INSTRUMENT_GATES_CFG_MAX_POLYPHONY;\
    if (Instrument_Gates_isFlagGateOpen(instrument.gates.gateNumberTmp)) {\
        Instrument_Gates_clrFlagGateOpen(instrument.gates.gateNumberTmp);\
    }\
    Instrument_Gates_CloseGateByNumber(instrument.gates.gateNumberTmp);\
}

/* 
 * Set GPIO port output pin to high level
 * Gate number is a port pin number
 */
#define Instrument_Gates_OpenGateByNumber(gateNum) {\
    clr_bit(instrumentGatesPortOut, gateNum);\
}

/* 
 * Set GPIO port output pin to low level
 * Gate number is a port pin number
 */
#define Instrument_Gates_CloseGateByNumber(gateNum) {\
    set_bit(instrumentGatesPortOut, gateNum);\
}

#define Instrument_Gates_AllNotesOn() {\
    for (system.var = 0; system.var < INSTRUMENT_GATES_CFG_MAX_POLYPHONY; system.var++) {\
        Instrument_Gates_setFlagGateOpen(system.var);\
        Instrument_Gates_OpenGateByNumber(system.var);\
    }\
}

/* 
 * Handle Note Off message by closing gate 
 * Note number is a gate number
 */
#define Instrument_Gates_AllNotesOff() {\
    for (system.var = 0; system.var < INSTRUMENT_GATES_CFG_MAX_POLYPHONY; system.var++) {\
        Instrument_Gates_clrFlagGateOpen(system.var);\
        Instrument_Gates_CloseGateByNumber(system.var);\
    }\
}
