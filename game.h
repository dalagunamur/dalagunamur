#ifndef _GAME_H_
#define _GAME_H_
#define DIFFICULTY 123 // this value will be used as a multiplying factor to control the pace at which the difficulty level will change
typedef struct game{
     int timer;
int score;
enum scrolling_pattern={vertical,horizontal}; map_t *first_map;
car_t *first_car;
missile_t *first_missile;
bonus_t *first_bonus;
} game_t;
game_t create_game(); // initialize a new game or load an existing game
void play(); // this function drives the various sequences of the game
void diplay_pause(); // when the players pauses the game, allows to save or exit or resume
void set_scrolling_pace(int timer);
void save_game();
#endif
