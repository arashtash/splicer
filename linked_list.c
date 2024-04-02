//
// Created by Alex Brodsky on 2023-09-20.
// Extended and modified by Arash Tashakori
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "linked_list.h"

extern linked_list_t * ll_new() {
    linked_list_t * list = calloc(1,sizeof(linked_list_t));
    return list;
}

extern void ll_destroy(linked_list_t *list) {
    assert(list != NULL);
    while (list->head != NULL) {
        ll_node_t *tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }

    free(list);
}

static ll_node_t *new_node(void *item, ll_node_t *prev, ll_node_t *next) {
    ll_node_t *n = calloc(1, sizeof(ll_node_t));
    if (n != NULL) {
        n->item = item;
        n->prev = prev;
        n->next = next;
    }
    return n;
}


extern int ll_add_front(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,NULL, list->head);
    if (n != NULL) {
        if (list->tail == NULL) {
            list->tail = n;
        } else {
            list->head->prev = n;
        }
        list->head = n;
    }
    list->size++;
    return n != NULL;
}

extern int ll_add_back(linked_list_t *list, void *item) {
    assert(list);

    ll_node_t *n = new_node(item,list->tail, NULL);
    if (n != NULL) {
        if (list->head == NULL) {
            list->head = n;
        } else {
            list->tail->next = n;
        }
        list->tail = n;
    }
    list->size++;
    return n != NULL;
}

extern void * ll_remove_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        ll_node_t *n = list->head;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        } else {
            list->head->prev = NULL;
        }

        item = n->item;
        free(n);
    }
    list->size--;
    return item;
}

extern void * ll_remove_back(linked_list_t *list) {
    assert(list);
    
    void *item = NULL;
    if (list->tail != NULL) {
        ll_node_t *n = list->tail;
        list->tail = list->tail->prev;
        if (list->tail == NULL) {
            list->head = NULL;
        } else {
            list->tail->next = NULL;
        }

        item = n->item;
        free(n);
    }
    list->size--;
    return item;
}

extern void * ll_get_front(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->head->item;
    }
    return item;
}

extern void * ll_get_back(linked_list_t *list) {
    assert(list);

    void *item = NULL;
    if (list->head != NULL) {
        item = list->tail->item;
    }
    return item;
}

extern unsigned int ll_size(linked_list_t *list) {
    assert(list);

    return list->size;
}

extern int ll_is_empty(linked_list_t *list) {
    assert(list);
    return list->head == NULL;
}

extern int ll_insert(linked_list_t *list, ll_node_t *node, void *item) {
    assert(list);
    assert(node);

    if (node->next == NULL) {
        assert(list->tail == node);
        return ll_add_back(list, item);
    } else {
        ll_node_t *n = new_node(item, node, node->next);
        if (n != NULL) {
            node->next->prev = n;
            node->next = n;
        }
        list->size++;
        return n != NULL;
    }
}


extern void * ll_remove(linked_list_t *list, ll_node_t *node) {
    assert(list);
    assert(node);

    if (node->prev == NULL) {
        assert(list->head == node);
        return ll_remove_front(list);
    } else if(node->next == NULL) {
        assert(list->tail == node);
        return ll_remove_back(list);
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        void *item = node->item;
        free(node);
        list->size--;
        return item;
    }
}

/************************************************************************
 * Your code below
 ************************************************************************/

extern unsigned int ll_overlap(linked_list_t *list1, linked_list_t *list2, 
                               int (*compare)(void *, void*)) {
    ll_node_t *tmp1 = list1->head;
    ll_node_t *tmp2 = list2->head;
    unsigned int max_overlap = 0;

    //Getting the potential overlaps starting from each linked list node to the end
    while (tmp1 != NULL && tmp2 != NULL){
        ll_node_t *idx_list1 = tmp1;
        ll_node_t *idx_list2 = list2->head;
        unsigned int overlap = 0;
        /*If idx_list2 reaches NULL it means list 2 is sublist of list 1, if idx_list1 reaches NULL
         * it means there is an overlap */
        while (idx_list1 != NULL && idx_list2 != NULL){
            if (compare(idx_list1->item, idx_list2->item) == 0){
                overlap++;
                idx_list1 = idx_list1->next;
                idx_list2 = idx_list2->next;
            } else {    //If equal elements detected before one idx reaches NULL, there is no overlap
                break;
            }
        }

        if (overlap > max_overlap && (idx_list2 == NULL || idx_list1 == NULL)) {
            max_overlap = overlap;
        }

        tmp1 = tmp1->next;
    }

    return max_overlap;
}

extern void ll_splice(linked_list_t *list1, linked_list_t *list2, 
                      unsigned int overlap) {
    assert(list1);
    assert(list2);

    /*If overlap == size of list2 it means list2 is a subset of list1. In that case list1 is
    *the concatenation and list2 is the overlap by default. We check that before proceed to the
    * second case where list2 is not a subset of list1. If it is a subset the function doesn't
    * need to do anything*/
   if (overlap != ll_size(list2)) {

       ll_node_t *tmp1 = list1->tail;
       ll_node_t *tmp2 = list2->head;

       //Setting the list2 tail to the end of the overlap sublist or to NULL if no overlap
       if(overlap > 0){
           list2->tail = tmp1;
       } else {
           list2->tail = NULL;
           list2->head = NULL;
       }

       //Getting to the last non-overlapping element in list 1
       for (unsigned int i = 0; i < overlap && tmp1 != NULL; i++) {
           //Modify the list2's head in the last iteration to avoid getting to NULL in case of list1 containing
           //no non-overlapping elements
           if (i == overlap-1) {
               list2->head = tmp1;
           }
           tmp1 = tmp1->prev;
       }

       //Setting the prev pointer of the overlap list's first element to NULL
       if (tmp1 != NULL && tmp1->next != NULL) {
           tmp1->next->prev = NULL;
       }

       if (tmp1 == NULL) { //If there is no non-overlapping element in list 1
           list1->head = tmp2;
           list2->head = tmp1;
       } else {  //If there are non-overlapping elements in L1
           //Concatenating the lists
           tmp1->next = tmp2;
           if (tmp2 != NULL) {
               tmp2->prev = tmp1;
               //Getting the tail of the concatenated list by looping through list 2 (If list is not empty)
               while (tmp2->next != NULL){
                   tmp2 = tmp2->next;
               }
               list1->tail = tmp2;
           }
       }

       //Updating the list's sizes
       int totalSize = ll_size(list1) + ll_size(list2);
       list2->size = overlap;
       list1->size = totalSize - overlap;
   }
}

