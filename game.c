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

pGame createGame(void){
    pGame game;
    game = (pGame) malloc (sizeof(struct game));

    game->timer = 0;
    game->score = 0;
    game->difficulty = 0;
    game->verticalScrolling = true; // by default, will be set to True meaning the screen will scroll vertically. In a future version, if set to false, the screen will scroll horizontally, from the right to the left
    
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
void play(pGame game, char **map, pPlayer p, pCarList carList, pMissileList missileList, pObstacleList obstacleList, pBonusList bonusList){
    drawMap();  //display the map on screen
    drawObstacles(obstacleList); // display all the obstacles on the screen
    drawBonuses(bonusList); // display all the bonuses on the screen
    drawCars(carList); //display all the ennemies
    drawPlayer(p); //display the player
    drawMissiles(missileList); //display all the missiles
    
    glutKeyboardFunc(handleKeyboard);        //callback to the function handling the keyboard
    
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
        if(listOfMissiles->playerMissileCounter < maxNbrMissilesPlayer){ // the player can only fire up to a certain number of missiles at the same time. This number can be increased via the bonuses
            pMissile newMissile = createMissileFromPlayer();
            addMissile(listOfMissiles, newMissile);
        }
        FIRE_MISSILE = false;
    }
    
    game->timer++;
    game->score++;

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
        theGame->score++;
    }
}

// this function checks for all the potential impacts between elements of the game
void glutCheckImpacts(int timer){
    checkImpactCars(listOfCars, listOfMissiles); // checks if missiles shot by the player hit a car
    checkMissileImpactsPlayer(p, listOfMissiles); // checks if missiles shot by cars hit the player
    checkCarsImpactPlayer(p,listOfCars); // checks if cars hit the player
    checkObstaclesImpactPlayer(p, listOfObstacles); // checks if the player hits an obstacle
    checkBonusesImpactPlayer(p, listOfBonuses); // checks if the player collects a bonus
    checkCarsImpactBonuses(listOfCars, listOfBonuses); // checks if cars hit a bonus
    checkMissilesImpactBonuses(listOfMissiles, listOfBonuses); // check if missiles shot from the cars hit a bonus
    
    glutPostRedisplay();
    glutTimerFunc(10, glutCheckImpacts, 7);
}

// this function scans through all the missiles in game that were shot from a car and compares their position to the one of the player
void checkMissileImpactsPlayer(pPlayer player, pMissileList missileList){
    if(missileList->firstMissile != NULL){ //if there's at least one missile in the list, perform the scan. Else do nothing
        // creating a temporary missile to scan through the list of all missiles
        pMissile loopMissile;
        loopMissile = (pMissile) malloc(sizeof(struct missile));
        loopMissile = missileList->firstMissile;

        int x = player->pos_x;
        int y = player->pos_y;
        bool impactX = false;
        bool impactY = false;
    
        while(loopMissile != NULL){
            if(loopMissile->missileFromPlayer==false){ // if the missile has been shot by a car, check the coordinates of the missile vs the ones of the player, else do nothing
                // the size of the player on the screen is twice that of a missile, this impacts the check on the coordindates
                if( (loopMissile->pos_x >= x*2) && (loopMissile->pos_x <= (x*2)+1) ){
                    impactX = true;
                }
                
                // the size of the player on the screen is twice that of a missile, this impacts the check on the coordindates
                if( (loopMissile->pos_y >= y*2) && (loopMissile->pos_y <= (y*2)+1) ){
                    impactY = true;
                }
                
                // if both x and y coordinates indicate an impact, the missile is deactivated and the function player_loose_health() is called to reduce the health points of the player
                if(impactX && impactY){
                    loopMissile->missileActive = false;
                    player_loose_health(player);
                }
            }
            // resetting the values for the next missile
            impactX = false;
            impactY = false;
            
            loopMissile = loopMissile->nextMissile;
        }
        free(loopMissile);
    }
}

// this function scans through all the cars in game and compares their coordinates with the one of the player to identify if there is an impact (car driving over player)
void checkCarsImpactPlayer(pPlayer player, pCarList carList){
    if(carList->firstCar !=NULL){ // if there's at least one car in the list, perform the scan. Otherwise, do nothing
        // creating a temporary car to scan through the list of all cars
        pCar loopCar;
        loopCar = (pCar) malloc(sizeof(struct car));
        loopCar = carList->firstCar;
        
        int x = player->pos_x;
        int y = player->pos_y;
        bool impactX = false;
        bool impactY = false;
        
        while(loopCar != NULL){
            // the car is 4 times as long as the player
            if( (loopCar->pos_x >= x-3) && (loopCar->pos_x <= x) ){
                impactX = true;
            }
            
            // the car is twice as wide as the player
            if( (loopCar->pos_y >= y-1) && (loopCar->pos_y <= y) ){
                impactY = true;
            }
            
            // if both x and y coordinates indicate an impact, the car is deactivated (the player's bike is very though !!) and the function player_loose_health() is called to reduce the health points of the player
            if(impactX && impactY){
                loopCar->carActive = false;
                player_loose_health(player);
            }
            
            // resetting the values for the next car
            impactX = false;
            impactY = false;
            
            loopCar = loopCar->nextCar;
        }
        free(loopCar);
    }
}

// this function scans through all the obstacles in game and compares their coordinates with the one of the player to identify if there is an impact (player cycling over obstacle)
void checkObstaclesImpactPlayer(pPlayer player, pObstacleList obstacleList){
    if(obstacleList->firstObstacle !=NULL){ // if there's at least one obstacle in the list, perform the scan. Otherwise, do nothing
        // creating a temporary obstacle to scan through the list of all obstacles
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = obstacleList->firstObstacle;
        
        int x, y;
        bool impactX = false;
        bool impactY = false;
        
        while(loop != NULL){
            x = player->pos_x;
            y = player->pos_y;
            // the obstacle is twice as long as the player
            if( (loop->pos_x >= x-1) && (loop->pos_x <= x) ){
                impactX = true;
            }
            
            // the obstacle is twice as wide as the player
            if( (loop->pos_y >= y-1) && (loop->pos_y <= y) ){
                impactY = true;
            }
            
            // if both x and y coordinates indicate an impact, the function player_loose_health() is called to reduce the health points of the player. The obstacle is NOT deactivated and the player is pushed aside
            if(impactX && impactY){
                player_loose_health(player);
                
                if(player->pos_y > (WINDOW_SIZE_Y - 12) ){ //if the player is too close to the right border of the screen, it will be moved by the obstacle on the left
                    player->pos_y = loop->pos_y-1;
                }
                else{ // else, the player is moved on the right
                    player->pos_y = loop->pos_y+2;
                }
            }
            
            // resetting the values for the next car
            impactX = false;
            impactY = false;
            
            loop = loop->nextObstacle;
        }
        free(loop);
    }
}

// this function scans through all the bonuses in game and compares their coordinates with the one of the player to identify if there is an impact (player cycling over obstacle)
void checkBonusesImpactPlayer(pPlayer player, pBonusList bonusList){
    if(bonusList->firstBonus !=NULL){ // if there's at least one bonus in the list, perform the scan. Otherwise, do nothing
        // creating a temporary bonus to scan through the list of all bonuses
        pBonus loop;
        loop = (pBonus) malloc(sizeof(struct bonus));
        loop = bonusList->firstBonus;
        
        int x = player->pos_x;
        int y = player->pos_y;
        bool impactX = false;
        bool impactY = false;
        
        while(loop != NULL){
            // the bonus has the same length as the player
            if(loop->pos_x == x){
                impactX = true;
            }
            
            // the bonus has the same width as the player
            if(loop->pos_y == y){
                impactY = true;
            }
            
            // if both x and y coordinates indicate an impact, the function apply_bonus() is called to impact the player with the benefits of the bonus
            if(impactX && impactY){
                loop->bonusActive = false;
                apply_bonus(player, loop);
            }
            
            // resetting the values for the next car
            impactX = false;
            impactY = false;
            
            loop = loop->nextBonus;
        }
        free(loop);
    }
}

// This function scans through all the bonuses and all the cars to identify if there is an impact. In case a car hits a bonus, the bonus is destroyed, the car gains 1HP and fires a new missile
void checkCarsImpactBonuses(pCarList carList, pBonusList bonusList){
    if (carList->firstCar != NULL && bonusList->firstBonus != NULL){ // if there is at least one car AND one bonus start checking for impacts. Else, do nothing.
        
        // creating 2 temp structures to loop through the whole list of cars and bonuses
        pCar loopCar;
        loopCar = (pCar) malloc(sizeof(struct car));
        loopCar = carList->firstCar;
        
        pBonus loopBonus;
        loopBonus = (pBonus) malloc(sizeof(struct bonus));
        
        bool impactX = false;
        bool impactY = false;
    
        while(loopCar != NULL){ // as long as we did not go through the whole list of cars, check for impacts on bonuses
            loopBonus = bonusList->firstBonus;
            while(loopBonus != NULL){
                // the car is 4 times as long as the bonus
                if( (loopCar->pos_x >= loopBonus->pos_x-3) && (loopCar->pos_x <= loopBonus->pos_x) ){
                    impactX = true;
                }
                
                // the car is twice as wide as the bonus
                if( (loopCar->pos_y >= loopBonus->pos_y-1) && (loopCar->pos_y <= loopBonus->pos_y) ){
                    impactY = true;
                }
                
                // in case of impact, the bonus is destroyed and the car gains one health point + fires a missile
                if(impactX && impactY){
                    loopBonus->bonusActive = false;
                    loopCar->healthPoints++;
                    createMissileFromCar(loopCar);
                    printf("The car used the bonus!\n");
                }
                //move to the next bonus and reset the impactX and impactY to false
                loopBonus = loopBonus->nextBonus;
                impactX = false;
                impactY = false;
            }
            loopCar = loopCar->nextCar;
        }
        free(loopCar);
        free(loopBonus);
    }
}

// This function scans through all the bonuses and all the missiles to identify if there is an impact. In case a missile shot from a car hits a bonus, the bonus is destroyed
void checkMissilesImpactBonuses(pMissileList missileList, pBonusList bonusList){
    if (missileList->firstMissile != NULL && bonusList->firstBonus != NULL){ // if there is at least one missile AND one bonus start checking for impacts. Else, do nothing.
        
        // creating 2 temp structures to loop through the whole list of missiles and bonuses
        pMissile loopMissile;
        loopMissile = (pMissile) malloc(sizeof(struct missile));
        loopMissile = missileList->firstMissile;
        
        pBonus loopBonus;
        loopBonus = (pBonus) malloc(sizeof(struct bonus));
        
        bool impactX = false;
        bool impactY = false;
    
        while(loopMissile != NULL){ // as long as we did not go through the whole list of missiles, check for impacts on bonuses
            if(loopMissile->missileFromPlayer==false){ // only check if the missile was shot from a car (missileFromPlayer=False)
                loopBonus = bonusList->firstBonus;
                while(loopBonus != NULL){
                    // the missile is twice as small as the bonus
                    if( (loopMissile->pos_x >= (loopBonus->pos_x *2))  && (loopMissile->pos_x <= (loopBonus->pos_x *2)+1) ){
                        impactX = true;
                    }
                
                    // the missile is twice as small as the bonus
                    if( (loopMissile->pos_y >= (loopBonus->pos_y *2))  && (loopMissile->pos_y <= (loopBonus->pos_y *2)+1) ){
                        impactY = true;
                    }
                
                    // in case of impact, the bonus is destroyed
                    if(impactX && impactY){
                        loopBonus->bonusActive = false;
                        printf("The missile destroyed the bonus!\n");
                    }
                    //move to the next bonus and reset the impactX and impactY to false
                    loopBonus = loopBonus->nextBonus;
                    impactX = false;
                    impactY = false;
                }
            }
            loopMissile = loopMissile->nextMissile;
        }
        free(loopMissile);
        free(loopBonus);
    }
}
