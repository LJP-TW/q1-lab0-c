#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue
 * No effect if q is NULL
 */
void q_free(queue_t *q)
{
    list_ele_t *ele;
    if (q == NULL)
        return;
    /* Free queue structure */
    ele = q->head;
    while (ele != NULL) {
        q->head = ele->next;
        free(ele->value);
        free(ele);
        ele = q->head;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *news;
    unsigned long len, tmp;
    if (q == NULL)
        goto ERROR;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        goto ERROR;
    len = 0;
    while (*(s + len))
        ++len;
    /* Plus 1 for NULL byte */
    news = malloc(sizeof(char) * (len + 1));
    if (news == NULL) {
        free(newh);
        goto ERROR;
    }
    /* Copy string, including the NULL byte */
    for (tmp = 0; tmp <= len; ++tmp) {
        news[tmp] = s[tmp];
    }
    newh->value = news;
    newh->prev = NULL;
    newh->next = q->head;
    if (newh->next != NULL) {
        newh->next->prev = newh;
    }
    q->head = newh;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    ++q->size;
    return true;
ERROR:
    return false;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *news;
    unsigned long len, tmp;
    if (q == NULL)
        goto _ERROR;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        goto _ERROR;
    len = 0;
    while (*(s + len))
        ++len;
    news = malloc(sizeof(char) * (len + 1));
    if (news == NULL) {
        free(newh);
        goto _ERROR;
    }
    for (tmp = 0; tmp <= len; ++tmp) {
        news[tmp] = s[tmp];
    }
    newh->value = news;
    newh->prev = q->tail;
    newh->next = NULL;
    if (newh->prev != NULL) {
        newh->prev->next = newh;
    }
    q->tail = newh;
    if (q->head == NULL) {
        q->head = newh;
    }
    ++q->size;
    return true;
_ERROR:
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;
    if (sp != NULL) {
        char *v;
        unsigned long i;
        v = q->head->value;
        for (i = 0; i < bufsize - 1; ++i) {
            sp[i] = v[i];
        }
        sp[i] = '\0';
    }
    free(q->head->value);
    if (q->head == q->tail) {
        /* There is only one element in list */
        free(q->head);
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
        free(q->head->prev);
        q->head->prev = NULL;
    }
    --q->size;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
