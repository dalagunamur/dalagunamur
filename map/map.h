#ifndef _MAP_H_
#define _MAP_H_

#include <stdbool.h>
#include <string.h>

#define MAP_SIZE_X 20
#define MAP_SIZE_Y 40
#define WINDOW_SIZE_X 40
#define WINDOW_SIZE_Y 40


struct mapRow{
	char rowContent[MAP_SIZE_Y];
	struct mapRow * nextRow;	
};

typedef struct mapRow * listMap;

char **fullMap; // variable that will be used to store in a matrix the content of each row

bool loadMapFile(int x, int y); // function used to read the map.txt file and store it in fullMap, which will be read each time the scrolling happens
listMap createFirstRow(void); // function used to create the first row when the game starts
listMap createRow(void); // generic function to create a new row by reading out of fullMap
void addRow(listMap * map, listMap * newRow); // inserts a row as new head of the chained list
void deleteRow(listMap map); // removes the last row of the chained list
void displayMap(listMap map); // displays the map on screen


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
void load_file_map(int starting_row); map_t create_map_element();
void scroll_map(map_buffer_t *map);
#endif
*/
