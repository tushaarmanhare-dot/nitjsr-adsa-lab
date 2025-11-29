#include <stdio.h>
#include <stdlib.h>

// Structure to represent a Job
struct Job {
    int id;         // Job ID
    int deadline;   // Deadline (integer time slot)
    int profit;     // Profit if job is completed before or on deadline
};

// Compare function for sorting by profit (descending)
int compare(const void *a, const void *b) {
    struct Job *j1 = (struct Job *)a;
    struct Job *j2 = (struct Job *)b;
    return j2->profit - j1->profit;
}

// Function to implement Job Sequencing with Deadlines
void jobSequencing(struct Job jobs[], int n) {
    // Step 1: Sort jobs by profit (descending)
    qsort(jobs, n, sizeof(struct Job), compare);

    // Step 2: Find maximum deadline
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    // Step 3: Create result and slot arrays
    int result[maxDeadline + 1]; // job index
    int slot[maxDeadline + 1];   // 0 = free, 1 = occupied

    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = 0;

    int totalProfit = 0;

    // Step 4: Assign jobs to slots
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                result[j] = i;
                slot[j] = 1;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Step 5: Print the scheduled jobs
    printf("Job sequence for maximum profit:\n");
    for (int i = 1; i <= maxDeadline; i++)
        if (slot[i])
            printf("J%d ", jobs[result[i]].id);

    printf("\nTotal Profit = %d\n", totalProfit);
}

int main() {
    struct Job jobs[] = {
        {1, 2, 100},
        {2, 1, 19},
        {3, 2, 27},
        {4, 1, 25},
        {5, 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);
    return 0;
}
