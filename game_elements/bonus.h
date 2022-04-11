#ifndef _BONUS_H_
#define _BONUS_H_

#include <stdbool.h>

struct bonus{
    int pos_x;
    int pos_y;
    bool bonusActive; // true when the bonus has to be displayed on screen. Becomes false when it leaves the screen or is taken by the player
    bool typeHealth; // type health = recuperate one lost health point
    bool typeMissile; // type missile = max number of missiles is increased by 2 units
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

pBonusList createListBonuses(void); // this function returns a newly created list of bonuses. This function is called at the beginning of the game, for initialization
pBonus createBonus(void); // to create a new instance of a bonus
void addBonus(pBonusList list, pBonus newBonus); // this function adds a newly created bonus to the list of all bonuses, as new head of the list
void destroyBonuses(pBonusList list); // this function removes from the game all inactive bonuses. A bonus becomes inactive if it reaches the end of the map, if it is taken by the player or if it is destroyed by a car or a car missile
void moveBonuses(pBonusList list); // this function moves all the bonuses created in the game and flags them as inactive when scrolling out of the map. The bonuses actually do not move, they simply follow the scrolling of the map.

void glutCreateBonus(int timer); // this function periodically calls the function createBonus() to create a new bonus
void glutDestroyBonuses(int timer); // this function periodically calls the function to remove from the game all the inactive bonuses (callback via glutTimerFunc())

#endif
