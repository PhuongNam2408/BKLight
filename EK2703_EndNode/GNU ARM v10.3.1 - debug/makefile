################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFR32MG24/subdir.mk
-include BKLight_Driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EK2703_EndNode
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: EK2703_EndNode.axf

# Tool invocations
EK2703_EndNode.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "D:\STUDY_NAMNP\BKLight\LINUX\Main_Repository\EK2703_EndNode\src\xg24_linker_script.ld" -Xlinker --gc-sections -Xlinker -Map="EK2703_EndNode.map" -mfpu=fpv5-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o EK2703_EndNode.axf "./BKLight_Driver/ACS712.o" "./BKLight_Driver/BH1750.o" "./BKLight_Driver/LoRa_E32.o" "./BKLight_Driver/PWM.o" "./BKLight_Driver/aes.o" "./BKLight_Driver/delay.o" "./BKLight_Driver/nam_rtc.o" "./BKLight_Driver/nam_uart.o" "./CMSIS/EFR32MG24/startup_gcc_efr32mg24.o" "./CMSIS/EFR32MG24/system_efr32mg24.o" "./emlib/em_burtc.o" "./emlib/em_can.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_eusart.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_iadc.o" "./emlib/em_ldma.o" "./emlib/em_msc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_wdog.o" "./src/main.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: EK2703_EndNode.out'
	arm-none-eabi-objcopy "EK2703_EndNode.axf" "EK2703_EndNode.out"
	@echo ' '

	@echo 'Building hex file: EK2703_EndNode.hex'
	arm-none-eabi-objcopy -O ihex "EK2703_EndNode.axf" "EK2703_EndNode.hex"
	@echo ' '

	@echo 'Building bin file: EK2703_EndNode.bin'
	arm-none-eabi-objcopy -O binary "EK2703_EndNode.axf" "EK2703_EndNode.bin"
	@echo ' '

	@echo 'Building s37 file: EK2703_EndNode.s37'
	arm-none-eabi-objcopy -O srec "EK2703_EndNode.axf" "EK2703_EndNode.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "EK2703_EndNode.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) EK2703_EndNode.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
