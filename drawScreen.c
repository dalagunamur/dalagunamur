#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "map/map.h"
#include "game_elements/player.h"
#include "game_elements/car.h"
#include "game_elements/missile.h"
#include "drawScreen.h"
#include "game.h"

// This function draws the player on the screen as a light blue square
void drawPlayer(pPlayer p){
    int i, j;
    i = p->pos_x;
    j = p->pos_y;
    glColor3f(0.67f,0.91f,0.91f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(j*Square_size,i*Square_size,0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(Square_size,0.0f,0.0f);
    glVertex3f(Square_size,Square_size,0.0f);
    glVertex3f(0.0f,Square_size,0.0f);
    glEnd();
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
                glColor3f(0.0f,0.3f,0.0f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(0.0,0.3,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            else if(*(*(mapToRender + j) + i) == 'H')
            {
                glColor3f(1.0f,0.25f,0.20f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(1.0,0.25,0.20);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
                glVertex3f(Square_size,Square_size, 0.0f);
                glVertex3f(0.0f,Square_size, 0.0f);

                glEnd();
            }
            else if(*(*(mapToRender + j) + i) == '@')
            {
                glColor3f(1.0f,1.0f,0.0f);
                glMatrixMode(GL_MODELVIEW);
                
                glLoadIdentity();
                glTranslatef(i*Square_size,j*Square_size,0.0f);
                
                
                glBegin(GL_QUADS);
                glColor3f(1.0,1.0,0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(Square_size, 0.0f, 0.0f);
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
        pCar loop;
        loop = (pCar) malloc(sizeof(struct car));
        loop = list->firstCar;
        int x, y; // temp variables will be used to store the position of the current car
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glColor3f(0.53f,0.12f,0.47f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(Square_size*2,0.0f,0.0f);
            glVertex3f(Square_size*2,Square_size*4,0.0f);
            glVertex3f(0.0f,Square_size*4,0.0f);
            glEnd();
            
            loop = loop->nextCar;
        }
        free(loop);
    }
}

// this function draws the missiles on the screen as small black squares
void drawMissiles(pMissileList list){
    if (list->firstMissile != NULL ){ // if the list of all missiles is not empty, draw the misiles. If list of missiles is empty, do nothing
        pMissile loop;
        loop = (pMissile) malloc(sizeof(struct missile));
        loop = list->firstMissile;
        int x, y; // temp variables will be used to store the position of the current missile
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glColor3f(0.0f,0.0f,0.0f);
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
        pObstacle loop;
        loop = (pObstacle) malloc(sizeof(struct obstacle));
        loop = list->firstObstacle;
        int x, y; // temp variables will be used to store the position of the current obstacle
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glColor3f(0.1f,0.1f,0.1f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(Square_size*2,0.0f,0.0f);
            glVertex3f(Square_size*2,Square_size*2,0.0f);
            glVertex3f(0.0f,Square_size*2,0.0f);
            glEnd();
            
            loop = loop->nextObstacle;
        }
        free(loop);
    }
}

// this function draws the bonuses on the screen as pink squares
void drawBonuses(pBonusList list){
    if (list->firstBonus != NULL ){ // if the list of all bonuses is not empty, draw the bonus. If list of bonuses is empty, do nothing
        pBonus loop; // creating a temp variable to go through the loop
        loop = (pBonus) malloc(sizeof(struct bonus));
        loop = list->firstBonus;
        int x, y; // temp variables will be used to store the position of the current bonus
        
        while(loop != NULL){
            x = loop->pos_x;
            y = loop->pos_y;
            
            glColor3f(0.737255f,0.560784f,0.560784f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(y*Square_size,x*Square_size,0.0f);
            glBegin(GL_QUADS);
            glVertex3f(0.0f,0.0f,0.0f);
            glVertex3f(Square_size,0.0f,0.0f);
            glVertex3f(Square_size,Square_size,0.0f);
            glVertex3f(0.0f,Square_size,0.0f);
            glEnd();
            
            loop = loop->nextBonus;
        }
        free(loop);
    }
}
