#include "event.h"

#include <string.h>

static void event_format(event_t *ev, FILE *fp)
{
    struct tm start_tm, end_tm;
    char start_buf[EVENT_DATE_LEN_MAX+1], end_buf[EVENT_DATE_LEN_MAX+1];

    
    start_tm = *localtime(&ev->start);
    end_tm = *localtime(&ev->end);
    memset(start_buf, 0, sizeof(start_buf));
    memset(end_buf, 0, sizeof(end_buf));
    strftime(start_buf, sizeof(start_buf), "%m/%d/%Y   %I:%M%p", &start_tm);
    strftime(end_buf, sizeof(end_buf), "%I:%M%p", &end_tm);

    fprintf(fp ? fp : stdout, " %s   %s %s\n", start_buf, end_buf, ev->name);
}

event_t* event_new_list()
{
    event_t *head;

    head = event_new("head", time(NULL), time(NULL));

    return head;
}

event_t* event_new(const char *name, time_t start, time_t end)
{
    event_t *ev;

    if (!name || strlen(name) > EVENT_NAME_LEN_MAX)
        return NULL;

    ev = (event_t *) malloc(sizeof(event_t));
    if (!ev)
        return NULL;

    memset(ev, 0, sizeof(event_t));
    memcpy(ev->name, name, strlen(name));
    ev->start = start;
    ev->end = end;

    return ev;
}

/* event_insert insert new event into event list by start time. */
event_t* event_insert(event_t *head, event_t *ev)
{
    event_t *curr;

    if (!head || !ev)
        return NULL;

    for (curr = head; curr->next != NULL; curr = curr->next) {
        if (ev->start <= curr->next->start) {
            ev->next = curr->next;
            ev->prev = curr;
            curr->next->prev = ev;
            curr->next = ev;
            return ev;
        }
    }

    ev->prev = curr;
    curr->next = ev;
    return ev;
}

void event_delete(event_t *ev)
{
    if (!ev)
        return;

    if (ev->prev)
        ev->prev->next = ev->next;

    if (ev->next)
        ev->next->prev = ev->prev;

    free(ev);
}

bool event_show_all(event_t *head)
{
    event_t *curr;

    for (curr = head->next; curr != NULL; curr = curr->next) {
        event_format(curr, NULL);
    }

    return true;
}

bool event_show_current(event_t *head, time_t current)
{
    event_t *curr;

    for (curr = head->next; curr != NULL; curr = curr->next) {
        if (curr->start <= current && curr->end >= current) {
            event_format(curr, NULL);
            return true;
        }
    }

    return false;
}

bool event_delete_expired(event_t *head, time_t current)
{
    event_t *curr;
    bool flag;

    flag = false;
    for (curr = head->next; curr != NULL; curr = curr->next) {
        if (curr->end < current) {
            flag = true;
            curr = curr->prev;
            event_delete(curr->next);
        }
    }

    return flag;
}
