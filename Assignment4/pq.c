/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Reed Boeshans
 * Email: boeshanr@oregonstate.edu
 */
#include <stdio.h>
#include <stdlib.h>

#include "dynarray.h"
#include "pq.h"

struct pq_val{
	void* value;
	int priority;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* heap;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* pq = malloc(sizeof(struct pq));
	pq->heap = dynarray_create();
		
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->heap);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	if(dynarray_size(pq->heap) == 0) 
		return 1;
	else
		return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void swap(struct pq* pq, int idx_1, int idx_2) {
	struct pq_val* temp = dynarray_get(pq->heap, idx_1);
	dynarray_set(pq->heap, idx_1, dynarray_get(pq->heap, idx_2));
	dynarray_set(pq->heap, idx_2, temp);
}

void pq_insert(struct pq* pq, void* value, int priority) {
	struct pq_val* node = malloc(sizeof(struct pq_val)); 
	int idx, idx_next=0;
	struct pq_val* parent;
	node->value = value; 
	node->priority = priority;
	dynarray_insert(pq->heap, -1, node);
	idx = dynarray_size(pq->heap)-1;
	node = dynarray_get(pq->heap, idx);
	if( dynarray_size(pq->heap) >1) {	
	while(idx_next >= 0) {            //stops when the node has reached the top of the tree
		idx_next = ((idx-1)/2);
		parent = dynarray_get(pq->heap, idx_next);
		if(node->priority < parent->priority){  //compares child priority to parents
			swap(pq, idx, idx_next);
			idx = idx_next;
		}
		else    // child is greater than parent
			break;
	}
	}
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	struct pq_val* node = dynarray_get(pq->heap, 0); 
	 return node->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
        struct pq_val* node = dynarray_get(pq->heap, 0);
         return node->priority;

}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	struct pq_val* front = dynarray_get(pq->heap, 0);
        struct pq_val* end = dynarray_get(pq->heap, -1);
        struct pq_val* right;
        struct pq_val* left;
	void* value = 0;
	int test = 0, idx=0, left_idx=0, right_idx=0, end_idx=0;

	dynarray_set(pq->heap, 0, end);
	dynarray_remove(pq->heap, -1);
	end_idx = dynarray_size(pq->heap);
	value = front->value;
	free(front);

	while(test != 1) {
		right_idx = (2*idx)+1;
		left_idx = (2*idx)+2;
		if(end_idx == 0)
			test = 1;
		else if(left_idx < end_idx) {       //checks for left child
			left = dynarray_get(pq->heap, left_idx);
			if(right_idx < end_idx) {      //checks for right child
				right = dynarray_get(pq->heap, right_idx);
				if(left->priority < end->priority && right->priority < end->priority) {  //checks both children's p-val
					if( left->priority < right->priority) {  // left child has lower p-val
						swap(pq, left_idx, idx);
						idx = left_idx;
					}
					else {			//right has lower p-val
						swap(pq, right_idx, idx);
						idx = right_idx;
					
					}

				}
				else if(left->priority < end->priority) { //checks if only left p-val is lower
					swap(pq, left_idx, idx);
					idx = left_idx;
				}
				else if(right->priority < end->priority) {  //checks right only
					swap(pq, right_idx, idx);
                                        idx = right_idx;
				}
				else 
					test = 1;
			}
			else if(left->priority < end->priority) {  //checks left as there is no right child
				swap(pq, left_idx, idx);
				idx = left_idx;
			}
			else
				test = 1;
		}
		else 
			test = 1;
	}
	return value;


}

