cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)
project(slideswitch)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# sources
add_executable(slideswitch
		slideswitch.c
		)

# pull in lib dependencies
target_link_libraries(slideswitch pico_stdlib hardware_gpio)

# output : turn on usb - off uart
pico_enable_stdio_usb(slideswitch 1)
pico_enable_stdio_uart(slideswitch 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(slideswitch)

# add url via pico_set_program_url
#example_auto_set_url(blink)
