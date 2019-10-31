/*
    Author:		 Cael Shoop
    Email:		 cshoop2018@my.fit.edu
    Course:		 cse2010
    Section:	 2j
    Description: Homework Assignment 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>

typedef struct nodes {
    char data[101];
    struct nodes *child;
    struct nodes *list;
}nodes;

void add_list(nodes **parent_node, nodes **list_node);
void add_child(nodes **parent_node, nodes **child_node); //to maintain alphabetical/loxicographical order of the children
int identify_queries(FILE *queries);
void get_children(nodes **node);
void get_parent(nodes **node);
/*
    Description of the function, parameter, and return value (if any)
*/

int main(int argc, char* argv[]) {
    int newline = 0;
    char input[12];
    FILE *data = fopen(argv[1], "r");
	if (data == NULL)
		return (1);
    nodes *head = malloc(sizeof(nodes));
    fscanf(data, "%s", head->data);
	nodes *child0 = malloc(sizeof(nodes));
	head->child = child0;
	strcpy(child0->data, "empty");
    while (newline == 0) {
        fgets(input, 12, data);
		if (input[0] == ' ')
			for (int i = 0; i < 12; i++)
				input[i] = input[i + 1];

        printf("in while loop, input: %s; newline: %d\n", input, newline);
        sleep(1);

        for (int i = 0; i < 12; i++) {
			if (input[i] == '\n') {

                printf("newline detected\n");

                newline = 1;
                strtok(input, "\n");
            }
        }
        nodes *temp = malloc(sizeof(nodes));
        strcpy(temp->data, input);
        add_list(&child0, &temp);
    }
	nodes *child1 = malloc(sizeof(nodes));
	child0->child = child1;
	strcpy(child1->data, "empty");
	while (!feof(data)) {
		if (feof(data))
			break;

		printf("in while loop, input: %s\n", input);
        sleep(1);

		fgets(input, 12, data);
		for (int i = 0; i < 12; i++) {
			if (input[i] == '\n') {

                printf("newline detected\n");

                newline = 1;
                strtok(input, "\n");
            }
        }
		nodes *temp = malloc(sizeof(nodes));
		strcpy(temp->data, input);
		add_list(&child1, &temp);
	}
	fclose(data);
	FILE *queries = fopen(argv[2], "r");
	if (queries == NULL)
		return (1);
    switch (identify_queries(queries)) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            printf("\n\nError, file input not recognized: exiting program.\n\n");
            return (1);
    }
/*
    description of each "block" (about 5 lines of instructions)
*/
	fclose(queries);
    return (0);
}

void add_list(nodes **parent_node, nodes **list_node) {
	if (strcmp((*parent_node)->data, "empty") == 0)
		*parent_node = *list_node;
	else if (strcmp((*list_node)->data, (*parent_node)->data) < 0) {
		(*list_node)->list = *parent_node;
		*parent_node = *list_node;
	}
	else {
		nodes *temp = *parent_node;
		while (temp->list != NULL && strcmp((*parent_node)->data, (*list_node)->data) < 0)
			temp = temp->list;
		(*list_node)->list = temp->list;
		temp->list = *list_node;
	}
}

void add_child(nodes **parent_node, nodes **child_node) {

}

int identify_queries(FILE *queries) {
    char search[30];
    fscanf(queries, "%s", search);
    printf("\n%s ", search);
    if (strcmp(search, "GetNamesByCategory") == 0)
        return (0);
    else if (strcmp(search, "GetNamesByState") == 0)
        return (1);
    else if (strcmp(search, "GetNamesByCategoryAndState") == 0)
        return (2);
    else if (strcmp(search, "GetNamesWithMultipleStates") == 0)
        return (3);
    else if (strcmp(search, "GetNamesWithMultipleCategories") == 0)
        return (4);
    else if (strcmp(search, "GetCategory") == 0)
        return (5);
    else if (strcmp(search, "GetState") == 0)
        return (6);
}

void get_children(nodes **node) {

}

void get_parent(nodes **node) {

}
