#ifndef _MENU_H_
#define _MENU_H_

// the following global variables and functions will be used for each window
int windowHome; // Home page
int windowGame; // Game window
int windowLoadMenu; // Load a game page
int windowScores; // Page with high scores
int windowOptions; // Page with configuration options

// Functions used by all windows
void initRendering(void);
void handleResize(int width,int heigth);

// Functions used by the home page window
void display_home(void); // function that creates the window to display the home page and calls the various glut functions
void displayHomePage(void); // function that handles the creation of the home page
void handleHomePage(void); // function that calls the handleKeyboardHomePage + requests to draw the various elements on screen
void handleKeyboardHomePage(unsigned char input, int x, int y); // function that handles the keyboard specifically on the home page


// Functions used by the Game window
void display_game(int gameId); // displays the game window, gameId allows to load a previously saved game or to start a new game
void display(void); // this function calls the play() function, that requests the rendering of all the elements of the game on the screen


// Functions used by the load game window
void display_load(void); // function that creates the window to display the load a game page
void displayLoadPage(void); // function that handles the creation of the load game page
void handleLoadPage(void); // function that calls the handleKeyboardLoadPage + requests to draw the various elements on screen
void handleKeyboardLoadPage(unsigned char input, int x, int y); // function that handles the keyboard specifically on the load page

// Functions used by the display high scores window
void display_scores(void); // function that creates the window to display the High Scores page
void displayScoresPage(void); // function that handles the creation of the High Scores page
void handleScoresPage(void); // function that calls the handleKeyboardScoresPage + requests to draw the various elements on screen
void handleKeyboardScoresPage(unsigned char input, int x, int y); // function that handles the keyboard specifically on the High Scores page


// Functions used by the configuration and options window
void display_options(void); // function that creates the window to display the Options page
void displayOptionsPage(void); // function that handles the creation of the options page
void handleOptionsPage(void); // function that calls the handleKeyboardOptionsPage + requests to draw the various elements on screen
void handleKeyboardOptionsPage(unsigned char input, int x, int y); // function that handles the keyboard specifically on the Options page

#endif
