#include "monkey.h"

int monkeyOp_add(int x, int y)
{
    return x+y;
}

int monkeyOp_mul(int x, int y)
{
    return x*y;
}

int monkeyOp_square(int x, int y)
{
    // y is just dummy here, but kept it in so all the functions can have the same args
    return x*x;
}