################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/OS/subdir.mk
-include Src/MCAL/UART/subdir.mk
-include Src/MCAL/TIMER/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/SCB/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/NVIC/subdir.mk
-include Src/MCAL/I2C/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/FLASH/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/MCAL/CAN/subdir.mk
-include Src/MCAL/AFIO/subdir.mk
-include Src/MCAL/ADC/subdir.mk
-include Src/HAL/lm35/subdir.mk
-include Src/HAL/UDS/subdir.mk
-include Src/HAL/Servo_Motor/subdir.mk
-include Src/HAL/NVRAM/subdir.mk
-include Src/HAL/Mirror/subdir.mk
-include Src/HAL/Limit_Switch/subdir.mk
-include Src/HAL/LED/subdir.mk
-include Src/HAL/HC_05/subdir.mk
-include Src/HAL/FEE/subdir.mk
-include Src/HAL/EEPROM/subdir.mk
-include Src/HAL/CAR_DC_MOTORS/subdir.mk
-include Src/APP/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Car_ECU.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Car_ECU.list \

OBJCOPY_HEX += \
Car_ECU.hex \

OBJCOPY_BIN += \
Car_ECU.bin \


# All Target
all: Car_ECU.elf secondary-outputs

# Tool invocations
Car_ECU.elf: $(OBJS) $(USER_OBJS) D:\software\NTI\Final_Projecgt_Workspace1\Car_ECU\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Car_ECU.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\software\NTI\Final_Projecgt_Workspace1\Car_ECU\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Car_ECU.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Car_ECU.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Car_ECU.list"
	@echo 'Finished building: $@'
	@echo ' '

Car_ECU.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Car_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

Car_ECU.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Car_ECU.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
