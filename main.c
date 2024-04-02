/**
 * @author Arash Tashakori
 * @brief Linked List Manipulation and Splicing
 * @details This program tests the implementation of linked list operations, including matching
 * and splicing, as part of a data reassembly task. The program reads segments of text, stores
 * them as linked lists, and then reassembles them into a single document based on overlapping
 * content.
 */
#include <stdio.h>
#include "linked_list.h"
#include <string.h>
#include <stdlib.h>


// Function to compare two words (string) or anything comparable with strcmp
int compare(void *a, void *b) {
    return strcmp(a, b);
}

int main() {
    linked_list_t *segments = ll_new();
    char next_word [50];

    scanf("%s ", next_word);

    //Add segments until terminated with the final EOS
    while (compare(next_word, "EOS") != 0){
        linked_list_t *words = ll_new();

        //Add words until terminated with an EOS
        while (compare(next_word, "EOS") != 0){
            ll_add_back(words, strdup(next_word));
            scanf("%s", next_word);
        }

        //Adding the created segment to segments
        ll_add_back(segments, words);
        scanf("%s", next_word);
    }

    //Variables to keep track of the max overlap found
    unsigned int max_overlap = 0;
    int max_overlap_idx = 0;
    int max_overlap_order = 0; //T,S is 0 and S,T is 1

    /*Removing the segment at the head, finding its max overlap with all other segments, and splice
     *it into that segment with the order that the highest overlap occurs at T,S or S,T  */
    while (ll_size(segments) > 1){
        linked_list_t *removed_seg = ll_remove_front(segments);
        ll_node_t *tmp = segments->head;
        int curr_idx = 0;

        //For each segment S get the overlap of removed_seg in both orders (removed_seg,S & S,removed_seg) and find the max overlap so far
        while (tmp != NULL){
            //If the removed_seg,S overlap is the highest overlap so far, store its info
            unsigned int overlap = ll_overlap(removed_seg, (linked_list_t *) tmp->item, compare);
            if (overlap > max_overlap){
                max_overlap = overlap;
                max_overlap_idx = curr_idx;
                max_overlap_order = 0;
            }

            //If the S,removed_seg overlap is the highest overlap so far, store its info
            overlap = ll_overlap((linked_list_t *) tmp->item, removed_seg, compare);
            if (overlap > max_overlap){
                max_overlap = overlap;
                max_overlap_idx = curr_idx;
                max_overlap_order = 1;
            }

            curr_idx++;
            tmp = tmp->next;
        }

        //Getting the segment with which removed_seg has the highest overlap
        tmp = segments->head;
        for (unsigned int i = 0; i <max_overlap_idx; i++){
            tmp = tmp->next;
        }

        //Splicing removed_seg,S or S,removed_seg (based on which one was higher) into S
        if (max_overlap_order == 1){
            ll_splice (tmp->item, removed_seg, max_overlap);
            free(removed_seg);
        } else {
            ll_splice(removed_seg, tmp->item, max_overlap);
            linked_list_t * tmp_freeing = tmp->item;
            tmp->item = removed_seg;
            free (tmp_freeing);
        }

        //Resetting max_overlap variables for the next iteration
        max_overlap = 0;
        max_overlap_order = 0;
        max_overlap_idx = 0;

    }

    //Printing the final spliced section, wrapping lines after each 30 characters
    if (ll_size(segments) == 1) {
        //Getting the first word to print
        linked_list_t *final_segment = segments->head->item;
        ll_node_t *curr_word = final_segment->head;

        int line_length = 0;

        while (curr_word != NULL){
            //Getting the length for the current curr_word and the line so far
            int curr_word_len = strlen((char*) curr_word->item);
            line_length = line_length + curr_word_len + 1;

            printf("%s ", (char*) curr_word->item);

            // Wrap line if longer than 30 characters so far
            if (line_length > 30) {
                printf("\n");
                line_length = 0;
            }

            curr_word = curr_word->next;
        }

        ll_destroy(final_segment); //Free the final spliced segment

    }

    ll_destroy(segments); //Free the array of segments

    return 0;
}
