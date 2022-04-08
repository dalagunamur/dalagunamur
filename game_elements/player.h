#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COOLDOWN 100 // cooldown period during which the alternate weapon will not be available anymore

// this structure is used to capture the key attributes of the player
struct player{
    int pos_x;
    int pos_y;
    int health_points;
    bool alt_weapon_available; // the usage of the secondary weapon will only be possible after a defined cooldown
};

// pPlayer points to an element of structure player
typedef struct player * pPlayer;

// This global variable p is used to represent to player across the program
pPlayer p;

pPlayer createPlayer(); // this function creates the player. It is initialized at the beginning of the game
void move_player_up(char **map); // this function moves the player up by one row, unless if reaching the highest row
void move_player_down(char **map); // this function moves the player down by one row, unless if reaching the lowest row
void move_player_left(char **map); // this function moves the player left by one column, unless if reaching the left side of the road
void move_player_right(char **map); // this function moves the player right by one column, unless if reaching the right side of the road


// NOT IMPLEMENTED YET
void player_fires(); // fire the main weapon
void player_fires_alt(); // fire the alternate weapon
void player_collision(); // obstacle or car hits player
void apply_bonus(); // player hits a bonus
void player_loose_health();

#endif
