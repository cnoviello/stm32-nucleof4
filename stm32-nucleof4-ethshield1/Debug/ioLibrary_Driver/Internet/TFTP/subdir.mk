################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver/Internet/TFTP/netutil.c \
../ioLibrary_Driver/Internet/TFTP/tftp.c 

OBJS += \
./ioLibrary_Driver/Internet/TFTP/netutil.o \
./ioLibrary_Driver/Internet/TFTP/tftp.o 

C_DEPS += \
./ioLibrary_Driver/Internet/TFTP/netutil.d \
./ioLibrary_Driver/Internet/TFTP/tftp.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver/Internet/TFTP/%.o: ../ioLibrary_Driver/Internet/TFTP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wextra  -g3 -DDEBUG -DTRACE -DSTM32F401xE -I"../include" -I"../system/include" -I"../system/include/Device" -I"../system/include/cmsis" -I"../system/include/stm32f4xx" -I"../ioLibrary_Driver/Ethernet" -I"../ioLibrary_Driver/Ethernet/W5100" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


