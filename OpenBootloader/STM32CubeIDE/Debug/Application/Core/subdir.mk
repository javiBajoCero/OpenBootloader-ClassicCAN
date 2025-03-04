################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/main.c \
C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/stm32g4xx_hal_msp.c \
C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/stm32g4xx_it.c \
../Application/Core/syscalls.c \
../Application/Core/sysmem.c 

OBJS += \
./Application/Core/main.o \
./Application/Core/stm32g4xx_hal_msp.o \
./Application/Core/stm32g4xx_it.o \
./Application/Core/syscalls.o \
./Application/Core/sysmem.o 

C_DEPS += \
./Application/Core/main.d \
./Application/Core/stm32g4xx_hal_msp.d \
./Application/Core/stm32g4xx_it.d \
./Application/Core/syscalls.d \
./Application/Core/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Core/main.o: C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/main.c Application/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../../Core/Inc -I../../Middlewares/ST/OpenBootloader/Modules/USART -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Middlewares/ST/OpenBootloader/Core -I../../OpenBootloader/App -I../../OpenBootloader/Target -I../../Middlewares/ST/OpenBootloader/Modules/Mem -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/OpenBootloader/Modules/FDCAN -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/STM32CubeIDE/Middlewares/OpenBootloader/Modules/CLASSICCAN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/Core/stm32g4xx_hal_msp.o: C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/stm32g4xx_hal_msp.c Application/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../../Core/Inc -I../../Middlewares/ST/OpenBootloader/Modules/USART -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Middlewares/ST/OpenBootloader/Core -I../../OpenBootloader/App -I../../OpenBootloader/Target -I../../Middlewares/ST/OpenBootloader/Modules/Mem -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/OpenBootloader/Modules/FDCAN -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/STM32CubeIDE/Middlewares/OpenBootloader/Modules/CLASSICCAN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/Core/stm32g4xx_it.o: C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/Core/Src/stm32g4xx_it.c Application/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../../Core/Inc -I../../Middlewares/ST/OpenBootloader/Modules/USART -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Middlewares/ST/OpenBootloader/Core -I../../OpenBootloader/App -I../../OpenBootloader/Target -I../../Middlewares/ST/OpenBootloader/Modules/Mem -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/OpenBootloader/Modules/FDCAN -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/STM32CubeIDE/Middlewares/OpenBootloader/Modules/CLASSICCAN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/Core/%.o Application/Core/%.su Application/Core/%.cyclo: ../Application/Core/%.c Application/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -DDEBUG -c -I../../Core/Inc -I../../Middlewares/ST/OpenBootloader/Modules/USART -I../../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../../Middlewares/ST/OpenBootloader/Core -I../../OpenBootloader/App -I../../OpenBootloader/Target -I../../Middlewares/ST/OpenBootloader/Modules/Mem -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/OpenBootloader/Modules/FDCAN -I../../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/JavierMunozSaez/Documents/GitHub/firmware-poc-openbootloader-target/OpenBootloader/STM32CubeIDE/Middlewares/OpenBootloader/Modules/CLASSICCAN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Core

clean-Application-2f-Core:
	-$(RM) ./Application/Core/main.cyclo ./Application/Core/main.d ./Application/Core/main.o ./Application/Core/main.su ./Application/Core/stm32g4xx_hal_msp.cyclo ./Application/Core/stm32g4xx_hal_msp.d ./Application/Core/stm32g4xx_hal_msp.o ./Application/Core/stm32g4xx_hal_msp.su ./Application/Core/stm32g4xx_it.cyclo ./Application/Core/stm32g4xx_it.d ./Application/Core/stm32g4xx_it.o ./Application/Core/stm32g4xx_it.su ./Application/Core/syscalls.cyclo ./Application/Core/syscalls.d ./Application/Core/syscalls.o ./Application/Core/syscalls.su ./Application/Core/sysmem.cyclo ./Application/Core/sysmem.d ./Application/Core/sysmem.o ./Application/Core/sysmem.su

.PHONY: clean-Application-2f-Core

