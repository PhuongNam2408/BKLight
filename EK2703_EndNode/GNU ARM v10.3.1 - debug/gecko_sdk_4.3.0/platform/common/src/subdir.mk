################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/common/src/sl_assert.c 

OBJS += \
./gecko_sdk_4.3.0/platform/common/src/sl_assert.o 

C_DEPS += \
./gecko_sdk_4.3.0/platform/common/src/sl_assert.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.0/platform/common/src/sl_assert.o: C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk/platform/common/src/sl_assert.c gecko_sdk_4.3.0/platform/common/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\gecko_sdk_4.3.0" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\BRD4186C_EFR32MG24_usart_async_interrupt\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"C:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"gecko_sdk_4.3.0/platform/common/src/sl_assert.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


