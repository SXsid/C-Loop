#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>
#include <stddef.h>
#include "EventLoop.h"
typedef struct timer
{
    uint64_t timer_id;
    timer_callback_t callback;
    void *user_data;
    uint64_t expiry_time;
    uint64_t interval;
    size_t index;
} timer_t;

typedef struct priorityQueue
{
    size_t capacity;
    size_t size;
    // pointer to the m
    struct
    {
        timer_t *timer;
    } *nodes;
} priorityQueue_t;

priorityQueue_t *PQ_Create(size_t int_Cap);
void PQ_Destroy(priorityQueue_t *queue);
int Free_PQ(priorityQueue_t *queue);

int pq_insert(priorityQueue_t *queue, timer_t *timer);
int pq_remove(priorityQueue_t *queue, size_t index);
timer_t *pq_peek(priorityQueue_t *queue);
timer_t *pq_pop(priorityQueue_t *queue);

#endif