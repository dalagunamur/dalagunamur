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
 0 = update of the map and obstacles
 1 = creation of new cars
 2 = movement of the cars
 3 = destruction of inactive cars and obstacles
 4 = movement of the missiles
 5 = destruction of inactive missiles
 6 = cars shooting missiles
 7 = check for impacts
 8 = creation of obstacles and bonuses
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
    play(theGame,mapToRender, p, listOfCars, listOfMissiles, listOfObstacles, listOfBonuses);
    glFlush();
}

int main(int argc, char *argv[]){

	srand(time(NULL)); // to allow the usage of random values
	
	// INITIALIZE THE MAP - THE PLAYER - THE LISTS OF CARS, MISSILES, BONUSES AND OBSTACLES
	row = NULL;
	map = NULL;
    p = createPlayer();
    listOfCars = createCarList();
    listOfMissiles = createMissileList();
    listOfObstacles = createObstacleList();
    listOfBonuses = createListBonuses();
    maxNbrMissilesPlayer = 10; // initially setting the max nbr of missiles a player can shoot at the same time to 10
        
    loadMapFile(MAP_SIZE_X,MAP_SIZE_Y);
    for(int i=0; i < WINDOW_SIZE_X; i++){
        row = createRow();
        map = addRow(map, row);
    }
    displayMap(map);
    theGame = createGame();
    // END OF INITIALIZATION
    
    // TEMP SOLUTION TO DISPLAY INITIAL VALUES - UNTIL INTEGRATED IN GLUT
    printf("\n********** INSTRUCTIONS **********\n");
    printf("Press 'z' to move up, 's' to move down, 'q' to move left and 'd' to move right\n");
    printf("Press the space bar to shoot towards the incoming cars.\n");
    printf("\n********** THE GAME STARTS **********\n");
    printf("Player's HP = %i - Current Max Nbr of missiles = %i\n\n",p->health_points,maxNbrMissilesPlayer);
    
    // GLUT CREATION OF THE WINDOW
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(WINDOW_SIZE_Y*Square_size, WINDOW_SIZE_X*Square_size);

    glutCreateWindow("Velo vs Voiture");
    
    // GLUT HANDLING OF THE MAIN LOOP AND INITIALIZING THE CALLBACKS
    initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    glutTimerFunc(2000, updateMap, 0);
    glutTimerFunc(1000, glutCreateCars, 1);
    glutTimerFunc(500, glutMoveCars, 2);
    glutTimerFunc(100, glutDestroyCars, 3);
    glutTimerFunc(100, glutDestroyObstacles, 3);
    glutTimerFunc(100, glutDestroyBonuses, 3);
    glutTimerFunc(50, glutMoveMissiles, 4);
    glutTimerFunc(10, glutDestroyMissiles, 5);
    glutTimerFunc(2000, glutCreateMissileFromCar, 6);
    glutTimerFunc(10, glutCheckImpacts, 7);
    glutTimerFunc(6000, glutCreateObstacle, 8);
    glutTimerFunc(10000, glutCreateBonus, 8);
    

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
	
	return 0;
	
}
