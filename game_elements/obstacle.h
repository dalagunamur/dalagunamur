#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <stdbool.h>

struct obstacle{
    float pos_x;
    float pos_y;
    bool obstacleActive; // true if the obstacle has to be displayed on the screen. Becomes false if the obstacle leaves the screen. Inactive obstacles are removed from the list
    struct obstacle * previousObstacle;
    struct obstacle * nextObstacle;
};

// pObstacle points to obstacle
typedef struct obstacle * pObstacle;

struct obstacleList{
    int obstacleCounter;
    pObstacle firstObstacle;
    pObstacle lastObstacle;
};

// pObstacleList points to obstacleList
typedef struct obstacleList * pObstacleList;

pObstacleList listOfObstacles; // this global variable is used to store the list of the obstacles.

// this function is called each time a new obstacle is created by the game, and returns a newly created obstacle. When creating a new obstacle in game, the value loadedObstacle is set to 0 and the other attributes are 0 as well. When the value loadedObstacle is set to 1, then it means the obstacle is created while loading a saved game; the other attributes then store the coordinates x, y of the obstacle and the active status of the obstacle.
pObstacle createObstacle(int loadedObstacle, float x, float y, int active);

pObstacleList createObstacleList(void); // this function is called at the beginning of the game is used to return a list of all the obstacles created during the game
void addObstacle(pObstacleList obstacleList, pObstacle newObstacle); // this function adds a newly created obstacle to the list of all obstacles in the game
void moveObstacles(pObstacleList list); // this function moves all the obstacles created in the game and flags them as inactive when scrolling out of the map. The obstacle actually do not move, they simply follow the scrolling of the map.
void destroyObstacles(pObstacleList list); // this function removes from the game all obstacles that have become inactive

void setInactiveAllObstacles(pObstacleList list); // this function sets all active obstacles as inactive. It is called along with the destroyObstacles() function when killing a game.

#endif
