#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COUNTING_MATRIX_SIZE    500
#define NUMBER_OF_KNOTS         10
#define GRID_SIZE               ((NUMBER_OF_KNOTS-1)*2+1)
#define GRID_MIDDLE             (NUMBER_OF_KNOTS-1)

typedef struct
{
    int x;
    int y;
}coord_t;

coord_t knot_coords[NUMBER_OF_KNOTS] = {0};

int countingMatrix[COUNTING_MATRIX_SIZE][COUNTING_MATRIX_SIZE] = {0};
char visualizationMatrix[GRID_SIZE][GRID_SIZE];

void removeTrailingCharacters(char* input)
{
    char* delimiters = "\n";
    strtok(input,delimiters);
}

void printGrid()
{
    coord_t relative_knot_coords;

    //clear the grid
    for(int x=0;x<GRID_SIZE;x++)
    {
        for(int y=0;y<GRID_SIZE;y++)
        {
            visualizationMatrix[x][y] = '-';
        }
    }

    for(int knot=NUMBER_OF_KNOTS-1;knot>=0;knot--)
    {
        relative_knot_coords.x = knot_coords[knot].x-knot_coords[0].x+GRID_MIDDLE;
        relative_knot_coords.y = knot_coords[knot].y-knot_coords[0].y+GRID_MIDDLE;

        visualizationMatrix[relative_knot_coords.x][relative_knot_coords.y] = knot+'0';
    }

    for(int y=0;y<GRID_SIZE;y++)
    {
        for(int x=0;x<GRID_SIZE;x++)
        {
            printf("%c",visualizationMatrix[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

FILE* fptr_write;
void processData2(char dir, int magnitude)
{
    for(int x = 0; x < magnitude; x++)
    {
        //move head
        switch(dir)
        {
            case 'R':
                knot_coords[0].x++;
                break;
            case 'L':
                knot_coords[0].x--;
                break;
            case 'U':
                knot_coords[0].y--;
                break;
            case 'D':
                knot_coords[0].y++;
                break;
            default:
                break;
        }

        // printf("moving 0\n");
        // printGrid();
        for(int k=1;k<NUMBER_OF_KNOTS;k++)
        {
            //printf("moving %d\n",k);
            if (knot_coords[k].x == knot_coords[k-1].x)// same row
            {
                if (knot_coords[k].y < knot_coords[k-1].y-1)
                {
                    knot_coords[k].y++;
                }
                else if (knot_coords[k].y > knot_coords[k-1].y+1)
                {
                    knot_coords[k].y--;
                }
            }
            else if (knot_coords[k].y == knot_coords[k-1].y)// same col
            {
                if (knot_coords[k].x < knot_coords[k-1].x-1)
                {
                    knot_coords[k].x++;
                }
                else if (knot_coords[k].x > knot_coords[k-1].x+1)
                {
                    knot_coords[k].x--;
                }
            }
            else //neither match
            {
                //x is far away
                if (knot_coords[k].x < knot_coords[k-1].x-1)
                {
                    //y is far left
                    if (knot_coords[k].y < knot_coords[k-1].y-1)
                    {
                        knot_coords[k].x++;
                        knot_coords[k].y++;
                    }
                    //y is far right
                    else if (knot_coords[k].y > knot_coords[k-1].y+1)
                    {
                        knot_coords[k].x++;
                        knot_coords[k].y--;
                    }
                    else
                    {
                        knot_coords[k].x++;
                        knot_coords[k].y = knot_coords[k-1].y;
                    }
                }
                //x is far away
                else if (knot_coords[k].x > knot_coords[k-1].x+1)
                {
                    //y is far left
                    if (knot_coords[k].y < knot_coords[k-1].y-1)
                    {
                        knot_coords[k].x--;
                        knot_coords[k].y++;
                    }
                    //y is far right
                    else if (knot_coords[k].y > knot_coords[k-1].y+1)
                    {
                        knot_coords[k].x--;
                        knot_coords[k].y--;
                    }
                    else
                    {
                        knot_coords[k].x--;
                        knot_coords[k].y = knot_coords[k-1].y;
                    }
                }
                //y is far away
                else if (knot_coords[k].y < knot_coords[k-1].y-1)
                {
                    knot_coords[k].y++;
                    knot_coords[k].x = knot_coords[k-1].x;
                }
                else if (knot_coords[k].y > knot_coords[k-1].y+1)
                {
                    knot_coords[k].y--;
                    knot_coords[k].x = knot_coords[k-1].x;
                }
            }
            //printGrid();
        }
        //update places
        countingMatrix[knot_coords[NUMBER_OF_KNOTS-1].x][knot_coords[NUMBER_OF_KNOTS-1].y] |= 1;
    }
}

void processData()
{
    //char filename[] = "largerExampleInput.txt";
    char filename[] = "input.txt";
    FILE* fptr = fopen(filename,"r");
    char* ptr;
    char lineInput[256];

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    printf("GRID_SIZE = %d\n",GRID_SIZE);
    //init knot_coords
    for(int x=0;x<NUMBER_OF_KNOTS;x++)
    {
        knot_coords[x] = (coord_t){100,100};
    }

    //printGrid();
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

            for(int x=0;x<NUMBER_OF_KNOTS;x++)
            {
                if ((knot_coords[x].x < 0) || (knot_coords[x].x < 0))
                {
                    exit(-1);
                }
            }

            //printGrid();
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