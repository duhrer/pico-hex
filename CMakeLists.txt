cmake_minimum_required(VERSION 3.13)

set(NAME pico_hex)

add_library(${NAME} INTERFACE)

# TODO: Confirm that this works with an example project and document how/when it
# needs to be included.
# Set up the Pico SDK
# set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk)
# include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# pico_sdk_init()

set(SOURCE_FILES
    src/helpful-neopixel.cpp
    src/hex-unit.cpp
)

add_subdirectory(lib/pico_neopixels build)

target_sources(${NAME} INTERFACE
    ${SOURCE_FILES}
)

# Pedantic warnings on for project source code only.
# set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_OPTIONS "-Wextra;-Wpedantic")

# Include our own header files.
target_include_directories(${NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${NAME} INTERFACE
    pico_stdlib
    pico_neopixel
    hardware_pio
    pico_time
    pico_rand
)
