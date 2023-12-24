################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/CAN/CAN.c \
../Src/MCAL/CAN/CAN_config.c 

OBJS += \
./Src/MCAL/CAN/CAN.o \
./Src/MCAL/CAN/CAN_config.o 

C_DEPS += \
./Src/MCAL/CAN/CAN.d \
./Src/MCAL/CAN/CAN_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/CAN/%.o Src/MCAL/CAN/%.su Src/MCAL/CAN/%.cyclo: ../Src/MCAL/CAN/%.c Src/MCAL/CAN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/include" -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/Portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-CAN

clean-Src-2f-MCAL-2f-CAN:
	-$(RM) ./Src/MCAL/CAN/CAN.cyclo ./Src/MCAL/CAN/CAN.d ./Src/MCAL/CAN/CAN.o ./Src/MCAL/CAN/CAN.su ./Src/MCAL/CAN/CAN_config.cyclo ./Src/MCAL/CAN/CAN_config.d ./Src/MCAL/CAN/CAN_config.o ./Src/MCAL/CAN/CAN_config.su

.PHONY: clean-Src-2f-MCAL-2f-CAN

