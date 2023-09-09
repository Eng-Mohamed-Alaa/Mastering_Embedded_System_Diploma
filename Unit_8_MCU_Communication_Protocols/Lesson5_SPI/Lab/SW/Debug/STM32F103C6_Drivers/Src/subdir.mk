################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.c \
../STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.c \
../STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.c \
../STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.c \
../STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.c 

OBJS += \
./STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.o \
./STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.o \
./STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.o \
./STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.o \
./STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.o 

C_DEPS += \
./STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.d \
./STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.d \
./STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.d \
./STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.d \
./STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/STM32F103C6_Drivers/Inc" -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/HAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_EXTI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/STM32F103C6_Drivers/Inc" -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/HAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/STM32F103C6_Drivers/Inc" -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/HAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_RCC_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/STM32F103C6_Drivers/Inc" -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/HAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_SPI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.o: ../STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/STM32F103C6_Drivers/Inc" -I"D:/software/Learn_In_Depth/my_codes/Unit_8/Lesson5/Lab/SW/HAL/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32F103C6_Drivers/Src/STM32F103C6_USART_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

