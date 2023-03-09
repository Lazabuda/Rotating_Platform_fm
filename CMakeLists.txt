SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.13) 

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain-arm-none-eabi.cmake") 
list(APPEND CMAKE_MODULE_PATH cmake)
include(cmake/functions.cmake) 

SET(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/stm32_flash.ld")

SET(MCU_FAMILY_STD mcpu=cortex-m4)

#Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)


SET(FPU_FLAGS "")

SET(COMMON_FLAGS
        "-mcpu=cortex-m4 -mthumb ${FPU_FLAGS} -ffunction-sections -fdata-sections \
         -g -fno-common -fmessage-length=0 -specs=nano.specs -specs=nosys.specs")

SET(CMAKE_CXX_FLAGS_INIT "${COMMON_FLAGS} -std=c++14 -fno-rtti -fno-exceptions -fno-threadsafe-statics")
SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS} -std=gnu99")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage")


project(Rotating_Table_CL_fm C CXX ASM) 
set(CMAKE_CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(POSTFIX "d")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(POSTFIX "")
else()
    message(WARNING "Unknown build type")
    message(FATAL_ERROR "Set CMAKE_BUILD_TYPE to Debug or Release and reconfigure")
endif()


set(HAL_LL_SRC_PATH "Libraries/STM32F4xx_StdPeriph_Driver/")
set(HAL_LL_SRC
        "${HAL_LL_SRC_PATH}/src/stm32f4xx_gpio.c"
        "${HAL_LL_SRC_PATH}/src/stm32f4xx_i2c.c"
        "${HAL_LL_SRC_PATH}/src/stm32f4xx_flash.c"
        "${HAL_LL_SRC_PATH}/src/stm32f4xx_rcc.c"
        "${HAL_LL_SRC_PATH}/src/stm32f4xx_exti.c"
		"${HAL_LL_SRC_PATH}/src/stm32f4xx_usart.c"
		"${HAL_LL_SRC_PATH}/src/stm32f4xx_exti.c"
		"${HAL_LL_SRC_PATH}/src/stm32f4xx_pwr.c"
		"${HAL_LL_SRC_PATH}/src/stm32f4xx_tim.c"
		"${HAL_LL_SRC_PATH}/src/misc.c")
		
set(FREERTOS_SRC
        "Libraries/FreeRTOS/src/tasks.c"
        "Libraries/FreeRTOS/src/list.c"
        "Libraries/FreeRTOS/src/queue.c"
        "Libraries/FreeRTOS/src/timers.c"
        "Libraries/FreeRTOS/src/port.c"
        "Libraries/FreeRTOS/src/heap_3.c")
		
#set(MY_LIBS_SRC_PATH "Libraries/My_libs/")
#set(HAL_LL_SRC
#        "${MY_LIBS_SRC_PATH}/src/hardware.c")

set(COMMON_SRC ${HAL_LL_SRC} ${FREERTOS_SRC})

set(HAL_LL_INC "${HAL_LL_SRC_PATH}/inc")
set(CMSIS_INC "Libraries/CMSIS/Include" "Libraries/CMSIS/Device/ST/STM32F4xx/Include")
set(FREERTOS_INC "Libraries/FreeRTOS/inc")
#set(MY_LIBS_INC "Libraries/My_libs/inc")
set(APP_INC "include")

include_directories(${CMSIS_INC})
include_directories(${HAL_LL_INC})
include_directories(${FREERTOS_INC})
#include_directories(${MY_LIBS_INC})
include_directories(${APP_INC})




set(COMMON_DEFINITIONS "-DSTM32F4xx_MD -DSTM32F401xx -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT")

add_definitions(${COMMON_DEFINITIONS})
#Uncomment for hardware floating point
add_definitions(-D__FPU_PRESENT=1 -DARM_MATH_CM4=1)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -DTRACE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -DTRACE")


set(PROJECT_SRC
        src/main.c        
        src/stm32f4xx_it.c
        src/system_stm32f4xx.c
        src/hardware.c
        src/startup_stm32f401xc.s
        )


set(PN "App${POSTFIX}")
add_executable(${PN}.elf ${PROJECT_SRC} ${COMMON_SRC}) 
set_options(${PN} ${LINKER_SCRIPT})

# target_compile_definitions(${PN}.elf PRIVATE "HSE_VALUE=25000000")
