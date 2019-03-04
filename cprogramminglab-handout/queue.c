/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        // do nothing
        return;
    }

    /* How about freeing the list elements? */
    /* Free queue structure */
    list_ele_t *curr = q->head;
    list_ele_t *next = q->head;

    while (curr) {
        next = curr->next;
        free(curr);
        curr = 0; // same as curr = NULL
        curr = next;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));

    /* What if malloc returned NULL? */
    if (newh == NULL) {
        return false;
    }

    newh->value = v;
    newh->next = q->head;
    if (q->tail == NULL) {
        q->tail = newh;
    }

    q->head = newh;
    ++q->size;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if (q == NULL) {
        return false;
    }

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) return false; // same as checking if newt == NULL
    
    newt->value = v;

    if (q->tail == NULL) {
        assert(q->head = NULL);
        q->tail = q->head = newt;
    } else {
        q->tail->next = newt;
        q->tail = q->tail->next;
    }

    q->tail->next = NULL;
    ++q->size;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (!q || !q->head) {
        return false;
    }

    list_ele_t *to_remove = q->head;
    q->head = to_remove->next;

    if (vp) {
        *vp = to_remove->value;
    }
    
    free(to_remove); 
    to_remove = NULL;
    --q->size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head) {
        return;
    }
    assert(q->tail != NULL);
    
    list_ele_t *curr = q->head;
    list_ele_t *next = NULL;

    while (curr != q->tail) {
       next = curr->next;
       curr->next = q->tail->next;
       q->tail->next = curr;
       curr = next;
    }

    // swap head and tail pointers
    list_ele_t *temp = q->head;
    q->head = q->tail;
    q->tail = temp;
} 
