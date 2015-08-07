Light-Controller
================

This project is a mini light show setup. I guess it's best to show what it can do with a short video first.
https://www.youtube.com/watch?v=73we8rbzlRw

##Getting Started
###TODO


##Electronic
A goal for this project was to build the electronic using only logic chips. No programmable components were used. 

The lights are controlled via a feed from the serial port. The asynchronious data sent through the serial port are first synchronized with a clock signal and then passed to the lighting devices, along with the clock signal.

As for now, the system is composed of moving lights (red, green and blue leds mounted on a servomotor). Nevertheless, many other devices can be created by making very small modifications to the same schematics. For example: fixed RGB Lights, strobes(triggered by one bit of the 4094 for example), led matrix, ...

The schematics can be found in the "*electronic*" folder.

##Software
The software was developped under Linux using Qt designer 5.2.1. 

The software is used to control the light devices via the serial port. Typically, the user chosoe a song, put markers on it and link each of these markers to a light setup. The connections between these cues can be customized, for example by fading the setup between 2 cues or at the opposite, by making the transition sharp.

Some other modules are present in the software allowing the user to record more easilly a light show. The user can for example group fixtures of the same type to apply modification to all of these fixtures all at once. He can also record scenes that will often be used and call them back easilly.

The sources can be found in the "*LightController3*" folder.
#####External dependency: 
* FMOD Sound System (Linux version include in this branch)
* Serial port available on the computer (optionnal: the software works anyway but cannot transmit to the lights)

This project was developed under Linux but should be working on Windows without too much work (nevertheless, I haven't test it). The main compenent that will need to be modify is the FMOD Sound System: You will need to use the Windows version available at: http://www.fmod.org/download/.
