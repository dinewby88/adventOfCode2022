#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'

#define MY_ROCK 'X'
#define MY_PAPER 'Y'
#define MY_SCISSORS 'Z'

#define SCORE_ROCK 1
#define SCORE_PAPER 2
#define SCORE_SCISSORS 3

#define SCORE_LOSE 0
#define SCORE_DRAW 3
#define SCORE_WIN 6

int scoreRound(char opponent_choice, char my_choice)
{
    int myChoiceScore = 0;
    int resultScore = 0;

    switch(my_choice)
    {
        case MY_ROCK: myChoiceScore = SCORE_ROCK; break;
        case MY_PAPER: myChoiceScore = SCORE_PAPER; break;
        case MY_SCISSORS: myChoiceScore = SCORE_SCISSORS; break;
        default: myChoiceScore = 0;
    }

    switch(opponent_choice)
    {
        case OPPONENT_ROCK:
        {
            switch(my_choice)
            {
                case MY_ROCK:     resultScore = SCORE_DRAW; break;
                case MY_PAPER:    resultScore = SCORE_WIN; break;
                case MY_SCISSORS: resultScore = SCORE_LOSE; break;
                default:          resultScore = 0;
            }
            break;
        }
        case OPPONENT_PAPER:
        {
            switch(my_choice)
            {
                case MY_ROCK:     resultScore = SCORE_LOSE; break;
                case MY_PAPER:    resultScore = SCORE_DRAW; break;
                case MY_SCISSORS: resultScore = SCORE_WIN; break;
                default:          resultScore = 0;
            }
            break;
        }
        case OPPONENT_SCISSORS:
        {
            switch(my_choice)
            {
                case MY_ROCK:     resultScore = SCORE_WIN; break;
                case MY_PAPER:    resultScore = SCORE_LOSE; break;
                case MY_SCISSORS: resultScore = SCORE_DRAW; break;
                default:          resultScore = 0;
            }
            break;
        }
        default: resultScore = 0;
    }

    return resultScore + myChoiceScore;
}

void processData()
{
    char filename[] = "input.txt";
    char lineInput[50];
    FILE* fptr = fopen(filename,"r");
    int roundScore = 0;
    int totalScore = 0;
    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(fgets(lineInput,sizeof(lineInput),fptr) != 0)
    {
        char opponent_choice = lineInput[0];
        char my_choice = lineInput[2];
        roundScore = scoreRound(opponent_choice,my_choice);
        printf("%c %c %d\n",opponent_choice, my_choice, roundScore);
        totalScore += roundScore;
    }

    printf("Total Score = %d\n",totalScore);
}

int main()
{
    processData();
}