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
#include <string.h>
#include <time.h>

#include "player.h"
//#include "../map/map.h"

pPlayer createPlayer(){
    pPlayer p;
    p = (pPlayer) malloc (sizeof(struct player));
    p->pos_x = 38;
    p->pos_y = 30;
    p->health_points = 3;
    p->alt_weapon_available = true;
    
    return p;
}

void move_player_up(char **map){
    int x = 0, y = 0;
    
    x = p->pos_x - 1;
    y = p->pos_y;
         
    if ( (*(*(map + x) + y)!='#') && (x > 10) ){
        p->pos_x = x;
    }
}

void move_player_down(char **map){
    int x = 0, y = 0;
    
    x = p->pos_x + 1;
    y = p->pos_y;
         
    if ( (*(*(map + x) + y)!='#')  && (x < 39) ){
        p->pos_x = x;
    }
}

void move_player_left(char **map){
    int x = 0, y = 0;
    
    x = p->pos_x;
    y = p->pos_y - 1;
         
    if (*(*(map + x) + y)!='#'){
        p->pos_y = y;
    }
}

void move_player_right(char **map){
    int x = 0, y = 0;
    x = p->pos_x;
    y = p->pos_y + 1;
         
    if (*(*(map + x) + y)!='#'){
        p->pos_y = y;
    }
}

void player_fires(); // fire the main weapon
void player_fires_alt(); // fire the alternate weapon
void player_collision(); // obstacle or car hits player
void apply_bonus(); // player hits a bonus
void player_loose_health();

