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

#include "car.h"
#include "../map/map.h"

// This function returns a new car, placing it on the first row of the screen, at a random position on the road
pCar createCar(void){
	pCar car;
    car = (pCar) malloc (sizeof(struct car));
    
    car->pos_x = 1;
    car->pos_y = ( rand() % (WINDOW_SIZE_Y - 15) ) + 8; // cars must appear on the first row and on the road, not on the grass
    car->healthPoints = 1;
    car->carFrozen = false; // by default a car is moving
    car->carActive = true;
    car->previousCar = NULL;
	car->nextCar = NULL;
	
	return car;
}

// This function returns the list of all the cars, which stores the counter of the active cars + the head and tail of the chained list
pCarList createCarList(void){
    pCarList carList;
    carList = (pCarList) malloc (sizeof(struct carList));
    
    carList->carCounter = 0;
    carList->firstCar = NULL;
    carList->lastCar = NULL;
    
    return carList;
}

// This function adds a car to the list of all the cars
void addCar(pCarList list, pCar newCar){
    if(list->firstCar == NULL){ // in case the list is currently empty, add the newCar as first and last element of the list (ie, the only one on the list)
        list->firstCar = newCar;
        list->lastCar = newCar;
    }
    else{ // otherwise, make the new car's next pointer equal to the head of the list, make the current head of the list point to the new car as previous pointer and finally update the head of the list as the new car
        newCar->nextCar = list->firstCar;
        list->firstCar->previousCar = newCar;
        list->firstCar = newCar;
    }
    // increase by 1 the number of cars in the list
    list->carCounter ++;
}

// This function moves all the cars down by one row
void moveCars(pCarList list){
    if (list->firstCar != NULL ){ // if the list of all cars is not empty, move the cars. If list of cars is empty, do nothing
        pCar loop;
        loop = (pCar) malloc(sizeof(struct car));
        loop = list->firstCar;
        int x;
        
        while(loop != NULL){ // as long as we did not go through the whole list of cars, move the current car down by 1 row
            x = loop->pos_x + 1;
                 
            if ((x < (WINDOW_SIZE_X - 1)) ){
                loop->pos_x = x;
            }
            else{ // in case the car has reached the last row, it becomes inactive and will be removed by destroyCars()
                loop->pos_x = x;
                loop->carActive = false;
            }
            loop = loop->nextCar;
        }
        free(loop);
    }
}

// This function destroy the inactive cars from the list of cars. It covers the various cases (car to remove is head, is tail, is both head and tail, is neither head nor tail)
void destroyCars(pCarList list){
    if (list->firstCar != NULL ){ // if the list of all cars is not empty, check if some cars have to be removed. If list of cars is empty, do nothing
        pCar loop;
        loop = (pCar) malloc(sizeof(struct car));
        loop = list->firstCar;
        
        while(loop != NULL){ // as long as we did not go through the whole list of cars, execute the following code
            if(loop->carActive == false){ // if the current car is inactive (ie, carActive == FALSE), then it must be deleted

                // creating a temporary car to be deleted, and moving the loop to the next item (before the car is actually removed from the list, while the link to the next one is still valid)
                pCar carToDelete;
                carToDelete = (pCar) malloc(sizeof(struct car));
                carToDelete = loop;
                loop = loop->nextCar;
                
                if(carToDelete == list->firstCar && carToDelete == list->lastCar){ // in case there is only one car in the list, update the list as empty
                    list->firstCar = NULL;
                    list->lastCar = NULL;
                }
                else if(carToDelete == list->firstCar && carToDelete != list->lastCar){ // in case the car to delete is the first one of a list of at least 2 cars
                    // the 2nd item in the list becomes the first and this new first item points to a NULL previous item
                    list->firstCar = carToDelete->nextCar;
                    list->firstCar->previousCar = NULL;
                }
                else if(carToDelete != list->firstCar && carToDelete == list->lastCar){ // in case the car to delete is the last one of a list of at least 2 cars
                    // the previous of the current last item becomes the new last item and this new last item points to a next NULL item
                    list->lastCar = carToDelete->previousCar;
                    list->lastCar->nextCar = NULL;
                }
                else{ // in all other cases, the car to delete is not the first nor the last of the list of at least 3 cars
                    // the car preceeding the one to delete must now point to the car following the one to delete, and vice versa
                    carToDelete->previousCar->nextCar = carToDelete->nextCar;
                    carToDelete->nextCar->previousCar = carToDelete->previousCar;
                }
            
                // the car to delete can be removed from memory + the counter of all ennemies can be reduced by 1
                free(carToDelete);
                list->carCounter --;
            }
            else{ // if the current Car is still active, do nothing
                loop = loop->nextCar;
            }
        }
        free(loop); // removing the temporary allocation of memory
    }
}

// this function is used to trigger the creation of a new car periodically
void glutCreateCars(int timer){
    pCar newCar = createCar();
    addCar(listOfCars, newCar);
    glutPostRedisplay();
    glutTimerFunc(2000, glutCreateCars, 1);
}

// this function is used to trigger the movement of existing cars periodically + flagging them as inactive if they reach the bottom of the screen
void glutMoveCars(int timer){
    moveCars(listOfCars);
    glutPostRedisplay();
    glutTimerFunc(500, glutMoveCars, 2);
}

// this function is used to trigger the removal of inactive cars periodically
void glutDestroyCars(int timer){
    destroyCars(listOfCars);
    glutPostRedisplay();
    glutTimerFunc(100, glutDestroyCars, 3);
}
