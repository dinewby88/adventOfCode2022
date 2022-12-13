#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'

#define RESULT_LOSE 'X'
#define RESULT_DRAW 'Y'
#define RESULT_WIN  'Z'

#define SCORE_ROCK 1
#define SCORE_PAPER 2
#define SCORE_SCISSORS 3

#define SCORE_LOSE 0
#define SCORE_DRAW 3
#define SCORE_WIN 6

int scoreRound(char opponent_choice, char desired_result)
{
    switch(opponent_choice)
    {
        case OPPONENT_ROCK:
        {
            switch(desired_result)
            {
                case RESULT_LOSE: return SCORE_LOSE + SCORE_SCISSORS;
                case RESULT_DRAW: return SCORE_DRAW + SCORE_ROCK;
                case RESULT_WIN:  return SCORE_WIN + SCORE_PAPER;
                default:          return 0;
            }
        }
        case OPPONENT_PAPER:
        {
            switch(desired_result)
            {
                case RESULT_LOSE: return SCORE_LOSE + SCORE_ROCK;
                case RESULT_DRAW: return SCORE_DRAW + SCORE_PAPER;
                case RESULT_WIN:  return SCORE_WIN + SCORE_SCISSORS;
                default:          return 0;
            }
        }
        case OPPONENT_SCISSORS:
        {
            switch(desired_result)
            {
                case RESULT_LOSE: return SCORE_LOSE + SCORE_PAPER;
                case RESULT_DRAW: return SCORE_DRAW + SCORE_SCISSORS;
                case RESULT_WIN:  return SCORE_WIN + SCORE_ROCK;
                default:          return 0;
            }
        }
    }
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
        char desired_result = lineInput[2];
        roundScore = scoreRound(opponent_choice, desired_result);
        printf("%c %c %d\n",opponent_choice, desired_result, roundScore);
        totalScore += roundScore;
    }

    printf("Total Score = %d\n",totalScore);
}

int main()
{
    processData();
}