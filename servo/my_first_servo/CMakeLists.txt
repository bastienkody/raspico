cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(mfservo)
set(CMAKE_C_STANDARD 11)

# Initialize the SDK
pico_sdk_init()

add_executable(mfservo my_first_servo.c libservo.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(mfservo pico_stdlib hardware_pwm)

# output : turn on usb - off uart
pico_enable_stdio_usb(mfservo 1)
pico_enable_stdio_uart(mfservo 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(mfservo)