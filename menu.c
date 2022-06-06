#ifdef __APPLE_CC__
#define GL_SILENCE_DEPRECATION TRUE // to silence warnings about GLUT not supported by recent versions of MacOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map/map.h"
#include "game.h"
#include "drawScreen.h"
#include "menu.h"
#include "glut/loadTextures.h"
#include "scores.h"

/*
 INFORMATION ABOUT GLUT TIMERS
 0 = handles all the movements of map, obstacles, bonuses, cars and missiles, as well as the check of collision and destruction of inactive elements
 1 = handles the creation of new items, ie cars, bonuses, obstacles and missiles shot by cars
 */

// The following variables are used to store the actual id of each window that can be created. By default, the program opens the windowHome, which displays the main menu.
// then based on its actions, other windows might be open. windowGame is the one where the actual games happens.
int windowHome;
int windowGame; // Game window
int windowOptions;
int windowLoadMenu;
int windowScores;


// The following boolean are used to monitor the various activities taken on home page or the load screen
bool NEW_GAME = false; // set to True when player wants to start a new game
bool LOAD_GAME = false; // set to True when player wants to display the load game screen
bool OPTIONS = false; // set to True when the player wants to display the options and configuration screen
bool HIGH_SCORES = false; // set to True when the player wants to display the high scores screen
bool RESUME_GAME = false; // set to True when the player wants to resume a previously started game
bool GO_BACK_HOME = false; // set to True when the player wants to go back to the home screen


GLuint textures[25];

// GLUT functionality to initialize rendering
void initRendering(){
    glEnable(GL_DEPTH_TEST);
}

// GLUT function to handle the resize of a screen
void handleResize(int width,int heigth){
    glViewport(0, 0, width, heigth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, heigth, 0);
}

/* *********************************************************** */

// functions that creates the home page and calls the function to create its content
void display_home(void){
    windowHome = glutCreateWindow("Home page");
    glutSetWindow(windowHome);
    initRendering();
    loadAllTextures(textures);
    
    glutDisplayFunc(displayHomePage);
    glutReshapeFunc(handleResize);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

// this function calls the handleHomePage() function, that requests the rendering of all the elements of the game on the screen
void displayHomePage(){
    glClearColor(0.27f,0.27f,0.27f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleHomePage();
    glFlush();
}

// This function is called each time the player hits a key on the keyboard while in the home page. In case the key pressed is one which is assigned a function, it records the action requested
void handleKeyboardHomePage(unsigned char input, int x, int y){
    switch(input)
        {
            case 'n':
                NEW_GAME = true;
                break;
            case 'l':
                LOAD_GAME = true;
                break;
            case 'o':
                OPTIONS = true;
                break;
            case 's':
                HIGH_SCORES = true;
                break;
            case 'q':
                exit(0);
        }
}

// This function requests the drawing of the home page + calls the function monitoring the keyboard actions + handles the redisplay
void handleHomePage(){
    drawHomePage();  //display the home page on screen
    
    glutKeyboardFunc(handleKeyboardHomePage);        //callback to the function handling the keyboard on the home page
    
    if (NEW_GAME){
        NEW_GAME = false;
        glutHideWindow(); // hides the current Window, ie the Home Page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_game(0); // calls the function to display the Game window, with argument set to 0, to indicate this is for a brand new game
    }
    if (LOAD_GAME){
        LOAD_GAME = false;
        glutHideWindow(); // hides the current window, ie the home page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_load(); // calls the function to display the load a game page
    }
    if (OPTIONS){
        OPTIONS = false;
        glutHideWindow(); // hides the current window, ie the home page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_options(); // calls the function to display the Options page
    }
    if (HIGH_SCORES){
        HIGH_SCORES = false;
        glutHideWindow(); // hides the current window, ie the home page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_scores(); // calls the function to display the High Scores page
    }

    glutPostRedisplay();
}


/* *********************************************************** */

// this function calls the play() function, that requests the rendering of all the home page menu items on the screen
void display(){
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    play(theGame,mapToRender, p, listOfCars, listOfMissiles, listOfObstacles, listOfBonuses);
    glFlush();
}

// displays the game window, gameId allows to load a previously saved game or to start a new game
void display_game(int gameId){
    
    // GLUT CREATION OF THE WINDOW

    windowGame = glutCreateWindow("Velo vs Voiture");
    glutSetWindow(windowGame);
    
    // GLOBAL VARIABLES CREATED BELOW
    // INITIALIZE THE MAP - THE PLAYER - THE LISTS OF CARS, MISSILES, BONUSES, OBSTACLES and HIGH SCORES
    row = NULL;
    map = NULL;
    listOfCars = createCarList();
    listOfMissiles = createMissileList();
    listOfObstacles = createObstacleList();
    listOfBonuses = createListBonuses();
    loadMapFile(MAP_SIZE_X,MAP_SIZE_Y);
    for(int i=0; i < WINDOW_SIZE_X; i++){
        row = createRow();
        map = addRow(map, row);
    }
    displayMap(map);
    
    if(gameId == 0){ // if the argument is passed with value 0, it means the game is a brand new one and there are no cars, bonuses, obstacles to create + the score and the number of missiles that can be shot simultaneously are set to their initial value + the starting position of the player is the default one
        p = createPlayer(37, 30, 3); // when creating a new game, the starting position is set to coordinates 37,30 and the number of available Health Points is 3
        maxNbrMissilesPlayer = 10; // initially setting the max nbr of missiles a player can shoot at the same time to 10
        theGame = createGame(0, 0); // when creating a brand new game, the initial values for the score and the timer are passed as 0
    }
    else{ // if the argument is passed with another value (ie always 1 currently), it means it is a previously saved game which is resumed. Hence the need to load existing cars, bonuses, obstacles, the player position and the game's score and timer
        load_game();
    }
    // END OF INITIALIZATION
    
    // GLUT HANDLING OF THE MAIN LOOP AND INITIALIZING THE CALLBACKS
    initRendering();
    loadAllTextures(textures);
    
    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
//    if(PAUSED_GAME == false){
        glutTimerFunc(500, glutCreateElements, 1);
        glutTimerFunc(1000, glutAnimateElements, 0);
//    }

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
}

/* *********************************************************** */

// functions that creates the load game page and calls the function to create its content
void display_load(void){
    windowLoadMenu = glutCreateWindow("Load a game");
    glutSetWindow(windowLoadMenu);
    initRendering();
    loadAllTextures(textures);
    glutDisplayFunc(displayLoadPage);
    glutReshapeFunc(handleResize);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

// this function calls the handleLoadPage() function
void displayLoadPage(){
    glClearColor(0.27f,0.27f,0.27f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleLoadPage();
    glFlush();
}

// This function is called each time the player hits a key on the keyboard while in the load page. In case the key pressed is one which is assigned a function, it records the action requested
void handleKeyboardLoadPage(unsigned char input, int x, int y){
    switch(input)
        {
            case 'r':
                RESUME_GAME = true;
                break;
            case 'h':
                GO_BACK_HOME = true;
                break;
        }
}

// This function requests the drawing of the load page + calls the function monitoring the keyboard actions + handles the redisplay
void handleLoadPage(){
    drawLoadPage();  //display the load a game page on screen
    
    glutKeyboardFunc(handleKeyboardLoadPage);        //callback to the function handling the keyboard on the load a game page
    
    if (RESUME_GAME){
        RESUME_GAME = false;
        glutHideWindow(); // hides the current Window, ie the Load Page
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_game(1); // calls the function to display the Game window, with value 1 to indicate this is from a saved game
    }
    if (GO_BACK_HOME){
        GO_BACK_HOME = false;
        glutHideWindow();
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_home();
    }

    glutPostRedisplay();
}

/* *********************************************************** */

// functions that creates the options page and calls the function to create its content
void display_options(void){
    windowOptions = glutCreateWindow("Options");
    glutSetWindow(windowOptions);
    initRendering();
    loadAllTextures(textures);
    glutDisplayFunc(displayOptionsPage);
    glutReshapeFunc(handleResize);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

// this function calls the handleOptionsPage() function
void displayOptionsPage(){
    glClearColor(0.27f,0.27f,0.27f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleOptionsPage();
    glFlush();
}

// This function is called each time the player hits a key on the keyboard while in the options page. In case the key pressed is one which is assigned a function, it records the action requested
void handleKeyboardOptionsPage(unsigned char input, int x, int y){
    switch(input)
        {
            case 'h':
                GO_BACK_HOME = true;
                break;
        }
}

// This function requests the drawing of the options page + calls the function monitoring the keyboard actions + handles the redisplay
void handleOptionsPage(void){
    drawOptionsPage();  //display the options page on screen
    
    glutKeyboardFunc(handleKeyboardOptionsPage);        //callback to the function handling the keyboard on the options page
    
    if (GO_BACK_HOME){
        GO_BACK_HOME = false;
        glutHideWindow();
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_home();
    }

    glutPostRedisplay();
}

/* *********************************************************** */

// functions that creates the high scores page and calls the function to create its content
void display_scores(void){
    windowScores = glutCreateWindow("High Scores");
    glutSetWindow(windowScores);
    initRendering();
    loadAllTextures(textures);
    
    glutDisplayFunc(displayScoresPage);
    glutReshapeFunc(handleResize);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

// this function calls the handleScoresPage() function
void displayScoresPage(){
    glClearColor(0.27f,0.27f,0.27f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleScoresPage();
    glFlush();
}

// This function is called each time the player hits a key on the keyboard while in the high scores page. In case the key pressed is one which is assigned a function, it records the action requested
void handleKeyboardScoresPage(unsigned char input, int x, int y){
    switch(input)
        {
            case 'h':
                GO_BACK_HOME = true;
                break;
        }
}

// This function requests the drawing of the high scores page + calls the function monitoring the keyboard actions + handles the redisplay
void handleScoresPage(){
    drawScoresPage(listOfHighScores);  //display the high scores page on screen
    
    glutKeyboardFunc(handleKeyboardScoresPage);        //callback to the function handling the keyboard on the home page
    
    if (GO_BACK_HOME){
        GO_BACK_HOME = false;
        glutHideWindow();
        glDeleteTextures(25, textures); // textures are linked to the window, need to delete them and reload in the next window
        display_home();
    }

    glutPostRedisplay();
}
