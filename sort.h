#ifndef LAB0_SORT_H
#define LAB0_SORT_H

/*
 * This program implements kinds of sorting algorithm for singly linked list
 * You must make sure that queue_t *q, q->head, q->head->next isn't NULL
 */

#include "queue.h"

typedef int (*strcmpfp)(char const *, char const *);

void merge_sort(queue_t *q, strcmpfp cmp);
void bubble_sort(queue_t *q, strcmpfp cmp);

#endif /* LAB0_SORT_H */
