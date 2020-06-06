/*
 * App_Gates module
 * 
 * Converts note on/off messages to gate open/close signals
 * at GPIO outputs.
 */
#define APP_GATES_CFG_MAX_POLYPHONY                      12

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

#define App_Gates_isFlagGateOpen(gateNum)		            bit_is_set(app.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)
#define App_Gates_setFlagGateOpen(gateNum)		            set_bit(app.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)
#define App_Gates_clrFlagGateOpen(gateNum)		            clr_bit(app.gates.activeGates[gateNum].flags, APP_GATES_FLAG_GATE_OPEN)


#define App_Gates_Init() {\
    app.gates.flags = 0;\
}

/* 
 * Handle Note On message by opening gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOn(noteNum, velocity) {\
    app.gates.gateNumberTmp = noteNum % APP_GATES_CFG_MAX_POLYPHONY;\
    if (!App_Gates_isFlagGateOpen(app.gates.gateNumberTmp)) {\
        App_Gates_setFlagGateOpen(app.gates.gateNumberTmp);\
    }\
    App_Gates_OpenGateByNumber(app.gates.gateNumberTmp);\
}

/* 
 * Handle Note Off message by closing gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOff(noteNum) {\
    app.gates.gateNumberTmp = noteNum % APP_GATES_CFG_MAX_POLYPHONY;\
    if (App_Gates_isFlagGateOpen(app.gates.gateNumberTmp)) {\
        App_Gates_clrFlagGateOpen(app.gates.gateNumberTmp);\
    }\
    App_Gates_CloseGateByNumber(app.gates.gateNumberTmp);\
}

/* 
 * Set GPIO port output pin to high level
 * Gate number will be converted to port pin number
 */
#define App_Gates_OpenGateByNumber(gateNum) {\
    if (gateNum < 7) {\
        set_bit(appGatesPortOut, gateNum);\
    } else {\
        set_bit(appGatesPortOut2, (gateNum - 4));\
    }\
}

/* 
 * Set GPIO port output pin to low level
 * Gate number will be converted to port pin number
 */
#define App_Gates_CloseGateByNumber(gateNum) {\
    if (gateNum < 7) {\
        clr_bit(appGatesPortOut, gateNum);\
    } else {\
        clr_bit(appGatesPortOut2, (gateNum - 4));\
    }\
}
