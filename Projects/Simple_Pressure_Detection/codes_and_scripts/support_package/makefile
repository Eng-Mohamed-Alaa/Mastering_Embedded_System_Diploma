#Mohamed Alaa
#Mastering Embedded Systems Online Diploma

CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -mthumb -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
PROJECT_NAME= High_Pressure_Detection_System

all: $(PROJECT_NAME).bin

%.o: %.c
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@


$(PROJECT_NAME).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(LIBS) -o $@ -Map=map_file.map

$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm *.elf *.bin *.map
	@echo "clean is done"

clean_all:
	rm *.o *.elf *.bin *.map
	@echo "clean all is done"


