# cmake required version >= 3.10
CMAKE_MINIMUM_REQUIRED(VERSION 3.23.1)

# PROJECT("${MY_PROJECT_NAME}")
project(shell_proj)

#以下用于屏蔽 error: unrecognized command line option ‘-rdynamic’
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# Toolchain path
# SET(TOOLCHAIN_PREFIX "arm-none-eabi")
# SET(TOOLCHAIN_PATH "/home/wanghao/gcc-arm-none-eabi/")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_AR "arm-none-eabi-ar")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP "arm-none-eabi-objdump")
set(CMAKE_SIZE "arm-none-eabi-size")

# set compiler flags
set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb")
#set(CMAKE_C_FLAGS_DEBUG "-g -gdwarf-2 -Og")
set(DBG_FLAGS "-g -gdwarf-2 -Og")
set(CMAKE_C_FLAGS "${MCU_FLAGS}  -Wall -fdata-sections -ffunction-sections ${DBG_FLAGS}") #-w -Wall

#set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp ${DBG_FLAGS}")

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32F103VETx_FLASH.ld")


set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -T${LINKER_SCRIPT} -specs=nosys.specs \
    -lc -lm -lnosys  -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections")
message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions(-DUSE_HAL_DRIVER -DSTM32F103xE)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

enable_language(ASM)
#set_property(SOURCE ${PROJECT_SOURCE_DIR}/library/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s PROPERTY LANGUAGE C)
#FILE(GLOB_RECURSE LIBRARY_SRC_LIST ${PROJECT_SOURCE_DIR}/library/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s)
#FILE(GLOB_RECURSE LIBRARY_SRC_LIST ${PROJECT_SOURCE_DIR}/library/*.c)
#FILE(GLOB_RECURSE BOARD_SRC_LIST ${PROJECT_SOURCE_DIR}/board/*.c)
SET(BOARD_SRC_LIST
board/src/main.c
board/src/stm32f1xx_hal_msp.c
board/src/stm32f1xx_it.c
board/src/system_stm32f1xx.c
board/timer/tim.c
board/usart/usart.c
board/gpio/gpio.c
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c 
library/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
library/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s
)

include_directories(
    library/CMSIS/Device/ST/STM32F1xx/Include
    library/CMSIS/Include
    library/STM32F1xx_HAL_Driver/Inc
    library/STM32F1xx_HAL_Driver/Inc/Legacy
    board/inc
    board/gpio
    board/usart
    board/timer
)


ADD_EXECUTABLE(${PROJECT_NAME}.elf ${BOARD_SRC_LIST})

message("EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}")
#Custom command
ADD_CUSTOM_COMMAND(TARGET "${PROJECT_NAME}.elf" POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.elf" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_OBJCOPY} "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.elf" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin"
)


