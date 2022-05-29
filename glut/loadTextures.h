#ifndef _LOADTEXTURES_H_
#define _LOADTEXTURES_H_

#include <stdbool.h>
// Include for all images to be used in the various menus and titles
#include "screenshot.c"
#include "backHome.c"
#include "highScores.c"
#include "homeTitle.c"
#include "loadGame.c"
#include "loadTitle.c"
#include "newGame.c"
#include "options.c"
#include "optionsTitle.c"
#include "optionsContent.c"
#include "quitGame.c"
#include "resumeGame.c"
#include "scoresTitle.c"

// include for all textures to be used in game
#include "game_plant1.c"
#include "game_plant2.c"
#include "game_plant3.c"
#include "game_car.c"
#include "game_hp3.c"
#include "game_hp2.c"
#include "game_hp1.c"
#include "game_hp0.c"
#include "game_bonus.c"
#include "game_obstacle.c"
#include "game_player.c"
#include "game_pause.c"

/* ##############################
The following mapping table between the .c files for the textures and the the image number will be used to simplify the load of all the textures at the initialization of the game + in drawScreen.c to bind a texture to a shape on screen
 
 image_id >> name of .c file
 image_0  >> screenshot.c
 image_1  >> homeTitle.c
 image_2  >> loadTitle.c
 image_3  >> optionsTitle.c
 image_4  >> scoresTitle.c
 image_5  >> newGame.c
 image_6  >> loadGame.c
 image_7  >> options.c
 image_8  >> highScores.c
 image_9  >> quitGame.c
 image_10 >> resumeGame.c
 image_11 >> backHome.c
 image_12 >> optionsContent.c

 image_13 >> game_pause.c
 image_14 >> game_player.c
 image_15 >> game_car.c
 image_16 >> game_hp0.c
 image_17 >> game_hp1.c
 image_18 >> game_hp2.c
 image_19 >> game_hp3.c
 image_20 >> game_plant1.c
 image_21 >> game_plant2.c
 image_22 >> game_plant3.c
 image_23 >> game_bonus.c
 image_24 >> game_obstacle.c
 
###############################*/

// This function is used to load one texture and to bind it to an id
void loadTexture(GLuint tex_id, unsigned int bytes_per_pixel, unsigned int width, unsigned int height, unsigned const char *pixel_data);

// This function is used to load all the textures that will be needed throughout the application. It is called once when launching the program
void loadAllTextures(GLuint *tex_ids);


#endif
