#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char AirportCode[4];

typedef struct NodeTag {
    AirportCode Airport;
    struct NodeTag *Link;
}NodeType;

void InsertNewFirstNode(char A[], NodeType *L);
void DeleteFirst(NodeType **L);
void InsertNewMiddleNode(NodeType *A, NodeType *M, NodeType *N);
void Reverse(NodeType *L);
void print(NodeType *L);

int main(void) {
    NodeType *L = malloc(sizeof(NodeType)), *M = malloc(sizeof(NodeType)), *N = malloc(sizeof(NodeType));
    strcpy(L->Airport, "JYO");
    char temp[4];
    strcpy(temp, "IAD");
    InsertNewFirstNode(temp, L);
    strcpy(temp, "GLA");
    InsertNewFirstNode(temp, L);
    strcpy(temp, "YYZ");
    InsertNewFirstNode(temp, L);
    print(L);
    DeleteFirst(&L);
    print(L);
    NodeType *A = malloc(sizeof(NodeType));
    strcpy(A->Airport, "ZRH");
    InsertNewMiddleNode(A, M, N);
    print(L);
    Reverse(L);
    print(L);
    return (0);
}

void print(NodeType *L) {
    NodeType *print = L;
    while (print != NULL) {
        printf("%s ", print->Airport);
        print = print->Link;
    }
    printf("\n\n");
    free(print);
}

void InsertNewFirstNode(char A[], NodeType *L) {
    if (L == NULL) {
        L = malloc(sizeof(NodeType));
        strcpy(L->Airport, A);
    }
    else {
        NodeType *new = L;
        strcpy(new->Airport, A);
        L = L->Link;
    }
}

void DeleteFirst(NodeType **L) {
    if (*L == NULL)
        return;
    NodeType *remove = *L;
    *L = (*L)->Link;
    free(remove);
}

void InsertNewMiddleNode(NodeType *A, NodeType *M, NodeType *N) {
    NodeType *temp = N->Link;
    N->Link = M;
    M->Link = temp;
    strcpy(temp->Airport, M->Airport);
    strcpy(M->Airport, N->Airport);
    strcpy(N->Airport, temp->Airport);
    free(temp);
}

void Reverse(NodeType *L) {
    NodeType *last, *list = L, *next;
    while (list != NULL) {
        next = list->Link;
        list->Link = last;
        last = list;
        list = next;
    }
    L = last;
    free(list);
    free(last);
    free(next);
}

//passing in an empty list would lead to an error
//you must switch the loop checks