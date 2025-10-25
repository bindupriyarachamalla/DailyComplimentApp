#include <stdio.h>
#include <string.h>

#define SIZE 20

// Queue for upcoming topics
char queue[SIZE][50];
int front = -1, rear = -1;

// Stack for completed topics
char stack[SIZE][50];
int top = -1;

// Function to add topic to queue
void enqueue(char topic[]) {
    if (rear == SIZE - 1) {
        printf("Study plan is full!\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    strcpy(queue[rear], topic);
    printf("Topic added to study plan.\n");
}

// Function to remove topic from queue (when studied)
int dequeue(char topic[]) {
    if (front == -1 || front > rear) {
        return 0; // Queue empty
    }
    strcpy(topic, queue[front]);
    front++;
    if (front > rear) front = rear = -1; // Reset queue if empty
    return 1; // Success
}

// Function to push topic to stack (mark as completed)
void push(char topic[]) {
    if (top == SIZE - 1) {
        printf("Completed list is full!\n");
        return;
    }
    top++;
    strcpy(stack[top], topic);
    printf("Studied: %s (moved to completed list)\n", topic);
}

// Function to pop topic from stack (undo last completed)
int pop(char topic[]) {
    if (top == -1) return 0; // Stack empty
    strcpy(topic, stack[top]);
    top--;
    return 1; // Success
}

// Display upcoming topics
void displayQueue() {
    int i; // declare outside for loop
    if (front == -1) {
        printf("No topics in study plan.\n");
        return;
    }
    printf("Upcoming Topics:\n");
    for (i = front; i <= rear; i++) {
        printf("%d. %s\n", i - front + 1, queue[i]);
    }
}

// Display completed topics
void displayStack() {
    int i; // declare outside for loop
    if (top == -1) {
        printf("No topics completed yet.\n");
        return;
    }
    printf("Completed Topics:\n");
    for (i = top; i >= 0; i--) {
        printf("%d. %s\n", top - i + 1, stack[i]);
    }
}

int main() {
    int choice;
    char topic[50];

    while (1) {
        printf("\n--- Smart Study Planner ---\n");
        printf("1. Add Topic\n");
        printf("2. Study Next Topic\n");
        printf("3. View Study Plan\n");
        printf("4. View Completed Topics\n");
        printf("5. Undo Last Completed\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline left by scanf

        switch (choice) {
            case 1:
                printf("Enter topic: ");
                fgets(topic, sizeof(topic), stdin);
                topic[strcspn(topic, "\n")] = 0; // remove newline
                enqueue(topic);
                break;

            case 2:
                if (dequeue(topic)) {
                    push(topic);
                } else {
                    printf("No topics to study.\n");
                }
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                displayStack();
                break;

            case 5:
                if (pop(topic)) {
                    enqueue(topic);
                    printf("Undo successful! %s added back to study plan.\n", topic);
                } else {
                    printf("No completed topics to undo.\n");
                }
                break;

            case 6:
                printf("Goodbye! Keep learning ??\n");
                return 0;

            default:
                printf("Invalid choice! Please enter 1-6.\n");
        }
    }
}
