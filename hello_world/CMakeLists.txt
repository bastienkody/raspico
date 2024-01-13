cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(hello_usb)

set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(hello_usb hw.c)

target_link_libraries(hello_usb pico_stdlib)

pico_enable_stdio_usb(hello_usb 1)
pico_enable_stdio_uart(hello_usb 0)

pico_add_extra_outputs(hello_usb)