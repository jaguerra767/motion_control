set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_SYSTEM_VERSION 1)

#Toolchain binaries
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-g++)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(AS arm-none-eabi-as)
set(AR arm-none-eabi-ar)
set(OBJCOPY arm-none-eabi-objcopy)
set(OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

set(MCU_FLAGS "-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
#Compiler flags
set(COMMON_FLAGS "-Wall --param max-inline-insns-single=50 -O3 -ffunction-sections -fdata-sections -g2 -Wall")

set(CMAKE_C_FLAGS "${MCU_FLAGS} ${COMMON_FLAGS} -x c -std=gnu11")
set(CMAKE_CXX_FLAGS "${MCU_FLAGS} ${COMMON_FLAGS} -fno-rtti -fno-exceptions -std=gnu++20 -fno-threadsafe-statics -Wno-register")

set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} --specs=rdimon.specs -Wl,--gc-sections")