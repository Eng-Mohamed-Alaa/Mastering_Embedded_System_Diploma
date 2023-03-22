#Mohamed Alaa

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
PROJECT_NAME=learn_in_depth_cortex_M3

all: $(PROJECT_NAME).bin

%.o: %.c
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(LIBS) $(ASOBJ) -o $@ -Map=map_file.map

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm *.elf *.bin
	@echo "clean is done"

clean_all:
	rm *.o *.elf *.bin
	@echo "clean all is done"

