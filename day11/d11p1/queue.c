
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"

int queue_add(queue_t* queue, dataStructure_t x)
{
    if (!queue) return __LINE__;

    queueElement_t* newItem = malloc(sizeof(queueElement_t));
    if (!newItem) return __LINE__;

    newItem->data = x;
    newItem->next = 0;

    if (!queue->tail)
    {
        // handle case where this is the first element in the list
        queue->head = newItem;
        queue->tail = newItem;
    }
    else
    {
        // handle case where there are already items in the list
        queue->tail->next = newItem;
        queue->tail = newItem;
    }
    return 0;
}

int queue_print(queue_t* queue)
{
    queueElement_t* currentItem = queue->head;
    printf("LIST:\n");
    while (currentItem != 0)
    {
        printf("%d\n",currentItem->data.worryLevel);
        currentItem = currentItem->next;
    }
    return 0;
}

int queue_destroy(queue_t* queue)
{
    queueElement_t* currentItem = queue->head;
    while (currentItem != 0)
    {
        queueElement_t* nextItem = currentItem->next;
        free(currentItem);

        // update currentItem for next loop
        currentItem = nextItem;
    }
    queue->head = 0;
    free(queue);
    return 0;
}

int queue_move(queue_t* source, queue_t* dest)
{
    queueElement_t* blob;
    if (!source) return __LINE__;       // pointer error
    if (!dest) return __LINE__;         // pointer error
    if (!source->head) return __LINE__; // no elements in the queue

    blob = source->head;                // save pointer to data
    source->head = source->head->next;  // update head on the source
    if (!source->head)
    {
        source->tail = 0;
    }

    if (dest->head)
    {
        dest->tail->next = blob;            // update tail on the dest
        dest->tail = blob;
        blob->next = 0;                     // end the list on the dest.
    }
    else
    {
        //no items in list, start list
        dest->head = blob;
        dest->tail = blob;
        blob->next = 0;                     // end the list on the dest.
    }


    return 0;
}

int queue_free(queue_t* queue)
{
    queueElement_t* next;
    if (!queue) return __LINE__;        // pointer error
    while (queue->head)
    {
        next = queue->head->next;
        free(queue->head);
        queue->head = next;
    }
    return 0;
}

// prob dont need to keep malloc and freeing for add and remove.
// can malloc in a separate create function
// then the remove could actually just be a 'move' or 'throw' function to
// move the element between lists rather than deleting.