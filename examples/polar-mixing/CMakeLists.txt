set(NAME polar-mixing)

set(SOURCE_FILES
    polar-mixing.cpp
)

add_executable(${NAME}
    ${SOURCE_FILES}
)

# Include the library's header files
target_include_directories(${NAME} PRIVATE ${PICO_HEX_PATH})

# Include our own header files
target_include_directories(${NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${NAME}
    pico_stdlib
    pico_hex
    pico_time
    pico_rand
    pico_bootsel_via_double_reset
)

target_compile_definitions(${NAME} PRIVATE)

pico_add_extra_outputs(${NAME})

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
    ${CMAKE_CURRENT_LIST_DIR}/README.md
    DESTINATION .
)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)
