################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../emlib/em_aes.c \
../emlib/em_burtc.c \
../emlib/em_can.c \
../emlib/em_cmu.c \
../emlib/em_core.c \
../emlib/em_emu.c \
../emlib/em_eusart.c \
../emlib/em_gpio.c \
../emlib/em_i2c.c \
../emlib/em_iadc.c \
../emlib/em_ldma.c \
../emlib/em_msc.c \
../emlib/em_system.c \
../emlib/em_timer.c \
../emlib/em_usart.c 

OBJS += \
./emlib/em_aes.o \
./emlib/em_burtc.o \
./emlib/em_can.o \
./emlib/em_cmu.o \
./emlib/em_core.o \
./emlib/em_emu.o \
./emlib/em_eusart.o \
./emlib/em_gpio.o \
./emlib/em_i2c.o \
./emlib/em_iadc.o \
./emlib/em_ldma.o \
./emlib/em_msc.o \
./emlib/em_system.o \
./emlib/em_timer.o \
./emlib/em_usart.o 

C_DEPS += \
./emlib/em_aes.d \
./emlib/em_burtc.d \
./emlib/em_can.d \
./emlib/em_cmu.d \
./emlib/em_core.d \
./emlib/em_emu.d \
./emlib/em_eusart.d \
./emlib/em_gpio.d \
./emlib/em_i2c.d \
./emlib/em_iadc.d \
./emlib/em_ldma.d \
./emlib/em_msc.d \
./emlib/em_system.d \
./emlib/em_timer.d \
./emlib/em_usart.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_aes.o: ../emlib/em_aes.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_aes.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_burtc.o: ../emlib/em_burtc.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_burtc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_can.o: ../emlib/em_can.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_can.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: ../emlib/em_cmu.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_cmu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_core.o: ../emlib/em_core.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_core.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: ../emlib/em_emu.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_emu.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_eusart.o: ../emlib/em_eusart.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_eusart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: ../emlib/em_gpio.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_i2c.o: ../emlib/em_i2c.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_iadc.o: ../emlib/em_iadc.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_iadc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_ldma.o: ../emlib/em_ldma.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_ldma.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_msc.o: ../emlib/em_msc.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_msc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: ../emlib/em_system.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_system.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_timer.o: ../emlib/em_timer.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_timer.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_usart.o: ../emlib/em_usart.c emlib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"emlib/em_usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


