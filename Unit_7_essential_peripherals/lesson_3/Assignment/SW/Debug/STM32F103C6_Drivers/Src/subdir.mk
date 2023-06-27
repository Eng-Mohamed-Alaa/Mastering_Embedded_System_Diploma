################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.c 

OBJS += \
./STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.o 

C_DEPS += \
./STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_7_essential_peripherals/lesson_3/Assignment/SW/HAL/Inc" -I../Inc -I"D:/software/Learn_In_Depth/my_codes/Unit_7_essential_peripherals/lesson_3/Assignment/SW/STM32F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

