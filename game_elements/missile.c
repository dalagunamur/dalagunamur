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
#include <time.h>


#include "../map/map.h"
#include "missile.h"
#include "car.h"
#include "player.h"
#include "../game.h"

// This function returns a new missile shot from the player. It will be called each time the player presses the key to shoot
pMissile createMissileFromPlayer(void){
    pMissile missile;
    missile = (pMissile) malloc (sizeof(struct missile));
    
    missile->pos_x = p->pos_x *2; //need to multiply the position of the missile by 2, as the size of the missile square is 1/2 of those of the player
    missile->pos_y = p->pos_y *2; //need to multiply the position of the missile by 2, as the size of the missile square is 1/2 of those of the player
    missile->missileFromPlayer = true;
    missile->missileActive = true;
    missile->previousMissile = NULL;
    missile->nextMissile = NULL;
    
    return missile;
}

// This function returns a new missile shot from a car. It is called periodically based on the function glutCreateMissileFromCar()
pMissile createMissileFromCar(pCar car){
    pMissile missile;
    missile = (pMissile) malloc (sizeof(struct missile));
    
    missile->pos_x = (car->pos_x *2) +8; //need to multiply the position of the missile by 2, as the size of the missile square is 1/2 of those of the cars and +8 to appear in front of the car
    missile->pos_y = (car->pos_y *2) +2; //need to multiply the position of the missile by 2, as the size of the missile square is 1/2 of those of the cars and +2 to appear centered vs the car
    missile->missileFromPlayer = false;
    missile->missileActive = true;
    missile->previousMissile = NULL;
    missile->nextMissile = NULL;

    return missile;
}

// This function creates the list of all the missiles and is called during the initialization of the game
pMissileList createMissileList(void){
    pMissileList missileList;
    missileList = (pMissileList) malloc (sizeof(struct missileList));
    
    missileList->carsMissileCounter = 0;
    missileList->playerMissileCounter = 0;
    missileList->firstMissile = NULL;
    missileList->lastMissile = NULL;
    
    return missileList;
}

// This function adds a missile to the list of all missiles
void addMissile(pMissileList list, pMissile newMissile){
    if(list->firstMissile == NULL){ // in case the list is currently empty, add the newMissile as first and last element of the list
        list->firstMissile = newMissile;
        list->lastMissile = newMissile;
    }
    else{ // otherwise, make the new missile's next pointer equal to the head of the list, make the current head of the list point to the new missile as previous pointer and finally update the head of the list as the new missile
        newMissile->nextMissile = list->firstMissile;
        list->firstMissile->previousMissile = newMissile;
        list->firstMissile = newMissile;
    }
    // increase by 1 the number of missiles in the list (for the player count or the ennemy count)
    if(newMissile->missileFromPlayer == true){
        list->playerMissileCounter ++;
    }
    else{
        list->carsMissileCounter ++;
    }
}

// This function moves all the missiles by one row up or down, depending if they were shot by the player or by a car, respectively
void moveMissiles(pMissileList list){
    if (list->firstMissile != NULL ){ // if the list of all missiles is not empty, move the missiles. If list of missiles is empty, do nothing
        pMissile loop;
        loop = (pMissile) malloc(sizeof(struct missile));
        loop = list->firstMissile;
        float x;
        
        while(loop != NULL){ // as long as we did not go through the whole list of missiles, move the current missile up by 1 row (ie, when shot by the player), else down by one row (when shot by a car).
            if(loop->missileFromPlayer == true){
                x = loop->pos_x - 0.8;
            }
            else{
                x = loop->pos_x + 0.8;
            }
            
                 
            if ((x < ((WINDOW_SIZE_X - 1)*2)) && (x > 1)){ // in case the missile is still within the boundaries of the map (multiplied by 2), it can move
                loop->pos_x = x;
            }
            else{ // in case the missile has reached the boundaries of the map, it becomes inactive and will be removed by destroyMissiles()
                loop->pos_x = x;
                loop->missileActive = false;
            }
            loop = loop->nextMissile;
        }
        free(loop);
    }
}

// This function destroy all the inactive missiles and removes them from the list of missiles
void destroyMissiles(pMissileList list){
    if (list->firstMissile != NULL ){ // if the list of all missiles is not empty, check if some missiles have to be removed. If list of missiles is empty, do nothing
        pMissile loop;
        loop = (pMissile) malloc(sizeof(struct missile));
        loop = list->firstMissile;
        
        while(loop != NULL){ // as long as we did not go through the whole list of missiles, execute the following code
            if(loop->missileActive == false){ // if the current missile is inactive (ie, missileActive == FALSE), then it must be deleted

                // creating a temporary missile to be deleted, and moving the loop to the next item (before the missile is actually removed from the list; while the link to the next one is still valid)
                pMissile missileToDelete;
                missileToDelete = (pMissile) malloc(sizeof(struct missile));
                missileToDelete = loop;
                loop = loop->nextMissile;
                
                if(missileToDelete == list->firstMissile && missileToDelete == list->lastMissile){ // in case there is only one missile in the list, update the list as empty
                    list->firstMissile = NULL;
                    list->lastMissile = NULL;
                }
                else if(missileToDelete == list->firstMissile && missileToDelete != list->lastMissile){ // in case the missile to delete is the first one of a list of at least 2 missiles
                    // the 2nd item in the list becomes the first and this new first item points to a NULL previous item
                    list->firstMissile = missileToDelete->nextMissile;
                    list->firstMissile->previousMissile = NULL;
                }
                else if(missileToDelete != list->firstMissile && missileToDelete == list->lastMissile){ // in case the missile to delete is the last one of a list of at least 2 missiles
                    // the previous of the current last item (ie, the one to delete) becomes the new last item and this new last item points to a next NULL item
                    list->lastMissile = missileToDelete->previousMissile;
                    list->lastMissile->nextMissile = NULL;
                }
                else{ // in all other cases, the missile to delete is not the first nor the last of the list of at least 3 missiles
                    // the missile preceeding the one to delete must now point to the missile following the one to delete, and vice versa
                    missileToDelete->previousMissile->nextMissile = missileToDelete->nextMissile;
                    missileToDelete->nextMissile->previousMissile = missileToDelete->previousMissile;
                }
            
                // the missile to delete can be removed from memory + the counter of all missiles can be reduced by 1, either for the player or the cars
                if(missileToDelete->missileFromPlayer == true){
                    list->playerMissileCounter --;
                }
                else{
                    list->carsMissileCounter --;
                }
                free(missileToDelete);
            }
            else{ // if the current Car is still active, do nothing
                loop = loop->nextMissile;
            }
        }
        free(loop); // removing the temporary allocation of memory
    }
}

// this function sets all active missiles as inactive. It is called along with the destroyMissiles() function when killing a game.
void setInactiveAllMissiles(pMissileList list){
    if (list->firstMissile != NULL ){ // if the list of all missiles is not empty, flag all active missiles as inactive. If list of missiles is empty, do nothing
        pMissile loop;
        loop = (pMissile) malloc(sizeof(struct missile));
        loop = list->firstMissile;
        
        while(loop != NULL){ // as long as we did not go through the whole list of missiles, execute the following code
            if(loop->missileActive == true){ // if the current missile is inactive (ie, missileActive == FALSE), then it must be set to inactive
                loop->missileActive = false;
            }
            loop = loop->nextMissile;
        }
        free(loop);
    }
}
