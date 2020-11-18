PREFIX 	= arm-none-eabi-
CC 		= $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
LD 		= $(PREFIX)ld

CFLAGS 	= -mlittle-endian
CFLAGS += -mthumb
CFLAGS += -mcpu=cortex-m3
CFLAGS += -mfloat-abi=soft
CFLAGS += -ggdb
CFLAGS += -Wall -O2

CFLAGS += -I inc/
CFLAGS += -I inc/CMSIS

.PHONY: all clean

all: main.elf
	$(OBJCOPY) -O binary -S $< main.bin

main.elf: build/main.o build/Startup.o
	$(LD) -nostartfiles -T flash.ld -o $@ $^

build/%.o: src/%.c
	if [ ! -d "./build" ]; then mkdir build; fi
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf *.bin *.elf build/
