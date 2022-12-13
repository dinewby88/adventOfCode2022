#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUMBER_OF_ROWS  9
char containerRow[NUMBER_OF_ROWS+1][255] = {0};

typedef struct
{
    int times;
    int source;
    int destination;
}myStruct_t;

void populateStruct(myStruct_t* x, char* line)
{
    char delimiters[] = " \n";
    char* token;
    //"move 3 from 4 to 6"
    // 1    2 3    4 5  6
    token = strtok(line, delimiters);   //1
    token = strtok(NULL, delimiters);   //2
    x->times = atoi(token);
    token = strtok(NULL, delimiters);   //3
    token = strtok(NULL, delimiters);   //4
    x->source = atoi(token);
    token = strtok(NULL, delimiters);   //5
    token = strtok(NULL, delimiters);   //6
    x->destination = atoi(token);
}

void moveContainer(myStruct_t* input)
{
    for(int x=0; x < input->times ;x++)
    {
        int srcLen = strlen(containerRow[input->source]);
        int destLen = strlen(containerRow[input->destination]);
        containerRow[input->destination][destLen] = containerRow[input->source][srcLen-1];
        containerRow[input->destination][destLen+1] = 0;
        containerRow[input->source][srcLen-1] = 0;
    }
}

void printTopContainers(void)
{
    printf("\n");
    for(int x=1; x <= NUMBER_OF_ROWS; x++)
    {
        int strLen = strlen(containerRow[x]);
        printf("%c",containerRow[x][strLen-1]);
    }
    printf("\n");
}
void processData()
{
    char filename[] = "input.txt";
    char lineInput[100];
    char* ptr;
    FILE* fptr = fopen(filename,"r");

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    strcpy(containerRow[1],"DLJRVGF");
    strcpy(containerRow[2],"TPMBVHJS");
    strcpy(containerRow[3],"VHMFDGPC");
    strcpy(containerRow[4],"MDPNGQ");
    strcpy(containerRow[5],"JLHNF");
    strcpy(containerRow[6],"NFVQDGTZ");
    strcpy(containerRow[7],"FDBL");
    strcpy(containerRow[8],"MJBSVDN");
    strcpy(containerRow[9],"GLD");

    while(1)
    {
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        
        if (ptr)
        {
            printf("%s",lineInput);
            myStruct_t myStruct = {0};
            populateStruct(&myStruct,lineInput);
            moveContainer(&myStruct);
            //process line of data
        }
        else
        {
            //EOF reached
            printTopContainers();
            break;
        }
    }
}

int main()
{
    processData();
}