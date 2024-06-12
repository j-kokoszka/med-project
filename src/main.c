#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "apriori.h"
#include "transactions.h"



#define MAX_TRANSACTION_LENGTH 256

// Timing utils
typedef struct {
    struct timeval startTime;
    struct timeval endTime;
} Timer;

void startTime(Timer *timer) { gettimeofday(&(timer->startTime), NULL); }
void stopTime(Timer *timer) { gettimeofday(&(timer->endTime), NULL); }
float elapsedTime(Timer timer) {
    return ((float)((timer.endTime.tv_sec - timer.startTime.tv_sec) +
                    (timer.endTime.tv_usec - timer.startTime.tv_usec) / 1.0e6));
}

void usage();


int main(int argc, char *argv[]) {

    
    Timer timer;

    if (argc != 3) { usage(); return EXIT_FAILURE; } 
    else {
        // Process run parameters
        char* filename = argv[1];
        float support = atof(argv[2]);

        // Read test file
        transaction_t *head = create_transaction_list(filename, MAX_TRANSACTION_LENGTH);
        // Count min_support from rel support
        int transaction_count = count_transactions(head);
        int min_support = (int)(transaction_count*support);

        // Measure execution time
        startTime(&timer);

        // Run apriori
        apriori(head, min_support);
        // candidate_t *candidates = first_iteration(head);

        stopTime(&timer);
        printf("\nExecution took %lf [s]\n", elapsedTime(timer));

        // Free the allocated memory for transaction list
        free_transactions(head);

        return EXIT_SUCCESS;
    }
}

// Usage function
void usage(){
    printf("[USAGE] ./med-project $CSV_FILE $MIN_SUPPORT\n");
}
