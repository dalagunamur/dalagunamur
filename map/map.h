#ifndef _MAP_H_
#define _MAP_H_

#include <stdbool.h>
#include <string.h>

#define MAP_SIZE_X 60
#define MAP_SIZE_Y 39
#define WINDOW_SIZE_X 40
#define WINDOW_SIZE_Y 39


struct mapRow{
	char rowContent[MAP_SIZE_Y];
	struct mapRow * nextRow;	
};

typedef struct mapRow * listMap;

char **fullMap; // variable that will be used to store in a matrix the content of each row of the map file
listMap map; // variable pointing to the head of the list of all current rows of the map
listMap row; // variable used to create a new row in the map
char **mapToRender; // variable that will be used to display the map on screen

bool loadMapFile(int x, int y); // function used to read the map.txt file and store it in fullMap, which will be read each time the scrolling happens
listMap createRow(void); // generic function to create a new row by reading out of fullMap
listMap addRow(listMap map, listMap newRow); // inserts a row as new head of the chained list
void deleteRow(listMap map); // removes the last row of the chained list
void displayMap(listMap map); // displays the map on screen
void updateMap(int timer);


#endif

/*
#ifndef _MAP_H_
#define _MAP_H_
#define MAP_SIZE_ROWS 123 // defines the nbr of rows of the map #define MAP_SIZE_COLS 123 // defines the nbr of columns of the map
typedef struct map_buffer{
char *map[MAP_SIZE_ROWS][MAP_SIZE_COLS];
} map_buffer_t;
typedef struct map{
     char *map[MAP_SIZE_COLS];
     map_t *next_element;
} map_t;
void load_file_map(int starting_row);
 map_t create_map_element();
void scroll_map(map_buffer_t *map);
#endif
*/
