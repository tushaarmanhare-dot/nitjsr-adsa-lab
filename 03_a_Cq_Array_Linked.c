//Implement a circular queue using (a) an array (b) linked list
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5   // For array-based circular queue

//ARRAY-BASED CIRCULAR QUEUE
typedef struct {
    int arr[SIZE];
    int front, rear;
} ArrayQueue;

// Initialize
void initArrayQueue(ArrayQueue *q) {
    q->front = q->rear = -1;
}

// Check empty
int isArrayEmpty(ArrayQueue *q) {
    return q->front == -1;
}

// Check full
int isArrayFull(ArrayQueue *q) {
    return ((q->rear + 1) % SIZE == q->front);
}

// Enqueue
void arrayEnqueue(ArrayQueue *q, int value) {
    if (isArrayFull(q)) {
        printf("[Array] Queue is full!\n");
        return;
    }
    if (isArrayEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % SIZE;
    }
    q->arr[q->rear] = value;
}

// Dequeue
int arrayDequeue(ArrayQueue *q) {
    if (isArrayEmpty(q)) {
        printf("[Array] Queue is empty!\n");
        return -1;
    }
    int data = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return data;
}

// Display
void arrayDisplay(ArrayQueue *q) {
    if (isArrayEmpty(q)) {
        printf("[Array] Queue is empty!\n");
        return;
    }
    printf("[Array] Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

//LINKED LIST CIRCULAR QUEUE
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *rear;
} ListQueue;

// Initialize
void initListQueue(ListQueue *q) {
    q->front = q->rear = NULL;
}

// Check empty
int isListEmpty(ListQueue *q) {
    return q->front == NULL;
}

// Enqueue
void listEnqueue(ListQueue *q, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("[List] Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    if (isListEmpty(q)) {
        q->front = q->rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = q->front;
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue
int listDequeue(ListQueue *q) {
    if (isListEmpty(q)) {
        printf("[List] Queue is empty!\n");
        return -1;
    }
    int data;
    if (q->front == q->rear) {
        data = q->front->data;
        free(q->front);
        q->front = q->rear = NULL;
    } else {
        Node *temp = q->front;
        data = temp->data;
        q->front = q->front->next;
        q->rear->next = q->front;
        free(temp);
    }
    return data;
}

// Display
void listDisplay(ListQueue *q) {
    if (isListEmpty(q)) {
        printf("[List] Queue is empty!\n");
        return;
    }
    printf("[List] Queue: ");
    Node *temp = q->front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

int main() {
    ArrayQueue aq;
    ListQueue lq;
    initArrayQueue(&aq);
    initListQueue(&lq);

    int choice, type, val;

    while (1) {
        printf("\nChoose Queue Type:\n1. Array-based\n2. Linked List-based\n3. Exit\nEnter: ");
        scanf("%d", &type);

        if (type == 3) break;

        printf("1. Enqueue\n2. Dequeue\n3. Display\nEnter choice: ");
        scanf("%d", &choice);

        switch (type) {
            case 1: // Array queue
                if (choice == 1) {
                    printf("Enter value: ");
                    scanf("%d", &val);
                    arrayEnqueue(&aq, val);
                } else if (choice == 2) {
                    printf("[Array] Dequeued: %d\n", arrayDequeue(&aq));
                } else if (choice == 3) {
                    arrayDisplay(&aq);
                }
                break;

            case 2: // Linked list queue
                if (choice == 1) {
                    printf("Enter value: ");
                    scanf("%d", &val);
                    listEnqueue(&lq, val);
                } else if (choice == 2) {
                    printf("[List] Dequeued: %d\n", listDequeue(&lq));
                } else if (choice == 3) {
                    listDisplay(&lq);
                }
                break;
        }
    }

    printf("Program exited.\n");
    return 0;
}
