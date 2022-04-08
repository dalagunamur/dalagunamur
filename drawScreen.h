#ifndef _DRAWSCREEN_H_
#define _DRAWSCREEN_H_

#include "map/map.h"
#include "game_elements/player.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#define Square_size 20.0
#define missile_size 10.0

void drawMap(void); //this function draws the map on the screen, out of the mapToRender global variable
void drawPlayer(pPlayer p); // this function draws the player on the screen
void drawCars(pCarList list); // this function draws all the cars on the screen
void drawMissiles(pMissileList list); // this function draws all the missiles on the screen

#endif
