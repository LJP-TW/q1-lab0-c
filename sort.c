#include "sort.h"

static inline void swap(unsigned long long *a, unsigned long long *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

static inline void merge(list_ele_t **start1,
                         list_ele_t **end1,
                         list_ele_t **start2,
                         list_ele_t **end2,
                         strcmpfp cmp)
{
    list_ele_t *tmp, *tmp2;
    /* Make sure that start1 is smaller than start2 */
    if (cmp((*start1)->value, (*start2)->value) > 0) {
        swap((unsigned long long *) start1, (unsigned long long *) start2);
        swap((unsigned long long *) end1, (unsigned long long *) end2);
    }
    /* Merge */
    list_ele_t *astart = *start1, *aend = *end1;
    list_ele_t *bstart = *start2, *bend = *end2;
    list_ele_t *bendnext = bend->next;
    while (astart != aend && bstart != bendnext) {
        if (cmp(astart->next->value, bstart->value) > 0) {
            /* Handle astart->next->next later */
            tmp = bstart->next;
            tmp2 = bstart->next = astart->next;
            tmp2->prev = bstart;
            tmp2 = astart->next = bstart;
            tmp2->prev = astart;
            bstart = tmp;
        }
        /* astart will be the smallest item of unsorted items
         * and largest item of sorted items
         */
        astart = astart->next;
    }
    if (astart == aend) {
        /* Both astart ~ aend and bstart ~ bend are sorted
         * Now we just need to link the edge items
         * This part of code deals with previously ignored astart->next->next
         */
        aend->next = bstart;
        bstart->prev = aend;
    } else {
        /* aend is largest item */
        *end2 = *end1;
    }
}

void merge_sort(queue_t *q, strcmpfp cmp)
{
    for (unsigned int gap = 1; gap < q->size; gap *= 2) {
        char firstIter = 1;
        list_ele_t *start1 = q->head, *end1;
        list_ele_t *start2, *end2;
        list_ele_t *prev = NULL, *tmp;
        while (start1) {
            unsigned int counter;
            /* The first part to be merged */
            counter = gap;
            end1 = start1;
            /* If the amount of item of first part is less than gap, that it
             * is already sorted
             */
            while (--counter && end1->next)
                end1 = end1->next;
            start2 = end1->next;
            if (start2 == NULL)
                break;
            /* The second part to be merged */
            counter = gap;
            end2 = start2;
            while (--counter && end2->next)
                end2 = end2->next;
            tmp = end2->next;
            /* Merge */
            merge(&start1, &end1, &start2, &end2, cmp);
            if (firstIter) {
                q->head = start1;
                start1->prev = NULL;
                firstIter = 0;
            } else {
                prev->next = start1;
                start1->prev = prev;
            }
            prev = end2;
            start1 = tmp;
        }
        /* start1 isn't NULL when there is no second part to be merged */
        prev->next = start1;
        if (start1 == NULL) {
            q->tail = prev;
        } else {
            /* There is no second part to be merged */
            start1->prev = prev;
            q->tail = end1;
        }
    }
}

// void bubble_sort(queue_t *q, strcmpfp cmp)
// {
//     list_ele_t *tail, *curr, *tmp;
//     tail = q->tail;
//     while (q->head != tail) {
//         curr = q->head;
//         while (curr != tail) {
//             if (cmp(curr->value, curr->next->value) > 0) {
//                 /* Swap curr and curr->next */
//                 /* Fix next chain */
//                 tmp = curr->next;
//                 curr->next = tmp->next;
//                 tmp->next = curr;
//                 if (curr == q->head) {
//                     q->head = tmp;
//                     tmp->prev = NULL;
//                 } else {
//                     curr->prev->next = tmp;
//                 }
//                 /* Fix prev chain */
//                 tmp->prev = curr->prev;
//                 curr->prev = tmp;
//                 if (curr->next != NULL) {
//                     curr->next->prev = curr;
//                 }
//                 if (tmp == tail) {
//                     tail = curr;
//                     if (tmp == q->tail) {
//                         q->tail = curr;
//                     }
//                 }
//             } else {
//                 curr = curr->next;
//             }
//         }
//         tail = tail->prev;
//     }
// }
