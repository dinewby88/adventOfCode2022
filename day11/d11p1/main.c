#include <stdio.h>
#include "monkey.h"

#define MAX_MONKEYS 10
#define NO_ROUNDS 20
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
        printf("Monkey %d: %d\n", i,monkeys[i].inspectionCount);
    }
}

void multiplyLargestInspectionCounts(void)
{
    int first = monkeys[0].inspectionCount;
    int second = monkeys[1].inspectionCount;

    // Ensure first is the greatest and second is the second greatest
    if (first < second) 
    {
        int temp = first;
        first = second;
        second = temp;
    }

    for (int i = 0; i < MAX_MONKEYS; i++)
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
    printf("multiplied: %d\n",first*second);
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
     if (parse_monkeys("sampleinput.txt", monkeys, MAX_MONKEYS) == 0) {
        // Successfully parsed the monkeys
        printf("Parsed monkeys successfully.\n");
        //printMonkeys_verbose();
        printMonkeys_justItems();

    } else {
        printf("Failed to parse monkeys.\n");
    }

    for(int round = 1; round <= NO_ROUNDS; round++)
    {
        // for each monkey

        for(int monkeyIdx = 0; monkeyIdx < MAX_MONKEYS; monkeyIdx++)
        {
            monkey_t* currentMonkey = &monkeys[monkeyIdx];
            // for each item the monkey has
            queueElement_t* currentItem = monkeys[monkeyIdx].items.head;
            if (!currentItem) continue;    //monkey has no items
            // monkey handles items
            while(currentItem)
            {
                queueElement_t* nextItem = currentItem->next;
                //printMonkeys_justItems();
                // monkey inspects items, so increase worry level
                currentItem->data.worryLevel = currentMonkey->operation(currentItem->data.worryLevel,currentMonkey->operand);
                currentMonkey->inspectionCount++;
                // reduce worry
                currentItem->data.worryLevel = currentItem->data.worryLevel/3;

                // test worry level
                if (currentItem->data.worryLevel % currentMonkey->divisor == 0)
                {
                    //printf("test passed, throwing to monkey %d\n", currentMonkey->trueMonkey);
                    queue_move(&monkeys[monkeyIdx].items, &monkeys[currentMonkey->trueMonkey].items);
                }
                else
                {
                    //printf("test failed, throwing to monkey %d\n", currentMonkey->falseMonkey);
                    queue_move(&monkeys[monkeyIdx].items, &monkeys[currentMonkey->falseMonkey].items);
                }
                //printMonkeys_justItems();
                currentItem = nextItem;
            }
        }
        printf("round %d:\n",round);
        printMonkeys_justItems();
    }
    printMonkeys_inspectionCount();
    multiplyLargestInspectionCounts();
    return 0;
}