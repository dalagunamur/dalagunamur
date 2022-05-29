#ifndef _DRAWSCREEN_H_
#define _DRAWSCREEN_H_

#include "game.h"
#include "scores.h"
#include "map/map.h"
#include "game_elements/player.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#include "game_elements/obstacle.h"
#include "game_elements/bonus.h"
#define Square_size 20.0
#define missile_size 10.0

// This function is used to print text via GLUT. It receives a string to be printed and x and y coordinates to indicate where it should be printed out
void drawText(char *string, float x, float y);

// The following functions are used to draw the screens other than the game window
void drawHomePage(void); // this function draws the main page, with the various menu items as rectangles
void drawLoadPage(void); // this function draws the load a game page, with the various menu items as rectangles
void drawOptionsPage(void); // this function draws the options page, with the various menu items as rectangles
void drawScoresPage(pScoresList list); // this function draws the high scores page, with the various menu items as rectangles

// The following functions are used to draw elements of the game
void drawMap(void); //this function draws the map on the screen, out of the mapToRender global variable
void drawPlayer(pPlayer p); // this function draws the player on the screen
void drawCars(pCarList list); // this function draws all the cars on the screen
void drawMissiles(pMissileList list); // this function draws all the missiles on the screen
void drawObstacles(pObstacleList list); // this function draws all the obstacles on the screen
void drawBonuses(pBonusList list); // this function draws all the bonuses on the screen
void drawHealth(pPlayer p); // this function draws the current level of the player's health
void drawBlankSpaceForScore(void); // this function is used to blank out the space in front of which the current score is going to be printed
void drawScore(pGame game); // this function draws the current score and the max number of missiles (stored in maxNbrMissilesPlayer) the player can shoot simultaneously
void displayPause(void); // this function displays on the game window the paused game window, advising about the potential actions
void displayGameOver(pGame game); // this function displays the game over window, advising about the potential actions

#endif
