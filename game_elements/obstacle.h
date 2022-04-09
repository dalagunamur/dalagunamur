#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct obstacle{
    int pos_x;
    int pos_y;
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

#endif
