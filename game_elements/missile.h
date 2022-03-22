#ifndef _MISSILE_H_
#define _MISSILE_H_
typedef struct missile{
     int pos_x;
int pos_y;
Page 12 sur 14
IHDCB132 – Rapport phase 1 David Laguesse
int speed;
enum direction={up,down,right,left}; missile_t *next_element;
} missile_t;
missile_t create_missile(); // to create a new instance of a missile void move_missile(missile_t *missile);
void destroy_missile(missile_t *missile);
#endif
