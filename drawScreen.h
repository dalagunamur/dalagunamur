#ifndef _DRAWSCREEN_H_
#define _DRAWSCREEN_H_

#include "map/map.h"
#include "game_elements/player.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#define Square_size 20.0
#define missile_size 10.0

void drawMap(void);
void drawPlayer(pPlayer p);
void drawCars(pCarList list);
void drawMissiles(pMissileList list);

#endif
