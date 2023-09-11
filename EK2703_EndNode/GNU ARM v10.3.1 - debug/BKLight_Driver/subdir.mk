################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BKLight_Driver/ACS712.c \
../BKLight_Driver/BH1750.c \
../BKLight_Driver/LoRa_E32.c \
../BKLight_Driver/PWM.c \
../BKLight_Driver/delay.c \
../BKLight_Driver/nam_rtc.c \
../BKLight_Driver/nam_uart.c 

OBJS += \
./BKLight_Driver/ACS712.o \
./BKLight_Driver/BH1750.o \
./BKLight_Driver/LoRa_E32.o \
./BKLight_Driver/PWM.o \
./BKLight_Driver/delay.o \
./BKLight_Driver/nam_rtc.o \
./BKLight_Driver/nam_uart.o 

C_DEPS += \
./BKLight_Driver/ACS712.d \
./BKLight_Driver/BH1750.d \
./BKLight_Driver/LoRa_E32.d \
./BKLight_Driver/PWM.d \
./BKLight_Driver/delay.d \
./BKLight_Driver/nam_rtc.d \
./BKLight_Driver/nam_uart.d 


# Each subdirectory must supply rules for building sources it contributes
BKLight_Driver/ACS712.o: ../BKLight_Driver/ACS712.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/ACS712.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/BH1750.o: ../BKLight_Driver/BH1750.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/BH1750.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/LoRa_E32.o: ../BKLight_Driver/LoRa_E32.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/LoRa_E32.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/PWM.o: ../BKLight_Driver/PWM.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/PWM.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/delay.o: ../BKLight_Driver/delay.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/delay.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/nam_rtc.o: ../BKLight_Driver/nam_rtc.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/nam_rtc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BKLight_Driver/nam_uart.o: ../BKLight_Driver/nam_uart.c BKLight_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"BKLight_Driver/nam_uart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


