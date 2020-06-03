/*
 * Controller_Gates module
 * 
 * controls processor physical outputs as discrete
 * CV gate signals.
 */

/* 
 * Change gate out to logical high state
 * gateNum can be 0, 1, 2
 */
#define Controller_Gates_On(gateNum) {\
    set_bit(controllerGatesPortOut, gateNum + 5);\
}

/* 
 * Change gate out to logical low state
 */
#define Controller_Gates_Off(gateNum) {\
    clr_bit(controllerGatesPortOut, gateNum + 5);\
}

/*
 * Turns on the gate by note number
 * Note number will be converted to gate number
 */
#define Controller_Gates_NoteOn(noteNum) {\
    Controller_Gates_On(noteNum % 3);\
}

/*
 * Turns off the gate by note number
 * Note number will be converted to gate number
 */
#define Controller_Gates_NoteOff(noteNum) {\
    Controller_Gates_Off(noteNum % 3);\
}
