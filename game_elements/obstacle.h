#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

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

pObstacle createObstacle(void); // this function is called each time a new obstacle is created by the game, and returns a newly created obstacle
pObstacleList createObstacleList(void); // this function is called at the beginning of the game is used to return a list of all the obstacles created during the game
void addObstacle(pObstacleList obstacleList, pObstacle newObstacle); // this function adds a newly created obstacle to the list of all obstacles in the game
void moveObstacles(pObstacleList list); // this function moves all the obstacles created in the game and flags them as inactive when scrolling out of the map. The obstacle actually do not move, they simply follow the scrolling of the map.
void destroyObstacles(pObstacleList list); // this function removes from the game all obstacles that have become inactive

void glutCreateObstacle(int timer); // this function is called periodically to create a new obstacle
void glutDestroyObstacles(int timer); // this function is used to remove from the game all the inactive obstacles and handles the callback via glutTimerFunc()

#endif
