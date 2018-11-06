/* MIDI Controller Numbers */

#define MIDI_CONTROLLER_NUMBER_0        0x00 // Bank Select (Controller # 32 more commonly used)
#define MIDI_CONTROLLER_NUMBER_1        0x01 // Modulation Wheel
#define MIDI_CONTROLLER_NUMBER_2        0x02 // Breat Contoller
#define MIDI_CONTROLLER_NUMBER_3        0x03 // Undefined
#define MIDI_CONTROLLER_NUMBER_4        0x04 // Foot Controller
#define MIDI_CONTROLLER_NUMBER_5        0x05 // Portamento Time
#define MIDI_CONTROLLER_NUMBER_6        0x06 // Data Entry MSB
#define MIDI_CONTROLLER_NUMBER_7        0x07 // Main Volume
#define MIDI_CONTROLLER_NUMBER_8        0x08 // Balance
#define MIDI_CONTROLLER_NUMBER_9        0x09 // Undefined
#define MIDI_CONTROLLER_NUMBER_10       0x0A // Pan
#define MIDI_CONTROLLER_NUMBER_11       0x0B // 0Ch
#define MIDI_CONTROLLER_NUMBER_12       0x0C // Effect Control 1
#define MIDI_CONTROLLER_NUMBER_13       0x0D // Effect Control 2
#define MIDI_CONTROLLER_NUMBER_14       0x0e // Undefined
#define MIDI_CONTROLLER_NUMBER_15       0x0f // Undefined
#define MIDI_CONTROLLER_NUMBER_16       0x10 // 10-13  General Purpose Controllers (Nos. 1-4)
#define MIDI_CONTROLLER_NUMBER_17       0x11 // 10-13  General Purpose Controllers (Nos. 1-4)
#define MIDI_CONTROLLER_NUMBER_18       0x12 // 10-13  General Purpose Controllers (Nos. 1-4)
#define MIDI_CONTROLLER_NUMBER_19       0x13 // 10-13  General Purpose Controllers (Nos. 1-4)

#define MIDI_CONTROLLER_NUMBER_20       0x14 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_21       0x15 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_22       0x16 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_23       0x17 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_24       0x18 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_25       0x19 // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_26       0x1a // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_27       0x1b // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_28       0x1c // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_29       0x1d // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_30       0x1e // 14-1F  Undefined
#define MIDI_CONTROLLER_NUMBER_31       0x1f // 14-1F  Undefined

#define MIDI_CONTROLLER_NUMBER_32       0x20 // 20-3F  LSB for Controllers 0-31 (rarely implemented)
#define MIDI_CONTROLLER_NUMBER_63       0x3f //
#define MIDI_CONTROLLER_NUMBER_64       0x40 // Damper Pedal (Sustain) [Data Byte of 0-63=0ff, 64-127=On]
#define MIDI_CONTROLLER_NUMBER_65       0x41 // Portamento
#define MIDI_CONTROLLER_NUMBER_66       0x42 // Sostenuto
#define MIDI_CONTROLLER_NUMBER_67       0x43 // Soft Pedal
#define MIDI_CONTROLLER_NUMBER_68       0x44 // Legato Footswitch
#define MIDI_CONTROLLER_NUMBER_69       0x45 // Hold 2
#define MIDI_CONTROLLER_NUMBER_70       0x46 // Sound Controller 1 (default: Sound Variation)
#define MIDI_CONTROLLER_NUMBER_71       0x47 // Sound Controller 2 (default: Timbre/Harmonic Content)
#define MIDI_CONTROLLER_NUMBER_72       0x48 // Sound Controller 3 (default: Release Time)
#define MIDI_CONTROLLER_NUMBER_73       0x49 // Sound Controller 4 (default: Attack Time)
#define MIDI_CONTROLLER_NUMBER_74       0x4A // Sound Controller 5 (default: Brightness)

#define MIDI_CONTROLLER_NUMBER_75       0x4b // 4B-4F  Sound Controller 6-10 (no defaults)
#define MIDI_CONTROLLER_NUMBER_76       0x4C //
#define MIDI_CONTROLLER_NUMBER_77       0x4b //
#define MIDI_CONTROLLER_NUMBER_78       0x4e //
#define MIDI_CONTROLLER_NUMBER_79       0x4f //

#define MIDI_CONTROLLER_NUMBER_81       0x51 // 50-53  General Purpose Controllers (Nos. 5-8)
#define MIDI_CONTROLLER_NUMBER_82       0x52 //
#define MIDI_CONTROLLER_NUMBER_83       0x53 //

#define MIDI_CONTROLLER_NUMBER_84       0x54 // Portamento Control

#define MIDI_CONTROLLER_NUMBER_85       0x55 // Undefined
#define MIDI_CONTROLLER_NUMBER_86       0x56 // Undefined
#define MIDI_CONTROLLER_NUMBER_87       0x57 // Undefined
#define MIDI_CONTROLLER_NUMBER_88       0x58 // Undefined
#define MIDI_CONTROLLER_NUMBER_89       0x59 // Undefined
#define MIDI_CONTROLLER_NUMBER_90       0x5a // Undefined

#define MIDI_CONTROLLER_NUMBER_91       0x5B // Effects 1 Dept (previously External Effects Depth)
#define MIDI_CONTROLLER_NUMBER_92       0x5C // Effects 2 Dept (previously Tremolo Depth)
#define MIDI_CONTROLLER_NUMBER_93       0x5D // Effects 3 Dept (previously Chorus Depth)
#define MIDI_CONTROLLER_NUMBER_94       0x5E // Effects 4 Dept (previously Detune Depth)
#define MIDI_CONTROLLER_NUMBER_95       0x5F // Effects 5 Dept (previously Phaser Depth)
#define MIDI_CONTROLLER_NUMBER_96       0x60 // Data Increment
#define MIDI_CONTROLLER_NUMBER_97       0x61 // Data Decrement
#define MIDI_CONTROLLER_NUMBER_98       0x62 // Non-Registered Parameter Number LSB
#define MIDI_CONTROLLER_NUMBER_99       0x63 // Non-Registered Parameter Number LSB
#define MIDI_CONTROLLER_NUMBER_100      0x64 // Registered Parameter Number LSB
#define MIDI_CONTROLLER_NUMBER_101      0x65 // Registered Parameter Number MSB

#define MIDI_CONTROLLER_NUMBER_102      0x66  // Undefined
#define MIDI_CONTROLLER_NUMBER_103      0x67
#define MIDI_CONTROLLER_NUMBER_104      0x68
#define MIDI_CONTROLLER_NUMBER_105      0x69
#define MIDI_CONTROLLER_NUMBER_106      0x6a
#define MIDI_CONTROLLER_NUMBER_107      0x6b
#define MIDI_CONTROLLER_NUMBER_108      0x6c
#define MIDI_CONTROLLER_NUMBER_109      0x6d
#define MIDI_CONTROLLER_NUMBER_110
#define MIDI_CONTROLLER_NUMBER_111
#define MIDI_CONTROLLER_NUMBER_112
#define MIDI_CONTROLLER_NUMBER_113
#define MIDI_CONTROLLER_NUMBER_114
#define MIDI_CONTROLLER_NUMBER_115
#define MIDI_CONTROLLER_NUMBER_116
#define MIDI_CONTROLLER_NUMBER_117
#define MIDI_CONTROLLER_NUMBER_118
#define MIDI_CONTROLLER_NUMBER_119
#define MIDI_CONTROLLER_NUMBER_120

/* Channel Mode Messages */
#define MIDI_CONTROLLER_NUMBER_121 0x79 // Reset All Controllers
#define MIDI_CONTROLLER_NUMBER_122 0x7A // Local Control
#define MIDI_CONTROLLER_NUMBER_123 0x7B // All Notes Off
#define MIDI_CONTROLLER_NUMBER_124 0x7C // Omni Off
#define MIDI_CONTROLLER_NUMBER_125 0x7D // Omni On
#define MIDI_CONTROLLER_NUMBER_126 0x7E // Mono On (Poly Off)
#define MIDI_CONTROLLER_NUMBER_127 0x7F // Poly On (Mono Off)
