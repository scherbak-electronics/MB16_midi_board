/*
 * Controller_Mode_0
 * 
 * Mode: MIDI controller. (default mode)
 * Provides logic of interaction between all other modules.
 */
 #include "Key/module.h"
 #include "Knob/module.h"
 #include "View/template.h"

/*
 * Module Initialization.
 */
#define Controller_Mode_0_Init() {\
}

/*
 * Module Main Process.
 */
#define Controller_Mode_0_Process() {\
}

/*
 * Mode specific internal initialisation. 
 * Call this method each time when selecting this mode.
 */
#define Controller_Mode_0_Select() {\
    Controller_Mode_0_View_Show();\
}

/*
 * Method used to clear resources after using.
 */
#define Controller_Mode_0_Unselect() {\
}
