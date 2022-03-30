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

bool MOVE_UP = false;
bool MOVE_DOWN = false;
bool MOVE_LEFT = false;
bool MOVE_RIGHT = false;


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
            case 27:
                exit(0);
        }
}

void play(char **map, pPlayer p){
    drawMap();  //display the map on screen
    drawPlayer(p);
    
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

    glutPostRedisplay();
}
