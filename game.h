#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>

#include "map/map.h"
#include "game_elements/bonus.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#include "game_elements/player.h"
#include "game_elements/obstacle.h"
#include "game_elements/bonus.h"

// This structure is used to store the score, the timer and the pointer to the various lists of elements to display during a game
struct game{
    int timer; // this variable will count the time since the beginning of the game, which will affect the difficulty and the score
    int score; // this will store the score
    int difficulty; // this value will be used as a multiplying factor to control the pace at which the difficulty level will change
    bool verticalScrolling; // by default, will be set to True meaning the screen will scroll vertically. In a future version, if set to false, the screen will scroll horizontally, from the right to the left
};

// an element of type pGame points to an element of the structure game
typedef struct game * pGame;

// this global variable will be used to store the information about the game
pGame theGame;

pGame createGame(void); // initialize a new game or load an existing game
void handleKeyboard(unsigned char input, int x, int y); // this function is used to capture the key pressed by the player and trigger the ad hoc function in case it is a binded key
void play(pGame game, char **map, pPlayer p, pCarList carlist, pMissileList missileList, pObstacleList obstacleList, pBonusList bonusList); // this function drives the various sequences of the game

void glutCheckImpacts(int timer); // this function is used to call the various functions checking for impacts between all the elements of the game, and uses the glut callback functionality via glutTimerFunc()
void checkImpactCars(pCarList carList, pMissileList missileList); //This function scans through all the missiles and the cars and calls the function checkMissileImpactsCar() to identify if there's an impact for each combination
void checkMissileImpactsCar(pCar car, pMissile missile); //This function compares the coordinates of a missile with those of a car to identify if there is an impact
void checkMissileImpactsPlayer(pPlayer player, pMissileList missileList); //This function compares the coordinates of each missile shot from a car with those of the player to identify if there is an impact
void checkCarsImpactPlayer(pPlayer player, pCarList carList); //This function compares the coordinates of each car with those of the player to identify if there is an impact
void checkObstaclesImpactPlayer(pPlayer player, pObstacleList obstacleList); //This function compares the coordinate of each obstacle with those of the player to identify if there is an impact
void checkBonusesImpactPlayer(pPlayer player, pBonusList bonusList); // this function compares the coordinate of each bonus with those of the player to identify if there is an impact
void checkCarsImpactBonuses(pCarList carList, pBonusList bonusList); // this function compares the coordinates of each bonus with those of each car to identify if there is an impact
void checkMissilesImpactBonuses(pMissileList missileList, pBonusList bonusList); // this function compares the coordinates of each bonus with those of each missile shot from a car to identify if there is an impact


// NOT YET IMPLEMENTED
void diplay_pause(void); // when the players pauses the game, allows to save or exit or resume
void set_scrolling_pace(int timer);
void save_game(void);

#endif
