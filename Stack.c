
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100 

int stack[MAX_SIZE];
int top = -1; 

int isFull()
{
    return top == MAX_SIZE - 1;
}

int isEmpty()
{
    return top == -1;
}

void push(int data)
{
    if (isFull())
    {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = data;
    printf("%d pushed to stack\n", data);
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        return -1; 
    }
    return stack[top--];
}

int peek()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}

void show()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = top; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
}

int main()
{
    int choice, data;
    while (1)
    {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Show\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data to push: ");
            scanf("%d", &data);
            push(data);
            break;
        case 2:
            if (data != -1)
            {
                printf("%d popped from stack\n", pop());
            }
            break;
        case 3:
            data = peek();
            if (data != -1)
            {
                printf("Top element of stack: %d\n", data);
            }
            break;
        case 4:
            show();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
