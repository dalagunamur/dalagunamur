#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdbool.h>
#include "bonus.h"

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

pPlayer p; // This global variable p is used to represent to player across the program
int maxNbrMissilesPlayer; // this global variable will store the maximum number of missiles from the player that can be displayed on screen. By default it will be 10, but can be increased via bonuses

pPlayer createPlayer(); // this function creates the player. It is initialized at the beginning of the game
void move_player_up(char **map); // this function moves the player up by one row, unless if reaching the highest row
void move_player_down(char **map); // this function moves the player down by one row, unless if reaching the lowest row
void move_player_left(char **map); // this function moves the player left by one column, unless if reaching the left side of the road
void move_player_right(char **map); // this function moves the player right by one column, unless if reaching the right side of the road
void player_loose_health(pPlayer player); // this function is used to reduce the health points count of the player. If it reaches 0, the game ends
void apply_bonus(pPlayer player, pBonus bonus); // player has hit a bonus and either regains some health or can fire more missiles

#endif
