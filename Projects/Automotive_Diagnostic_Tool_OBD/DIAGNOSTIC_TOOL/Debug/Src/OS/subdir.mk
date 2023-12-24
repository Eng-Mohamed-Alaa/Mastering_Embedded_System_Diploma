################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/OS/croutine.c \
../Src/OS/event_groups.c \
../Src/OS/heap_4.c \
../Src/OS/list.c \
../Src/OS/port.c \
../Src/OS/queue.c \
../Src/OS/stream_buffer.c \
../Src/OS/tasks.c \
../Src/OS/timers.c 

OBJS += \
./Src/OS/croutine.o \
./Src/OS/event_groups.o \
./Src/OS/heap_4.o \
./Src/OS/list.o \
./Src/OS/port.o \
./Src/OS/queue.o \
./Src/OS/stream_buffer.o \
./Src/OS/tasks.o \
./Src/OS/timers.o 

C_DEPS += \
./Src/OS/croutine.d \
./Src/OS/event_groups.d \
./Src/OS/heap_4.d \
./Src/OS/list.d \
./Src/OS/port.d \
./Src/OS/queue.d \
./Src/OS/stream_buffer.d \
./Src/OS/tasks.d \
./Src/OS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/OS/%.o Src/OS/%.su Src/OS/%.cyclo: ../Src/OS/%.c Src/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/include" -I"D:/newnti/Relase 2/DIAGNOSTIC_TOOL_FINAL/Inc/OS/Portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-OS

clean-Src-2f-OS:
	-$(RM) ./Src/OS/croutine.cyclo ./Src/OS/croutine.d ./Src/OS/croutine.o ./Src/OS/croutine.su ./Src/OS/event_groups.cyclo ./Src/OS/event_groups.d ./Src/OS/event_groups.o ./Src/OS/event_groups.su ./Src/OS/heap_4.cyclo ./Src/OS/heap_4.d ./Src/OS/heap_4.o ./Src/OS/heap_4.su ./Src/OS/list.cyclo ./Src/OS/list.d ./Src/OS/list.o ./Src/OS/list.su ./Src/OS/port.cyclo ./Src/OS/port.d ./Src/OS/port.o ./Src/OS/port.su ./Src/OS/queue.cyclo ./Src/OS/queue.d ./Src/OS/queue.o ./Src/OS/queue.su ./Src/OS/stream_buffer.cyclo ./Src/OS/stream_buffer.d ./Src/OS/stream_buffer.o ./Src/OS/stream_buffer.su ./Src/OS/tasks.cyclo ./Src/OS/tasks.d ./Src/OS/tasks.o ./Src/OS/tasks.su ./Src/OS/timers.cyclo ./Src/OS/timers.d ./Src/OS/timers.o ./Src/OS/timers.su

.PHONY: clean-Src-2f-OS

