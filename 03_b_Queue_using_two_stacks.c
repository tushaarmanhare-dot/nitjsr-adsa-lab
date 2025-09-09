#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
typedef struct {
    int arr[MAX];
    int top;
} Stack;

// Initialize stack
void init(Stack *s) {
    s->top = -1;
}

// Check if empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push into stack
void push(Stack *s, int val) {
    if (s->top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    s->arr[++s->top] = val;
}

// Pop from stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;
    }
    return s->arr[s->top--];
}

// Peek
int peek(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[s->top];
}

/* ---------------- Method 1: Push costly ---------------- */
typedef struct {
    Stack s1, s2;
} Queue1;

void initQueue1(Queue1 *q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue (costly)
void enqueue1(Queue1 *q, int val) {
    // Move everything from s1 to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }
    // Push new element to s1
    push(&q->s1, val);
    // Move back
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
}

// Dequeue (easy)
int dequeue1(Queue1 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return pop(&q->s1);
}

/* ---------------- Method 2: Pop costly ---------------- */
typedef struct {
    Stack s1, s2;
} Queue2;

void initQueue2(Queue2 *q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue (easy)
void enqueue2(Queue2 *q, int val) {
    push(&q->s1, val);
}

// Dequeue (costly)
int dequeue2(Queue2 *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty!\n");
        return -1;
    }
    // Move everything to s2
    while (!isEmpty(&q->s1)) {
        push(&q->s2, pop(&q->s1));
    }
    // Pop from s2
    int val = pop(&q->s2);
    // Move back
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }
    return val;
}

/* ---------------- MAIN ---------------- */
int main() {
    Queue1 q1;
    initQueue1(&q1);

    printf("Method 1 (Push costly):\n");
    enqueue1(&q1, 10);
    enqueue1(&q1, 20);
    enqueue1(&q1, 30);
    printf("Dequeued: %d\n", dequeue1(&q1));
    printf("Dequeued: %d\n", dequeue1(&q1));

    Queue2 q2;
    initQueue2(&q2);

    printf("\nMethod 2 (Pop costly):\n");
    enqueue2(&q2, 100);
    enqueue2(&q2, 200);
    enqueue2(&q2, 300);
    printf("Dequeued: %d\n", dequeue2(&q2));
    printf("Dequeued: %d\n", dequeue2(&q2));

    return 0;
}
