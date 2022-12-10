# cmake required version >= 3.10
CMAKE_MINIMUM_REQUIRED(VERSION 3.23.1)

project(netxduo_base_proj)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# Toolchain path
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_AR "arm-none-eabi-ar")
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP "arm-none-eabi-objdump")
set(CMAKE_SIZE "arm-none-eabi-size")

# set compiler flags
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(FPU_FLAGS "-mfpu=fpv4-sp-d16")
set(FLOAT_ABI_FLAGS "-mfloat-abi=hard")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(DBG_FLAGS "-g -gdwarf-2 -Og")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(DBG_FLAGS "-O2")
endif()

set(CMAKE_C_FLAGS "${MCU_FLAGS} ${FPU_FLAGS} ${FLOAT_ABI_FLAGS} -Wall -fdata-sections -ffunction-sections ${DBG_FLAGS}") # -w -Wall
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp ${DBG_FLAGS}")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32F429BITx_FLASH.ld")

set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -T${LINKER_SCRIPT} -specs=nosys.specs \
    -lc -lm -lnosys  -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections")
message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

add_definitions(-DUSE_HAL_DRIVER -DSTM32F429xx -DTX_INCLUDE_USER_DEFINE_FILE)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

enable_language(ASM)
FILE(GLOB_RECURSE LIBRARY_SRC_LIST ${PROJECT_SOURCE_DIR}/library/*.c)
FILE(GLOB_RECURSE BOARD_SRC_LIST ${PROJECT_SOURCE_DIR}/board/*.c)
SET(STARTUP_SRC library/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f429xx.s)
FILE(GLOB_RECURSE STARTUP_SRC_THREADX ${PROJECT_SOURCE_DIR}/library/threadx/ports/src/*.S)

LIST(REMOVE_ITEM REMOVE_LIST ${PROJECT_SOURCE_DIR}/library/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_rtc_wakeup_template.c
    ${PROJECT_SOURCE_DIR}/library/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_rtc_alarm_template.c
    ${PROJECT_SOURCE_DIR}/library/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_tim_template.c
)

include_directories(
    library/CMSIS/Device/ST/STM32F4xx/Include
    library/CMSIS/Include
    library/STM32F4xx_HAL_Driver/Inc
    library/STM32F4xx_HAL_Driver/Inc/Legacy
    library/threadx/common/inc
    library/threadx/ports/inc
    library/netxduo/common/inc
    library/netxduo/ports/inc
    library/netxduo/ports
    board
    board/bsp
    board/bsp/inc

    # board/timer
)

ADD_EXECUTABLE(${PROJECT_NAME}.elf ${STARTUP_SRC} ${BOARD_SRC_LIST} ${LIBRARY_SRC_LIST} ${REMOVE_LIST} ${STARTUP_SRC_THREADX})

message("EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}")

# Custom command
ADD_CUSTOM_COMMAND(TARGET "${PROJECT_NAME}.elf" POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.elf" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex"
    COMMAND ${CMAKE_OBJCOPY} "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.elf" "${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin"
)
