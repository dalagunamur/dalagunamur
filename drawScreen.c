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
#include "drawScreen.h"
#include "game.h"

void drawPlayer(pPlayer p){
    int i, j;
    i = p->pos_x;
    j = p->pos_y;
    glColor3f(0.67f,0.91F,0.91f);
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

void drawMap(void)
{

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
