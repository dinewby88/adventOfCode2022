#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monkey.h"
#define MAX_LINE_LENGTH 256
// Helper to parse and set the operation function
int (*parse_operation(char* op_str))(int, int)
{
    if (strstr(op_str, "old * old")) return monkeyOp_square;
    if (strstr(op_str, "*")) return monkeyOp_mul;
    if (strstr(op_str, "+")) return monkeyOp_add;
    return NULL;
}

// Function to parse the text file into an array of monkeys
int parse_monkeys(const char* filename, monkey_t* monkeys, int max_monkeys) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int monkey_index = -1;

    while (fgets(line, sizeof(line), file)) {
        // Parse "Monkey X:"
        if (sscanf(line, "Monkey %d:", &monkey_index) == 1 && monkey_index < max_monkeys) {
            monkeys[monkey_index].items.head = NULL;
            monkeys[monkey_index].items.tail = NULL;
        }
        // Parse "Starting items"
        else if (strstr(line, "Starting items:")) {
            char* items_str = strstr(line, ":") + 1;
            char* token = strtok(items_str, ", ");
            while (token) {
                dataStructure_t x = {.worryLevel = atoi(token)};
                queue_add(&monkeys[monkey_index].items,x);
                token = strtok(NULL, ", ");
            }
        }
        // Parse "Operation"
        else if (strstr(line, "Operation:")) {
            char op_str[MAX_LINE_LENGTH] = {0};
            char* op_pos = strstr(line, "Operation: ");
            int operand = -1;
            // Now we search for "Operation: " (after skipping leading spaces) 
            int rtnval = sscanf(op_pos, "  Operation: new = old %s %d", op_str, &operand);
            monkeys[monkey_index].operand = operand;
            monkeys[monkey_index].operation = parse_operation(line);
        }
        // Parse "Test"
        else if (strstr(line, "Test: divisible by")) {
            sscanf(line, " Test: divisible by %d", &monkeys[monkey_index].divisor);
        }
        // Parse "If true" for trueMonkey
        else if (strstr(line, "If true: throw to monkey")) {
            sscanf(line, " If true: throw to monkey %d", &monkeys[monkey_index].trueMonkey);
        }
        // Parse "If false" for falseMonkey
        else if (strstr(line, "If false: throw to monkey")) {
            sscanf(line, " If false: throw to monkey %d", &monkeys[monkey_index].falseMonkey);
        }
        monkeys[monkey_index].initialized = true;
    }

    fclose(file);
    return 0;
}