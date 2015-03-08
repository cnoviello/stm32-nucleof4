################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/gp_timer.c \
../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/list.c \
../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/osal.c 

OBJS += \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/gp_timer.o \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/list.o \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/osal.o 

C_DEPS += \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/gp_timer.d \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/list.d \
./bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/osal.d 


# Each subdirectory must supply rules for building sources it contributes
bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/%.o: ../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DBLUENRG_CONFIG=BLUENRG_32_MHZ -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DTRACE -DSTM32F401xE -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F4XX_NUCLEO -I../bluenrg-stack/Middlewares/ST/LowPowerManager/Inc -I../bluenrg-stack/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/includes -I../bluenrg-stack/BSP/STM32F4xx-Nucleo -I../bluenrg-stack/BSP/X-NUCLEO-IDB04A1 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


