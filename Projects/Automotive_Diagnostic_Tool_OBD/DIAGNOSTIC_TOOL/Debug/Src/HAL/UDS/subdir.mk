################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/UDS/UDS.c \
../Src/HAL/UDS/UDS_SECURITY_SERVICE.c 

OBJS += \
./Src/HAL/UDS/UDS.o \
./Src/HAL/UDS/UDS_SECURITY_SERVICE.o 

C_DEPS += \
./Src/HAL/UDS/UDS.d \
./Src/HAL/UDS/UDS_SECURITY_SERVICE.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/UDS/%.o Src/HAL/UDS/%.su Src/HAL/UDS/%.cyclo: ../Src/HAL/UDS/%.c Src/HAL/UDS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/include" -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/Portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-UDS

clean-Src-2f-HAL-2f-UDS:
	-$(RM) ./Src/HAL/UDS/UDS.cyclo ./Src/HAL/UDS/UDS.d ./Src/HAL/UDS/UDS.o ./Src/HAL/UDS/UDS.su ./Src/HAL/UDS/UDS_SECURITY_SERVICE.cyclo ./Src/HAL/UDS/UDS_SECURITY_SERVICE.d ./Src/HAL/UDS/UDS_SECURITY_SERVICE.o ./Src/HAL/UDS/UDS_SECURITY_SERVICE.su

.PHONY: clean-Src-2f-HAL-2f-UDS

