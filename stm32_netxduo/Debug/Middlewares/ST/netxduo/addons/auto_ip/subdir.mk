################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.c 

OBJS += \
./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.o 

C_DEPS += \
./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/netxduo/addons/auto_ip/%.o Middlewares/ST/netxduo/addons/auto_ip/%.su Middlewares/ST/netxduo/addons/auto_ip/%.cyclo: ../Middlewares/ST/netxduo/addons/auto_ip/%.c Middlewares/ST/netxduo/addons/auto_ip/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -DTX_INCLUDE_USER_DEFINE_FILE -DNX_INCLUDE_USER_DEFINE_FILE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../AZURE_RTOS/App -I../NetXDuo/App -I../NetXDuo/Target -I../Middlewares/ST/netxduo/common/drivers/ethernet/ -I../Middlewares/ST/netxduo/addons/auto_ip/ -I../Middlewares/ST/netxduo/addons/dhcp/ -I../Middlewares/ST/netxduo/common/inc/ -I../Middlewares/ST/netxduo/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/threadx/common/inc/ -I../Middlewares/ST/threadx/ports/cortex_m4/gnu/inc/ -I../Middlewares/ST/threadx/utility/low_power/ -I../Drivers/BSP/Components/lan8742/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-netxduo-2f-addons-2f-auto_ip

clean-Middlewares-2f-ST-2f-netxduo-2f-addons-2f-auto_ip:
	-$(RM) ./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.cyclo ./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.d ./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.o ./Middlewares/ST/netxduo/addons/auto_ip/nx_auto_ip.su

.PHONY: clean-Middlewares-2f-ST-2f-netxduo-2f-addons-2f-auto_ip

