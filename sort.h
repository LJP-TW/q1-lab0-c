#ifndef LAB0_SORT_H
#define LAB0_SORT_H

/*
 * This program implements kinds of sorting algorithm for doubly linked list
 */

#include "queue.h"

typedef int (*strcmpfp)(char const *, char const *);

void merge_sort(queue_t *q, strcmpfp cmp);
void bubble_sort(queue_t *q, strcmpfp cmp);

#endif /* LAB0_SORT_H */
