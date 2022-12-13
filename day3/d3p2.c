#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRIORITIES 52
#define ELVES_PER_GROUP 3
int getPriority(char x)
{
    if (x >= 'a' && x <= 'z')
    {
        return x-'a'+1;
    }
    if (x >= 'A' && x <= 'Z')
    {
        return x-'A'+27;
    }
    return 0;
}

char getPriorityReverse(int x)
{
    if (x >= 1 && x <= 26)
    {
        return x+'a'-1;
    }
    if (x >= 27 && x <= 52)
    {
        return x+'A'-27;
    }
    return 0;
}

void visualizeCompartment(int* ptr)
{
    for (int x=1; x<=MAX_PRIORITIES;x++)
    {
        printf("%02d ",x);
    }
    printf("\n");
    for (int x=1; x<=MAX_PRIORITIES;x++)
    {
        printf("%02c ",getPriorityReverse(x));
    }
    printf("\n");
    for (int x=1; x<=MAX_PRIORITIES;x++)
    {
        printf("%02d ",ptr[x]);
    }
    printf("\n");
}

void processData()
{
    char filename[] = "input.txt";
    char lineInput[ELVES_PER_GROUP][100];
    int compartment[ELVES_PER_GROUP][MAX_PRIORITIES+1];
    int compartmentSum[MAX_PRIORITIES+1] = {0};
    int total = 0;
    int posDiff;
    int priority;
    int elfGroupCounter = 0;
    bool processingComplete = 0;
    char* ptr;
    FILE* fptr = fopen(filename,"r");

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(!processingComplete)
    {
        elfGroupCounter++;
        for (int x=0;x<ELVES_PER_GROUP;x++)
        {
            for (int y=0;y<=MAX_PRIORITIES;y++)
            {
                compartment[x][y] = 0;
            }
        }
        
        for (int y=0;y<=MAX_PRIORITIES;y++)
        {
            compartmentSum[y] = 0;
        }

        for (int x=0;x<ELVES_PER_GROUP;x++)
        {
            // update compartment for each elf
            ptr = fgets(lineInput[x],sizeof(lineInput[x]),fptr);
            if (ptr)
            {
                posDiff = strlen(lineInput[x]);
                // remove trailing new line in calculations
                if (lineInput[x][posDiff-1] == '\n')
                {
                    lineInput[x][posDiff-1] = 0;
                }
                printf("elf %d = %s\n",x,lineInput[x]);

                for(int y = 0; y < strlen(lineInput[x]); y++)
                {
                    char c = lineInput[x][y];
                    //printf("%d; %c = %d\n", x, c, getPriority(c));
                    compartment[x][getPriority(lineInput[x][y])] |= 1;
                    //visualizeCompartment(compartment[x]);
                }
            }
            else
            {
                printf("total = %d\n", total);
                processingComplete = 1;
                break;
                //EOF reached
            }
        }

        if (!processingComplete)
        {
            for (int x=0;x<ELVES_PER_GROUP;x++)
            {
                for (int y=1;y<=MAX_PRIORITIES;y++)
                {
                    compartmentSum[y] += compartment[x][y];
                }
            }

            visualizeCompartment(compartmentSum);

            for (int y=1;y<=MAX_PRIORITIES;y++)
            {
                if (compartmentSum[y] == 3)
                {
                    priority = y;
                    total += priority;
                    printf("match for elf Group %d: %d %c %d\n", elfGroupCounter, y, getPriorityReverse(y), total);
                    break;
                }
            }
        }
    }
}

int main()
{
    processData();
}