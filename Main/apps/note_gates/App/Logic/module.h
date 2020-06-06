/*
 * App_Logic Module
 * 
 * Application logic module controls interaction 
 * between all other app modules
 */
struct APP_LOGIC_MODULE {
    BYTE flags;
};

#define App_Logic_Init() {\
    app.logic.flags = 0b00000000;\
}

#define App_Logic_NoteOn(noteNum, velocity) {\
    App_Gates_NoteOn(noteNum, velocity);\
}

#define App_Logic_NoteOff(noteNum) {\
    App_Gates_NoteOff(noteNum);\
}

/*
 * Key Actions
 */
#define App_Logic_KeyDownEvent(keyNum) {\
}

#define App_Logic_KeyUpEvent(keyNum) {\
}
