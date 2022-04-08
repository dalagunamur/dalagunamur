#ifndef _GAME_H_
#define _GAME_H_

#include "map/map.h"
#include "game_elements/bonus.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#include "game_elements/player.h"

#define DIFFICULTY 123 // this value will be used as a multiplying factor to control the pace at which the difficulty level will change

// This structure is used to store the score, the timer and the pointer to the various lists of elements to display during a game
struct game{
    int timer;
    int score;
//    enum scrollingPattern {vertical, horizontal};
    listMap first_map;
    pCar first_car;
    pMissile first_missile;
    pBonus first_bonus;
};

void handleKeyboard(unsigned char input, int x, int y); // this function is used to capture the key pressed by the player and trigger the ad hoc function in case it is a binded key
void play(char **map, pPlayer p, pCarList carlist, pMissileList missileList); // this function drives the various sequences of the game


// NOT YET IMPLEMENTED
struct game create_game(void); // initialize a new game or load an existing game
void diplay_pause(void); // when the players pauses the game, allows to save or exit or resume
void set_scrolling_pace(int timer);
void save_game(void);

#endif
