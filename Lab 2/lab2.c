#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
}node;

void insert(node **element, int data);
void delete(node **element, int data);
void print_list(node *element);

int main(void) {
    node *code = NULL;
    insert(&code, 3);
    insert(&code, 1);
    insert(&code, 4);
    insert(&code, 2);
    print_list(code);
    delete(&code, 4);
    print_list(code);
    return (0);
}

void insert(node **element, int data) {
    node *new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    if ((*element) == NULL) { //linked list is empty, head node becomes new node
        *element = new;
    }
    else if (new->data < (*element)->data) { //if the data value is lower than head node value
        new->next = (*element);
        *element = new;
    }
    else { //if the data value is somewhere within the list or at the end
        node *temp = *element;
        while (temp->next != NULL && temp->next->data < data) {
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
    }
}

void delete(node **element, int data) {
    node *remove = *element, *temp;
    while (remove->next != NULL) {
        if (remove->next->data == data) {
            temp = remove->next;
            remove->next = temp->next;
            free(temp);
            break;
        }
        else
            remove = remove->next;
    }
}

void print_list(node *element) {
    node *print = element;
    while (print != NULL) {
        printf("%d\n", print->data);
        print = print->next;
    }
    printf("\n");
}