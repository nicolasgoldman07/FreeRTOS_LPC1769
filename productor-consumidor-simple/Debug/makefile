################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: productor-consumidor-simple.axf

# Tool invocations
productor-consumidor-simple.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/nico/Documents/MCUXpresso_11.1.0_3209/workspace/lpcopen_2_10_lpcxpresso_nxp_lpcxpresso_1769.zip_expanded/lpc_chip_175x_6x/Debug" -L"/home/nico/Documents/MCUXpresso_11.1.0_3209/workspace/lpcopen_2_10_lpcxpresso_nxp_lpcxpresso_1769.zip_expanded/lpc_board_nxp_lpcxpresso_1769/Debug" -Xlinker -Map="productor-consumidor-simple.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "freertos_blinky_Debug.ld" -o "productor-consumidor-simple.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) productor-consumidor-simple.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "productor-consumidor-simple.axf"; # arm-none-eabi-objcopy -v -O binary "productor-consumidor-simple.axf" "productor-consumidor-simple.bin" ; # checksum -p LPC1769 -d "productor-consumidor-simple.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
