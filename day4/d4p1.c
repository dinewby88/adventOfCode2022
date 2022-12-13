#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    int set1_min;
    int set1_max;
    int set2_min;
    int set2_max;
} myStruct_t;

bool detectSubset(myStruct_t* x)
{
    if (x->set1_min >= x->set2_min && x->set1_max <= x->set2_max)
    {
        return true;
    }
    if (x->set2_min >= x->set1_min && x->set2_max <= x->set1_max)
    {
        return true;
    }
    return false;
}

void populateStruct(myStruct_t* x, char* line)
{
    char delimiters[] = ",-";
    char* token;
    token = strtok(line, delimiters);
    x->set1_min = atoi(token);
    token = strtok(NULL, delimiters);
    x->set1_max = atoi(token);

    token = strtok(NULL, delimiters);
    x->set2_min = atoi(token);
    token = strtok(NULL, delimiters);
    x->set2_max = atoi(token);
}

void processData()
{
    char filename[] = "input.txt";
    char lineInput[100];
    char lineInput2[100];
    char* ptr;
    FILE* fptr = fopen(filename,"r");

    int total = 0;
    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(1)
    {
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        
        if (ptr)
        {
            myStruct_t myStruct = {0};

            int inputLength = strlen(lineInput);
            // remove trailing new line in calculations
            if (lineInput[inputLength-1] == '\n')
            {
                lineInput[inputLength-1] = 0;
            }

            strcpy(lineInput2, lineInput);

            populateStruct(&myStruct, lineInput);
            bool subset = detectSubset(&myStruct);
            total += subset;
            printf("%s, subset = %d %d\n", lineInput2, subset, total);
            //process line of data
        }
        else
        {
            //EOF reached
            break;
        }
    }
}

int main()
{
    processData();
}