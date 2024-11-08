#include <stdio.h>
#include "monkey.h"

#define MAX_MONKEYS 10
#define NO_ROUNDS 10000
monkey_t monkeys[MAX_MONKEYS] = {0};

void printMonkeys_verbose(void)
{
    // Print the parsed monkeys
    for (int i = 0; i < MAX_MONKEYS; i++) {
        if (monkeys[i].initialized == false) continue; // Skip uninitialized monkeys
        printf("Monkey %d:\n", i);
        printf("  Operation: %p\n", (void*)monkeys[i].operation);
        printf("  Operand: %d\n", monkeys[i].operand);
        printf("  Divisor: %d\n", monkeys[i].divisor);
        printf("  True Monkey: %d\n", monkeys[i].trueMonkey);
        printf("  False Monkey: %d\n", monkeys[i].falseMonkey);
        // Print queue items
        queueElement_t* item = monkeys[i].items.head;
        printf("  Starting items:");
        while (item) {
            printf(" %d", item->data.worryLevel);
            item = item->next;
        }
        printf("\n");
    }
}

void printMonkeys_inspectionCount(void)
{
    // Print the parsed monkeys
    printf("Inspection Counts:\n");
    for (int i = 0; i < MAX_MONKEYS; i++) {
        if (monkeys[i].initialized == false) continue; // Skip uninitialized monkeys
        printf("Monkey %d: %d %d %d\n", i,monkeys[i].inspectionCount, monkeys[i].trueThrowCount, monkeys[i].falseThrowCount);
    }
}

void multiplyLargestInspectionCounts(void)
{
    long long first = monkeys[0].inspectionCount;
    long long second = monkeys[1].inspectionCount;

    // Ensure first is the greatest and second is the second greatest
    if (first < second) 
    {
        long long temp = first;
        first = second;
        second = temp;
    }

    for (int i = 2; i < MAX_MONKEYS; i++)
    {
        if (monkeys[i].initialized == false) continue; // Skip uninitialized monkeys
        if (monkeys[i].inspectionCount > first) {
            second = first;  // Update second to the previous greatest
            first = monkeys[i].inspectionCount;  // Update first to the current number
        } else if (monkeys[i].inspectionCount > second) {
            second = monkeys[i].inspectionCount;  // Update second if it's smaller than the current number
        }
    }
    printf("The two greatest numbers are: %d and %d\n", first, second);
    printf("multiplied: %lld\n",first*second);
}

void printMonkeys_justItems(void)
{
    // Print the parsed monkeys
    for (int i = 0; i < MAX_MONKEYS; i++) {
        if (monkeys[i].initialized == false) continue; // Skip uninitialized monkeys
        printf("Monkey %d:", i);
        // Print queue items
        queueElement_t* item = monkeys[i].items.head;
        while (item) {
            printf(" %d", item->data.worryLevel);
            item = item->next;
        }
        printf("\n");
    }
}

int main()
{
     if (parse_monkeys("input.txt", monkeys, MAX_MONKEYS) == 0) {
        // Successfully parsed the monkeys
        printf("Parsed monkeys successfully.\n");
        printMonkeys_verbose();
        //printMonkeys_justItems();

    } else {
        printf("Failed to parse monkeys.\n");
        return __LINE__;
    }

    // calc supermod
    int supermod = 1;

    for(int monkeyIdx = 0; monkeyIdx < MAX_MONKEYS; monkeyIdx++)
    {
        if (!monkeys[monkeyIdx].initialized) break;
        supermod = supermod * monkeys[monkeyIdx].divisor;
    }
    // printf("supermod = %d\n",supermod);

    for(int round = 1; round <= NO_ROUNDS; round++)
    {
        // for each monkey
        // printf("round %d\n", round);
        for(int monkeyIdx = 0; monkeyIdx < MAX_MONKEYS; monkeyIdx++)
        {
            monkey_t* currentMonkey = &monkeys[monkeyIdx];
            // for each item the monkey has
            queueElement_t* currentItem = monkeys[monkeyIdx].items.head;
            if (!currentItem) continue;    //monkey has no items
            // monkey handles items
            // printf("Monkey %d:\n", monkeyIdx);

            while(currentItem)
            {
                queueElement_t* nextItem = currentItem->next;
                // printMonkeys_justItems();
                // monkey inspects items, so increase worry level
                // printf("  Monkey inspects an item with worry level %d\n",currentItem->data.worryLevel);
                long long prevWorryLevel = currentItem->data.worryLevel;
                currentItem->data.worryLevel = currentMonkey->operation(currentItem->data.worryLevel,currentMonkey->operand);
                // printf("    Worry level increases to %d\n", currentItem->data.worryLevel);
                currentMonkey->inspectionCount++;
                // printf("    Inspection Count increases to %d\n", currentMonkey->inspectionCount);
                // reduce worry
                //currentItem->data.worryLevel /= 3;
                if (currentItem->data.worryLevel < prevWorryLevel)
                {
                    __nop();
                }
                currentItem->data.worryLevel %= supermod;
                // printf("    Worry level decreases to %d\n", currentItem->data.worryLevel);

                // test worry level
                if (currentItem->data.worryLevel % currentMonkey->divisor == 0)
                {
                    // printf("    test passed, throwing %d to monkey %d\n", currentItem->data.worryLevel, currentMonkey->trueMonkey);
                    currentMonkey->trueThrowCount++;
                    queue_move(&monkeys[monkeyIdx].items, &monkeys[currentMonkey->trueMonkey].items);
                }
                else
                {
                    // printf("    test failed, throwing %d to monkey %d\n", currentItem->data.worryLevel, currentMonkey->falseMonkey);
                    currentMonkey->falseThrowCount++;
                    queue_move(&monkeys[monkeyIdx].items, &monkeys[currentMonkey->falseMonkey].items);
                }
                currentItem = nextItem;
            }
        }

        // Print inspection counts for each monkey at the end of each round
        // printf("Round %d inspection counts:\n", round);
        // for (int i = 0; i < MAX_MONKEYS; ++i) {
        //     if (monkeys[i].initialized)
        //     {
        //         printf("  Monkey %d: %d\n", i, monkeys[i].inspectionCount);
        //     }
        // }
        // printf("\n");  // Add a newline for readability between rounds
    }
    printMonkeys_inspectionCount();
    multiplyLargestInspectionCounts();
    return 0;
}