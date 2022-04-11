# dalagunamur

0- About
Author: David Laguesse - david.laguesse@student.unamur.be
This repository contains the game built in C using the GLUT library for the UNamur class IHDBC132 - Programmation 2

The player drives a bycycle and has to avoid being driven over by cars. The player can shoot missiles on the oncoming traffic, but so do the cars. As this is a belgian road, it is also full of potholes. Being driven over by a car, hit by a missile or cycling over a pothole costs the player one health point. After loosing 3 health points, the game is over.


1- Features that have already been implemented
* Launching the application opens a window that displays the various elements of the game:
    - The road appears on the center in light grey.
    - On the side of the road the light green represents the grass, while the red squares represent houses and dark green squares represent trees
    - The player is represented as a light blue square 
    - The cars are represented as large purple rectangles
    - The obstacles are represented as large dark grey squares
    - The missiles (from the player or from the cars) are represented as small black squares
    - The bonuses are represented as pink squares

* The scrolling of the map is done via the load of a new randomly selected row of the map, that is displayed on top while the bottom one is removed. Obstacles and bonuses move at the same pace as the map, cars move faster and missiles are the fastest.

* Moving the player is done via the keyboard. The following key biding is hardcoded: "z" for UP, "q" for LEFT, "s" for DOWN and "d" for RIGHT. Pressing the space bar fires a missile (initially there is max. 10 missiles from the player at a time on screen)

* Cars fire missiles targeting the player, with a random car selected to fire

* Bonuses grant the player to recover a lost health point, an increased number of available missiles or both effects at the same time. If a car drives over a bonus, it fires a new missile + gets stronger (1 extra HP). Missiles from cars destroy the bonuses

* When cycling through an obstacle, the player is pushed to the side



2- Features that still need to be implemented
* Additional screens for the menu, for the "Load a saved game", for the "High scores", for the "Configuration and rules"

* Functionality to offer the player to choose between vertical and horizontal scrolling

* Textures will be applied to the various elements appearing on screen

* Functionality to allow to pause the game and save the current game to reload at a later time

* Improved strategy for the cars to try to hit the player (currently driving in a straight line) + strategy to select which car will fire the missile might change (for example, selecting the car which is closest to the player to fire) + based on the computed difficulty level of the current game, the cars might have more than 1-2 health points

* Better integration of the timer and the score, which will have a direct impact on the difficulty level of the game

* Improved collision system, the computation to decide if there's an impact should be based on the constants about square sizes and not hardcoded values
