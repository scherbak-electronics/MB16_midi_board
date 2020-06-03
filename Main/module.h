/*
 * Main module
 * 
 * Connects all other nested sub modules together
 * Defines GPIO ports mapping, events and action calls routing
 */
#include "MB16/lib/system_m16.h"
#include "apps/default/App/module.h"
// #include "apps/note_gates/App/module.h"
// #include "apps/instrument_HDD_heads/App/module.h"
// #include "apps/controller_C8145/App/module.h"
// #include "apps/controller_C8145_eurorack/App/module.h"
// #include "apps/instrument_city_12/App/module.h"
#include "MB16/System/module.h"
#include "MB16/MIDI/module.h"
