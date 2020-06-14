typedef unsigned int     				WORD;
typedef unsigned char      				BYTE;

#define _BV(bit)						      (1 << (bit))
#define set_bit(byte, bit) 				(byte |= _BV(bit))
#define clr_bit(byte, bit) 				(byte &= ~_BV(bit))
#define inv_bit(byte, bit)              byte ^= (1 << bit)
#define get_bit(byte, bit) 				((byte >> bit) & 0x01)
#define word_bit_is_set(word, bit)       (_SFR_WORD(word) & _BV(bit))

#define make_byte(nlow, nhi) 			((BYTE)((nlow & 0x0f) | (nhi & 0x0f) << 4))
#define get_lo_nibble(byte)				(byte & 0x0f)
#define get_hi_nibble(byte)				((byte & 0xf0) >> 4)
