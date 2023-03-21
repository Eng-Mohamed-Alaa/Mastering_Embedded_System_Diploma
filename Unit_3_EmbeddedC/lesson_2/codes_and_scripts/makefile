#learn-in-depth
#Mohamed Alaa
CC=arm-none-eabi-
CFLAGS=-mcpu=arm926ej-s
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
PROJECT_NAME=learn_in_depth

all: $(PROJECT_NAME).bin

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(ASOBJ) -o $@ -Map=map_file.map

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm *.elf *.bin
	@echo "clean is done"

clean_all:
	rm *.o *.elf *.bin
	@echo "clean all is done"

