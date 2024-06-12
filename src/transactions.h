#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

typedef struct transaction {
    int id;
    char* items;
    struct transaction * next;
} transaction_t;

transaction_t* create_transaction(int id, const char *items);
void free_transactions(transaction_t *head);
void print_transaction_list(transaction_t *head);
transaction_t* create_transaction_list(char *filename, int MAX_TRANSACTION_LENGTH);
int count_transactions(transaction_t *head);

#endif  // TRANSACTIONS_H