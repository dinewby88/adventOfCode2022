#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COUNTING_MATRIX_SIZE    500
typedef struct
{
    int x;
    int y;
}coord_t;

coord_t h_coord = {100,100};
coord_t t_coord = {100,100};

int countingMatrix[COUNTING_MATRIX_SIZE][COUNTING_MATRIX_SIZE] = {0};

void removeTrailingCharacters(char* input)
{
    char* delimiters = "\n";
    strtok(input,delimiters);
}

void printGrid()
{
    coord_t t;
    coord_t h = {2,2};
    t.x = h_coord.x-t_coord.x+2;
    t.y = h_coord.y-t_coord.y+2;

    for(int x=0;x<5;x++)
    {
        for(int y=0;y<5;y++)
        {
            if(h.x == x && h.y == y)
            {
                printf("H");
            }
            else if(t.x == x && t.y == y)
            {
                printf("T");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void processData2(char dir, int magnitude)
{
    for(int x = 0; x < magnitude; x++)
    {
        //move head
        switch(dir)
        {
            case 'R':
                h_coord.x++;
                break;
            case 'L':
                h_coord.x--;
                break;
            case 'U':
                h_coord.y--;
                break;
            case 'D':
                h_coord.y++;
                break;
            default:
                break;
        }

        //move tail
        if (t_coord.x == h_coord.x)// same row
        {
            if (t_coord.y < h_coord.y-1)
            {
                t_coord.y++;
            }
            else if (t_coord.y > h_coord.y+1)
            {
                t_coord.y--;
            }
        }
        else if (t_coord.y == h_coord.y)// same col
        {
            if (t_coord.x < h_coord.x-1)
            {
                t_coord.x++;
            }
            else if (t_coord.x > h_coord.x+1)
            {
                t_coord.x--;
            }
        }
        else //neither match
        {
            //x is far away
            if (t_coord.x < h_coord.x-1)
            {
                t_coord.x++;
                t_coord.y = h_coord.y;
            }
            else if (t_coord.x > h_coord.x+1)
            {
                t_coord.x--;
                t_coord.y = h_coord.y;
            }

            //y is far away
            if (t_coord.y < h_coord.y-1)
            {
                t_coord.y++;
                t_coord.x = h_coord.x;
            }
            else if (t_coord.y > h_coord.y+1)
            {
                t_coord.y--;
                t_coord.x = h_coord.x;
            }
        }

        //update places
        countingMatrix[t_coord.x][t_coord.y] |= 1;
        //printGrid();
    }
}

void processData()
{
    char filename[] = "input.txt";
    FILE* fptr = fopen(filename,"r");
    char* ptr;
    char lineInput[256];

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }
        
    printGrid();
    while(1)
    {
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        if (ptr)
        {
            removeTrailingCharacters(lineInput);
            printf("%s\n", lineInput);
            char* delimiters = " ";
            char* ptr1;
            char* ptr2;
            ptr1 = strtok(lineInput,delimiters);
            ptr2 = strtok(NULL,delimiters);
            processData2(ptr1[0],atoi(ptr2));
        }
        else
        {
            if (ferror(fptr))
            {
                printf("ERROR\n");
                break;
            }
            if (feof(fptr))
            {
                printf("EOF\n");
                break;
            }
            break;
            // EOF
        }
    }

    int totalSpotsVisited = 0;
    for(int x=0;x<COUNTING_MATRIX_SIZE;x++)
    {
        for(int y=0;y<COUNTING_MATRIX_SIZE;y++)
        {
            totalSpotsVisited += countingMatrix[x][y];
        }
    }

    printf("totalSpotsVisited = %d\n",totalSpotsVisited);
}

int main()
{
    processData();
}