#ifndef APRIORI_H
#define APRIORI_H

#include "transactions.h"


typedef struct candidate {
    int support;
    char *set;
    struct candidate * next;
} candidate_t;

// void test_function();

int apriori(transaction_t *transactions, float min_support);

// // Iterate over candidates and calculate their support
// void find_candidates_support(candidate_t *candidates);

// // Calculate support of one candidate
// int calculate_candidate_support(transaction_t *transactions, candidate_t *candidate);

// // Find new candidates list of i length
// candidate_t *find_new_candidates_list(transaction_t *transations, int set_length);

// void print_candidates(candidate_t *candidates);

// // char **find_candidates(char **candidates);


// // bool check_candidates();

// candidate_t* create_candidate(const char *set);
// void free_candidates(candidate_t *candidates, int count);
// int is_in_candidates(candidate_t *candidates, char *set);

// candidate_t *first_iteration(transaction_t *transactions);
// candidate_t* apriori_first_iteration(transaction_t *transactions);



#endif  // APRIORI_H