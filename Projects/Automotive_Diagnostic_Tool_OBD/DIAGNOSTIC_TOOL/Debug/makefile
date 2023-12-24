################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/OS/subdir.mk
-include Src/MCAL/UART/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/SCB/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/NVIC/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/CAN/subdir.mk
-include Src/MCAL/ADC/subdir.mk
-include Src/HAL/UDS/subdir.mk
-include Src/HAL/TFT/subdir.mk
-include Src/HAL/KEYPAD/subdir.mk
-include Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DIAGNOSTIC_TOOL_FINAL
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DIAGNOSTIC_TOOL_FINAL.elf \

MAP_FILES += \
DIAGNOSTIC_TOOL_FINAL.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DIAGNOSTIC_TOOL_FINAL.list \

OBJCOPY_HEX += \
DIAGNOSTIC_TOOL_FINAL.hex \

OBJCOPY_BIN += \
DIAGNOSTIC_TOOL_FINAL.bin \


# All Target
all: main-build

# Main-build Target
main-build: DIAGNOSTIC_TOOL_FINAL.elf secondary-outputs

# Tool invocations
DIAGNOSTIC_TOOL_FINAL.elf DIAGNOSTIC_TOOL_FINAL.map: $(OBJS) $(USER_OBJS) D:\newnti\Relase\ 2\DIAGNOSTIC_TOOL_FINAL\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "DIAGNOSTIC_TOOL_FINAL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\newnti\Relase 2\DIAGNOSTIC_TOOL_FINAL\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DIAGNOSTIC_TOOL_FINAL.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DIAGNOSTIC_TOOL_FINAL.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DIAGNOSTIC_TOOL_FINAL.list"
	@echo 'Finished building: $@'
	@echo ' '

DIAGNOSTIC_TOOL_FINAL.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "DIAGNOSTIC_TOOL_FINAL.hex"
	@echo 'Finished building: $@'
	@echo ' '

DIAGNOSTIC_TOOL_FINAL.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "DIAGNOSTIC_TOOL_FINAL.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DIAGNOSTIC_TOOL_FINAL.bin DIAGNOSTIC_TOOL_FINAL.elf DIAGNOSTIC_TOOL_FINAL.hex DIAGNOSTIC_TOOL_FINAL.list DIAGNOSTIC_TOOL_FINAL.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
