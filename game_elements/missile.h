#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "car.h"

struct missile{
    int pos_x;
    int pos_y;
    int speed;
    bool missileFromPlayer;
    bool missileActive;
    struct missile * previousMissile;
    struct missile * nextMissile;
};

typedef struct missile * pMissile;

struct missileList{
    int missileCounter;
    struct missile * firstMissile;
    struct missile * lastMissile;
};

typedef struct missileList * pMissileList;

// global variables
pMissileList listOfMissiles;

pMissileList createMissileList(void); // this function creates a list of missiles as a pointer to struct carList. It is called when initializing the game
pMissile createMissileFromPlayer(void); // to create a new instance of a missile shot from the player
pMissile createMissileFromCar(pCar car); // to create a new instance of a missile shot from a car
void addMissile(pMissileList list, pMissile newMissile); // adds a newly created missile to the list of all missiles, as new head
void moveMissiles(pMissileList list); // make all missiles move by one position
void destroyMissiles(pMissileList list); // remove all inactive missiles. Missiles can become inactive if they leave the map or if they hit

void glutMoveMissiles(int timer);
void glutDestroyMissiles(int timer);

#endif
