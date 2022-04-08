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
#include <unistd.h>

#include "map/map.h"
#include "game.h"
#include "drawScreen.h"

/*
 INFORMATION ABOUT GLUT TIMERS
 0 = update of the map
 1 = creation of new cars
 2 = movement of the cars
 3 = destruction of inactive cars
 4 = movement of the missiles
 5 = destruction of inactive missiles
 6 = cars shooting missiles
 */


void initRendering(){
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int width,int heigth){
    glViewport(0, 0, width, heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, heigth, 0);
}

// this function calls the play() function, that requests the rendering of all the elements of the game on the screen
void display(){
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    play(mapToRender, p, listOfCars, listOfMissiles);
    glFlush();
}

int main(int argc, char *argv[]){

	srand(time(NULL));
	
	// INITIALIZE THE MAP - THE PLAYER - THE LIST OF ENNEMY CARS
	row = NULL;
	map = NULL;
    p = createPlayer();
    listOfCars = createCarList();
    listOfMissiles = createMissileList();
        
    loadMapFile(MAP_SIZE_X,MAP_SIZE_Y);
//    printf("Buffer full map created.\n");
    
    for(int i=0; i < WINDOW_SIZE_X; i++){
        row = createRow();
        map = addRow(map, row);
    }
//    printf("Chained list for map created\n");
    updateMap(map);
//    printf("Init completed\n");

    // GLUT CREATION OF THE WINDOW
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize((WINDOW_SIZE_Y-2)*Square_size, WINDOW_SIZE_X*Square_size);

    glutCreateWindow("Velo vs Voiture");
    
    // GLUT HANDLING OF THE MAIN LOOP AND INITIALIZING THE CALLBACKS
    initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    glutTimerFunc(2000, updateMap, 0);
    glutTimerFunc(2000, glutCreateCars, 1);
    glutTimerFunc(500, glutMoveCars, 2);
    glutTimerFunc(100, glutDestroyCars, 3);
    glutTimerFunc(50, glutMoveMissiles, 4);
    glutTimerFunc(10, glutDestroyMissiles, 5);
    glutTimerFunc(2000, glutCreateMissileFromCar, 6);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
	
	return 0;
	
}
