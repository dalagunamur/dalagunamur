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

#include "bonus.h"
#include "../map/map.h"

// This function returns a newly created bonus
pBonus createBonus(void){
    pBonus newBonus;
    newBonus = (pBonus) malloc(sizeof(struct bonus));
    
    newBonus->pos_x = (rand() % 10) + 10; // the bonus appears in the rows 10 to 20
    newBonus->pos_y = ( rand() % (WINDOW_SIZE_Y - 15) ) + 7;
    newBonus->bonusActive = true;
    newBonus->previousBonus = NULL;
    newBonus->nextBonus = NULL;
    
    int typeBonus = rand() %3; // bonuses can be of type health only, missile only or both health and missile
    if(typeBonus == 0){
        newBonus->typeHealth = true;
        newBonus->typeMissile = false;
    }
    else if(typeBonus == 1){
        newBonus->typeHealth = false;
        newBonus->typeMissile = true;
    }
    else{
        newBonus->typeHealth = true;
        newBonus->typeMissile = true;
    }
    
    return newBonus;
}


// This function returns a list of bonuses, containing a pointer to the first and last elements of the list + the number of items currently in the list
pBonusList createListBonuses(void){
    pBonusList listBonuses;
    listBonuses = (pBonusList) malloc(sizeof(struct bonusList));
    
    listBonuses->bonusCounter = 0;
    listBonuses->firstBonus = NULL;
    listBonuses->lastBonus = NULL;
    
    return listBonuses;
}

// This function adds a newly created bonus to the list of all bonuses
void addBonus(pBonusList list, pBonus newBonus){
    if(list->firstBonus == NULL){ // in case the list is currently empty, add the newBonus as first and last element of the list
        list->firstBonus = newBonus;
        list->lastBonus = newBonus;
    }
    else{ // otherwise, make the new bonus's next pointer equal to the current head of the list, make the current head of the list point to the new bonus as previous pointer and finally update the head of the list as the new bonus
        newBonus->nextBonus = list->firstBonus;
        list->firstBonus->previousBonus = newBonus;
        list->firstBonus = newBonus;
    }
    // increase by 1 the number of bonuses in the list
    list->bonusCounter ++;
}

//This function removes from the list all inactive bonuses
void destroyBonuses(pBonusList list){
    if (list->firstBonus != NULL ){ // if the list of all bonuses is not empty, check if some bonuses have to be removed. If list of bonuses is empty, do nothing
        pBonus loop; // creating a temporary bonus to navigate through the list of bonuses
        loop = (pBonus) malloc(sizeof(struct bonus));
        loop = list->firstBonus;
        
        while(loop != NULL){ // as long as we did not go through the whole list of bonuses, execute the following code
            if(loop->bonusActive == false){ // if the current bonus is inactive (ie, bonusActive == FALSE), then it must be deleted

                // creating a temporary bonus to be deleted, and moving the loop to the next item (before the bonus is actually removed from the list; while the link to the next one is still valid)
                pBonus bonusToDelete;
                bonusToDelete = (pBonus) malloc(sizeof(struct bonus));
                bonusToDelete = loop;
                loop = loop->nextBonus;
                
                if(bonusToDelete == list->firstBonus && bonusToDelete == list->lastBonus){ // in case there is only one bonus in the list, update the list as empty
                    list->firstBonus = NULL;
                    list->lastBonus = NULL;
                }
                else if(bonusToDelete == list->firstBonus && bonusToDelete != list->lastBonus){ // in case the bonus to delete is the first one of a list of at least 2 bonuses
                    // the 2nd item in the list becomes the new head and this newly appointed first item points to a NULL previous item
                    list->firstBonus = bonusToDelete->nextBonus;
                    list->firstBonus->previousBonus = NULL;
                }
                else if(bonusToDelete != list->firstBonus && bonusToDelete == list->lastBonus){ // in case the bonus to delete is the last one of a list of at least 2 bonuses
                    // the previous of the current last item (ie, the one to delete) becomes the new last item and this new last item points to a next NULL item
                    list->lastBonus = bonusToDelete->previousBonus;
                    list->lastBonus->nextBonus = NULL;
                }
                else{ // in all other cases, the bonus to delete is not the first nor the last of the list of at least 3 bonuses
                    // the bonus preceeding the one to delete must now point to the bonus following the one to delete, and vice versa
                    bonusToDelete->previousBonus->nextBonus = bonusToDelete->nextBonus;
                    bonusToDelete->nextBonus->previousBonus = bonusToDelete->previousBonus;
                }
            
                // the bonus to delete can be removed from memory + the counter of all bonuses can decreased by one unit
                list->bonusCounter --;
                free(bonusToDelete);
            }
            else{ // if the current bonus is still active, do nothing and check with the following from the list
                loop = loop->nextBonus;
            }
        }
        free(loop); // freeing the temporary allocation of memory
    }
}

// This function makes all active bonuses move. The bonuses move at the same pace as the map and the obstacles
void moveBonuses(pBonusList list){
    if (list->firstBonus != NULL ){ // if the list of all bonuses is not empty, move the bonuses. If list of bonuses is empty, do nothing
        pBonus loop;
        loop = (pBonus) malloc(sizeof(struct bonus));
        loop = list->firstBonus;
        int x;
        
        while(loop != NULL){ // as long as we did not go through the whole list of bonuses, move the current bonus down by 1 row
            x = loop->pos_x + 1;
                 
            if ( x < (WINDOW_SIZE_X - 1)){ // in case the bonus is still within the boundaries of the map, it can move
                loop->pos_x = x;
            }
            else{ // in case the bonus has reached the boundaries of the map, it becomes inactive and will be removed by destroyBonuses()
                loop->pos_x = x;
                loop->bonusActive = false;
            }
            loop = loop->nextBonus;
        }
        free(loop);
    }
}

// This function periodically calls the function to create a new Bonus
void glutCreateBonus(int timer){
    pBonus newBonus = createBonus();
    addBonus(listOfBonuses, newBonus);
    glutPostRedisplay();
    glutTimerFunc(20000, glutCreateBonus, 8);
}

// This function periodically calls the function to remove deactivated bonuses
void glutDestroyBonuses(int timer){
    destroyBonuses(listOfBonuses);
    glutPostRedisplay();
    glutTimerFunc(100, glutDestroyBonuses, 3);
}
