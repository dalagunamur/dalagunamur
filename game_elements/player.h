#ifndef _PLAYER_H_
#define _PLAYER_H_

#define COOLDOWN 100 // cooldown period during which the alternate weapon will not be available anymore

struct player{
    int pos_x;
    int pos_y;
    int health_points;
    bool alt_weapon_available; // the usage of the secondary weapon will only be possible after a defined cooldown
};

typedef struct player * pPlayer;


void move_player();
void player_fires(); // fire the main weapon
void player_fires_alt(); // fire the alternate weapon
void player_collision(); // obstacle or car hits player
void apply_bonus(); // player hits a bonus
void player_loose_health();

#endif
