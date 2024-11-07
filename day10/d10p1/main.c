#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFileToBuffer(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory for the buffer
    char *buffer = (char*)malloc(fileSize + 1);  // +1 for null terminator
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Read file into buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the buffer
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}

char* readLineFromBuffer(char** currentPos) {
    if (currentPos == NULL || *currentPos == NULL || **currentPos == '\0') {
        return NULL;  // End of buffer
    }

    // Pointer to the start of the line
    char* lineStart = *currentPos;
    char* lineEnd = lineStart;

    // Find the end of the line by looking for \r or \n
    while (*lineEnd != '\r' && *lineEnd != '\n' && *lineEnd != '\0') {
        lineEnd++;
    }

    // Calculate line length
    size_t lineLength = lineEnd - lineStart;

    // Allocate memory for the line (including null terminator)
    char* line = (char*)malloc(lineLength + 1);
    if (!line) {
        return NULL;  // Memory allocation failed
    }

    // Copy the line and add null terminator
    strncpy(line, lineStart, lineLength);
    line[lineLength] = '\0';

    // Advance currentPos to the next line
    *currentPos = lineEnd;

    // Skip over line endings (\r, \n, or \r\n)
    if (**currentPos == '\r') (*currentPos)++;
    if (**currentPos == '\n') (*currentPos)++;

    return line;
}

void cycle_tick(int x, int* cycle, int numCycles)
{
    // consider the signal strength on this cycle
    static int considerSignalStrengthOnCycle = 20;
    static int sumSignalStrength = 0;
    while(numCycles--)
    {
        (*cycle)++;
        if (*cycle == considerSignalStrengthOnCycle)
        {
            int signalStrength = *cycle * x;
            sumSignalStrength += signalStrength;
            printf("signalStrength at cycle %d = %d, sum = %d\n", *cycle, signalStrength,sumSignalStrength);
            // increase the next time to check signal strength
            considerSignalStrengthOnCycle += 40;
        }
    }
}

void process_noop(int* x, int* cycle)
{
    cycle_tick(*x,cycle,1);
    //printf("noop: after cycle %d x %d\n", *cycle, *x);
}

void process_addx(int* x, int* cycle, int adder)
{
    cycle_tick(*x,cycle,2);
    *x += adder;
    //printf("addx: after cycle %d x %d\n", *cycle, *x);
}

int main(void)
{
    printf("hello world\n");
    char* buffer = readFileToBuffer("input.txt");
    char* currentPos = buffer;
    char* strLine = NULL;
    int x = 1;
    int cycle = 0;
    do
    {
        strLine = readLineFromBuffer(&currentPos);
        if (strLine == NULL) break;
        //printf("%s\n",strLine);
        if (strncmp(strLine,"addx",4) == 0)
        {
            // process addx command
            int adder = atoi(strLine+5);
            process_addx(&x, &cycle, adder);
        }
        if (strncmp(strLine,"noop",4) == 0)
        {
            // process noop command
            process_noop(&x, &cycle);
        }

        free(strLine);
    } while(1);


    //read lines

    free(buffer);
}