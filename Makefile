# Name: Makefile
# Author: SE systems
# Copyright: SE systems
# License: Free

# This is a prototype Makefile. Modify it according to your needs.
# You should at least check the settings for
# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected. We recommend that you leave it undefined and
#                add settings like this to your ~/.avrduderc file:
#                   default_programmer = "stk500v2"
#                   default_serial = "avrdoper"
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

DEVICE     = atmega32
CLOCK      = 16000000
PROGRAMMER = -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X
OBJECTS    = main.o
FUSES      = -U hfuse:w:0xcf:m -U lfuse:w:0xff:m

# ATMega16 fuse bits used above (fuse bits for other devices are different!):
# Example for 16 MHz external crystal oscillator
# Fuse high byte:
# 0xcf = 1 1 0 0   1 1 1 1 <-- BOOTRST (boot reset vector at 0x0000)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0 (bootloader size: 00 = 1024, 01 = 512)
#        | | | |   | +-------- BOOTSZ1 (10 = 256, 11 = 128)
#        | | | |   +---------- EESAVE (set to 0 to preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (clock option, depends on oscillator type)
#        | | +---------------- SPIEN (if set to 1, serial programming is disabled)
#        | +------------------ JTAGEN (if set to 0, JTAG is enabled)
#        +-------------------- OCDEN (if set to 0, on-board debug enabled)
# Fuse low byte:
# 0xff = 1 1 1 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (8M internal RC)
#        | |  +--------------- SUT 1..0 (slowly rising power)
#        | +------------------ BODEN (if 0, brown-out detector is enabled)
#        +-------------------- BODLEVEL (if 0: 4V, if 1: 2.7V)
#
# For computing fuse byte values for other devices and options see
# the fuse bit calculator at http://www.engbedded.com/fusecalc/


# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -w -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

read:
	avrdude -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X -p $(DEVICE) -U hfuse:r:hfuse_dump.hex:i -U lfuse:r:lfuse_dump.hex:i -U flash:r:main_dump.hex:i

read_eeprom:
	avrdude -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X -p $(DEVICE) -U eeprom:r:eeprom_dump.hex:i
	hexdump -C -n1024 eeprom_dump.hex

checkfuse:
	avrdude -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X -p $(DEVICE) -U hfuse:v:hfuse_dump.hex:i -U lfuse:v:lfuse_dump.hex:i

write:
	avrdude -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X -p $(DEVICE) $(FUSES) -U flash:w:main.hex:i

checkmain:
	avrdude -c avrispv2 -P /dev/cu.usbserial-FTSLSN7X -p $(DEVICE) -U flash:v:main.hex:i
