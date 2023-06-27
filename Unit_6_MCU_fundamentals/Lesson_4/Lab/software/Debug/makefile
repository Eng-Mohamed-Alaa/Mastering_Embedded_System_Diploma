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
Lesson4_labs.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Lesson4_labs.list \

OBJCOPY_BIN += \
Lesson4_labs.bin \


# All Target
all: Lesson4_labs.elf secondary-outputs

# Tool invocations
Lesson4_labs.elf: $(OBJS) $(USER_OBJS) D:\software\Learn_In_Depth\my_codes\Unit_6_fundamentals\Lesson_4\software\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Lesson4_labs.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\software\Learn_In_Depth\my_codes\Unit_6_fundamentals\Lesson_4\software\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Lesson4_labs.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Lesson4_labs.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Lesson4_labs.list"
	@echo 'Finished building: $@'
	@echo ' '

Lesson4_labs.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Lesson4_labs.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
