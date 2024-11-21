#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the circular linked list
struct Node {
    int position;
    struct Node* next;
};

// Function to create a circular linked list with n nodes
struct Node* createCircle(int n) {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* prev = NULL;

    for (int i = 1; i <= n; i++) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->position = i;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;  // Set the first node as the head
        } else {
            prev->next = temp;  // Link the new node to the previous node
        }
        prev = temp;
    }
    prev->next = head;  // Make it circular by linking the last node to the head
    return head;
}

// Function to solve the Josephus problem
int josephusUsingList(struct Node* head, int k) {
    struct Node* current = head;
    struct Node* prev = NULL;

    // Traverse until only one node is left in the circle
    while (current->next != current) {
        // Skip k-1 nodes
        for (int count = 1; count < k; count++) {
            prev = current;
            current = current->next;
        }
        // Remove the k-th node
        printf("Eliminating position: %d\n", current->position);
        prev->next = current->next;
        free(current);  // Free the memory of the removed node
        current = prev->next;
    }
    int survivor = current->position;
    free(current);  // Free the last remaining node
    return survivor;
}

int main() {
    int n, k;

    // Input: Number of people (n) and step size (k)
    printf("Enter the number of people (n): ");
    scanf("%d", &n);
    printf("Enter the step size (k): ");
    scanf("%d", &k);

    // Create a circular linked list representing the people
    struct Node* head = createCircle(n);

    // Solve the Josephus problem
    int survivor = josephusUsingList(head, k);

    // Output the position of the survivor
    printf("The position of the survivor is: %d\n", survivor);

    return 0;
}
