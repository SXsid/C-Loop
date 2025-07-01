#include "IO_Watcher.h"
#include <stdlib.h>

watcher_t *Find_Watcher(watcher_t *head, int fd)
{
    watcher_t *current = head;
    while (current)
    {
        if (current->fd == fd)
        {
            return current;
        }
        current = head->next;
    }
    return NULL;
}

watcher_t *Add_Watcher(watcher_t **head, int fd, void *user_data, event_callback_t callback, event_type_t event)
{
    // if chagnes occured on alredy existing fd
    watcher_t *isWatcherExist = Find_Watcher(head, fd);
    if (isWatcherExist)
    {
        isWatcherExist->event = event;
        isWatcherExist->user_data = user_data;
        isWatcherExist->callback = callback;

        return isWatcherExist;
    }

    // new watcher

    watcher_t *newWatcher = malloc(sizeof(watcher_t));
    if (!newWatcher)
        return NULL;
    newWatcher->callback = callback;
    newWatcher->event = event;
    newWatcher->fd = fd;
    newWatcher->next = *head;
    *head = newWatcher;
    return newWatcher;
}
int Remove_Watcher(watcher_t **head, int fd)
{
    watcher_t *currentWatcher = *head;
    watcher_t *previousWatcher = NULL;
    while (currentWatcher)
    {
        if (currentWatcher->fd == fd)
        {
            // chagne the head
            if (previousWatcher)
            {
                previousWatcher->next = currentWatcher->next;
            }
            else
            {
                *head = currentWatcher->next;
            }
            free(currentWatcher);
            return 0;
        }
        previousWatcher = currentWatcher;
        currentWatcher = currentWatcher->next;
    }
    return -1;
}
void Free_Watchers(watcher_t **head)
{
    watcher_t *current = *head;
    while (current)
    {
        *head = current->next;
        free(current);
        current = *head;
    }
    *head = NULL;
}