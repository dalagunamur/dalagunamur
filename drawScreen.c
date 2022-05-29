#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map/map.h"
#include "game_elements/player.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#include "drawScreen.h"
#include "game.h"
#include "glut/loadTextures.h"
#include "scores.h"


extern GLuint textures[25];

// This function is used to print text via GLUT. It receives a string to be printed and x and y coordinates to indicate where it should be printed out
void drawText(char *string, float x, float y){
    char *c;
    glRasterPos2f(x, y);
    for(c = string; *c!='\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

// This function draws the home page, with the various menu items displayed as boxes in the window
void drawHomePage(){
    
    // drawing the rectangle that will contain the name of the game
    

    glBindTexture(GL_TEXTURE_2D,textures[1]);
    glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
    
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(200,50,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(400.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(400.0f, 100.0f, 1.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 100.0f, 1.0f);
    glEnd();
    
// drawing the rectangle with the New Game menu item
    glBindTexture(GL_TEXTURE_2D,textures[5]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,250,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the Load Game menu item
    glBindTexture(GL_TEXTURE_2D,textures[6]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,350,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the Options menu item
    glBindTexture(GL_TEXTURE_2D,textures[7]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,450,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the High Scores menu item
    glBindTexture(GL_TEXTURE_2D,textures[8]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,550,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();

// drawing the rectangle with the Quit menu item
    glBindTexture(GL_TEXTURE_2D,textures[9]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,650,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the screenshot of the game, on the right hand side
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(300,250,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(450.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(450.0f, 450.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 450.0f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

/* *********************************************************** */

// This function draws the load game page, with the various menu items displayed as boxes in the window
void drawLoadPage(){
    
// drawing the rectangle that will contain the name of the window, "Load a game"
    
    glBindTexture(GL_TEXTURE_2D,textures[2]);
    glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(200,50,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(400.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(400.0f, 100.0f, 1.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 100.0f, 1.0f);
    glEnd();

// drawing the rectangle with the Resume Game menu item
    glBindTexture(GL_TEXTURE_2D,textures[10]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,350,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();

// drawing the rectangle with the Go Back to Home page menu item
    glBindTexture(GL_TEXTURE_2D,textures[11]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,550,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the screenshot of the game, on the right hand side
    glBindTexture(GL_TEXTURE_2D,textures[0]);
    glColor3f(0.1f,0.1f,0.1f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(300,250,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(450.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(450.0f, 450.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 450.0f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

/* *********************************************************** */

// This function draws the options page, with the various menu items displayed as boxes in the window
void drawOptionsPage(){
    
// drawing the rectangle that will contain the name of the window, "About the game"
    
    glBindTexture(GL_TEXTURE_2D,textures[3]);
    glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(200,50,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(400.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(400.0f, 100.0f, 1.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 100.0f, 1.0f);
    glEnd();

// drawing the rectangle with the Go Back to Home page menu item
    glBindTexture(GL_TEXTURE_2D,textures[11]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,650,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
// drawing the rectangle with the content of the page
    glBindTexture(GL_TEXTURE_2D,textures[12]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,250,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(700.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f);  glVertex3f(700.0f, 350.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f);  glVertex3f(0.0f, 350.0f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

/* *********************************************************** */

// This function draws the high scores page, with the various menu items displayed as boxes in the window
void drawScoresPage(pScoresList list){
    
    // drawing the rectangle that will contain the name of the window, "High scores"
    glBindTexture(GL_TEXTURE_2D,textures[4]);
    glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(200,50,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(400.0f, 0.0f, 1.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(400.0f, 100.0f, 1.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 100.0f, 1.0f);
    glEnd();

    // drawing the rectangle with the Go Back to Home page menu item
    glBindTexture(GL_TEXTURE_2D,textures[11]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,650,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
        
    // drawing the rectangle with the content of the page, the list of high scores
    glColor3f(0.1f,0.1f,0.1f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(50,250,0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(700.0f, 0.0f, 0.0f);
    glVertex3f(700.0f, 350.0f, 0.0f);
    glVertex3f(0.0f, 350.0f, 0.0f);
    glEnd();
    
    if (list->firstScore!= NULL ){ // if the list of all high scores is not empty, draw the high scores. If list is empty, do nothing
        
        pScore loop;
        loop = list->firstScore;
        char drawScore[25],drawTime[25],drawRank[25]; // temp variables will be used to store the score and time of the current score
        int i=1; // to give a rank to the scores
        
        while(loop != NULL){
            sprintf(drawRank, "RANK %d", i);
            sprintf(drawScore, "SCORE: %d", loop->score);
            sprintf(drawTime, "TIME: %d", loop->time);
            
            // Displaying text
            glColor3f(1.0f,1.0f,1.0f);
            drawText(drawRank, 100, (100+(i*15)));
            drawText(drawScore, 175, (100+(i*15)));
            drawText(drawTime, 250, (100+(i*15)));
            
            loop = loop->nextScore;
            i++;
        }
    }
    
}

/* *********************************************************** */

/*
 THE FUNCTIONS BELOW ARE ALL USED FOR THE DISPLAY OF THE GAME SCREEN
 */

// This function draws the player on the screen as a light blue square
void drawPlayer(pPlayer p){
    glBindTexture(GL_TEXTURE_2D,textures[14]);
    glEnable(GL_TEXTURE_2D);
    
    float i, j;
    i = p->pos_x;
    j = p->pos_y;
    
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(j*Square_size,i*Square_size,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size,0.0f,0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size,Square_size*2,0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size*2,0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

// This function draws the player's health on the screen, in the top left corner, with between 0 and 3 red hearts
void drawHealth(pPlayer p){
    
    glEnable(GL_TEXTURE_2D);
    
    if(p->health_points==3){
        glBindTexture(GL_TEXTURE_2D,textures[19]);
        glColor3f(1.0f,1.0f,1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(Square_size,0.0f,0.0f);
        glBegin(GL_QUADS);
        glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(5*Square_size,0.0f,0.0f);
        glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(5*Square_size,2*Square_size,0.0f);
        glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,2*Square_size,0.0f);
        glEnd();
    }
    else if(p->health_points==2){
        glBindTexture(GL_TEXTURE_2D,textures[18]);
        glColor3f(1.0f,1.0f,1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(Square_size,0.0f,0.0f);
        glBegin(GL_QUADS);
        glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(5*Square_size,0.0f,0.0f);
        glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(5*Square_size,2*Square_size,0.0f);
        glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,2*Square_size,0.0f);
        glEnd();
    }
    else if(p->health_points==1){
        glBindTexture(GL_TEXTURE_2D,textures[17]);
        glColor3f(1.0f,1.0f,1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(Square_size,0.0f,0.0f);
        glBegin(GL_QUADS);
        glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(5*Square_size,0.0f,0.0f);
        glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(5*Square_size,2*Square_size,0.0f);
        glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,2*Square_size,0.0f);
        glEnd();
    }
    else{
        glBindTexture(GL_TEXTURE_2D,textures[16]);
        glColor3f(1.0f,1.0f,1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(Square_size,0.0f,0.0f);
        glBegin(GL_QUADS);
        glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(5*Square_size,0.0f,0.0f);
        glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(5*Square_size,2*Square_size,0.0f);
        glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,2*Square_size,0.0f);
        glEnd();
    }
    
        glDisable(GL_TEXTURE_2D);
}

// This function draws a green rectangle in the top right corner of the screen, to allow for a clean and readable display of the score and max nbr of missles, handled separately via drawScore()
void drawBlankSpaceForScore(void){
// Creating in the top right corner a green rectangle
    glColor3f(0.0f,1.0f,0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(33*Square_size,0.0f,0.0f); // positionned on the first row, where the grass begins on the right hand side of the screen
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(5*Square_size,0.0f,0.0f);
    glVertex3f(5*Square_size,5*Square_size,0.0f);
    glVertex3f(0.0f,5*Square_size,0.0f);
    glEnd();
    
}

// This function draws the current score and the maximum number of missiles, in the top right corner of the screen
void drawScore(pGame game){
// Converting the score and the maximum number of missiles the player can shoot simultaneously to string, to allow usage of glut functionality
    char score[12], maxMissiles[12];
    sprintf(score, "SCORE: %d", game->score);
    sprintf(maxMissiles, "#Shoots: %d", maxNbrMissilesPlayer);
    
    // Displaying text
    glColor3f(0.0f,0.0f,0.0f);
    drawText(score, 32 * Square_size, Square_size);
    drawText(maxMissiles, 32 * Square_size, 2 * Square_size);
}

// This function draws the map on the screen, by reading each character of the mapToRender matrix.
// Each blank element is drawn as a grey square (road), each # as a white square (white lines on the side of the road), each B as a black square (border of the screen), each G as a light green square (grass), each T as a dark green square (trees), each H as a red square (Houses) and each @ as a yellow square (line in the center of the road)
void drawMap(void){
    
    for (int j = 0; j < WINDOW_SIZE_X; ++j)
    {
        for (int i = 0; i < WINDOW_SIZE_Y; ++i)
        {
            if(*(*(mapToRender + j) + i) == '#')
            {
                glColor3f(1.0f,1.0f,1.0f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(1.0,1.0,1.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            else if(*(*(mapToRender + j) + i) == 'B')
            {
                glColor3f(0.0f,0.0f,0.0f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(0.0,0.0,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            else if(*(*(mapToRender + j) + i) == 'G')
            {
                glColor3f(0.0f,1.0f,0.0f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(0.0,1.0,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            else if(*(*(mapToRender + j) + i) == 'T')
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,textures[20]);
                glColor3f(1.0f,1.0f,1.0f);
                glMatrixMode(GL_MODELVIEW);

                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);


                glBegin(GL_QUADS);
                glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size,Square_size, 0.0f);
                glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
            else if(*(*(mapToRender + j) + i) == 'F')
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,textures[21]);
                glColor3f(1.0f,1.0f,1.0f);
                glMatrixMode(GL_MODELVIEW);

                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);

                glBegin(GL_QUADS);
                glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size,Square_size, 0.0f);
                glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
            else if(*(*(mapToRender + j) + i) == 'H')
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,textures[22]);
                glColor3f(1.0f,1.0f,1.0f);
                glMatrixMode(GL_MODELVIEW);

                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);

                glBegin(GL_QUADS);
                glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size, 0.0f, 0.0f);
                glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size,Square_size, 0.0f);
                glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
            else if(*(*(mapToRender + j) + i) == '@')
            {
                glColor3f(0.7f,0.7f,0.7f);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size /2, 0.0f);
                glVertex3f(0.0f,Square_size /2, 0.0f);
                glEnd();
                
                glColor3f(1.0f,1.0f,1.0f);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                glBegin(GL_QUADS);
                glVertex3f(0.0f, Square_size /2, 0.0f);
                glVertex3f(Square_size, Square_size /2, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);
                glEnd();
            }
            else{
                glColor3f(0.7f,0.7f,0.7f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                glBegin(GL_QUADS);
                glColor3f(0.7,0.7,0.7);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            
           }
        }

}

// this function draws the cars as purple square on the screen
void drawCars(pCarList list){
    if (list->firstCar != NULL ){ // if the list of all cars is not empty, draw the cars. If list of cars is empty, do nothing
        glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
        
        pCar loop;
        loop = (pCar) malloc(sizeof(struct car));
        loop = list->firstCar;
        float x, y; // temp variables will be used to store the position of the current car
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glBindTexture(GL_TEXTURE_2D,textures[15]);
            glColor3f(1.0f,1.0f,1.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,1.0f);
            glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size*3,0.0f,1.0f);
            glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size*3,Square_size*6,1.0f);
            glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size*6,1.0f);
            glEnd();
            
            loop = loop->nextCar;
        }
        free(loop);
    }
    glDisable(GL_TEXTURE_2D);
}

// this function draws the missiles on the screen as small black squares
void drawMissiles(pMissileList list){
    if (list->firstMissile != NULL ){ // if the list of all missiles is not empty, draw the misiles. If list of missiles is empty, do nothing
        pMissile loop;
        loop = (pMissile) malloc(sizeof(struct missile));
        loop = list->firstMissile;
        float x, y; // temp variables will be used to store the position of the current missile
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            if(loop->missileFromPlayer == false){
                glColor3f(0.0f,0.0f,0.0f);
            }
            else{
                glColor3f(1.0f,0.0f,0.0f);
            }
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*missile_size,x*missile_size,0.0f);
            glBegin(GL_QUADS);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(missile_size,0.0f,0.0f);
            glVertex3f(missile_size,missile_size,0.0f);
            glVertex3f(0.0f,missile_size,0.0f);
            glEnd();
            
            loop = loop->nextMissile;
        }
        free(loop);
    }
}

// this function draws the obstacles on the screen as dark grey squares
void drawObstacles(pObstacleList list){
    if (list->firstObstacle != NULL ){ // if the list of all obstacles is not empty, draw the obstacles. If list of obstacles is empty, do nothing
        glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
        
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = list->firstObstacle;
        float x, y; // temp variables will be used to store the position of the current obstacle
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glBindTexture(GL_TEXTURE_2D,textures[24]);
            glColor3f(1.0f,1.0f,1.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
            glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size*2,0.0f,0.0f);
            glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size*2,Square_size*2,0.0f);
            glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size*2,0.0f);
            glEnd();
            
            loop = loop->nextObstacle;
        }
        free(loop);
    }
    glDisable(GL_TEXTURE_2D);
}

// this function draws the bonuses on the screen as pink squares
void drawBonuses(pBonusList list){
    if (list->firstBonus != NULL ){ // if the list of all bonuses is not empty, draw the bonus. If list of bonuses is empty, do nothing
        glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
        
        pBonus loop; // creating a temp variable to go through the loop
        loop = (pBonus) malloc(sizeof(struct bonus));
        loop = list->firstBonus;
        float x, y; // temp variables will be used to store the position of the current bonus
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glBindTexture(GL_TEXTURE_2D,textures[23]);
            glColor3f(1.0f,1.0f,1.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
            glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(Square_size,0.0f,0.0f);
            glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(Square_size,Square_size,0.0f);
            glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,Square_size,0.0f);
            glEnd();
            
            loop = loop->nextBonus;
        }
        free(loop);
    }
    glDisable(GL_TEXTURE_2D);
}

// this function displays the paused game menu, advising about the potential actions the player can take
void displayPause(void){
    glEnable(GL_TEXTURE_2D);    // enable functionality to add textures
        
    glBindTexture(GL_TEXTURE_2D,textures[13]);
    glColor3f(1.0f,1.0f,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(175,215,0.0f);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(450,0.0f,0.0f);
    glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(450,350,0.0f);
    glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(0.0f,350,0.0f);
    glEnd();
        

    glDisable(GL_TEXTURE_2D);
}

// this function displays the game over screen, providing the final score and allowing to leave the game
void displayGameOver(pGame game){
    glColor3f(0.0f,0.0f,0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(175,215,0.0f); // positionned on the first row, where the grass begins on the right hand side of the screen
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(450,0.0f,0.0f);
    glVertex3f(450,350,0.0f);
    glVertex3f(0.0f,350,0.0f);
    glEnd();

    
    // Converting the score and the maximum number of missiles the player can shoot simultaneously to string, to allow usage of glut functionality
    char score[12];
    sprintf(score, "SCORE: %d", game->score);
    
    // Displaying text
    glColor3f(1.0f,1.0f,1.0f);
    drawText("GAME OVER", 185, 80);
    drawText(score, 175, 150);
    drawText("Press h to go to the main menu", 130, 250);
    drawText("Press ESC to exit", 160, 300);
}
