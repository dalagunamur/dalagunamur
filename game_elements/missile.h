#ifndef _MISSILE_H_
#define _MISSILE_H_

struct missile{
    int pos_x;
    int pos_y;
    int speed;
    enum direction {up,down,right,left};
    struct missile *next_element;
};

typedef struct missile * pMissile;

pMissile create_missile(void); // to create a new instance of a missile void move_missile(missile_t *missile);
void destroy_missile(pMissile missile);

#endif
