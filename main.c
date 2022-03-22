#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "map/map.h"


int main(){

	srand(time(NULL));
	
	// START INITIALIZE THE MAP
	listMap row=NULL;
	listMap map=NULL;

	loadMapFile(MAP_SIZE_X,MAP_SIZE_Y);
	
	row=createFirstRow();
	addRow(&map, &row);
	
	for(int i=0;i<WINDOW_SIZE_X-1;i++){
		row=createRow();
		addRow(&map, &row);
	}
	// END INITIALIZE MAP
	
	int exitAction=0;
	
	while(exitAction<100){
		displayMap(map);
		deleteRow(map);
		row=createRow();
		addRow(&map,&row);
		usleep(80000);
		exitAction++;
	}
	
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
