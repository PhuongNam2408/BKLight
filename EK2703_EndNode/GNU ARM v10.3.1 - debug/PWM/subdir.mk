################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PWM/PWM.c 

OBJS += \
./PWM/PWM.o 

C_DEPS += \
./PWM/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
PWM/PWM.o: ../PWM/PWM.c PWM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\emlib_inc" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/EFR32MG24_BRD4186C -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\I2C" -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\delay" -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\PWM" -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\BH1750" -I"C:\Users\HP\SimplicityStudio\v5_workspace\Tam_BKLight\LoRa" -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/bsp -IC:/Users/HP/Downloads/peripheral_examples-master/peripheral_examples-master/series2/kit/common/drivers -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"PWM/PWM.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


