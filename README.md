# PasscodeBreaker
## EE2361 Final Project Spring 2023

Designed to be used with MPLAB X IDE v5.50 using a PIC24FJ64GA002 microcontroller and CAP1188 8 Channel Capacitive Touch Sensor. 

A demo video of the full project can be seen [here](https://drive.google.com/file/d/1ezScyrWaestfbDl-gvvks3eRAyD4ct6V/view?usp=sharing). 

Documentation of the libraries used is attached in a pdf. 

## Core Game
The idea of the game is to guess a 4-digit passcode. When the player guesses a digit in the sequence correctly, an LED will glow green in its location. If the guess is less than the correct digit, then the LED will glow red. If the guess is greater than the correct digit, the LED will glow yellow. The player is given a set amount of attempts (configurable) to guess the correct sequence. The passcode is configurable within the code. A flow chart can be seen [here](https://drive.google.com/file/d/14HiZF9rkV0rohaJP4iovaxgV43ng2krC/view?usp=sharing).

### Win Case 
If the player guesses the correct passcode, a motor is actuated and a lock box is opened to reveal a prize. 
### Lose Case 
If the player fails to guess the correct passcode, the correct passcode is revealed to the player and a second motor is actuated to spray a water gun at the player. This feature was not implemented in the final product due to motor failure of the water mechanism.
## Contribution 
I, Ethan Keu, focused solely on designing the core game mechanisms in MPLAB X IDE. This included most of the microcontroller code and the library integration to connect the CAP1188 to the microcontroller.
