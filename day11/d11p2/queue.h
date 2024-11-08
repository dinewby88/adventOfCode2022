typedef struct
{
    long long worryLevel;
} dataStructure_t;

typedef struct queueElement_t
{
    dataStructure_t data;
    struct queueElement_t* next;
} queueElement_t;

typedef struct
{
    queueElement_t* head;
    queueElement_t* tail;
}queue_t;

// adds an element at the end of the queue
int queue_add(queue_t* queue, dataStructure_t x);
int queue_print(queue_t* queue);
int queue_destroy(queue_t* queue);
int queue_move(queue_t* source, queue_t* dest);
int queue_free(queue_t* queue);
