#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

//#include "map/map.h"
//#include "game.h"
#include "drawScreen.h"
#include "menu.h"

/*
 INFORMATION ABOUT GLUT TIMERS
 0 = handles all the movements of map, obstacles, bonuses, cars and missiles, as well as the check of collision and destruction of inactive elements
 1 = handles the creation of new items, ie cars, bonuses, obstacles and missiles shot by cars
 */


int main(int argc, char *argv[]){

	srand(time(NULL)); // to allow the usage of random values
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_SIZE_Y*Square_size, WINDOW_SIZE_X*Square_size);
    listOfHighScores = createListScores();
    loadHighScores(listOfHighScores);
    
    display_home();
	
	return 0;
	
}
