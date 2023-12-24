################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/ADC/ADC.c 

OBJS += \
./Src/MCAL/ADC/ADC.o 

C_DEPS += \
./Src/MCAL/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/ADC/ADC.o: ../Src/MCAL/ADC/ADC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"D:/software/NTI/Final_Projecgt_Workspace1/Car_ECU/Inc/OS/include" -I"D:/software/NTI/Final_Projecgt_Workspace1/Car_ECU/Inc/OS/Portable/GCC/ARM_CM3" -I"D:/software/NTI/Final_Projecgt_Workspace1/Car_ECU/Inc/APP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/ADC/ADC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

