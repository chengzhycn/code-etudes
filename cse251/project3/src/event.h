#ifndef __EVENT_H_
#define __EVENT_H_

#define __USE_XOPEN
#include <time.h>
#include <stdbool.h>

#include "common.h"

#define EVENT_NAME_LEN_MAX 50
#define EVENT_DATE_LEN_MAX 10 + 3 + 7 + 3 + 7
#define EVENT_FORMAT_HOUR(X) (X % 12 + 1)
#define EVENT_FORMAT_MERI(X) \
    (X > 12 ? "PM" : "AM")

typedef struct event event_t;
struct event {
    char name[EVENT_NAME_LEN_MAX+1];
    time_t start;
    time_t end;

    event_t *prev;
    event_t *next;
};

event_t* event_new_list();
event_t* event_new(const char *name, time_t start, time_t end);
event_t* event_insert(event_t *head, event_t *ev);
void event_delete(event_t *ev);
bool event_show_all(event_t *head);
bool event_show_current(event_t *head, time_t current);
bool event_delete_expired(event_t *head, time_t current);

#endif /* __EVENT_H_ */
