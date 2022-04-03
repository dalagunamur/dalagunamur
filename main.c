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
    
//    printf("Init completed\n");
    
    loadMapFile(MAP_SIZE_X,MAP_SIZE_Y);
//    printf("Buffer full map created.\n");
    
    for(int i=0; i < WINDOW_SIZE_X; i++){
        row = createRow();
        map = addRow(map, row);
    }
//    printf("Chained list for map created\n");
    updateMap(map);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize((WINDOW_SIZE_Y-2)*Square_size, WINDOW_SIZE_X*Square_size);

    glutCreateWindow("Velo vs Voiture");
    initRendering();

    glutDisplayFunc(display);
//    printf("screen created\n");
    glutReshapeFunc(handleResize);
    glutTimerFunc(1000, updateMap, 0);
    glutTimerFunc(2000, glutCreateCars, 1);
    glutTimerFunc(300, glutMoveCars, 2);
    glutTimerFunc(100, glutDestroyCars, 3);
    glutTimerFunc(50, glutMoveMissiles, 4);
    glutTimerFunc(50, glutDestroyMissiles, 5);
//    printf("Looping to update the map\n");

    glEnable(GL_DEPTH_TEST);
    

    glutMainLoop();
	
	return 0;
	
}


/* CODE USING CAR.H AND CAR.C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game_elements/car.h"
#include "game.h"

// CODE MAIN
int main(){
	
	srand(time(NULL));

	pCar car=NULL;
	pCar carList=NULL;
	ennemyCounter=0;
	
	int initCarCount=(rand()%MAX_ENNEMY_COUNT)+1;
	for(int i=0;i<initCarCount;i++){
		car=createCar();
		addCar(&carList,&car);
	}
	
	int j;
	
	while (ennemyCounter!=0) {
		printf("\n\nThere are %i ennemies in game.\n",ennemyCounter);
		displayCar(carList);
		damageAllCars(&carList);
		sleep(2);
		
		j = rand()%3;
		if(j == 0){ // in 1 case out of 3, add a new ennemy
			printf("\nA new contestant appears!!!\n");
			car = createCar();
			addCar(&carList,&car);
		}
	}
	
	return 0;
}


*/
