################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/CCS/ccsv5/tools/compiler/msp430_4.1.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./UART/UART_init.obj" \
"./UART/UART_Global.obj" \
"./UART/UART_FIFO.obj" \
"./UART/UART_Event.obj" \
"./memorizer.obj" \
"./main.obj" \
"./Time.obj" \
"./SPI.obj" \
"./Interrupt.obj" \
"./Init.obj" \
"./Global.obj" \
"./Data.obj" \
"./Count.obj" \
"./Bluetooth.obj" \
"./AT45DB081.obj" \
-l"libc.a" \
"../lnk_msp430g2253.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include UART/subdir_vars.mk
-include subdir_rules.mk
-include UART/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Belt_Count_1_4_SoftCheck.out

# Tool invocations
Belt_Count_1_4_SoftCheck.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"E:/CCS/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -O2 --advice:power=all --define=__MSP430G2253__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z --stack_size=80 -m"Belt_Count_1_4_SoftCheck.map" --heap_size=80 -i"E:/CCS/ccsv5/ccs_base/msp430/include" -i"E:/CCS/ccsv5/tools/compiler/msp430_4.1.1/lib" -i"E:/CCS/ccsv5/tools/compiler/msp430_4.1.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --rom_model -o "Belt_Count_1_4_SoftCheck.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MSP430_EXECUTABLE_OUTPUTS__QUOTED) "Belt_Count_1_4_SoftCheck.out"
	-$(RM) "AT45DB081.pp" "Bluetooth.pp" "Count.pp" "Data.pp" "Global.pp" "Init.pp" "Interrupt.pp" "SPI.pp" "Time.pp" "main.pp" "memorizer.pp" "UART\UART_Event.pp" "UART\UART_FIFO.pp" "UART\UART_Global.pp" "UART\UART_init.pp" 
	-$(RM) "AT45DB081.obj" "Bluetooth.obj" "Count.obj" "Data.obj" "Global.obj" "Init.obj" "Interrupt.obj" "SPI.obj" "Time.obj" "main.obj" "memorizer.obj" "UART\UART_Event.obj" "UART\UART_FIFO.obj" "UART\UART_Global.obj" "UART\UART_init.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
