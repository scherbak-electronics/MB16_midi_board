/*
 * App_Gates module
 * 
 * Converts note on/off messages to gate open/close signals
 * at GPIO outputs.
 */
#define APP_GATES_CFG_MAX_POLYPHONY                      8

#define APP_GATES_FLAG_GATE_OPEN                         0

struct GATE_DATA {
    BYTE flags;
    BYTE noteNumber;
};

struct GATES_MODULE {
    BYTE flags;
    struct GATE_DATA activeGates[APP_GATES_CFG_MAX_POLYPHONY];
    BYTE gateNumberTmp;
};

#define App_Gates_isFlagGateOpen(gateNum)		            bit_is_set(instrument.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)
#define App_Gates_setFlagGateOpen(gateNum)		            set_bit(instrument.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)
#define App_Gates_clrFlagGateOpen(gateNum)		            clr_bit(instrument.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)


#define App_Gates_Init() {\
    instrument.gates.flags = 0;\
}

/* 
 * Handle Note On message by opening gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOn(noteNum, velocity) {\
    instrument.gates.gateNumberTmp = noteNum % APP_GATES_CFG_MAX_POLYPHONY;\
    if (!App_Gates_isFlagGateOpen(instrument.gates.gateNumberTmp)) {\
        App_Gates_setFlagGateOpen(instrument.gates.gateNumberTmp);\
    }\
    App_Gates_OpenGateByNumber(instrument.gates.gateNumberTmp);\
}

/* 
 * Handle Note Off message by closing gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOff(noteNum) {\
    instrument.gates.gateNumberTmp = noteNum % APP_GATES_CFG_MAX_POLYPHONY;\
    if (App_Gates_isFlagGateOpen(instrument.gates.gateNumberTmp)) {\
        App_Gates_clrFlagGateOpen(instrument.gates.gateNumberTmp);\
    }\
    App_Gates_CloseGateByNumber(instrument.gates.gateNumberTmp);\
}

/* 
 * Set GPIO port output pin to high level
 * Gate number is a port pin number
 */
#define App_Gates_OpenGateByNumber(gateNum) {\
    set_bit(instrumentGatesPortOut, gateNum);\
}

/* 
 * Set GPIO port output pin to low level
 * Gate number is a port pin number
 */
#define App_Gates_CloseGateByNumber(gateNum) {\
    clr_bit(instrumentGatesPortOut, gateNum);\
}
