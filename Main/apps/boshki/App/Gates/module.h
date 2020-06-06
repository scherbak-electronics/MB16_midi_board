/*
 * App_Gates module
 * 
 * Converts note on/off messages to gate open/close signals
 * at GPIO outputs.
 */
#define APP_GATES_CFG_MAX_POLYPHONY                      8
#define APP_GATES_CFG_GATE_TIME                         50

#define APP_GATES_FLAG_GATE_OPEN                         0

struct GATE_DATA {
    BYTE flags;
    BYTE noteNumber;
    BYTE timer;
};

struct GATES_MODULE {
    BYTE flags;
    struct GATE_DATA activeGates[APP_GATES_CFG_MAX_POLYPHONY];
    BYTE gateNumberTmp;
};

#define App_Gates_isGateOpen(gateNum)		            bit_is_set(appGatesPortOut, gateNum)

#define App_Gates_Init() {\
    appGatesPortDir = 0;\
    app.gates.flags = 0;\
    app.gates.gateNumberTmp = 0;\
    app.gates.activeGates[0].timer = 0;\
    app.gates.activeGates[1].timer = 0;\
    app.gates.activeGates[2].timer = 0;\
    app.gates.activeGates[3].timer = 0;\
    app.gates.activeGates[4].timer = 0;\
    app.gates.activeGates[5].timer = 0;\
    app.gates.activeGates[6].timer = 0;\
    app.gates.activeGates[7].timer = 0;\
}

#define App_Gates_TimersProcess() {\
    App_Gates_TimerProcess(0);\
    App_Gates_TimerProcess(1);\
    App_Gates_TimerProcess(2);\
    App_Gates_TimerProcess(3);\
    App_Gates_TimerProcess(4);\
    App_Gates_TimerProcess(5);\
    App_Gates_TimerProcess(6);\
    App_Gates_TimerProcess(7);\
}

#define App_Gates_TimerProcess(gateNum) {\
    if (app.gates.activeGates[gateNum].timer != 0) {\
        app.gates.activeGates[gateNum].timer--;\
        if (app.gates.activeGates[gateNum].timer == 0) {\
            App_Gates_CloseGateByNumber(gateNum);\
        }\
    }\
}

/* 
 * Handle Note On message by opening gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOn(noteNum, velocity) {\
    app.gates.gateNumberTmp = noteNum % APP_GATES_CFG_MAX_POLYPHONY;\
    App_Gates_OpenGateByNumber(app.gates.gateNumberTmp);\
    app.gates.activeGates[app.gates.gateNumberTmp].timer = APP_GATES_CFG_GATE_TIME;\
}

/* 
 * Handle Note Off message by closing gate 
 * Note number is a gate number
 */
#define App_Gates_NoteOff(noteNum) {\
}

/* 
 * Set GPIO port output pin to high level
 * Gate number is a port pin number
 */
#define App_Gates_OpenGateByNumber(gateNum) {\
    set_bit(appGatesPortDir, gateNum);\
    set_bit(appGatesPortOut, gateNum);\
}

/* 
 * Set GPIO port output pin to low level
 * Gate number is a port pin number
 */
#define App_Gates_CloseGateByNumber(gateNum) {\
    clr_bit(appGatesPortOut, gateNum);\
    clr_bit(appGatesPortDir, gateNum);\
}
