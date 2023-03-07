################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/Src/ds1307.c \
../BSP/Src/lcd16x2.c 

OBJS += \
./BSP/Src/ds1307.o \
./BSP/Src/lcd16x2.o 

C_DEPS += \
./BSP/Src/ds1307.d \
./BSP/Src/lcd16x2.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/Src/%.o BSP/Src/%.su: ../BSP/Src/%.c BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"C:/Users/dawid/STM32CubeIDE/workspace_1.10.1/RTC/BSP/Inc" -I"C:/Users/dawid/STM32CubeIDE/workspace_1.10.1/RTC/BSP/Src" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-Src

clean-BSP-2f-Src:
	-$(RM) ./BSP/Src/ds1307.d ./BSP/Src/ds1307.o ./BSP/Src/ds1307.su ./BSP/Src/lcd16x2.d ./BSP/Src/lcd16x2.o ./BSP/Src/lcd16x2.su

.PHONY: clean-BSP-2f-Src

