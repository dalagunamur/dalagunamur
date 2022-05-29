#ifndef _SCORES_H_
#define _SCORES_H_

#include <stdio.h>
#include <stdbool.h>

char **fileHighScores; // this variable will contain the list of all high scores saved in the file

// This structure will be used to compare the scores saved in the list with the score obtained during the game
struct score{
    int score;
    int time;
    struct score * previousScore;
    struct score * nextScore;
};

typedef struct score * pScore;

// This structure will be used to store the head and tail of the chained list of scores
struct scoresList{
    int scoresCounter;
    pScore firstScore;
    pScore lastScore;
};

//pScoresList points to bonusList
typedef struct scoresList * pScoresList;

pScore newScore;
pScoresList listOfHighScores; // this global variable will be used to store the head and tail of the chained list

pScoresList createListScores(void); // this function returns a newly created list of scores. This function is called at the beginning of the game, for initialization
pScore createScore(int score, int time); // to create a new instance of a score, when reading the highscores file
void checkIfHighScore(pScoresList list, int checkScore, int checkTime); // This function checks if the score obtained has to be saved as a new high score + makes sure that only 10 high scores are kept

void loadHighScores(pScoresList list); // function used to read the scores.txt file and store it in the chained list

void saveHighScores(pScoresList list); // this function saves the updated high scores in the highScores.txt file

#endif /* scores_h */
