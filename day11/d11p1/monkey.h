#include "queue.h"
#include <stdbool.h>

typedef struct
{
    queue_t items;
    int (*operation)(int x, int y);
    int operand;
    int divisor;
    int trueMonkey;
    int falseMonkey;
    bool initialized;
    int inspectionCount;
} monkey_t;

int monkeyOp_add(int x, int y);
int monkeyOp_mul(int x, int y);
int monkeyOp_square(int x, int y);