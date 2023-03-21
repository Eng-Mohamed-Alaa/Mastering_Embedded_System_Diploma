################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
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
toggle_led_stm32f103c6.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
toggle_led_stm32f103c6.list \

OBJCOPY_HEX += \
toggle_led_stm32f103c6.hex \

OBJCOPY_BIN += \
toggle_led_stm32f103c6.bin \


# All Target
all: toggle_led_stm32f103c6.elf secondary-outputs

# Tool invocations
toggle_led_stm32f103c6.elf: $(OBJS) $(USER_OBJS) D:\software\Learn_In_Depth\my_codes\Unit_3_embedded\ _C\lesson_1\toggle_led_stm32f103c6\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -ansi -std=c89 -o "toggle_led_stm32f103c6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\software\Learn_In_Depth\my_codes\Unit_3_embedded _C\lesson_1\toggle_led_stm32f103c6\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="toggle_led_stm32f103c6.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

toggle_led_stm32f103c6.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "toggle_led_stm32f103c6.list"
	@echo 'Finished building: $@'
	@echo ' '

toggle_led_stm32f103c6.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "toggle_led_stm32f103c6.hex"
	@echo 'Finished building: $@'
	@echo ' '

toggle_led_stm32f103c6.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "toggle_led_stm32f103c6.bin"
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
