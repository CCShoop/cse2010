#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct graph_node;

typedef struct ptr_list {
	struct graph_node* destination;
	struct ptr_list* next;
} NODE_PTRS;

typedef struct graph_node {
	NODE_PTRS* children;
	char name;
	int in_degree;
} NODE;

typedef struct container {
	NODE* node;
	struct container* next;
} CONTAINER;

typedef struct yes_another_struct {
	CONTAINER* head;
	CONTAINER* tail;
} LIST;

void enqueue(LIST* list, NODE* node) {
	CONTAINER* head = list->head;
	CONTAINER* tail = list->tail;
	if (head == NULL) {
		head = malloc(sizeof(CONTAINER));
		head->next = NULL;
		head->node = node;
		tail = head;
	} else {
		CONTAINER* new = malloc(sizeof(CONTAINER));
		new->next = NULL;
		new->node = node;
		tail->next = new;
		tail = new;
	}
	list->head = head;
	list->tail = tail;
}

NODE* dequeue(LIST* list) {
	CONTAINER* head = list->head;
	CONTAINER* tail = list->tail;
	
	if (head == NULL) return NULL;
	else if (head->next == NULL) tail = NULL;
	
	NODE* ret_val = head->node;
	
	head = head->next;
	list->head = head;
	list->tail = tail;
	
	return ret_val;
}

void create_node(LIST* list, char c) {
	NODE* node = malloc(sizeof(NODE));
	node->name = c;
	node->children = NULL;
	node->in_degree = 0;
	enqueue(list, node);
}

NODE* find_node(CONTAINER* head, char c) {
	CONTAINER* temp = head;
	while (temp != NULL) {
		if (temp->node->name == c)
			return temp->node;
		temp = temp->next;
	}
	return NULL;
}

void add_connection(NODE* source, NODE* destination) {
	if (source->children == NULL) {
		source->children = malloc(sizeof(NODE_PTRS));
		source->children->destination = destination;
		source->children->next = NULL;
	} else {
		NODE_PTRS* temp = source->children;
		while (temp->next != NULL)
			temp = temp->next;
		
		NODE_PTRS* new = malloc(sizeof(NODE_PTRS));
		new->destination = destination;
		new->next = NULL;
		temp->next = new;
	}
}

int count_in_degrees(CONTAINER* head) {
	
	CONTAINER* temp = head;
	while (temp != NULL) {
		temp->node->in_degree = 0;
		temp = temp->next;
	}
	
	int total = 0;
	temp = head;
	while (temp != NULL) {
		NODE_PTRS* tempn = temp->node->children;
		while (tempn != NULL) {
			tempn->destination->in_degree++;
			tempn = tempn->next;
		}
		temp = temp->next;
		total++;
	}
	
	return total;
}

void topological_sort(CONTAINER* head) {
	LIST* queue = malloc(sizeof(LIST));
	queue->head = NULL;
	queue->tail = NULL;
	
	int visited = count_in_degrees(head);
	
	printf("Topological Order:\n");
	CONTAINER* temp = head;
	while (temp != NULL) {
		if (temp->node->in_degree == 0)
			enqueue(queue, temp->node);
		temp = temp->next;
	}
		
	while (queue->head != NULL) {
		visited--;
		NODE* node = dequeue(queue);
		printf("%c ", node->name);
		NODE_PTRS* tempn = node->children;
		while (tempn != NULL) {
			tempn->destination->in_degree--;
			if (tempn->destination->in_degree == 0)
				enqueue(queue, tempn->destination);
			tempn = tempn->next;
		}
	}
	printf("\n");
	
	if (visited != 0){
		printf("Cycle is present:\n");
		temp = head;
		while (temp != NULL) {
			if (temp->node->in_degree > 0)
				printf("%c, ", temp->node->name);
			temp = temp->next;
		}
	}
	free(queue);
}

void print_all_nodes(CONTAINER* head) {
	CONTAINER* temp = head;
	printf("All nodes:\n");
	while (temp != NULL) {
		printf("%c, ", temp->node->name);
		temp = temp->next;
	}
	printf("\n");
}

void print_all_connections(CONTAINER* head) {
	CONTAINER* temp = head;
	printf("All connections:\n");
	while (temp != NULL) {
		NODE_PTRS* tempn = temp->node->children;
		while (tempn != NULL) {
			printf("%c->%c, ", temp->node->name, tempn->destination->name);
			tempn = tempn->next;
		}
		temp = temp->next;
	}
	printf("\n");
}

void print_all_in_degrees(CONTAINER* head) {
	CONTAINER* temp = head;
	printf("All in-degrees:\n");
	while (temp != NULL) {
		printf("%c: %d, ", temp->node->name, temp->node->in_degree);
		temp = temp->next;
	}
	printf("\n");
}

int main() {
	LIST* list = malloc(sizeof(LIST));
	list->head = NULL;
	list->tail = NULL;
	
	create_node(list, 'a');
	create_node(list, 'b');
	create_node(list, 'c');
	create_node(list, 'd');
	create_node(list, 'f');
	create_node(list, 'k');
	create_node(list, 'u');
	NODE* a = find_node(list->head, 'a');
	NODE* b = find_node(list->head, 'b');
	NODE* c = find_node(list->head, 'c');
	NODE* d = find_node(list->head, 'd');
	NODE* f = find_node(list->head, 'f');
	NODE* k = find_node(list->head, 'k');
	NODE* u = find_node(list->head, 'u');
	add_connection(a, b);
	add_connection(a, c);
	add_connection(c, d);
	add_connection(c, k);
	add_connection(d, a);
	add_connection(f, a);
	add_connection(f, u);
	add_connection(k, b);
	add_connection(k, d);
	add_connection(u, c);
	add_connection(u, d);
	
	print_all_nodes(list->head);
	print_all_connections(list->head);
	topological_sort(list->head);
}