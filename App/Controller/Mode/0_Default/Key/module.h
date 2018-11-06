#include "5_mode_select.h"

/*
 * Key Down Actions
 */
#define Controller_Mode_0_Key_0_DownAction() {\
    if (Controller_Key_isNoteNumber(0)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(0), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(0), 127);\
    }\
}
#define Controller_Mode_0_Key_1_DownAction() {\
    if (Controller_Key_isNoteNumber(1)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(1), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(1), 127);\
    }\
}
#define Controller_Mode_0_Key_2_DownAction() {\
    if (Controller_Key_isNoteNumber(2)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(2), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(2), 127);\
    }\
}
#define Controller_Mode_0_Key_3_DownAction() {\
    if (Controller_Key_isNoteNumber(3)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(3), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(3), 127);\
    }\
}
#define Controller_Mode_0_Key_4_DownAction() {\
    if (Controller_Key_isNoteNumber(4)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(4), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(4), 127);\
    }\
}

#define Controller_Mode_0_Key_6_DownAction() {\
    if (Controller_Key_isNoteNumber(6)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(6), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(6), 127);\
    }\
}
#define Controller_Mode_0_Key_7_DownAction() {\
    if (Controller_Key_isNoteNumber(7)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(7), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(7), 127);\
    }\
}
#define Controller_Mode_0_Key_8_DownAction() {\
    if (Controller_Key_isNoteNumber(8)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(8), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(8), 127);\
    }\
}
#define Controller_Mode_0_Key_9_DownAction() {\
    if (Controller_Key_isNoteNumber(9)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(9), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(9), 127);\
    }\
}
#define Controller_Mode_0_Key_10_DownAction() {\
    if (Controller_Key_isNoteNumber(10)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(10), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(10), 127);\
    }\
}
#define Controller_Mode_0_Key_11_DownAction() {\
    if (Controller_Key_isNoteNumber(11)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(11), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(11), 127);\
    }\
}
#define Controller_Mode_0_Key_12_DownAction() {\
    if (Controller_Key_isNoteNumber(12)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(12), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(12), 127);\
    }\
}
#define Controller_Mode_0_Key_13_DownAction() {\
    if (Controller_Key_isNoteNumber(13)) {\
        MIDI_Out_SendNoteOn(Controller_Key_GetNoteNumber(13), CONTROLLER_CFG_DEFAULT_VELOCITY);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(13), 127);\
    }\
}


/*
 * Key Up Actions
 */
#define Controller_Mode_0_Key_0_UpAction() {\
    if (Controller_Key_isNoteNumber(0)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(0), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(0), 0);\
    }\
}
#define Controller_Mode_0_Key_1_UpAction() {\
    if (Controller_Key_isNoteNumber(1)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(1), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(1), 0);\
    }\
}
#define Controller_Mode_0_Key_2_UpAction() {\
    if (Controller_Key_isNoteNumber(2)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(2), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(2), 0);\
    }\
}
#define Controller_Mode_0_Key_3_UpAction() {\
    if (Controller_Key_isNoteNumber(3)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(3), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(3), 0);\
    }\
}
#define Controller_Mode_0_Key_4_UpAction() {\
    if (Controller_Key_isNoteNumber(4)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(4), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(4), 0);\
    }\
}

#define Controller_Mode_0_Key_6_UpAction() {\
    if (Controller_Key_isNoteNumber(6)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(6), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(6), 0);\
    }\
}
#define Controller_Mode_0_Key_7_UpAction() {\
    if (Controller_Key_isNoteNumber(7)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(7), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(7), 0);\
    }\
}
#define Controller_Mode_0_Key_8_UpAction() {\
    if (Controller_Key_isNoteNumber(8)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(8), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(8), 0);\
    }\
}
#define Controller_Mode_0_Key_9_UpAction() {\
    if (Controller_Key_isNoteNumber(9)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(9), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(9), 0);\
    }\
}
#define Controller_Mode_0_Key_10_UpAction() {\
    if (Controller_Key_isNoteNumber(10)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(10), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(10), 0);\
    }\
}
#define Controller_Mode_0_Key_11_UpAction() {\
    if (Controller_Key_isNoteNumber(11)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(11), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(11), 0);\
    }\
}
#define Controller_Mode_0_Key_12_UpAction() {\
    if (Controller_Key_isNoteNumber(12)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(12), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(12), 0);\
    }\
}
#define Controller_Mode_0_Key_13_UpAction() {\
    if (Controller_Key_isNoteNumber(13)) {\
        MIDI_Out_SendNoteOff(Controller_Key_GetNoteNumber(13), 0);\
    } else {\
        MIDI_Out_SendControlChange(Controller_Key_GetCCNumber(13), 0);\
    }\
}
