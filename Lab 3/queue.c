#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int data;
    struct queue *next;
    struct queue *prev;
}queue;

void push(queue *head, queue *tail, int new_data);
void print_queue(queue *head);

int main(void) {
    queue *head = NULL;
    queue *tail = NULL;
    int new_data;
    do {
        printf("Enter data [-1 to quit]: ");
        scanf("%d", &new_data);
        push(head, tail, new_data);
    } while (new_data != -1);
    print_queue(head);
    return (0);
}

void push(queue *head, queue *tail, int new_data) {
    queue *new = malloc(sizeof(queue));
    new->next = NULL;
    new->prev = NULL;
    new->data = new_data;
    if (head == NULL) {
        head = new;
        tail = new;
    }
    else {
        tail->next = new;
        new->prev = tail;
        tail = new;
        tail->next = head;
    }
}

void print_queue(queue *head) {
    queue *print = head;
    printf("\nQueue:\n");
    while (print->next != head) {
        printf("%d\n", print->data);
        print = print->next;
    }
    printf("\n");
}