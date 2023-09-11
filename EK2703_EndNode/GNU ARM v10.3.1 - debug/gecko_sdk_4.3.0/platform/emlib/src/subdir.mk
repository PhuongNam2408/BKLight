################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_burtc.c \
C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_msc.c \
C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_prs.c \
C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_timer.c 

OBJS += \
./gecko_sdk_4.3.0/platform/emlib/src/em_burtc.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_cmu.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_core.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_emu.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_gpio.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_msc.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_prs.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_system.o \
./gecko_sdk_4.3.0/platform/emlib/src/em_timer.o 

C_DEPS += \
./gecko_sdk_4.3.0/platform/emlib/src/em_burtc.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_cmu.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_core.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_emu.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_gpio.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_msc.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_prs.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_system.d \
./gecko_sdk_4.3.0/platform/emlib/src/em_timer.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.0/platform/emlib/src/em_burtc.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_burtc.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_burtc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_cmu.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_cmu.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_cmu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_core.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_core.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_core.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_emu.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_emu.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_emu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_gpio.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_gpio.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_msc.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_msc.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_msc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_prs.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_prs.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_prs.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_system.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_system.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_system.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.0/platform/emlib/src/em_timer.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/emlib/src/em_timer.c gecko_sdk_4.3.0/platform/emlib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/emlib/src/em_timer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


