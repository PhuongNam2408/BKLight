################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B210F1536IM48=1' -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\emlib_inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"D:/Users/HP/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/EFR32MG24/Include" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src" -I"D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\BKLight_Driver" -O0 -Wall -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -mcmse -MMD -MP -MF"src/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


