#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_ELVES_TO_COUNT  3
int maxCalories[MAX_ELVES_TO_COUNT] = {0};
int elfNumber = 0;

void readData()
{
    char filename[] = "input.txt";
    char lineInput[50];
    int totalCalories = 0;
    bool recordNeedsReporting = 0;
    bool recordInProgress = 0;
    int currentElfNumber = 1;
    FILE* fptr = fopen(filename,"r");
    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(1)
    {
        char* ptr = fgets(lineInput,sizeof(lineInput),fptr);
        bool exitFlag = 0;
        if (ptr)
        {
            int cal = atoi(lineInput);
            if (cal)
            {
                //printf("adding %d cals to %d elf\n", cal, elfNumber);
                totalCalories += cal;
                recordInProgress = 1;
            }
            else
            {
                recordNeedsReporting = 1;
            }
        }
        else if (recordInProgress)
        {
            recordNeedsReporting = 1;
            exitFlag = 1;
        }

        if (recordNeedsReporting)
        {
            //printf("finishing  elf # %d - %d total cal\n", currentElfNumber, totalCalories);
            for(int x = 0; x < MAX_ELVES_TO_COUNT; x++)
            {
                if (totalCalories > maxCalories[x]) 
                {
                    // need to push everything down to add here...
                    for (int y = MAX_ELVES_TO_COUNT - 2; y >= x; y--)
                    {
                        maxCalories[y+1] = maxCalories[y];
                    }
                    maxCalories[x] = totalCalories;
                    elfNumber = currentElfNumber;
                    //printf("** updating max calories %d = %d **\n", x, totalCalories);
                    break;
                }
            }

            totalCalories = 0;
            currentElfNumber++;
            recordNeedsReporting = 0;
            recordInProgress = 0;

            //printf("top %d:\n", MAX_ELVES_TO_COUNT);
            for(int x = 0; x < MAX_ELVES_TO_COUNT; x++)
            {
                //printf("%d = %d\n",x,maxCalories[x]);
            }
        }

        if (exitFlag)
        {
            break;
        }
    }
}

// GDB was having issues finding the input files because of problems with cwd, so using this to make sure the cwd is expected.
int printCWD()
{
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}

int main()
{
    printCWD();
    readData();

    int sum = 0;
    for(int x = 0; x < MAX_ELVES_TO_COUNT; x++)
    {
        //printf("elf %d had calories %d\n", x, maxCalories[x]);
        sum += maxCalories[x];
    }

    printf("total of top %d elves = %d\n", MAX_ELVES_TO_COUNT, sum);
    return 0;
}