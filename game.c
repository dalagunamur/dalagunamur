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
#include "menu.h"
#include "scores.h"

/*
 INFORMATION ABOUT GLUT TIMERS
 0 = handles all the movements of map, obstacles, bonuses, cars and missiles, as well as the check of collision and destruction of inactive elements
 1 = handles the creation of new items, ie cars, bonuses, obstacles and missiles shot by cars
 */

// These variables are assigned to store the action that was requested based on the keystroke, then read to trigger to right function corresponding to the action requested by the player
bool MOVE_UP = false;
bool MOVE_DOWN = false;
bool MOVE_LEFT = false;
bool MOVE_RIGHT = false;
bool FIRE_MISSILE = false;
bool GO_TO_MAIN = false;

// THis variable will be used to indicate that the game is paused or is over and that no movements are allowed.
bool PAUSED_GAME = false;
bool GAME_OVER = false;

// this array contains the ids of all the textures used in the application
extern GLuint textures[25];

pGame createGame(void){
    pGame game;
    game = (pGame) malloc (sizeof(struct game));

    game->timer = 0;
    game->score = 0;
    game->difficulty = 0;
    game->verticalScrolling = true; // by default, will be set to True meaning the screen will scroll vertically. In a future version, if set to false, the screen will scroll horizontally, from the right to the left
    
    // intializing both counterTimers that will be used by the glut call back functions.
    counterTimer0 = 0;
    counterTimer1 = 0;
    
    return game;
}

// This function is called each time the player hits a key on the keyboard. In case the key pressed is one which is assigned a function, it records it
void handleKeyboard(unsigned char input, int x, int y){
    switch(input)
        {
            case 'z':
                if(PAUSED_GAME == false && GAME_OVER == false) MOVE_UP = true;
                break;
            case 's':
                if(PAUSED_GAME == false && GAME_OVER == false) MOVE_DOWN = true;
                break;
            case 'q':
                if(PAUSED_GAME == false && GAME_OVER == false) MOVE_LEFT = true;
                break;
            case 'd':
                if(PAUSED_GAME == false && GAME_OVER == false) MOVE_RIGHT = true;
                break;
            case 32: // when hitting the space bar
                if(PAUSED_GAME == false && GAME_OVER == false) FIRE_MISSILE = true;
                break;
            case 'p': // Pauses the game if it was running, unpause the game otherwise
                if(PAUSED_GAME == false && GAME_OVER == false){
                    PAUSED_GAME = true;
                }
                else if(PAUSED_GAME == true && GAME_OVER == false){
                    PAUSED_GAME = false;
                }
                break;
            case 27: // when hitting the ESCAPE key, when in pause mode or game over mode, allows to leave the game
                if(PAUSED_GAME == true || GAME_OVER == true) exit(0);
                break;
            case 'h':
                if(PAUSED_GAME == true || GAME_OVER == true) GO_TO_MAIN = true;
                break;
        }
}

// This function drives the game, by requesting to draw the map on screen; then the cars, then the players and the missiles.
// It also call the function to capture the key pressed by the player on the keyboard and handles the movements of the player.
void play(pGame game, char **map, pPlayer p, pCarList carList, pMissileList missileList, pObstacleList obstacleList, pBonusList bonusList){
    drawMap();  //display the map on screen
    drawBlankSpaceForScore(); // display a green empty square to serve as background for the score and max number of missiles
    drawObstacles(obstacleList); // display all the obstacles on the screen
    drawBonuses(bonusList); // display all the bonuses on the screen
    drawCars(carList); //display all the ennemies
    drawPlayer(p); //display the player
    drawMissiles(missileList); //display all the missiles
    drawHealth(p); // display the current level of health
    drawScore(game); // display the current score and the maximum number of missiles the player can currently shoot
    if(PAUSED_GAME) displayPause(); // if the game is paused, display the paused menu. Else do nothing.
    if(GAME_OVER) displayGameOver(game); // if the game is over, display the game over screen. Else do nothing.
    
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
    if (GO_TO_MAIN){
        GO_TO_MAIN = false;
        glutHideWindow(); // hides the current window, ie the game page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_home(); // calls the function to display the home page
        
    }
    if(PAUSED_GAME == false && GAME_OVER == false){ // increase the score and the timer only when the game is not paused and not game over
        game->timer++;
        if( game->timer % 100 ==0) game->score++; // increase the score each time the timer increases by 100
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
    // we must take into account that the square size of a car is twice as much as the one of a missile + that a car has in total the length of 12 missiles
    if( (missile->pos_x >= x*2) && (missile->pos_x <= (x*2)+11) ){
        impactX = true;
    }
    
    // we must take into account that the square size of a car is twice as much as the one of a missile + that a car has in total the width of 6 missiles
    if( (missile->pos_y >= y*2) && (missile->pos_y <= (y*2)+5) ){
        impactY = true;
    }
    
    // if both x and y coordinates indicate an impact, the missile is deactivated + the function carHit() is called
    if(impactX && impactY){
        missile->missileActive = false;
        carHit(car);
        theGame->score += 2; // hitting a car increases the score by 2 points
    }
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
                // the vertical size of the player on the screen is 4 times that of a missile, this impacts the check on the coordinates
                if( (loopMissile->pos_x >= x*2) && (loopMissile->pos_x <= (x*2)+3) ){
                    impactX = true;
                }
                
                // the size of the player on the screen is twice that of a missile, this impacts the check on the coordinates
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
            // the car is 3 times as long as the player (car length=6, player length = 2)
            if( (loopCar->pos_x >= x-5) && (loopCar->pos_x <= x +1) ){
                impactX = true;
            }
            
            // the car is 3 times as wide as the player
            if( (loopCar->pos_y >= y-2) && (loopCar->pos_y <= y) ){
                impactY = true;
            }
            
            // if both x and y coordinates indicate an impact, the car is deactivated (the player's bike is very though !!) and the function player_loose_health() is called to reduce the health points of the player
            if(impactX && impactY){
                loopCar->carActive = false;
                player_loose_health(player);
                theGame->score -= 1; // being driven over by a car reduces the score by 1 point
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
            // the obstacle is as long as the player
            if( (loop->pos_x >= x-1) && (loop->pos_x <= x +1) ){
                impactX = true;
            }
            
            // the obstacle is twice as wide as the player
            if( (loop->pos_y >= y-1) && (loop->pos_y <= y) ){
                impactY = true;
            }
            
            // if both x and y coordinates indicate an impact, the function player_loose_health() is called to reduce the health points of the player. The obstacle is NOT deactivated and the player is pushed aside
            if(impactX && impactY){
                player_loose_health(player);
                theGame->score -= 2; // driving over an obstacle reduces the score by 2 points
                
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
            // the player is twice has long as a bonus
            if( (x >= loop->pos_x-1) && (x <= loop->pos_x) ){
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
                theGame->score += 5; // driving over a bonus increases the score by 5 points
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
                // the car is 6 times as long as the bonus
                if( (loopCar->pos_x >= loopBonus->pos_x-5) && (loopCar->pos_x <= loopBonus->pos_x) ){
                    impactX = true;
                }
                
                // the car is 3 times as wide as the bonus
                if( (loopCar->pos_y >= loopBonus->pos_y-2) && (loopCar->pos_y <= loopBonus->pos_y) ){
                    impactY = true;
                }
                
                // in case of impact, the bonus is destroyed and the car gains one health point + fires a missile
                if(impactX && impactY){
                    loopBonus->bonusActive = false;
                    loopCar->healthPoints++;
                    createMissileFromCar(loopCar);
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

// this function centralizes the creation of elements in the game, cars, missiles, obstacles and bonuses. It will be assigned the timer nbr 1
void glutCreateElements(int timer){
    // only perform these checks if the game is NOT paused and NOT game over
    if(!PAUSED_GAME && !GAME_OVER){
      
        // every run of the glutCreateElements function, create a new missile (if there are cars already)
        if(listOfCars->carCounter > 0){
            // identify randomly one car that will shoot the missile
            int i = rand() % listOfCars->carCounter;
            int j = 0;
            pCar loop;
            loop = (pCar) malloc(sizeof(struct car));
            loop = listOfCars->firstCar;
        
            while(j != i){
                loop = loop->nextCar;
                j++;
            }
            // create a new missile and shoot it from the identified car
            pMissile newMissile = createMissileFromCar(loop);
            addMissile(listOfMissiles, newMissile);
        }
        
        // every 2 runs of the glutCreateElements function, create a new car
        if(counterTimer1 %  2 == 0){
            pCar newCar = createCar();
            addCar(listOfCars, newCar);
        }
            
        // once every 4 runs of the glutCreateElements function, create a new obstacle
        if(counterTimer1 %  4 == 0){
            pObstacle newObstacle = createObstacle();
            addObstacle(listOfObstacles, newObstacle);
        }
        
        
        // once every 6 runs of the glutCreateElements function, create a new obstacle
        if(counterTimer1 %  6 == 0){
            pBonus newBonus = createBonus();
            addBonus(listOfBonuses, newBonus);
        }
    
    }
    
    counterTimer1 ++;
    glutPostRedisplay();
    glutTimerFunc(90000/SCREEN_FPS, glutCreateElements, 1); // runs every 4 seconds
}



// this function centralizes the movements of all elements (except the player), the check for collisions and the destruction of inactive elements
void glutAnimateElements(int timer){
    // only perform these checks if the game is NOT paused and NOT game over
    if(!PAUSED_GAME && !GAME_OVER){
        // every run of the glutAnimateElements function, check for impacts and destroy any inactive car, bonus, missile or obstacle
        checkImpactCars(listOfCars, listOfMissiles); // checks if missiles shot by the player hit a car
        checkMissileImpactsPlayer(p, listOfMissiles); // checks if missiles shot by cars hit the player
        checkCarsImpactPlayer(p,listOfCars); // checks if cars hit the player
        checkObstaclesImpactPlayer(p, listOfObstacles); // checks if the player hits an obstacle
        checkBonusesImpactPlayer(p, listOfBonuses); // checks if the player collects a bonus
        checkCarsImpactBonuses(listOfCars, listOfBonuses); // checks if cars hit a bonus
        checkMissilesImpactBonuses(listOfMissiles, listOfBonuses); // check if missiles shot from the cars hit a bonus
        
        destroyBonuses(listOfBonuses);
        destroyCars(listOfCars);
        destroyMissiles(listOfMissiles);
        destroyObstacles(listOfObstacles);

        // once every 12 runs of the glutAnimateElements function, move the maps and the obstacles
        if(counterTimer0 %  10 == 0){
            free(mapToRender);
            deleteRow(map);
            listMap row;
            row = createRow();
            map = addRow(map,row);
            displayMap(map);
            moveBonuses(listOfBonuses);
            moveObstacles(listOfObstacles);
        }
        
        // once every 2 runs of the glutAnimateElements function, move the cars
        if(counterTimer0 %  2 == 0){
            moveCars(listOfCars);
        }
        
        // once every 1 runs of the glutAnimateElements function, move the missiles
        if(counterTimer0 %  1 == 0){
            moveMissiles(listOfMissiles);
        }

    }
    
    counterTimer0 ++;
    glutPostRedisplay();
    glutTimerFunc(1020/SCREEN_FPS, glutAnimateElements, 0);
}

// this function is used to reset all the elements of the game to their initial value
void killGame(void){
    free(mapToRender);
    free(p);
    free(listOfCars);
    free(listOfMissiles);
    free(listOfObstacles);
    free(listOfBonuses);
    free(theGame);
    maxNbrMissilesPlayer = 10; // initially
}
