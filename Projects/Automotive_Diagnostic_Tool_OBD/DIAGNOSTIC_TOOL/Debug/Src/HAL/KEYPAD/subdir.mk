################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/KEYPAD/KEYPAD.c 

OBJS += \
./Src/HAL/KEYPAD/KEYPAD.o 

C_DEPS += \
./Src/HAL/KEYPAD/KEYPAD.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/KEYPAD/%.o Src/HAL/KEYPAD/%.su Src/HAL/KEYPAD/%.cyclo: ../Src/HAL/KEYPAD/%.c Src/HAL/KEYPAD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/include" -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/Portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-KEYPAD

clean-Src-2f-HAL-2f-KEYPAD:
	-$(RM) ./Src/HAL/KEYPAD/KEYPAD.cyclo ./Src/HAL/KEYPAD/KEYPAD.d ./Src/HAL/KEYPAD/KEYPAD.o ./Src/HAL/KEYPAD/KEYPAD.su

.PHONY: clean-Src-2f-HAL-2f-KEYPAD

