#ifndef _BONUS_H_
#define _BONUS_H_
typedef struct bonus{
     int pos_x;
     int pos_y;
enum type {}; //will be defined at a later stage
     bonus_t *next_element;
} bonus_t;
bonus_t create_bonus(); // to create a new instance of a bonus
void destroy_bonus(bonus_t *bonus);
#endif
