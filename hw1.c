#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** head, int val) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = (*head);
    (*head) = newNode;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

struct Node* merge(struct Node* head1, struct Node* head2) {
    struct Node* newhead = NULL;

    if (head1 == NULL) {
        return head2;
    } else if (head2 == NULL){
        return head1;
    }
    if (head1->data <= head2->data) {
        newhead = head1;
        newhead->next = merge(head1->next, head2);
    } else {
        newhead = head2;
        newhead->next = merge(head1, head2->next);
    }
    return newhead;
}

int getSize(struct Node* head) {
    int size = 0;
    while (head != NULL) {
        size += 1;
        head = head->next;
    }
    return size;
}

struct Node* mergeSort(struct Node* head, int size) {
    if (size <= 1) {
        return head;
    }

    int mid = 0;
    if (size % 2 == 0) {
        mid = size / 2;
    } else {
        mid = (size + 1) / 2;
    }

    struct Node* head2;
    struct Node* curr = head;
    struct Node* prev = head;
    for (int i = 0; i < mid; i++) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    head2 = curr;

    return merge(mergeSort(head, mid), mergeSort(head2, (size - mid)));
}

int main() {
        struct Node* head = NULL;

        insert(&head, 9);
        insert(&head, 5);
        insert(&head, 3);
        insert(&head, 7);
        insert(&head, 6);
        insert(&head, 1);

        printf("List before merge sort: \n");
        printList(head);
        printf("\n");

        head = mergeSort(head, getSize(head));

        printf("List after merge sort: \n");
        printList(head);
        return 0;
}