#ifndef _MISSILE_H_
#define _MISSILE_H_

#include <stdbool.h>
#include "car.h"

#define MAX_NBR_MISSILE_CARS 15

// This structure is used to create the missiles, shot from the player or from a car
struct missile{
    float pos_x;
    float pos_y;
    int speed;
    bool missileFromPlayer;
    bool missileActive;
    struct missile * previousMissile;
    struct missile * nextMissile;
};

// pMissile points to missile
typedef struct missile * pMissile;

// This structure is used to list all the missiles currently displayed on screen
struct missileList{
    int carsMissileCounter;
    int playerMissileCounter;
    struct missile * firstMissile;
    struct missile * lastMissile;
};

// pMissileList points to missileList
typedef struct missileList * pMissileList;

pMissileList listOfMissiles; // this global variable is used to store the list of all the missiles on screen

pMissileList createMissileList(void); // this function creates a list of missiles as a pointer to struct missileList. It is called when initializing the game
pMissile createMissileFromPlayer(void); // to create a new instance of a missile shot from the player
pMissile createMissileFromCar(pCar car); // to create a new instance of a missile shot from a car
void addMissile(pMissileList list, pMissile newMissile); // adds a newly created missile to the list of all missiles, as new head
void moveMissiles(pMissileList list); // make all missiles move by one position
void destroyMissiles(pMissileList list); // remove all inactive missiles. Missiles can become inactive if they leave the map or if they hit



#endif
