cmake_minimum_required(VERSION 3.13)

set(NAME pico-hex-examples)

set(PICO_PLATFORM rp2350)

#set(PICO_BOARD pico2_w)
set(PICO_BOARD pimoroni_pico_plus2_w_rp2350)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Specify the compiler to use
if(DEFINED ENV{PICO_TOOLCHAIN_PATH})
    set(CMAKE_C_COMPILER "$ENV{PICO_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "$ENV{PICO_TOOLCHAIN_PATH}/bin/arm-none-eabi-g++")
endif()

# Make a variable we can reuse for the library path.
set(PICO_HEX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Set up the Pico SDK
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# Compiler settings
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall)

pico_sdk_init()

# Bring in the pico_hex library source.
add_subdirectory(.. build)

# Bring in the build definitions for each example animation.
add_subdirectory(cubic-cycle)
add_subdirectory(italic-fill-row)
add_subdirectory(italic-sine-rainbow)
add_subdirectory(polar-flame)
add_subdirectory(polar-mixing)
add_subdirectory(ring-cycle)
add_subdirectory(ring-rainbow)
add_subdirectory(ring-spin)
add_subdirectory(rollup-eye)
add_subdirectory(rollup-all)


