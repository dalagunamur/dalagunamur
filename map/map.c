#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
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


listMap createRow(void){
	listMap row;
	row = (listMap) malloc (sizeof(struct mapRow));

	int readLine = (rand()%(MAP_SIZE_X -1)) +1; // get a random number between 1 and MAP_SIZE_X

	for(int i = 0; i < MAP_SIZE_Y; i++){
		(*row).rowContent[i] = fullMap[readLine][i];
	}

	(*row).nextRow = NULL;
	
	return row;
}

listMap addRow(listMap map, listMap newRow){ // adds newRow as new head of map and returns the new head
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
    mapToRender = malloc(sizeof(char *) * WINDOW_SIZE_X);
    int i;
    int j = 0;
    while (map != NULL){
        *(mapToRender + j) = malloc(sizeof(char *) * WINDOW_SIZE_Y);
        for(i = 0; i < MAP_SIZE_X; i++){
            mapToRender[j][i] = (*map).rowContent[i];
		}
        j++;
 		map = (*map).nextRow;
 	}
}

void updateMap(int timer){
    free(mapToRender);
    deleteRow(map);
    listMap row;
    row = createRow();
    map = addRow(map,row);
//    printf("Row deleted and new one added\n");
    displayMap(map);
//    printf("mapToRender populated\n");
    glutPostRedisplay();
    glutTimerFunc(1000, updateMap, 0);
//    printf("updateMap processing finished\n");
}
