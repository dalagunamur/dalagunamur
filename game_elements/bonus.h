#ifndef _BONUS_H_
#define _BONUS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct bonus{
    int pos_x;
    int pos_y;
    bool bonusActive; // true when the bonus has to be displayed on screen. Becomes false when it leaves the screen or is taken by the player
//     enum type {health, shield}; //will be defined at a later stage
    struct bonus * previousBonus;
    struct bonus * nextBonus;
};

typedef struct bonus * pBonus;

struct bonusList{
    int bonusCounter;
    pBonus firstBonus;
    pBonus lastBonus;
};

//pBonusList points to bonusList
typedef struct bonusList * pBonusList;

pBonusList listOfBonuses; // this global variable is used to store the list of the bonuses.

pBonus create_bonus(void); // to create a new instance of a bonus
void destroy_bonus(pBonus bonus);

#endif
