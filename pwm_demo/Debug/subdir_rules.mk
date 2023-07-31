################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me --include_path="F:/OneDrive - hcmute.edu.vn/Hocc/tivaC_TM4C123GH6PM/qpc/include" --include_path="F:/OneDrive - hcmute.edu.vn/Hocc/tivaC_TM4C123GH6PM/qpc/3rd_party/CMSIS/Include" --include_path="F:/OneDrive - hcmute.edu.vn/Hocc/tivaC_TM4C123GH6PM/qpc/3rd_party/ek-tm4c123gxl" --include_path="F:/OneDrive - hcmute.edu.vn/Hocc/tivaC_TM4C123GH6PM" --include_path="F:/OneDrive - hcmute.edu.vn/Hocc/tivaC_TM4C123GH6PM/pwm_demo" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


