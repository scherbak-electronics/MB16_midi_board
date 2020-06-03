#define MIDI_NOTE_C     0  // 00  C   -1              -----
#define MIDI_NOTE_Cb    1  // 01  C#  -1                    ====
#define MIDI_NOTE_D     2  // 02  D   -1              -----
#define MIDI_NOTE_Db    3  // 03  D#  -1                    ====
#define MIDI_NOTE_E     4  // 04  E   -1              -----
#define MIDI_NOTE_F     5  // 05  F   -1              -----
#define MIDI_NOTE_Fb    6  // 06  F#  -1                    ====
#define MIDI_NOTE_G     7  // 07  G   -1              -----
#define MIDI_NOTE_Gb    8  // 08  G#  -1                    ====
#define MIDI_NOTE_A     9  // 09  A   -1              -----
#define MIDI_NOTE_Ab    10 // 0A  A#  -1                    ====
#define MIDI_NOTE_B     11 // 0B  B   -1              -----


#define MIDI_Notes_GetNoteNumber(note, octave)      (note + ((octave + 2) * 12))