#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 4
char myStack[STACK_SIZE] = {0};

void pushStack(char c)
{
    //stack loads in at end of array.
    for(int x = 0; x < STACK_SIZE-1; x++)
    {
        myStack[x] = myStack[x+1];
    }
    myStack[STACK_SIZE-1] = c;
}

bool checkForStartSignal()
{
    bool unique = true;
    for(int x = 0; x < STACK_SIZE; x++)
    {
        if (!unique) break;
        for(int y = 0; y < STACK_SIZE; y++)
        {
            if (x == y) continue;
            if (myStack[x] == 0)
            {
                unique = false;
                break;
            }
            if (myStack[x] == myStack[y])
            {
                unique = false;
                break;
            }
        }
    }
    return unique;
}

void processData()
{
    char filename[] = "input.txt";
    FILE* fptr = fopen(filename,"r");

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    int charCounter = 0;
    while(1)
    {
        char c = fgetc(fptr);
        if (feof(fptr))
        {
            break;
        }
        charCounter++;
        pushStack(c);
        if (checkForStartSignal())
        {
            printf("start signal detected after %d chars\n",charCounter);
            break;
        }
    }
}

int main()
{
    processData();
}