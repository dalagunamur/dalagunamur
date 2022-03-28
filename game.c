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


void handleKeyboard(unsigned char input, int x, int y){
    switch(input)
        {
            case 27:
                exit(0);
        }
}

void play(char **map){
    drawMap();  //display the map on screen
    
    
    glutKeyboardFunc(handleKeyboard);        //fonction de glut gérant le clavier
    
//    if (LEFT == true)
//    {
//
//        moveLeft(p);        //va se déplacer vers la gauche si on appuie sur q
//        LEFT = false;
//
//    }
//    if (RIGHT == true)
//    {
//
//        moveRight(p);        //va se déplacer vers la droite si on apppuie sur d
//        RIGHT = false;
//    }
//    if (UP == true)
//    {
//        moveUp(p);
//        UP = false;
//    }
//
//    if (DOWN == true)
//    {
//
//                moveDown(p);
//        DOWN = false;
//    }


    glutPostRedisplay();
}
