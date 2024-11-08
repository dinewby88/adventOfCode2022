#include "queue.h"
#include <stdbool.h>

typedef struct
{
    queue_t items;
    long long (*operation)(int x, int y);
    int operand;
    int divisor;
    int trueMonkey;
    int falseMonkey;
    bool initialized;
    int inspectionCount;
    int trueThrowCount;
    int falseThrowCount;
} monkey_t;

long long monkeyOp_add(int x, int y);
long long monkeyOp_mul(int x, int y);
long long monkeyOp_square(int x, int y);