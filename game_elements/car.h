#ifndef _CAR_H_
#define _CAR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// structures created to handle cars and list of cars

struct car{
    int pos_x;
    int pos_y;
	int healthPoints;
    bool carFrozen; // cars will by default be MOVING, but can become FROZEN if hit by the special attack
    bool carActive; // an inactive car means it must be deleted from the game, as it either reached the botton of the screen or was hit by the player's missile
    struct car * previousCar;
    struct car * nextCar;
};

typedef struct car * pCar;

struct carList{
    int carCounter;
    pCar firstCar;
    pCar lastCar;
};

typedef struct carList * pCarList;

// global variables
pCarList listOfCars;

pCarList createCarList(void); // this function creates a list of cars as a pointer to struct carList. It is called when initializing the game
pCar createCar(void); // this function creates a new car as a pointer to struct car, it is called each time a new car has to be created
void addCar(pCarList list, pCar newCar); // adds a newly created car to the chained list of all cars, as new head
void destroyCars(pCarList list); // remove all inactive cars from the list of cars to display on screen
void moveCars(pCarList list); // make all cars move one row down

void glutCreateCars(int timer);
void glutMoveCars(int timer);
void glutDestroyCars(int timer);

void carFires(pCar car);
void carHit(pCar car); // when the car is hit by the main weapon
void carHitAlt(pCar car); // when the car is hit by the alternate weapon, it is frozen


#endif
