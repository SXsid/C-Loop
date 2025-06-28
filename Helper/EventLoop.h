#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#include <stdint.h>
// type of eventst
typedef enum
{
    EVENT_READ = 1,
    EVENT_WRITE = 2,
    EVENT_TIMEOUT = 4,
} event_type_t;

// evenloop intefrace type
typedef struct event_loop event_loop_t;
// struct  for io event
typedef void (*event_callback_t)(event_loop_t *loop, int fd, event_type_t event, void *user_data);
// struct for timer evert

typedef void (*timer_callback_t)(event_loop_t *loop, void *user_data);

// method  for the event loop

event_loop_t *Create_loop(void);
int Destroy_loop(event_loop_t *loop);
int Start_loop(event_loop_t *loop);
int Stop_loop(event_loop_t *loop);

int Add_IO(event_loop_t *loop, event_type_t event, event_callback_t callback, void *user_data, int fd);
int Remove_IO(event_loop_t *loop, int fd);
// will return a timer id
uint64_t Add_timer(event_loop_t *loop, uint64_t time_ms, timer_callback_t callback, void *user_data, int reccuring);
int Remove_timer(event_loop_t *loop, uint64_t timer_id);

#endif
