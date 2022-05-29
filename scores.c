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
#include <time.h>

#include "scores.h"


// This function returns a newly score
pScore createScore(int score, int time){
    pScore newScore;
    newScore = (pScore) malloc(sizeof(struct score));
    
    newScore->score = score;
    newScore->time = time;
    newScore->previousScore = NULL;
    newScore->nextScore = NULL;
    
    return newScore;
}


// This function returns a list of scores, containing a pointer to the first and last elements of the list + the number of items currently in the list
pScoresList createListScores(void){
    pScoresList listScores;
    listScores = (pScoresList) malloc(sizeof(struct scoresList));
    
    listScores->scoresCounter = 0;
    listScores->firstScore = NULL;
    listScores->lastScore = NULL;
    
    return listScores;
}

// This function checks if the score obtained has to be saved as a new high score + makes sure that only 10 high scores are kept
void checkIfHighScore(pScoresList list, int checkScore, int checkTime){
    // first create a score that will be compared with the list of high scores to determine the position
    pScore newScore=createScore(checkScore, checkTime);
    
    // if there are currently no high score, store as the first and only item in the list
    if(list->firstScore == NULL){
        list->firstScore = newScore;
        list->lastScore = newScore;
        list->scoresCounter ++;
    }
    
    // if the newScore is the smallest of all high scores and that there are less than 10 scores in the list, enter as the smallest
    else if(newScore->score < list->lastScore->score){
        if(list->scoresCounter < 10){
            list->lastScore->nextScore = newScore; // the last item in the list now points to the new last item
            newScore->previousScore = list->lastScore; // newScore points to the previous last score
            list->lastScore = newScore; // the last score of the list is set to newScore
            list->scoresCounter++;
        }
    }
    
    // else, go through the list of scores
    else{
        pScore loop; // creating a temporary score to navigate through the list of scores
        loop = list->firstScore;
        bool keepLoop = true;
        
        while(loop != NULL && keepLoop){ // as long as we did not go through the list of high scores, check if the new score has to be saved
            if(loop->score <= newScore->score){ // in case the new score is less than or equal to the current high score in the loop, move to the next one
                if(loop == list->firstScore){ // if the current in the loop is the first one, change the head of list and the former new score points to the newScore as previousScore
                    loop->previousScore = newScore;
                    newScore->nextScore = loop;
                    list->firstScore = newScore;
                    list->scoresCounter ++;
                    keepLoop = false;
                }
                else{ // if the current item in the loop is another one than the first, the newScore must be inserted in between 2 items of the list
                    newScore->previousScore = loop->previousScore; //newScore receives the previous score of the loop score
                    newScore->nextScore = loop; // newScore points to loop as following score
                    loop->previousScore->nextScore = newScore; // the score which is higher (previous) now points to newScore
                    loop->previousScore = newScore; // the current score in the list (loop) now has the newScore as previousScore
                    list->scoresCounter ++;
                    keepLoop = false;
                }
            }
            else{
                loop = loop->nextScore;
            }
        }
    }
        
    
    if(list->scoresCounter >10){    // if the list contains more than 10 entries, remove the last ones
        pScore scoreToDelete; // creating a temporary score to navigate through the list of scores
        while( list->scoresCounter > 10 ){
            scoreToDelete = list->lastScore;
            scoreToDelete->previousScore->nextScore = NULL ; // the entry before the score that will be deleted now points to a NULL nextScore
            list->lastScore = scoreToDelete->previousScore;
            list->scoresCounter --;
            free(scoreToDelete);
        }
    }

}

// this function is used to load the high scores saved in the file
void loadHighScores(pScoresList list){
    FILE *f = NULL;
    f = fopen("highScores.txt", "r");
    if(f == NULL)
    {
        printf("File not found.\n");
    }
    else{
        int score, time;
        
        fscanf(f,"%d%d", &score, &time);
        while (!feof(f)){
            checkIfHighScore(list, score, time);
            fscanf(f,"%d%d", &score, &time);
        }
        fclose(f);
    }
}

// this function saves the updated high scores in the highScores.txt file
void saveHighScores(pScoresList list){
    if (list->firstScore!= NULL ){ // if the list of all high scores is not empty, draw the high scores. If list is empty, do nothing
        FILE *f;
        f = fopen("highScores.txt","w");
        pScore loop;
        loop = list->firstScore;
        
        while(loop != NULL){
            fprintf(f, "%d %d\n", loop->score, loop->time);
            
            loop = loop->nextScore;
        }
        fclose(f);
    }
}
