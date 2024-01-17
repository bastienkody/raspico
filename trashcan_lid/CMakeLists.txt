cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(trashcan_lid)

set(CMAKE_C_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# sources
add_executable(trashcan_lid
		trashcan_lid.c
		libservo.c
		)

# pull in lib dependencies
target_link_libraries(trashcan_lid
		pico_stdlib
		hardware_gpio
		hardware_pwm
		)

# output : turn on usb - off uart
pico_enable_stdio_usb(trashcan_lid 1)
pico_enable_stdio_uart(trashcan_lid 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(trashcan_lid)

# add url via pico_set_program_url
#example_auto_set_url(blink)
