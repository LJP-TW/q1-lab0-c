#include "sort.h"

#define ENABLE_MERGE_SORT_RECURSIVE
// #define ENABLE_MERGE_SORT_ITERATIVE
// #define ENABLE_BUBBLE_SORT

#ifdef ENABLE_MERGE_SORT_RECURSIVE
static strcmpfp cmp;

static list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t buf;
    list_ele_t *tmp = &buf;

    while (l1 && l2) {
        if (cmp(l1->value, l2->value) <= 0) {
            tmp->next = l1;
            tmp = tmp->next;
            l1 = l1->next;
        } else {
            tmp->next = l2;
            tmp = tmp->next;
            l2 = l2->next;
        }
    }

    tmp->next = l1 ? l1 : l2;

    return buf.next;
}

static list_ele_t *_merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    // Split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    list_ele_t *l1 = _merge_sort(head);
    list_ele_t *l2 = _merge_sort(fast);

    return merge(l1, l2);
}

void merge_sort(queue_t *q, strcmpfp _cmp)
{
    list_ele_t *head, *curr;
    cmp = _cmp;

    // Sort
    head = _merge_sort(q->head);

    // Set queue_t
    q->head = head;
    curr = head;
    while (curr->next)
        curr = curr->next;
    q->tail = &(curr->next);
}
#endif

#ifdef ENABLE_MERGE_SORT_ITERATIVE
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
    list_ele_t *tmp;
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
            bstart->next = astart->next;
            astart->next = bstart;
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
    } else {
        /* aend is largest item */
        *end2 = *end1;
    }
}

void merge_sort(queue_t *q, strcmpfp cmp)
{
    list_ele_t *tmp;
    for (unsigned int gap = 1; gap < q->size; gap *= 2) {
        char firstIter = 1;
        list_ele_t *start1 = q->head, *end1;
        list_ele_t *start2, *end2;
        list_ele_t *prev = NULL;
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
                firstIter = 0;
            } else {
                prev->next = start1;
            }
            prev = end2;
            start1 = tmp;
        }
        /* start1 isn't NULL when there is no second part to be merged */
        prev->next = start1;
    }
    // Set queue_t
    tmp = q->head;
    while (tmp->next)
        tmp = tmp->next;
    q->tail = &(tmp->next);
}
#endif

#ifdef ENABLE_BUBBLE_SORT
// /* Get list_ele_t* from tail */
// #define tail2ele(tail) (list_ele_t *) ((char *) tail - 8)
//
// void bubble_sort(queue_t *q, strcmpfp cmp)
// {
//     list_ele_t *prev, *tail, *curr, *tmp;
//     tail = tail2ele(q->tail);
//     while (q->head != tail) {
//         prev = NULL;
//         curr = q->head;
//         while (curr != tail) {
//             if (cmp(curr->value, curr->next->value) > 0) {
//                 /* Swap curr and curr->next */
//                 tmp = curr->next;
//                 curr->next = tmp->next;
//                 tmp->next = curr;
//                 if (prev) {
//                     prev->next = tmp;
//                 }
//                 if (curr == q->head) {
//                     q->head = tmp;
//                 }
//                 if (tmp == tail) {
//                     tail = curr;
//                 }
//                 prev = tmp;
//             } else {
//                 prev = curr;
//                 curr = curr->next;
//             }
//         }
//         tail = prev;
//     }
//     curr = *(q->tail);
//     while (curr->next)
//         curr = curr->next;
//     q->tail = &(curr->next);
// }
#endif
