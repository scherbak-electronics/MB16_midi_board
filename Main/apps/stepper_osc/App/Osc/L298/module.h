/*
 * App_Osc_L298 module
 * 
 * Hardware driver for L298. 
 * L298 is an integrated monolithic circuit in a 15-
 * lead Multiwatt and PowerSO20 packages. It is a
 * high voltage, high current dual full-bridge driver designed to accept standard TTL logic levels and drive
 * inductive loads such as relays, solenoids, DC and stepping motors. 
 */
#define APP_OSC_L298_CFG_BIPOLAR_SEQUENCE_LEN                      4
#define APP_OSC_L298_FLAG_DIR                                       0

#define App_Osc_L298_getFlagDir(oscNum)		            bit_is_set(app.osc.oscillators[oscNum].l298.flags, APP_OSC_L298_FLAG_DIR)

struct OSC_L298_DATA {
    BYTE flags;
    BYTE bipolarSequence[APP_OSC_L298_CFG_BIPOLAR_SEQUENCE_LEN];
    BYTE sequenceStepNumber;
};

#define App_Osc_L298_Init() {\
}

#define App_Osc_L298_SetNextPhase(oscNum) {\
    App_Osc_L298_SetPhase(oscNum, app.osc.oscillators[oscNum].l298.bipolarSequence[(app.osc.oscillators[oscNum].l298.sequenceStepNumber & 0b00000011)] & 0b11110000);\
    if (App_Osc_L298_getFlagDir(oscNum)) {\
        app.osc.oscillators[oscNum].l298.sequenceStepNumber++;\
    } else {\
        app.osc.oscillators[oscNum].l298.sequenceStepNumber--;\
    }\
}

#define App_Osc_L298_SetPhase(oscNum, phase) {\
    switch (oscNum) {\
        case 0:\
        appOscL2980PortOut = phase;\
        break;\
        case 1:\
        appOscL2981PortOut = phase;\
        break;\
    }\
}
