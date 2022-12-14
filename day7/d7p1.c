#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_FILENAME_SIZE 20
typedef struct file_t
{
    int size;
    char name[MAX_FILENAME_SIZE];
    struct file_t* next;
} file_t;

typedef struct directory_t
{
    char name[MAX_FILENAME_SIZE];
    struct directory_t* parent;
    struct directory_t* child;
    struct directory_t* next;
    struct directory_t* prev;
    struct file_t* fileHead;
} directory_t;


directory_t rootDir = {"/", &rootDir, NULL,NULL};
directory_t* currentDir = 0;

void cdRoot(void)
{
    currentDir = &rootDir;
}

void cdParentDir(void)
{
    currentDir = currentDir->parent;
}

void cd(char* name)
{
    directory_t* ptr = currentDir->child;
    if (strcmp(ptr->name, name) == 0)
    {
        //found directory
        currentDir = ptr;
        return;
    }

    while (ptr->next)
    {
        if (strcmp(ptr->next->name, name) == 0)
        {
            //found directory
            currentDir = ptr->next;
            return;
        }
    }

    printf("error finding directory\n");
    exit(-1);
}

void printFolderStructure(directory_t* dir, int level)
{
    for(int x=0;x<level;x++)
    {
        printf(" ");
    }
    printf("-%s\n", dir->name);

    directory_t* ptr = dir->child;

    if (ptr)
    {
        printFolderStructure(ptr,level+1);

        while(ptr->next)
        {
            printFolderStructure(ptr->next,level+1);
            ptr = ptr->next;
        }
    }

    file_t* fptr = dir->fileHead;

    if (fptr)
    {
        for(int x=0;x<=level;x++)
        {
            printf(" ");
        }
        printf("*%s %d\n",fptr->name,fptr->size);
    }

    while(fptr->next)
    {
        fptr = fptr->next;
        for(int x=0;x<=level;x++)
        {
            printf(" ");
        }
        printf("*%s %d\n",fptr->name,fptr->size);
    }
}

void createFile(directory_t* parentDir, char* name, int size)
{
    file_t* ptr = parentDir->fileHead;
    file_t* newFile = 0;
    bool childrenExist = ptr;
    bool fileExists = false;
    if (childrenExist)
    {
        //traverse to end of list
        while(ptr->next)
        {
            if (strcmp(ptr->next->name, name) == 0)
            {
                //file already exists, nothing to do
                fileExists = true;
                break;
            }
            ptr = ptr->next;
        }
    }

    if (!childrenExist || (childrenExist && !fileExists))
    {
        if (strlen(name) > MAX_FILENAME_SIZE)
        {
            printf("FILE NAME OVERFLOW\n");
            exit(-1);
        }
        newFile = calloc(sizeof(file_t),1);
        strcpy(newFile->name, name);
        newFile->next = NULL;
        newFile->size = size;
    }

    if (!childrenExist)
    {
        parentDir->fileHead = newFile;
    }

    if (childrenExist && !fileExists)
    {
        ptr->next = newFile;
    }
}

void createDirectory(directory_t* parentDir, char* name)
{
    //appends the child directory name if not present on the list.
    directory_t* ptr = parentDir->child;
    bool directoryExists = false;
    bool childrenExist = parentDir->child;
    directory_t* newDir = 0;
    if (childrenExist)
    {
        while(ptr->next)
        {
            if (strcmp(ptr->next->name, name) == 0)
            {
                //directory already exists, nothing to do
                directoryExists = true;
                break;
            }

            ptr = ptr->next;
        }
    }

    if (!childrenExist || (childrenExist && !directoryExists))
    {
        // ptr now points to last element in list.
        if (strlen(name) > MAX_FILENAME_SIZE)
        {
            printf("FILE NAME OVERFLOW\n");
            exit(-1);
        }
        newDir = calloc(sizeof(directory_t),1);
        strcpy(newDir->name, name);
        newDir->parent = parentDir;
        newDir->next = NULL;
        newDir->fileHead = NULL;
    }

    if (!childrenExist)
    {
        parentDir->child = newDir;
    }

    if (childrenExist && !directoryExists)
    {
        ptr->next = newDir;
    }
}

void removeTrailingCharacters(char* input)
{
    char* delimiters = "\n";
    strtok(input,delimiters);
}

void processData()
{
    char filename[] = "input.txt";
    FILE* fptr = fopen(filename,"r");
    char* ptr;
    char lineInput[100];

    if (!fptr) 
    {
        printf("err %s\n",strerror(errno));
        return;
    }

    char* delimiters = " ";
    char* ptr2;
    char* ptr3;

    while(1)
    {
        ptr = fgets(lineInput,sizeof(lineInput),fptr);
        if (ptr)
        {
            removeTrailingCharacters(ptr);
            if (strcmp("$ cd /",ptr) == 0)
            {
                cdRoot();
                continue;
            }

            if (strcmp("$ cd ..",ptr) == 0)
            {
                cdParentDir();
                continue;
            }

            if (strncmp("$ cd", ptr, strlen("$ cd")) == 0)
            {
                ptr2 = strtok(lineInput,delimiters);
                ptr2 = strtok(NULL,delimiters);
                ptr2 = strtok(NULL,delimiters);
                cd(ptr2);
                continue;
            }

            if (strcmp("$ ls", ptr) == 0)
            {
                while(1)
                {
                    int pos1 = ftell(fptr);
                    ptr = fgets(lineInput,sizeof(lineInput),fptr);
                    if (ptr)
                    {
                        removeTrailingCharacters(ptr);
                        if (ptr[0] == '$')
                        {
                            //next command...
                            fseek(fptr,pos1,SEEK_SET);
                            break;
                        }
                        ptr2 = strtok(lineInput,delimiters);
                        ptr3 = strtok(NULL,delimiters);
                        if (strcmp(ptr2,"dir") == 0)
                        {
                            printf("DIR %s\n", ptr3);
                            createDirectory(currentDir,ptr3);
                            // directory
                        }
                        else
                        {
                            printf("file %s size %d\n",ptr3, atoi(ptr2));
                            createFile(currentDir, ptr3, atoi(ptr2));
                        }
                    }
                    else
                    {
                        break;
                        //EOF
                    }
                }
            }
            //process line of data
        }
        else
        {
            printFolderStructure(&rootDir, 0);
            //EOF reached
            break;
        }
    }

}

int main()
{
    processData();
}