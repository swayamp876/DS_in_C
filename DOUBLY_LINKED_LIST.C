#include <stdio.h>
#include <stdlib.h>

// Definition of the Doubly Linked List Node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Global head pointer
struct Node* head = NULL;

// 1. Insertion at the beginning
void insert_start(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
    printf("Inserted %d at the beginning.\n", value);
}

// 2. Insertion at the end
void insertEnd(int x) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = x;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
        printf("Inserted %d at the end.\n", x);
        return;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    printf("Inserted %d at the end.\n", x);
}

// 3. Insertion at a given position
void insertPosition(int value, int position) {
    if (position < 1) {
        printf("Invalid position. Position must be >= 1.\n");
        return;
    }

    if (position == 1) {
        insert_start(value);
        return;
    }

    struct Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid Position: Out of bounds.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", value, position);
}

// 4. Deletion at the beginning
void delete_start() {
    if (head == NULL) {
        printf("Doubly Linked List is Empty. Deletion not possible.\n");
        return;
    }

    struct Node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    printf("Deleted %d from the beginning.\n", temp->data);
    free(temp);
}

// 5. Deletion at the end
void deleteEnd() {
    if (head == NULL) {
        printf("Doubly Linked List is Empty. Deletion not possible.\n");
        return;
    }

    if (head->next == NULL) {
        printf("Deleted %d from the end.\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    printf("Deleted %d from the end.\n", temp->data);
    free(temp);
}

// 6. Deletion at a given position
void deletePosition(int position) {
    if (head == NULL) {
        printf("Doubly Linked List is Empty. Deletion not possible.\n");
        return;
    }

    if (position < 1) {
        printf("Invalid position. Position must be >= 1.\n");
        return;
    }

    if (position == 1) {
        delete_start();
        return;
    }

    struct Node* temp = head;
    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid Position: Node does not exist.\n");
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    printf("Deleted %d from position %d.\n", temp->data, position);
    free(temp);
}

// 7. Display list elements
void display() {
    if (head == NULL) {
        printf("Doubly Linked List is Empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 8. Count total nodes
void countNodes() {
    int count = 0;
    struct Node* temp = head;

    if (head == NULL) {
        printf("Doubly Linked List is Empty. Node count = 0\n");
        return;
    }

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total number of nodes = %d\n", count);
}

// Main interactive loop
int main() {
    int choice, val, pos;

    while (1) {
        printf("\n============================\n");
        printf("   DOUBLY LINKED LIST MENU  \n");
        printf("============================\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Specific Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Specific Position\n");
        printf("7. Display List\n");
        printf("8. Count Nodes\n");
        printf("9. Exit\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Terminating program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert at start: ");
                scanf("%d", &val);
                insert_start(val);
                break;

            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &val);
                insertEnd(val);
                break;

            case 3:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertPosition(val, pos);
                break;

            case 4:
                delete_start();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deletePosition(pos);
                break;

            case 7:
                display();
                break;

            case 8:
                countNodes();
                break;

            case 9:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid option! Please enter a choice between 1 and 9.\n");
        }
    }

    return 0;
}
