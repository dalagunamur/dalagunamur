# dalagunamur

0- About
Author: David Laguesse - david.laguesse@student.unamur.be
This repository contains the game built in C using the GLUT library for the UNamur class IHDBC132 - Programmation 2

The player drives a bycycle and has to avoid being driven over by cars. The player can shoot missiles on the oncoming traffic, but so do the cars. As this is a belgian road, it is also full of potholes. Being driven over by a car, hit by a missile or cycling over a pothole costs the player one health point. After loosing 3 health points, the game is over.


1- Features that have already been implemented
* Launching the application opens a main window with the menu:
    - The player can launch the game, view the high scores or some information about the game (key bindings); The load game is not yet supported.

* When playing:
    - The road appears on the center in light grey.
    - On the side of the road the light green represents the grass, with flowers
    - The player plays the bike that starts on the bottom right corner of the game window
    - The cars are coming from the top of the window
    - The potholes and bonuses (are gift boxes) appear on the map
    - The missiles from the cars are represented as small black squares
    - The missiles from the player are represented as small red squares

* The scrolling of the map is done via the load of a new randomly selected row of the map, that is displayed on top while the bottom one is removed. Obstacles and bonuses move at the same pace as the map, cars move faster and missiles are the fastest.

* Moving the player is done via the keyboard. The following key biding is hardcoded: "z" for UP, "q" for LEFT, "s" for DOWN and "d" for RIGHT. Pressing the space bar fires a missile (initially there is max. 10 missiles from the player at a time on screen, which can be increased by collecting bonuses)

* Cars fire missiles targeting the player, with a random car selected to fire

* Bonuses grant the player to recover a lost health point, an increased number of available missiles or both effects at the same time. If a car drives over a bonus, it fires a new missile + gets stronger (1 extra HP). Missiles from cars destroy the bonuses

* When cycling through an obstacle, the player is pushed to the side



2- Features that still need to be implemented

* Functionality to offer the player to choose between vertical and horizontal scrolling and modify the key bindings

* Functionality to allow to save the game and reload at a later time

* Increased difficulty as the game progresses + "smarter" cars when the game progresses
