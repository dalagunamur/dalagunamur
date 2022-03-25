#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "map.h"

bool loadMapFile(int x, int y)		//fonction qui ouvre le fichier txt et charge la carte dans le tableau
{
	fullMap = malloc(sizeof(char *) * x);
    FILE *f = NULL;
    f = fopen("map/map.txt", "r");
    if(f == NULL)
    {
        printf("File not found.\n");
        return false;
    }
    char c;
    int i = 0;
    int j = 0;

	for(i = 0; i < x; i++)
		{
		*(fullMap + i) = malloc(sizeof(char *) * y);
			for(j = 0; j < y; j++)
			{
				c = fgetc(f);
				*(*(fullMap +i) +j) = c;
			}
			fgetc(f);
		}

	    fclose(f);

	return true;
}


listMap createFirstRow(void){
	listMap row;
	row = (listMap) malloc (sizeof(struct mapRow));

	for(int i = 0; i < MAP_SIZE_Y; i++){
		(*row).rowContent[i] = fullMap[MAP_SIZE_X-1][i]; //gets the value of the last line of the map file, which is the starting position of the player
	}

	(*row).nextRow = NULL;
	
	return row;
}


listMap createRow(void){
	listMap row;
	row = (listMap) malloc (sizeof(struct mapRow));

	int readLine = (rand()%(MAP_SIZE_X - 2)) +1; // get a random number between 1 and MAP_SIZE_X-1, as the last row of the map should only be used when intializing the game

	for(int i = 0; i < MAP_SIZE_Y; i++){
		(*row).rowContent[i] = fullMap[readLine][i];
	}

	(*row).nextRow = NULL;
	
	return row;
}

listMap addRow(listMap map, listMap newRow){ // adds newRow as new head of map
 	(*newRow).nextRow = map;
 	return newRow;
}

void deleteRow(listMap map){
	listMap temp = map;
	while(temp->nextRow->nextRow != NULL){
		temp = temp->nextRow;
	}
	listMap rowToBeDeleted = temp->nextRow;
	temp->nextRow = NULL;
	free(rowToBeDeleted);

}

void displayMap(listMap map){ // prints the whole map on screen
 	while (map != NULL){
		for(int i = 0; i < MAP_SIZE_Y; i++){
			printf("%c",(*map).rowContent[i]);
		}
		printf("%p \n",(*map).nextRow);
 		map = (*map).nextRow;
 	}
}
