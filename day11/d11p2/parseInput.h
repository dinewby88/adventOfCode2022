#include "monkey.h"

int (*parse_operation(char* op_str))(int, int);
int parse_monkeys(const char* filename, monkey_t* monkeys, int max_monkeys);
