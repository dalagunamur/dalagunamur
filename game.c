#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "drawScreen.h"

// These variables are assigned to store the action that was requested based on the keystroke, then read to trigger to right function corresponding to the action requested by the player
bool MOVE_UP = false;
bool MOVE_DOWN = false;
bool MOVE_LEFT = false;
bool MOVE_RIGHT = false;
bool FIRE_MISSILE = false;

pGame createGame(char **mapForGame, pPlayer player, pCarList carList, pMissileList missileList){
    pGame game;
    game = (pGame) malloc (sizeof(struct game));

    game->timer = 0;
    game->score = 0;
    game->difficulty = 0;
    game->verticalScrolling = true; // by default, will be set to True meaning the screen will scroll vertically. In a future version, if set to false, the screen will scroll horizontally, from the right to the left
    game->map = mapForGame;
    game->player = player;
    game->cars = carList;
    game->missiles = missileList;
//    game->bonuses = bonusList;
//    game->obtacles = obstacleList;
    
    return game;
}

// This function is called each time the player hits a key on the keyboard. In case the key pressed is one which is assigned a function, it records it
void handleKeyboard(unsigned char input, int x, int y){
    switch(input)
        {
            case 'z':
                MOVE_UP = true;
                break;
            case 's':
                MOVE_DOWN = true;
                break;
            case 'q':
                MOVE_LEFT = true;
                break;
            case 'd':
                MOVE_RIGHT = true;
                break;
            case 32: // when hitting the space bar
                FIRE_MISSILE = true;
                break;
            case 27: // when hitting the ESCAPE key
                exit(0);
        }
}

// This function drives the game, by requesting to draw the map on screen; then the cars, then the players and the missiles.
// It also call the function to capture the key pressed by the player on the keyboard and handles the movements of the player.
void play(char **map, pPlayer p, pCarList carList, pMissileList missileList){
    drawMap();  //display the map on screen
    drawCars(carList); //display all the ennemies
    drawPlayer(p); //display the player
    drawMissiles(missileList); //display all the missiles
    
    glutKeyboardFunc(handleKeyboard);        //fonction de glut gérant le clavier
    
    if (MOVE_UP){
        move_player_up(map);
        MOVE_UP = false;
    }
    if (MOVE_DOWN){
        move_player_down(map);
        MOVE_DOWN = false;
    }
    if (MOVE_LEFT){
        move_player_left(map);
        MOVE_LEFT = false;
    }
    if (MOVE_RIGHT){
        move_player_right(map);
        MOVE_RIGHT = false;
    }
    if (FIRE_MISSILE){
        if(listOfMissiles->playerMissileCounter <= MAX_NBR_MISSILE_PLAYER){
            pMissile newMissile = createMissileFromPlayer();
            addMissile(listOfMissiles, newMissile);
        }
        FIRE_MISSILE = false;
    }

    glutPostRedisplay();
}

// This function drives the game, by requesting to draw the map on screen; then the cars, then the players and the missiles.
// It also call the function to capture the key pressed by the player on the keyboard and handles the movements of the player.
void playAlt(pGame game){
    drawMap();  //display the map on screen
    drawCars(game->cars); //display all the ennemies
    drawPlayer(game->player); //display the player
    drawMissiles(game->missiles); //display all the missiles
    
    glutKeyboardFunc(handleKeyboard);        //fonction de glut gérant le clavier
    
    if (MOVE_UP){
        move_player_up(game->map);
        MOVE_UP = false;
    }
    if (MOVE_DOWN){
        move_player_down(game->map);
        MOVE_DOWN = false;
    }
    if (MOVE_LEFT){
        move_player_left(game->map);
        MOVE_LEFT = false;
    }
    if (MOVE_RIGHT){
        move_player_right(game->map);
        MOVE_RIGHT = false;
    }
    if (FIRE_MISSILE){
        if(listOfMissiles->playerMissileCounter <= MAX_NBR_MISSILE_PLAYER){
            pMissile newMissile = createMissileFromPlayer();
            addMissile(listOfMissiles, newMissile);
        }
        FIRE_MISSILE = false;
    }

    glutPostRedisplay();
}

void checkImpactCars(pCarList carList, pMissileList missileList){
    if (carList->firstCar != NULL && missileList->firstMissile != NULL){ // if there is at least one car AND one missile start checking for impacts. Else, do nothing.
        
        // creating 2 temp structure to loop through the whole list of cars and missiles
        pCar loopCar;
        loopCar = (pCar) malloc(sizeof(struct car));
        loopCar = carList->firstCar;
        
        pMissile loopMissile;
        loopMissile = (pMissile) malloc(sizeof(struct missile));
    
        while(loopCar != NULL){ // as long as we did not go through the whole list of cars, check for impacts
            loopMissile = missileList->firstMissile;
            while(loopMissile != NULL){
                if(loopMissile->missileFromPlayer == true){
                    checkMissileImpactsCar(loopCar, loopMissile);
                }
                loopMissile = loopMissile->nextMissile;
            }
            loopCar = loopCar->nextCar;
        }
        free(loopCar);
        free(loopMissile);
    }
}

// This function compares the coordinate of a missile with those of a car to identify if there's an impact
void checkMissileImpactsCar(pCar car, pMissile missile){
    int x = car->pos_x;
    int y = car->pos_y;
    bool impactX = false;
    bool impactY = false;
    
    // TODO - base computation on size of squares rather than hard figures
    // we must take into account that the square size of a car is twice as much as the one of a missile + that a car has in total the length of 8 missiles
    if( (missile->pos_x >= x*2) && (missile->pos_x <= (x*2)+7) ){
        impactX = true;
    }
    
    // we must take into account that the square size of a car is twice as much as the one of a missile + that a car has in total the width of 4 missiles
    if( (missile->pos_y >= y*2) && (missile->pos_y <= (y*2)+3) ){
        impactY = true;
    }
    
    // if both x and y coordinates indicate an impact, the missile is deactivated + the function carHit() is called
    if(impactX && impactY){
        missile->missileActive = false;
        carHit(car);
    }
}

// this function checks for all the potential impacts between elements of the game
void glutCheckImpacts(int timer){
    checkImpactCars(listOfCars, listOfMissiles);
    
    glutPostRedisplay();
    glutTimerFunc(10, glutCheckImpacts, 7);
}
