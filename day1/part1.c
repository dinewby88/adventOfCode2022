#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int maxCalories = 0;
int elfNumber = 0;

void readData()
{
    char filename[] = "input.txt";
    char lineInput[50];
    int totalCalories = 0;
    bool recordNeedsReporting = 0;
    int currentElfNumber = 1;
    FILE* fptr = fopen(filename,"r");
    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    while(fgets(lineInput,sizeof(lineInput),fptr) != 0)
    {
        int cal = atoi(lineInput);
        if (cal)
        {
            //printf("adding %d cals to %d elf\n", cal, elfNumber);
            totalCalories += cal;
            recordNeedsReporting = 1;
        }
        else
        {
            //printf("finishing %d elf. %d total cal\n", currentElfNumber, totalCalories);
            if (totalCalories > maxCalories) 
            {
                maxCalories = totalCalories;
                elfNumber = currentElfNumber;
                //printf("** updating max calories **\n");
            }
            totalCalories = 0;
            currentElfNumber++;
            recordNeedsReporting = 0;
        }
    }
    
    if (recordNeedsReporting)
    {
            //printf("finishing %d elf. %d total cal\n", currentElfNumber, totalCalories);
            if (totalCalories > maxCalories) 
            {
                maxCalories = totalCalories;
                elfNumber = currentElfNumber;
                //printf("** updating max calories **\n");
            }
            totalCalories = 0;
            currentElfNumber++;
            recordNeedsReporting = 0;
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
    printf("elf %d had most calories %d\n", elfNumber, maxCalories);
    return 0;
}