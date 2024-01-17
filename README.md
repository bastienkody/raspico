# Raspeberry Pico (rsp2040) debut

## C/C++ via pico-sdk (no micropython yet)

### Sources : 
- pico-sdk
	- https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#sdk-setup
	- https://github.com/raspberrypi/pico-sdk/tree/master
	- https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf
	- https://github.com/raspberrypi/pico-examples/tree/master
	- https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*f0lc7c*_ga*MTE1Mjg1NzgzLjE3MDQ5Nzg4NTc.*_ga_22FD70LWDS*MTcwNDk3ODg1Ni4xLjEuMTcwNDk3ODg5OC4wLjAuMA..
	- doc pico-sdk via doxygen
	- github thomas kleist for servo lib
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

# Main project for now : trashcan_lid
Automatic trashcan lid (=couvercle de poubelle automatique) that I broke.  
I want to rebuild the system with : 
- Passive Infra Red (PIR) sensor that detects motion
- Slideswitch (bouton a glissiere) that can lock the state (wether it keeps closed or opened)
- Servo motor that opens the lid
All 3 components controlled by (and wired to) the rpi.  

Problems : 
- Pir sensor range it too big (minimum 2m). Already turn at lowest sensi and time. I could try to blur the lens
- Powering rpi + components is a matter : via usb and wall plug? via raw battery? using a battery holder? 
- Can I only power the raspberry then it powers the 3 components? I think so via vsys vbus and 3v3 (enough for pir and switch at least)
- To gain power consumption I wanted to on/off the system but the pir required a calibration time : if you power just before use you may need to wait 30 sec to be able to use which is absolutely useless : it wil always be running ; sleeping seems to consume very few power. 
- Are inline functions relevant for the compiler? If not it might consume too much power for nothing and I should only use one uniq main function
- Would be way cleaner to separate sourcefiles (such as libservo) within several directories but I don't handle cmake very well yet. 
- Solvering header on rpi : ok nickel
- Solvering the all mechanism, with power acces to rpi, solid but also flex for debug or maintenance, components must keep in place. I need a better plan. 