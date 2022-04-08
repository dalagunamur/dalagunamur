#ifndef _MAP_H_
#define _MAP_H_

#include <stdbool.h>
#include <string.h>

#define MAP_SIZE_X 60 //number of rows of the map.txt file
#define MAP_SIZE_Y 39 //number of columns of the map.txt file
#define WINDOW_SIZE_X 40 //number of rows to be displayed on screen when playing
#define WINDOW_SIZE_Y 39 //number of columns to be displayed on screen when playing

// this structure contains one row of the map, and points to the next one
struct mapRow{
	char rowContent[MAP_SIZE_Y];
	struct mapRow * nextRow;	
};

// this is a pointer to mapRow
typedef struct mapRow * listMap;

char **fullMap; // variable that will be used to store in a matrix the content of each row of the map.txt file. When scrolling, this variable is read, rather than accessing the map.txt file each time
listMap map; // variable pointing to the head of the list of all current rows of the map
listMap row; // variable used to create a new row in the map
char **mapToRender; // matrix that will store the actual map to display on screen. It is populated based on the chained list starting at the head pointed by the variable "map"

bool loadMapFile(int x, int y); // function used to read the map.txt file and store it in fullMap, which will be read each time the scrolling happens
listMap createRow(void); // generic function to create a new row by reading out of fullMap
listMap addRow(listMap map, listMap newRow); // inserts a row as new head of the chained list
void deleteRow(listMap map); // removes the last row of the chained list
void displayMap(listMap map); // displays the map on screen

void updateMap(int timer); // calls the other functions related to the map, and handles the callback via glutTimerFunc()

#endif
