#Mohamed Alaa

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m4 -mthumb -gdwarf-2 -g
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
PROJECT_NAME=unit3_lab4_cortex_M4

all: $(PROJECT_NAME).bin


%.o: %.c
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(LIBS) $(ASOBJ) -o $@ -Map=map_file.map
	cp $(PROJECT_NAME).elf $(PROJECT_NAME).axf

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm *.elf *.bin *.axf
	@echo "clean is done"

clean_all:
	rm *.o *.elf *.bin *.axf
	@echo "clean all is done"

