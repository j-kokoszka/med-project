#include "apriori.h"

#include "transactions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


static void debug(const char *format, ...) {
    fprintf(stderr, "[DEBUG]: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

static void info(const char *format, ...) {
    fprintf(stderr, "[INFO]: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}



// Utility function to free candidates list
void free_candidates(candidate_t *head, int count) {
    candidate_t *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->set); // Free the duplicated string
        free(temp);
    }
}


void print_candidates(candidate_t *candidate_head){
    if(candidate_head) {
        candidate_t *current_candidate = candidate_head;
        while(current_candidate) {
            printf("Candidate set: [%s], candidate support: [%d]\n", current_candidate->set, current_candidate->support);
            current_candidate = current_candidate->next;
        }
    } else {
        info("No candidates to print\n");
    }
     

}

candidate_t *create_candidate(char *set_candidate){
    candidate_t *new_candidate = (candidate_t *)malloc(sizeof(candidate_t));
    if (!new_candidate) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    // new_candidate->id = id;
    new_candidate->set = strdup(set_candidate); // Duplicate the string
    new_candidate->support = 1;
    new_candidate->next = NULL;

    return new_candidate;
}


int is_in_candidates(candidate_t *candidates, char *set_candidate) {
    candidate_t *current_candidate = candidates;
    int candidate_counter = 0;
    while(current_candidate) {
        candidate_counter++;
        char *items = current_candidate->set;
        int counter = 0;
        while (*items != '\0') {
            char *current_set_candidate = set_candidate;
            while(*current_set_candidate != '\0') {
                if(*items == *current_set_candidate) { counter++; }
                if (counter == strlen(set_candidate)) { return 1; }
                current_set_candidate++;
            }
            items++;
        }
        current_candidate = current_candidate->next;
    }
    return 0;
}


void calc_support(transaction_t *transactions, candidate_t *candidate) {
    transaction_t *current_transaction = transactions;
    int counter =0;
    
    while(current_transaction) {
        char *transaction_items = current_transaction->items;
        counter = 0;
        while(*transaction_items != '\0') {
            char *set_char = candidate->set;
            while(*set_char != '\0') {
                if(*transaction_items == *set_char) {
                    counter++;
                } else {
                }
                if (counter == strlen(candidate->set)) {
                    candidate->support++;
                    counter = 0;
                    set_char = '\0'; 
                    break;
                }                
                set_char++;
            }
            transaction_items++;
        }
        current_transaction = current_transaction->next;
    }
}

candidate_t *join_step(transaction_t *transactions, candidate_t *previous_candidates, int min_support) { 
    
    transaction_t *current_transaction = transactions;
    candidate_t *head_candidate = NULL, *current_candidate = NULL;

    if(!previous_candidates) {
        info("Join step level 1\n");
        // Iterate over transactions in order to create first set
        while(current_transaction) {
            char *items = current_transaction->items;
            
            // Iterate over items in transaction
            while (*items != '\0') {
                char *set_candidate = (char *)malloc(2);
                // malloc error handler
                if (set_candidate == NULL) {fprintf(stderr, "Memory allocation error\n"); exit(EXIT_FAILURE);}

                // Copy item value
                set_candidate[0] = *items;  // Kopiowanie bieżącego znaku
                set_candidate[1] = '\0';    // Dodawanie znaku null
                
                // Check if item is in candidates - if item is not in candidates, support is incremented
                if(!is_in_candidates(head_candidate, set_candidate)){
                    candidate_t *new_candidate = create_candidate(set_candidate);
                    calc_support(transactions, new_candidate);
                    if (new_candidate->support >= min_support) {
                        if (!head_candidate) {
                            head_candidate = new_candidate;
                            current_candidate = head_candidate;
                        } else {
                            current_candidate->next = new_candidate;
                            current_candidate = current_candidate->next;
                        }
                    }
                } 

                free(set_candidate);
                items++;
            }
            current_transaction = current_transaction->next;
        }
    } 
    else {
        info("Join step level %d\n", strlen(previous_candidates->set)+1);
        candidate_t *current_candidate = previous_candidates, *it_candidate = NULL, *current_new_candidate = NULL;

        if(current_candidate->next) {
            int set_len = strlen(current_candidate->set);
            while(current_candidate) {
                it_candidate = current_candidate->next;

                char *set_mask = (char *)malloc(set_len);
                strncpy(set_mask, current_candidate->set, set_len-1);
                set_mask[set_len-1] = '\0';


                char *set_candidate = (char *)malloc(set_len+2);
                strcpy(set_candidate, current_candidate->set);
                while(it_candidate) {

                    set_candidate[set_len] = it_candidate->set[set_len-1];
                    set_candidate[set_len+1] = '\0';

                    if(!is_in_candidates(head_candidate, set_candidate)) {
                        candidate_t *new_candidate = create_candidate(set_candidate);
                        new_candidate->support = 0;
                        calc_support(transactions, new_candidate);
                        if (new_candidate->support >= min_support) {
                            if (!head_candidate) {
                                head_candidate = new_candidate;
                                current_new_candidate = head_candidate;
                            } else {
                                current_new_candidate->next = new_candidate;
                                current_new_candidate = current_new_candidate->next;
                            }
                        }
                    }

                    if(strncmp(set_mask, it_candidate->set, strlen(set_mask))) { it_candidate = NULL; break; }

                    it_candidate = it_candidate->next;
                }
                current_candidate = current_candidate->next;
            }
        } else {
            info("No more sets to create\n");
            return NULL;
        }

    }
    
    return head_candidate;
}

void prune_step(candidate_t *candidate_head, int min_support) {
    info("Next prune step\n");
    candidate_t *current_candidate = candidate_head, *prev_candidate = candidate_head, *temp = NULL;
    while(current_candidate) {
        if(current_candidate->support < min_support) {
            if(current_candidate == candidate_head) {
                temp = candidate_head;
                candidate_head = candidate_head->next;
                free(temp->set); 
                free(temp);
            } else {
                prev_candidate->next = current_candidate->next;
                temp = current_candidate;
                current_candidate = current_candidate->next;
                free(temp->set); 
                free(temp);
            }
        } else {
            prev_candidate = current_candidate;
            current_candidate = current_candidate->next;
        }
    }
}


void apriori(transaction_t *transactions, float min_support){

    info("Starting apriori algorithm\n");
    candidate_t *prev_candidates = NULL, *candidate_head = NULL;
    candidate_head = join_step(transactions, prev_candidates, min_support);
    print_candidates(candidate_head);
    while(candidate_head) {
        prev_candidates = candidate_head;
        candidate_head = join_step(transactions, prev_candidates, min_support);
        
        // prune_step(candidate_head, min_support);
        print_candidates(candidate_head);
    }   
}