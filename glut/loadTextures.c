#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "loadTextures.h"

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

// This function is used to load one texture and to bind it to an id. The following arguments are used: tex_id is the name of an already created texture id, and image is a pointer to the texture image to load for the corresponding texture id
void loadTexture(GLuint tex_id, unsigned int bytes_per_pixel, unsigned int width, unsigned int height, unsigned const char *pixel_data) {

    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    gluBuild2DMipmaps(GL_TEXTURE_2D, bytes_per_pixel,
                      width, height, GL_RGB, GL_UNSIGNED_BYTE,
                      pixel_data );
}


// This function is used to load all the textures that will be needed throughout the application. It is called once when launching the program.
// number_of_textures is used to loop the correct number of times, tex_ids is a pointer to already alocated array of GLuint of size number_of_textures and images is a pointer to array of images to load as texture
void loadAllTextures(GLuint *tex_ids) {
    glGenTextures(25, tex_ids);
    
    loadTexture(tex_ids[0], image_0.bytes_per_pixel, image_0.width, image_0.height, image_0.pixel_data);
    loadTexture(tex_ids[1], image_1.bytes_per_pixel, image_1.width, image_1.height, image_1.pixel_data);
    loadTexture(tex_ids[2], image_2.bytes_per_pixel, image_2.width, image_2.height, image_2.pixel_data);
    loadTexture(tex_ids[3], image_3.bytes_per_pixel, image_3.width, image_3.height, image_3.pixel_data);
    loadTexture(tex_ids[4], image_4.bytes_per_pixel, image_4.width, image_4.height, image_4.pixel_data);
    loadTexture(tex_ids[5], image_5.bytes_per_pixel, image_5.width, image_5.height, image_5.pixel_data);
    loadTexture(tex_ids[6], image_6.bytes_per_pixel, image_6.width, image_6.height, image_6.pixel_data);
    loadTexture(tex_ids[7], image_7.bytes_per_pixel, image_7.width, image_7.height, image_7.pixel_data);
    loadTexture(tex_ids[8], image_8.bytes_per_pixel, image_8.width, image_8.height, image_8.pixel_data);
    loadTexture(tex_ids[9], image_9.bytes_per_pixel, image_9.width, image_9.height, image_9.pixel_data);
    loadTexture(tex_ids[10], image_10.bytes_per_pixel, image_10.width, image_10.height, image_10.pixel_data);
    loadTexture(tex_ids[11], image_11.bytes_per_pixel, image_11.width, image_11.height, image_11.pixel_data);
    loadTexture(tex_ids[12], image_12.bytes_per_pixel, image_12.width, image_12.height, image_12.pixel_data);
    loadTexture(tex_ids[13], image_13.bytes_per_pixel, image_13.width, image_13.height, image_13.pixel_data);
    loadTexture(tex_ids[14], image_14.bytes_per_pixel, image_14.width, image_14.height, image_14.pixel_data);
    loadTexture(tex_ids[15], image_15.bytes_per_pixel, image_15.width, image_15.height, image_15.pixel_data);
    loadTexture(tex_ids[16], image_16.bytes_per_pixel, image_16.width, image_16.height, image_16.pixel_data);
    loadTexture(tex_ids[17], image_17.bytes_per_pixel, image_17.width, image_17.height, image_17.pixel_data);
    loadTexture(tex_ids[18], image_18.bytes_per_pixel, image_18.width, image_18.height, image_18.pixel_data);
    loadTexture(tex_ids[19], image_19.bytes_per_pixel, image_19.width, image_19.height, image_19.pixel_data);
    loadTexture(tex_ids[20], image_20.bytes_per_pixel, image_20.width, image_20.height, image_20.pixel_data);
    loadTexture(tex_ids[21], image_21.bytes_per_pixel, image_21.width, image_21.height, image_21.pixel_data);
    loadTexture(tex_ids[22], image_22.bytes_per_pixel, image_22.width, image_22.height, image_22.pixel_data);
    loadTexture(tex_ids[23], image_23.bytes_per_pixel, image_23.width, image_23.height, image_23.pixel_data);
    loadTexture(tex_ids[24], image_24.bytes_per_pixel, image_24.width, image_24.height, image_24.pixel_data);
}
