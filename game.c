#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "drawScreen.h"
#include "map/map.h"
#include "game_elements/player.h"

// These variables are assigned to store the action that was requested based on the keystroke, then read to trigger to right function corresponding to the action requested by the player
bool MOVE_UP = false;
bool MOVE_DOWN = false;
bool MOVE_LEFT = false;
bool MOVE_RIGHT = false;
bool FIRE_MISSILE = false;

// This function is called each time the player hits a key on the keyboard. In case the key pressed is one which is assigned a function, it records it
void handleKeyboard(unsigned char input, int x, int y){
    switch(input)
        {
            case 'z':
                MOVE_UP = true;
                break;
            case 's':
                MOVE_DOWN = true;
                break;
            case 'q':
                MOVE_LEFT = true;
                break;
            case 'd':
                MOVE_RIGHT = true;
                break;
            case 32: // when hitting the space bar
                FIRE_MISSILE = true;
                break;
            case 27: // when hitting the ESCAPE key
                exit(0);
        }
}

// This function drives the game, by requesting to draw the map on screen; then the cars, then the players and the missiles.
// It also call the function to capture the key pressed by the player on the keyboard and handles the movements of the player.
void play(char **map, pPlayer p, pCarList carList, pMissileList missileList){
    drawMap();  //display the map on screen
    drawCars(carList); //display all the ennemies
    drawPlayer(p); //display the player
    drawMissiles(missileList); //display all the missiles
    
    glutKeyboardFunc(handleKeyboard);        //fonction de glut gérant le clavier
    
    if (MOVE_UP){
        move_player_up(map);
        MOVE_UP = false;
    }
    if (MOVE_DOWN){
        move_player_down(map);
        MOVE_DOWN = false;
    }
    if (MOVE_LEFT){
        move_player_left(map);
        MOVE_LEFT = false;
    }
    if (MOVE_RIGHT){
        move_player_right(map);
        MOVE_RIGHT = false;
    }
    if (FIRE_MISSILE){
        pMissile newMissile = createMissileFromPlayer();
        addMissile(listOfMissiles, newMissile);
        FIRE_MISSILE = false;
    }

    glutPostRedisplay();
}
