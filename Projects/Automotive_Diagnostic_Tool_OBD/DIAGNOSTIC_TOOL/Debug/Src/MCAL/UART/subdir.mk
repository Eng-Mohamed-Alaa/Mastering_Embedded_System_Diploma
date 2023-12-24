################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/UART/USART.c \
../Src/MCAL/UART/USART_config.c 

OBJS += \
./Src/MCAL/UART/USART.o \
./Src/MCAL/UART/USART_config.o 

C_DEPS += \
./Src/MCAL/UART/USART.d \
./Src/MCAL/UART/USART_config.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/UART/%.o Src/MCAL/UART/%.su Src/MCAL/UART/%.cyclo: ../Src/MCAL/UART/%.c Src/MCAL/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/include" -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/Portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-UART

clean-Src-2f-MCAL-2f-UART:
	-$(RM) ./Src/MCAL/UART/USART.cyclo ./Src/MCAL/UART/USART.d ./Src/MCAL/UART/USART.o ./Src/MCAL/UART/USART.su ./Src/MCAL/UART/USART_config.cyclo ./Src/MCAL/UART/USART_config.d ./Src/MCAL/UART/USART_config.o ./Src/MCAL/UART/USART_config.su

.PHONY: clean-Src-2f-MCAL-2f-UART

