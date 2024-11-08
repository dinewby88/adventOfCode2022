#include "monkey.h"

long long monkeyOp_add(int x, int y)
{
    return x+y;
}

long long monkeyOp_mul(int x, int y)
{
    return x*y;
}

long long monkeyOp_square(int x, int y)
{
    // y is just dummy here, but kept it in so all the functions can have the same args
    return (long long)x*x;
}