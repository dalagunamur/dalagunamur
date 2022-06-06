#ifndef _BONUS_H_
#define _BONUS_H_

#include <stdbool.h>

struct bonus{
    float pos_x;
    float pos_y;
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

// this function is called each time a new bonus is created by the game, and returns a newly created bonus. When creating a new bonus in game, the value loadedBonus is set to 0 and the other attributes are 0 as well. When the value loadedBonus is set to 1, then it means the bonus is created while loading a saved game; the other attributes then store the coordinates x, y of the bonus, its active status and the information about the type of bonus.
pBonus createBonus(int loadedBonus, float x, float y, int active, int health, int missile);

pBonusList createListBonuses(void); // this function returns a newly created list of bonuses. This function is called at the beginning of the game, for initialization
void addBonus(pBonusList list, pBonus newBonus); // this function adds a newly created bonus to the list of all bonuses, as new head of the list
void destroyBonuses(pBonusList list); // this function removes from the game all inactive bonuses. A bonus becomes inactive if it reaches the end of the map, if it is taken by the player or if it is destroyed by a car or a car missile
void moveBonuses(pBonusList list); // this function moves all the bonuses created in the game and flags them as inactive when scrolling out of the map. The bonuses actually do not move, they simply follow the scrolling of the map.
void setInactiveAllBonuses(pBonusList list); // this function sets all active bonuses as inactive. It is called along with the destroyBonuses() function when killing a game.


#endif
