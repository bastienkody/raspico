cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(pirsensor)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# sources
add_executable(pirsensor	pirsensor.c)

# pull in lib dependencies
target_link_libraries(pirsensor	pico_stdlib	hardware_gpio)

# output : turn on usb - off uart
pico_enable_stdio_usb(pirsensor 1)
pico_enable_stdio_uart(pirsensor 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(pirsensor)
