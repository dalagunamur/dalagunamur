#ifndef _BONUS_H_
#define _BONUS_H_

struct bonus{
     int pos_x;
     int pos_y;
     enum type {health, shield}; //will be defined at a later stage
     struct bonus *next_element;
};

typedef struct bonus * pBonus;

pBonus create_bonus(void); // to create a new instance of a bonus
void destroy_bonus(pBonus bonus);

#endif
