#include "transactions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new transaction node
transaction_t* create_transaction(int id, const char *items) {
    transaction_t *new_transaction = (transaction_t *)malloc(sizeof(transaction_t));
    if (!new_transaction) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    new_transaction->id = id;
    new_transaction->items = strdup(items); // Duplicate the string
    new_transaction->next = NULL;
    return new_transaction;
}

transaction_t* create_transaction_list(char *filename, int MAX_TRANSACTION_LENGTH){
    transaction_t *head = NULL, *current = NULL;
    
    char line[MAX_TRANSACTION_LENGTH];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        int id;
        char items[MAX_TRANSACTION_LENGTH];
        if (sscanf(line, "%d,%s", &id, items) != 2) {
            fprintf(stderr, "Invalid line format: %s", line);
            continue;
        } 


        transaction_t *new_transaction = create_transaction(id, items);
        if (!head) {
            head = new_transaction;
            current = head;
        } else {
            current->next = new_transaction;
            current = current->next;
        }
    }
    
    fclose(file);

    return head;
}

// Print the transactions to verify
void print_transaction_list(transaction_t *head){
    printf("Loaded transaction list:\n");
    transaction_t *current = head;
    while (current) {
        printf("ID: %d, Items: %s\n", current->id, current->items);
        current = current->next;
    }
}

// Function to free the linked list
void free_transactions(transaction_t *head) {
    transaction_t *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->items); // Free the duplicated string
        free(temp);
    }
}

int count_transactions(transaction_t *head){
    int counter = 0;
    while(head) {
        counter++;
        head = head->next;
    }
    return counter;
}