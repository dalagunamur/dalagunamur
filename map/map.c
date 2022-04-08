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

// This function loads the .txt file containing the map into a table. The table will in turn be read each time a new row will be added to the map to be displayed on screen
bool loadMapFile(int x, int y){
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


// This function reads a random row from the map loaded in a table and returns the row
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

// This function adds newRow as new head of the chained list and returns the new head opf the list
listMap addRow(listMap map, listMap newRow){
 	(*newRow).nextRow = map;
 	return newRow;
}

// This function deletes the last row in the list currently displayed on screen
void deleteRow(listMap map){
	listMap temp = map;
	while(temp->nextRow->nextRow != NULL){
		temp = temp->nextRow;
	}
	listMap rowToBeDeleted = temp->nextRow;
	temp->nextRow = NULL;
	free(rowToBeDeleted);

}

// This function copies each row of the chained list into one table with x and y coordinates. This "mapToRender" is updated each time the map scrolls and is then displayed on screen via the function drawMap()
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

// This function is called each time the map needs to scroll (via the glutTimerFunc callback). It deletes the last row of the map (appearing at the bottom of the screen) and adds a new random row as first row of the screen, then request to redisplay of the map on screen
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
    glutTimerFunc(2000, updateMap, 0);
//    printf("updateMap processing finished\n");
}
