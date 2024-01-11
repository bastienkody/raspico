# Raspeberry Pico (rsp2040) debut

## Most probably in C/C++ via sdk (vs micropython)

### Sources : 
- pico-sdk
	- https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#sdk-setup
	- https://github.com/raspberrypi/pico-sdk/tree/master
	- https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
	- https://github.com/raspberrypi/pico-examples/tree/master
	- https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*f0lc7c*_ga*MTE1Mjg1NzgzLjE3MDQ5Nzg4NTc.*_ga_22FD70LWDS*MTcwNDk3ODg1Ni4xLjEuMTcwNDk3ODg5OC4wLjAuMA..
- solvering
	- http://www.framboiseetcompagnie.fr/soudure-des-connecteurs-sur-la-raspberry-pi-pico/

# How to
- First get a local copy of pico-sdk (gcl somewhere on your machine)
- Set an envar "PICO_SDK_PATH" : `export PICO_SDK_PATH="path_to_following_cloned_repo/pico-sdk/"`
- Then you need a repo for your project, where you'll have :
	- a copy of "external/pico_sdk_import.cmake" from pico-sdk (you just cloned it)
	- create a "CMakeLists.txt" (see doc for what to write in it)
	- sourcefiles in c/c++ ; must be added to the cmake file too
	- create a build dir in repo project
- Compile :
	- go to build and run `cmake ..`
	- then make
- Load exec into the pico board :
	- press bootsel before and while pluging it in your machine
	- drag and drop the .uf2 exec into the pico
