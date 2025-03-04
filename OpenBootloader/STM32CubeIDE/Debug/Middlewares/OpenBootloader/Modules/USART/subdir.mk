################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Middlewares/ST/OpenBootloader/Modules/USART/openbl_usart_cmd.c 

OBJS += \
./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.o 

C_DEPS += \
./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.o: C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Middlewares/ST/OpenBootloader/Modules/USART/openbl_usart_cmd.c Middlewares/OpenBootloader/Modules/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../../Core/Inc -I../../Middlewares/ST/OpenBootloader/Modules/USART -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Middlewares/ST/OpenBootloader/Core -I../../OpenBootloader/App -I../../OpenBootloader/Target -I../../Middlewares/ST/OpenBootloader/Modules/Mem -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/OpenBootloader/Modules/FDCAN -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/STM32CubeIDE/Middlewares/OpenBootloader/Modules/CLASSICCAN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-OpenBootloader-2f-Modules-2f-USART

clean-Middlewares-2f-OpenBootloader-2f-Modules-2f-USART:
	-$(RM) ./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.cyclo ./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.d ./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.o ./Middlewares/OpenBootloader/Modules/USART/openbl_usart_cmd.su

.PHONY: clean-Middlewares-2f-OpenBootloader-2f-Modules-2f-USART

