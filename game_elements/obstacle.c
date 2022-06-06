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

#include "obstacle.h"
#include "../map/map.h"
#include "../game.h"

// This function returns a new obstacle. It is called periodically based on the function glutCreateObstacle()
pObstacle createObstacle(int loadedObstacle, float x, float y, int active){
    pObstacle obstacle;
    obstacle = (pObstacle) malloc (sizeof(struct obstacle));
    
    if(loadedObstacle==0){
        obstacle->pos_x = 1;
        obstacle->pos_y = ( rand() % (WINDOW_SIZE_Y - 15) ) + 7;
        obstacle->obstacleActive = true;
        obstacle->previousObstacle = NULL;
        obstacle->nextObstacle = NULL;
    }
    else{
        obstacle->pos_x = x;
        obstacle->pos_y = y;
        if(active == 1){
            obstacle->obstacleActive = true;
        }
        else{
            obstacle->obstacleActive = false;
        }
        
        obstacle->previousObstacle = NULL;
        obstacle->nextObstacle = NULL;
    }
    
    return obstacle;
}

// This function creates the list of all the obstacles and is called during the initialization of the game
pObstacleList createObstacleList(void){
    pObstacleList obstacleList;
    obstacleList = (pObstacleList) malloc (sizeof(struct obstacleList));
    
    obstacleList->obstacleCounter = 0;
    obstacleList->firstObstacle = NULL;
    obstacleList->lastObstacle = NULL;
    
    return obstacleList;
}

// This function adds an obstacle to the list of all obstacles
void addObstacle(pObstacleList obstacleList, pObstacle newObstacle){
    if(obstacleList->firstObstacle == NULL){ // in case the list is currently empty, add the newObstacle as first and last element of the list
        obstacleList->firstObstacle = newObstacle;
        obstacleList->lastObstacle = newObstacle;
    }
    else{ // otherwise, make the new obstacle's next pointer equal to the current head of the list, make the current head of the list point to the new obstacle as previous pointer and finally update the head of the list as the new obstacle
        newObstacle->nextObstacle = obstacleList->firstObstacle;
        obstacleList->firstObstacle->previousObstacle = newObstacle;
        obstacleList->firstObstacle = newObstacle;
    }
    // increase by 1 the number of obstacles in the list
    obstacleList->obstacleCounter ++;
}

// This function moves all the obstacles by one, but as they move at the same speed as the map, the glutcallback is handled in map.c
void moveObstacles(pObstacleList list){
    if (list->firstObstacle != NULL ){ // if the list of all obstacles is not empty, move the obstacles. If list of obstacles is empty, do nothing
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = list->firstObstacle;
        float x;
        
        while(loop != NULL){ // as long as we did not go through the whole list of obstacles, move the current obstacle down by 1 row
            x = loop->pos_x + 1;
                 
            if ( x < (WINDOW_SIZE_X - 1)){ // in case the obstacle is still within the boundaries of the map, it can move
                loop->pos_x = x;
            }
            else{ // in case the obstacle has reached the boundaries of the map, it becomes inactive and will be removed by destroyObstacles()
                loop->pos_x = x;
                loop->obstacleActive = false;
            }
            loop = loop->nextObstacle;
        }
        free(loop);
    }
}

// This function destroy all the inactive obstacles and removes them from the list of obstacles
void destroyObstacles(pObstacleList list){
    if (list->firstObstacle != NULL ){ // if the list of all obstacles is not empty, check if some obstacles have to be removed. If list of osbtacles is empty, do nothing
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = list->firstObstacle;
        
        while(loop != NULL){ // as long as we did not go through the whole list of obstacles, execute the following code
            if(loop->obstacleActive == false){ // if the current obstacle is inactive (ie, obstacleActive == FALSE), then it must be deleted

                // creating a temporary obstacle to be deleted, and moving the loop to the next item (before the obstacle is actually removed from the list; while the link to the next one is still valid)
                pObstacle obstacleToDelete;
                obstacleToDelete = (pObstacle) malloc(sizeof(struct obstacle));
                obstacleToDelete = loop;
                loop = loop->nextObstacle;
                
                if(obstacleToDelete == list->firstObstacle && obstacleToDelete == list->lastObstacle){ // in case there is only one obstacle in the list, update the list as empty
                    list->firstObstacle = NULL;
                    list->lastObstacle = NULL;
                }
                else if(obstacleToDelete == list->firstObstacle && obstacleToDelete != list->lastObstacle){ // in case the obstacle to delete is the first one of a list of at least 2 obstacles
                    // the 2nd item in the list becomes the first and this new first item points to a NULL previous item
                    list->firstObstacle = obstacleToDelete->nextObstacle;
                    list->firstObstacle->previousObstacle = NULL;
                }
                else if(obstacleToDelete != list->firstObstacle && obstacleToDelete == list->lastObstacle){ // in case the obstacle to delete is the last one of a list of at least 2 obstacles
                    // the previous of the current last item (ie, the one to delete) becomes the new last item and this new last item points to a next NULL item
                    list->lastObstacle = obstacleToDelete->previousObstacle;
                    list->lastObstacle->nextObstacle = NULL;
                }
                else{ // in all other cases, the obstalcle to delete is not the first nor the last of the list of at least 3 obstacles
                    // the obstacle preceeding the one to delete must now point to the obstacle following the one to delete, and vice versa
                    obstacleToDelete->previousObstacle->nextObstacle = obstacleToDelete->nextObstacle;
                    obstacleToDelete->nextObstacle->previousObstacle = obstacleToDelete->previousObstacle;
                }
            
                // the obstacle to delete can be removed from memory + the counter of all obstacles can decreased by one unit
                list->obstacleCounter --;
                free(obstacleToDelete);
            }
            else{ // if the current obstacle is still active, do nothing and check with the following from the list
                loop = loop->nextObstacle;
            }
        }
        free(loop); // freeing the temporary allocation of memory
    }
}

// this function sets all active obstacles as inactive. It is called along with the destroyObstacles() function when killing a game.
void setInactiveAllObstacles(pObstacleList list){
    if (list->firstObstacle != NULL ){ // if the list of all obstacles is not empty, all active obstacles are set to inactive. If list of osbtacles is empty, do nothing
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = list->firstObstacle;
        
        while(loop != NULL){ // as long as we did not go through the whole list of obstacles, execute the following code
            if(loop->obstacleActive == true){ // if the current obstacle is active, then it is set to inactive
                loop->obstacleActive = false;
            }
            loop = loop->nextObstacle;
        }
        free(loop); // freeing the temporary allocation of memory
    }
}
