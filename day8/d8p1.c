#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char treeMatrix[99][99];    //by inspection;
int rowSize = 0;
int colSize = 0;

void removeTrailingCharacters(char* input)
{
    char* delimiters = "\n";
    strtok(input,delimiters);
}

void processData2()
{
    bool visibile = false;
    bool blockedView = false;
    int visibleTrees = 0;
    for(int row = 0; row < rowSize; row++)
    {
        for(int col = 0; col < colSize; col++)
        {
            // for each element in the array...


            // if on the outside ring, is inherently visible
            if ((col == 0) || (col == (colSize-1)) || (row == 0) || (row == (rowSize-1)))
            {
                visibleTrees++;
                continue;
            }

            //check visibility from left...
            blockedView = false;
            for(int col2 = 0; (col2 < col) && !blockedView; col2++)
            {
                if (treeMatrix[row][col2] >= treeMatrix[row][col])
                {
                    blockedView = true;
                    break;
                }
            }
            if (!blockedView)
            {
                visibleTrees++;
                continue;
            }

            //check visibility from right...
            blockedView = false;
            for(int col2 = (colSize-1); (col2 > col) && !blockedView; col2--)
            {
                if (treeMatrix[row][col2] >= treeMatrix[row][col])
                {
                    blockedView = true;
                    break;
                }
            }
            if (!blockedView)
            {
                visibleTrees++;
                continue;
            }

            //check visibility from top...
            blockedView = false;
            for(int row2 = 0; (row2 < row) && !blockedView; row2++)
            {
                if (treeMatrix[row2][col] >= treeMatrix[row][col])
                {
                    blockedView = true;
                    break;
                }
            }
            if (!blockedView)
            {
                visibleTrees++;
                continue;
            }

            //check visibility from bottom...
            blockedView = false;
            for(int row2 = (rowSize-1); (row2 > row) && !blockedView; row2--)
            {
                if (treeMatrix[row2][col] >= treeMatrix[row][col])
                {
                    blockedView = true;
                    break;
                }
            }
            if (!blockedView)
            {
                visibleTrees++;
                continue;
            }
        }
    }
    printf("visible trees = %d\n",visibleTrees);
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

    while(1)
    {
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        if (ptr)
        {
            removeTrailingCharacters(lineInput);
            if (!colSize) colSize = strlen(lineInput);
            strcpy(&treeMatrix[rowSize][0],lineInput);

            printf("%d %s\n",rowSize, lineInput);
            rowSize++;
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
}

int main()
{
    processData();
    processData2();
}