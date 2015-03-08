################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c \
../src/bluenrg_interface.c \
../src/clock.c \
../src/cube_hal_f4.c \
../src/main.c \
../src/sensor_service.c \
../src/stm32xx_it.c 

OBJS += \
./src/_initialize_hardware.o \
./src/_write.o \
./src/bluenrg_interface.o \
./src/clock.o \
./src/cube_hal_f4.o \
./src/main.o \
./src/sensor_service.o \
./src/stm32xx_it.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d \
./src/bluenrg_interface.d \
./src/clock.d \
./src/cube_hal_f4.d \
./src/main.d \
./src/sensor_service.d \
./src/stm32xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DBLUENRG_CONFIG=BLUENRG_32_MHZ -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DTRACE -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F4XX_NUCLEO -I../bluenrg-stack/Middlewares/ST/LowPowerManager/Inc -I../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/includes -I../bluenrg-stack/BSP/STM32F4xx-Nucleo -I../bluenrg-stack/BSP/X-NUCLEO-IDB04A1 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


