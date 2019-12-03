#include <stdio.h>

typedef struct node {
	int test;
	struct node *next;
}node;

int main(void) {
	node *test_node = malloc(sizeof(node));
	test_node->test = 4;
	test_node->next = NULL;

	return (0);
}