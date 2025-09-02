#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // for isdigit

#define MAX 100

// Stack implementation
char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return stack[top--];
}

char peek() {
    if (top == -1) return '\0';
    return stack[top];
}

// Precedence function
int precedence(char op) {
    if (op == '/' || op == '*')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Check if operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i, k = 0;
    char c;
    
    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        // If operand, add to postfix
        if (isdigit(c)) {
            postfix[k++] = c;
        }
        // If '(', push to stack
        else if (c == '(') {
            push(c);
        }
        // If ')', pop until '('
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            if (peek() == '(') pop();  // remove '('
        }
        // If operator
        else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0'; // Null terminate
}
// int evaluatePostfix(char *postfix)
// {
//     for (int i = 0; postfix[i] != '\0'; i++) 
//     {
//         char c = postfix[i];
//         if (isdigit(c)) 
//         {
//             push(c - '0'); // convert char digit → int
//         } 
//         else if (isOperator(c)) 
//         {
//             int b = pop();
//             int a = pop();
//             int res;
//             switch (c) {
//                 case '+': res = a + b; break;
//                 case '-': res = a - b; break;
//                 case '*': res = a * b; break;
//                 case '/': res = a / b; break;
//             }
//             push(res);
//         }
//     }
//     return pop();
// }

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);
    
//     int result = evaluatePostfix(postfix);
//     printf("Result = %d\n", result);
}

