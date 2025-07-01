#ifndef WATCHER_H
#define WATCHER_H
#include "EventLoop.h"

typedef struct watcher
{
    int fd;
    void *user_data;
    event_callback_t callback;
    struct watcher *next;
    event_type_t event;
} watcher_t;

// method

watcher_t *Find_Watcher(watcher_t *head, int fd);
watcher_t *Add_Watcher(watcher_t **head, int fd, void *user_data, event_callback_t callback, event_type_t event);
int Remove_Watcher(watcher_t **head, int fd);
void Free_Watchers(watcher_t **head);

#endif