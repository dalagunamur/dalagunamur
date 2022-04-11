#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "player.h"
#include "../map/map.h"
#include "../game.h"
#include "bonus.h"

// this function returns the player, initializing its position on the map
pPlayer createPlayer(){
    pPlayer p;
    p = (pPlayer) malloc (sizeof(struct player));
    p->pos_x = 38;
    p->pos_y = 30;
    p->health_points = 3;
    p->alt_weapon_available = true;
    
    return p;
}

// this function moves the player up by one row, unless he's trying to access one of the top ten rows
void move_player_up(char **map){
    int x = 0;
    
    x = p->pos_x - 1;
            
    if (x > 10){
        p->pos_x = x;
    }
}

//this function moves the player down by one row, unless he's trying to access the last row
void move_player_down(char **map){
    int x = 0;
    
    x = p->pos_x + 1;
         
    if (x < (WINDOW_SIZE_X -1) ){ //(*(*(map + x) + y)!='#') &&
        p->pos_x = x;
    }
}

// this function moves the player left by one column, unless he's trying to go out of the road
void move_player_left(char **map){
    int x = 0, y = 0;
    
    x = p->pos_x;
    y = p->pos_y - 1;
         
    if (*(*(map + x) + y)!='#'){
        p->pos_y = y;
    }
}

// this function moves the player right by one column, unless he's trying to go out of the road
void move_player_right(char **map){
    int x = 0, y = 0;
    x = p->pos_x;
    y = p->pos_y + 1;
         
    if (*(*(map + x) + y)!='#'){
        p->pos_y = y;
    }
}

// This function is used to reduce the health points count of the player. If the HP drop to 0, the player has lost and the game ends
void player_loose_health(pPlayer player){
    player->health_points --;
    printf("\n!! PLAYER HAS BEEN HIT !! - %i HP remaining\n",player->health_points);
    
    if (player->health_points <= 0){
        printf("\nGAME OVER\n");
        printf("Final time: %i\n",theGame->timer);
        printf("Final score: %i\n",theGame->score);
        exit(0);
    }
}

// This function is used to apply a bonus to the player. A bonus can heal one lost health point or allow to fire some extra missiles, or both
void apply_bonus(pPlayer player, pBonus bonus){
    // if the bonus has the type health, it can grant back one hp to the player
    if(bonus->typeHealth == true){
        if(player->health_points < 3){
            player->health_points ++;
            printf("Bonus heals 1 HP - %i HP remaining\n",player->health_points);
        }
        else{
            printf("Max HP already - %i HP remaining\n",player->health_points);
        }
    }
    
    // if the bonus has the type missile, it increases the max number of missiles that can be shot
    if(bonus->typeMissile == true){
        maxNbrMissilesPlayer = maxNbrMissilesPlayer +2;
        printf("Bonus grants new missiles - Max nbr now %i\n",maxNbrMissilesPlayer);
    }
}
