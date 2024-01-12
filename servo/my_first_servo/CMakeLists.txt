cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(mfservo)
set(CMAKE_C_STANDARD 11)

# Initialize the SDK
pico_sdk_init()

add_executable(mfservo my_first_servo.c libservo.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(mfservo pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(mfservo)