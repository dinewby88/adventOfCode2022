#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRIORITIES 52

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
    char lineInput[100];
    int compartment1[MAX_PRIORITIES+1];
    int compartment2[MAX_PRIORITIES+1];
    int total = 0;
    int posDiff;
    int priority;
    int lineCounter = 0;
    char* ptr;
    FILE* fptr = fopen(filename,"r");

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(1)
    {
        for (int x=0;x<=MAX_PRIORITIES;x++)
        {
            compartment1[x] = 0;
            compartment2[x] = 0;
        }
        lineCounter++;
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        
        if (ptr)
        {

            posDiff = strlen(lineInput);
            // remove trailing new line in calculations
            if (lineInput[posDiff-1] == '\n')
            {
                posDiff -= 1;
            }

            for(int x = 0; x < posDiff/2; x++)
            {
                char c = lineInput[x];
                //printf("%d; %c = %d\n", x, c, getPriority(c));
                compartment1[getPriority(lineInput[x])] |= 1;
                //visualizeCompartment(compartment1);
            }

            for(int x = posDiff/2; x < posDiff; x++)
            {
                char c = lineInput[x];
                //printf("%d; %c = %d\n", x, c, getPriority(c));
                compartment2[getPriority(lineInput[x])] |= 1;
                //visualizeCompartment(compartment2);
            }

            for (int x=1;x<=MAX_PRIORITIES;x++)
            {
                if (compartment1[x] && compartment2[x])
                {
                    priority = x;
                    total += priority;
                    printf("match on LINE %d: %d %c %d\n", lineCounter, x, getPriorityReverse(x), total);
                    break;
                }
            }

            //printf("%s = %d\n",lineInput, priority);
        }
        else
        {
            printf("total = %d\n", total);
            break;
            //EOF reached
        }
    }

}

int main()
{
    processData();
}