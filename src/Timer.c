#include "Timer.h"
#include <stdlib.h>

static inline size_t parent_index(size_t i) { return (i - 1) / 2; };
static inline size_t left_child_index(size_t i) { return 2 * i + 1; };
static inline size_t right_child_index(size_t i) { return 2 * i + 2; };

priorityQueue_t *PQ_Create(size_t int_cap)
{
    priorityQueue_t *queue = malloc(sizeof(priorityQueue_t));
    if (!queue)
        return NULL;
    queue->nodes = malloc(int_cap * sizeof(*queue->nodes));
    if (!queue->nodes)
    {
        free(queue);
        return NULL;
    }
    queue->capacity = int_cap;
    queue->size = 0;
    return queue;
}
void PQ_Destroy(priorityQueue_t *queue)
{
    if (queue)
    {
        free(queue->nodes);
        free(queue);
    }
}

void Swap(priorityQueue_t *queue, size_t index1, size_t index2)
{
    timer_t *temp_timer = queue->nodes[index1].timer;
    queue->nodes[index1].timer = queue->nodes[index2].timer;
    queue->nodes[index1].timer = temp_timer;

    // change the inside index so removal can happen

    queue->nodes[index1].timer->index = index1;
    queue->nodes[index2].timer->index = index2;
    ;
}

static void BubbleUp(priorityQueue_t *queue, size_t index)
{
    if (index == 0)
    {
        return;
    }
    size_t parentIndex = parent_index(index);
    if (queue->nodes[parentIndex].timer->expiry_time > queue->nodes[index].timer)
    {
        Swap(queue, parentIndex, index);
        BubbleUp(queue, parentIndex);
    }
}

static void Sink(priorityQueue_t *queue, size_t index)
{
    size_t smallestIndex = index;
    size_t leftChildIndex = left_child_index(index);
    size_t rightChildIndex = right_child_index(index);

    if (queue->size > leftChildIndex && queue->nodes[index].timer->expiry_time > queue->nodes[leftChildIndex].timer->expiry_time)
    {
        smallestIndex = leftChildIndex;
    }

    if (queue->size > rightChildIndex && queue->nodes[index].timer->expiry_time > queue->nodes[rightChildIndex].timer->expiry_time)
    {
        smallestIndex = rightChildIndex;
    }

    if (smallestIndex != index)
    {
        Swap(queue, smallestIndex, index);
        Sink(queue, smallestIndex);
    }
}
// 0(1)
timer_t *pq_peek(priorityQueue_t *queue)
{
    if (queue->size == 0)
    {
        return NULL;
    }
    return queue->nodes[0].timer;
}
int pq_insert(priorityQueue_t *queue, timer_t *timer)
{
    // increae the capacity
    if (queue->size >= queue->capacity)
    {
        queue->capacity = 2 * queue->capacity;
        int *newNodes = realloc(queue->nodes, queue->capacity * sizeof(*queue->nodes));
        if (!newNodes)
        {
            return -1;
        }
        queue->nodes = newNodes;
    }
    // add the new
    size_t indextoadd = queue->size++;
    queue->nodes[indextoadd].timer = timer;

    BubbleUp(queue, indextoadd);
    queue->size = indextoadd;
    return 0;
}

// n(log(n))

int pq_remove(priorityQueue_t *queue, size_t index)
{
    if (queue->size <= index)
    {
        return -1;
    }

    size_t parentIndex = parent_index(index);
    // remove
    queue->nodes[index].timer = queue->nodes[--queue->size].timer;
    queue->nodes[index].timer->index = index;

    if (index > 0 && queue->nodes[parentIndex].timer->expiry_time > queue->nodes[index].timer->expiry_time)
    {
        BubbleUp(queue, index);
    }
    else
    {
        Sink(queue, index);
    }

    return 0;
}
timer_t *pq_pop(priorityQueue_t *queue)
{
    if (queue->size == 0)
    {
        return NULL;
    }
    timer_t *firstTimer = queue->nodes[0].timer;

    // replace with the last
    if (queue->size > 1)
    {
        queue->nodes[0].timer = queue->nodes[--queue->size].timer;
        queue->nodes[0].timer->index = 0;
        Sink(queue, 0);
    }
    else
    {
        queue->size--;
    }
    return firstTimer;
}

int Free_PQ(priorityQueue_t *queue)
{
    while (queue->size > 0)
    {
        timer_t *timer = pq_pop(queue);
        free(timer);
    }
}