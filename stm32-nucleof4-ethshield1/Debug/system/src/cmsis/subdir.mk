################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_stm32f4xx.c 

S_UPPER_SRCS += \
../system/src/cmsis/startup_stm32f401xe.S 

OBJS += \
./system/src/cmsis/startup_stm32f401xe.o \
./system/src/cmsis/system_stm32f4xx.o 

S_UPPER_DEPS += \
./system/src/cmsis/startup_stm32f401xe.d 

C_DEPS += \
./system/src/cmsis/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/%.o: ../system/src/cmsis/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wextra  -g3 -x assembler-with-cpp -DDEBUG -DTRACE -I"../include" -I"../system/include" -I"../system/include/Device" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/cmsis/%.o: ../system/src/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F401xE -I"../include" -I"../system/include" -I"../system/include/Device" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -I"../ioLibrary_Driver/Ethernet" -I"../ioLibrary_Driver/Ethernet/W5100" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


