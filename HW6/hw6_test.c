/*
	Author: Cael Shoop
	Email: cshoop2018@my.fit.edu
	Course: CSE 2010
	Section: 2
	Description: Homework Assignment 6
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entity {
	int y;
	int x;
}entity;

typedef struct map {
	char occupied_by;
	int visited;
	entity *point;
}map;

typedef struct route {
	entity *node;
	struct route *next;
	struct route *prev;
}route;

typedef struct tree {
	int distance;
	entity *point;
	struct tree *parent;
	struct tree *right;
	struct tree *left;
	struct tree *up;
	struct tree *down;
}tree;

entity *pacman = NULL, *ghost_g = NULL, *ghost_h = NULL, *ghost_o = NULL, *ghost_s = NULL;
int score = 0, debug = 0, up_or_down = 0;

void print_grid(int height, int width, map grid[height][width]);
void ghost_check(int ghost, int height, int width, map grid[height][width]);
void BFS(int *y, int *x, int height, int width, map grid[height][width]);
void enqueue(route **path, int y, int x);
entity *pop(route **path);
void add_branch(tree **search, entity *v, int direction);
tree *search_tree(tree *search, entity *v);

int main(int argc, char* argv[]) {
	char direction;
	int wall_or_ghost = 0, height, width, dots = 0, move = 0;
	FILE *input;
	if (argv[1] != NULL)
		input = fopen(argv[1], "r");
	else {
		printf("Error: No file specified. Exiting.\n");
		return (1);
	}
	if (input == NULL) {
		printf("Error: File \"%s\" not found. Exiting.\n", argv[1]); //exits program if file is not found
		return (1);
	}
	if (argv[2] != NULL && strcmp(argv[2], "debug") == 0) //put "debug" after the file in command prompt
		debug = 1;										  //to view debug output
	fscanf(input, "%d %d", &height, &width);
	if (width == 0) {
		printf("\nGrid width is 0, program terminating.\n");
		fclose(input);
		return (1);
	}
	else if (height == 0) {
		printf("\nGrid height is 0, program terminating.\n");
		fclose(input);
		return (1);
	}
	if (debug == 1)
		printf("--height: %d, width: %d\n", height, width);
	map grid[height][width];
	if (debug == 1)
		printf("--created grid\n");
	char line[width + 3];
	if (debug == 1)
		printf("--created line\n");
	fgets(line, width, input);
	for (int i = 0; i < height; i++) {
		fgets(line, width + 3, input);
		strtok(line, "\n");
		for (int j = 0; j < width; j++) {
			grid[i][j].occupied_by = line[j];
			if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
				grid[i][j].visited = 0;
			else
				grid[i][j].visited = 1;
			entity *point = malloc(sizeof(entity));
			point->y = i;
			point->x = j;
			grid[i][j].point = point;
			if (line[j] == '.' || line[j] == 'G' || line[j] == 'H' || line[j] == 'O' || line[j] == 'S')
				dots++;
			if (line[j] == 'P' || line[j] == 'p') {
				pacman = malloc(sizeof(entity));
				pacman->y = i;
				pacman->x = j;
			}
			else if (line[j] == 'G' || line[j] == 'g') {
				ghost_g = malloc(sizeof(entity));
				ghost_g->y = i;
				ghost_g->x = j;
			}
			else if (line[j] == 'H' || line[j] == 'h') {
				ghost_h = malloc(sizeof(entity));
				ghost_h->y = i;
				ghost_h->x = j;
			}
			else if (line[j] == 'O' || line[j] == 'o') {
				ghost_o = malloc(sizeof(entity));
				ghost_o->y = i;
				ghost_o->x = j;
			}
			else if (line[j] == 'S' || line[j] == 's') {
				ghost_s = malloc(sizeof(entity));
				ghost_s->y = i;
				ghost_s->x = j;
			}
		}
	}
	fclose(input);
	if (debug == 1)
		printf("--dots: %d\n", dots);
	if (dots == 0) {
		printf("There are no dots! Pac-man wins by default!\n");
		return (1);
	}
	do {
		print_grid(height, width, grid);
		do {
			printf("\nPlease enter your move [u(p), d(own), l(eft), or r(ight)]: ");
			scanf(" %c", &direction);
			printf("\n");
			if (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r') {
				printf("Error: Invalid direction.\n");
				move = 0;
			}
			else if (direction == 'u') {
				if (grid[pacman->y - 1][pacman->x].occupied_by == '#' || grid[pacman->y - 1][pacman->x].occupied_by == 'G' || grid[pacman->y - 1][pacman->x].occupied_by == 'g' || grid[pacman->y - 1][pacman->x].occupied_by == 'H' || grid[pacman->y - 1][pacman->x].occupied_by == 'h' || grid[pacman->y - 1][pacman->x].occupied_by == 'O' || grid[pacman->y - 1][pacman->x].occupied_by == 'o' || grid[pacman->y - 1][pacman->x].occupied_by == 'S' || grid[pacman->y - 1][pacman->x].occupied_by == 's') {
					printf("Error: Pac-man cannot move up!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'd') {
				if (grid[pacman->y + 1][pacman->x].occupied_by == '#' || grid[pacman->y + 1][pacman->x].occupied_by == 'G' || grid[pacman->y + 1][pacman->x].occupied_by == 'g' || grid[pacman->y + 1][pacman->x].occupied_by == 'H' || grid[pacman->y + 1][pacman->x].occupied_by == 'h' || grid[pacman->y + 1][pacman->x].occupied_by == 'O' || grid[pacman->y + 1][pacman->x].occupied_by == 'o' || grid[pacman->y + 1][pacman->x].occupied_by == 'S' || grid[pacman->y + 1][pacman->x].occupied_by == 's') {
					printf("Error: Pac-man cannot move down!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'l') {
				if (grid[pacman->y][pacman->x - 1].occupied_by == '#' || grid[pacman->y][pacman->x - 1].occupied_by == 'G' || grid[pacman->y][pacman->x - 1].occupied_by == 'g' || grid[pacman->y][pacman->x - 1].occupied_by == 'H' || grid[pacman->y][pacman->x - 1].occupied_by == 'h' || grid[pacman->y][pacman->x - 1].occupied_by == 'O' || grid[pacman->y][pacman->x - 1].occupied_by == 'o' || grid[pacman->y][pacman->x - 1].occupied_by == 'S' || grid[pacman->y][pacman->x - 1].occupied_by == 's') {
					printf("Error: Pac-man cannot move left!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'r') {
				if (grid[pacman->y][pacman->x + 1].occupied_by == '#' || grid[pacman->y][pacman->x + 1].occupied_by == 'G' || grid[pacman->y][pacman->x + 1].occupied_by == 'g' || grid[pacman->y][pacman->x + 1].occupied_by == 'H' || grid[pacman->y][pacman->x + 1].occupied_by == 'h' || grid[pacman->y][pacman->x + 1].occupied_by == 'O' || grid[pacman->y][pacman->x + 1].occupied_by == 'o' || grid[pacman->y][pacman->x + 1].occupied_by == 'S' || grid[pacman->y][pacman->x + 1].occupied_by == 's') {
					printf("Error: Pac-man cannot move right!\n");
					move = 0;
				}
				else
					move = 1;
			}
		} while (move == 0);
		grid[pacman->y][pacman->x].occupied_by = ' ';
		switch (direction) {
			case 'u':
				pacman->y--;
				break;
			case 'd':
				pacman->y++;
				break;
			case 'l':
				pacman->x--;
				break;
			case 'r':
				pacman->x++;
				break;
			default:
				printf("Error: Unrecognized Direction. Exiting.\n");
				return(1);
		}
		if (grid[pacman->y][pacman->x].occupied_by == '.')
			score++;
		grid[pacman->y][pacman->x].occupied_by = 'P';
		print_grid(height, width, grid);
		if (score == dots) {
			printf("\nPac-man is full!\n\n");
			return (0);
		}
		printf("\nPoints: %d\n", score);
		if (ghost_g != NULL) {
			ghost_check(0, height, width, grid);
		}
		if (ghost_h != NULL) {
			ghost_check(1, height, width, grid);
		}
		if (ghost_o != NULL) {
			ghost_check(2, height, width, grid);
		}
		if (ghost_s != NULL) {
			ghost_check(3, height, width, grid);
		}
		printf("\n");
		if (pacman == NULL) {
			printf("A ghost is not hungry anymore!\n\n");
			return (0);
		}
	} while (score != dots);
    return (0);
}

void print_grid(int height, int width, map grid[height][width]) {
	printf("  ");
	for (int i = 0; i < width; i++)
		printf("%d", i);
	for (int i = 0; i < height; i++) {
		printf("\n%d ", i);
		for (int j = 0; j < width; j++) {
			printf("%c", grid[i][j].occupied_by);
		}
	}
	printf("\n");
}

void ghost_check(int ghost, int height, int width, map grid[height][width]) {
	int new_y, new_x;
	switch (ghost) {
		case 0: //ghost_g
			printf("Ghost g:"); // move (u/l/d/r), distance, points on path
			new_y = ghost_g->y;
			new_x = ghost_g->x;
			BFS(&new_y, &new_x, height, width, grid);
			if (grid[ghost_g->y][ghost_g->x].occupied_by == 'G')
				grid[ghost_g->y][ghost_g->x].occupied_by = '.';
			else
				grid[ghost_g->y][ghost_g->x].occupied_by = ' ';
			ghost_g->y = new_y;
			ghost_g->x = new_x;
			if (grid[new_y][new_x].occupied_by == 'P') {
				pacman = NULL;
				grid[new_y][new_x].occupied_by = 'g';
				return;
			}
			else if (grid[new_y][new_x].occupied_by == '.')
				grid[new_y][new_x].occupied_by = 'G';
			else
				grid[new_y][new_x].occupied_by = 'g';
			break;
		case 1: //ghost_h
			printf("Ghost h: ");
			new_y = ghost_h->y;
			new_x = ghost_h->x;
			//BFS(&new_y, &new_x, height, width, grid);
			if (grid[ghost_h->y][ghost_h->x].occupied_by == 'H')
				grid[ghost_h->y][ghost_h->x].occupied_by = '.';
			else
				grid[ghost_h->y][ghost_h->x].occupied_by = ' ';
			ghost_h->y = new_y;
			ghost_h->x = new_x;
			if (grid[new_y][new_x].occupied_by == 'P') {
				pacman = NULL;
				grid[new_y][new_x].occupied_by = 'h';
				return;
			}
			else if (grid[new_y][new_x].occupied_by == '.')
				grid[new_y][new_x].occupied_by = 'H';
			else
				grid[new_y][new_x].occupied_by = 'h';
			break;
		case 2: //ghost_o
			printf("Ghost o: ");
			new_y = ghost_o->y;
			new_x = ghost_o->x;
			//BFS(&new_y, &new_x, height, width, grid);
			if (grid[ghost_o->y][ghost_o->x].occupied_by == 'O')
				grid[ghost_o->y][ghost_o->x].occupied_by = '.';
			else
				grid[ghost_o->y][ghost_o->x].occupied_by = ' ';
			ghost_o->y = new_y;
			ghost_o->x = new_x;
			if (grid[new_y][new_x].occupied_by == 'P') {
				pacman = NULL;
				grid[new_y][new_x].occupied_by = 'o';
				return;
			}
			else if (grid[new_y][new_x].occupied_by == '.')
				grid[new_y][new_x].occupied_by = 'O';
			else
				grid[new_y][new_x].occupied_by = 'o';
			break;
		case 3: //ghost_s
			printf("Ghost s: ");
			new_y = ghost_s->y;
			new_x = ghost_s->x;
			//BFS(&new_y, &new_x, height, width, grid);
			if (grid[ghost_s->y][ghost_s->x].occupied_by == 'S')
				grid[ghost_s->y][ghost_s->x].occupied_by = '.';
			else
				grid[ghost_s->y][ghost_s->x].occupied_by = ' ';
			ghost_s->y = new_y;
			ghost_s->x = new_x;
			if (grid[new_y][new_x].occupied_by == 'P') {
				pacman = NULL;
				grid[new_y][new_x].occupied_by = 's';
				return;
			}
			else if (grid[new_y][new_x].occupied_by == '.')
				grid[new_y][new_x].occupied_by = 'S';
			else
				grid[new_y][new_x].occupied_by = 's';
			break;
		default:
			printf("Error: Ghost does not exist.\n");
			break;
	}
	printf("\n");
}

void BFS(int *y, int *x, int height, int width, map grid[height][width]) {
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			grid[i][j].visited = 0;
		}
	}
	entity *point = malloc(sizeof(entity));
	point->y = *y;
	point->x = *x;
	route *path = malloc(sizeof(route)); //queue = new empty node
	path->next = NULL;
	path->prev = NULL;
	path->node = point;
	enqueue(&path, *y, *x); //enqueue(queue, s)
	tree *found = malloc(sizeof(tree)); //shortest route path via tree
	found->down = NULL;
	found->up = NULL;
	found->right = NULL;
	found->left = NULL;
	found->parent = NULL;
	found->distance = 0;
	found->point = point;
	tree *search = NULL;
	while (path != NULL) { //while not is_empty(queue)
		entity *v = pop(&path); //v = dequeue(queue)
		if (debug == 1)
			printf("\n\n--popped (%d, %d), visited: %d", v->y, v->x, grid[v->y][v->x].visited);
		if (grid[v->y][v->x].visited == 0) { //if getlabel(v) != VISITED
			grid[v->y][v->x].visited = 1; //setlabel(v, VISITED)
			search = search_tree(found, v);
			if (grid[v->y - 1][v->x].occupied_by != '#' && grid[v->y - 1][v->x].occupied_by != 'G' && grid[v->y - 1][v->x].occupied_by != 'g' && grid[v->y - 1][v->x].occupied_by != 'H' && grid[v->y - 1][v->x].occupied_by != 'h' && grid[v->y - 1][v->x].occupied_by != 'O' && grid[v->y - 1][v->x].occupied_by != 'o' && grid[v->y - 1][v->x].occupied_by != 'S' && grid[v->y - 1][v->x].occupied_by != 's' && grid[v->y - 1][v->x].visited == 0) {
				enqueue(&path, v->y - 1, v->x); //neighbors = get_adjacent_vertices(G, v)
				add_branch(&search, v, 0);
			}
			if (grid[v->y + 1][v->x].occupied_by != '#' && grid[v->y + 1][v->x].occupied_by != 'G' && grid[v->y + 1][v->x].occupied_by != 'g' && grid[v->y + 1][v->x].occupied_by != 'H' && grid[v->y + 1][v->x].occupied_by != 'h' && grid[v->y + 1][v->x].occupied_by != 'O' && grid[v->y + 1][v->x].occupied_by != 'o' && grid[v->y + 1][v->x].occupied_by != 'S' && grid[v->y + 1][v->x].occupied_by != 's' && grid[v->y + 1][v->x].visited == 0) {
				enqueue(&path, v->y + 1, v->x); //if getlabel(w) != VISITED
				add_branch(&search, v, 1);
			}
			if (grid[v->y][v->x - 1].occupied_by != '#' && grid[v->y][v->x - 1].occupied_by != 'G' && grid[v->y][v->x - 1].occupied_by != 'g' && grid[v->y][v->x - 1].occupied_by != 'H' && grid[v->y][v->x - 1].occupied_by != 'h' && grid[v->y][v->x - 1].occupied_by != 'O' && grid[v->y][v->x - 1].occupied_by != 'o' && grid[v->y][v->x - 1].occupied_by != 'S' && grid[v->y][v->x - 1].occupied_by != 's' && grid[v->y][v->x - 1].visited == 0) {
				enqueue(&path, v->y, v->x - 1); //for each w in neighbors "children"
				add_branch(&search, v, 2);
			}
			if (grid[v->y][v->x + 1].occupied_by != '#' && grid[v->y][v->x + 1].occupied_by != 'G' && grid[v->y][v->x + 1].occupied_by != 'g' && grid[v->y][v->x + 1].occupied_by != 'H' && grid[v->y][v->x + 1].occupied_by != 'h' && grid[v->y][v->x + 1].occupied_by != 'O' && grid[v->y][v->x + 1].occupied_by != 'o' && grid[v->y][v->x + 1].occupied_by != 'S' && grid[v->y][v->x + 1].occupied_by != 's' && grid[v->y][v->x + 1].visited == 0) {
				enqueue(&path, v->y, v->x + 1); //enqueue(queue, w)
				add_branch(&search, v, 3);
			}
			if (v->y == pacman->y && v->x == pacman->x) { //found pacman
				if (debug == 1)
					printf("\n--pacman found!");
				break;
			}
		}
	}
}

void enqueue(route **path, int y, int x) {
	route *new = malloc(sizeof(route)), *temp = *path;
	entity *point = malloc(sizeof(entity));
	point->y = y;
	point->x = x;
	new->node = point;
	new->next = NULL;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

entity *pop(route **path) {
	if (*path != NULL) {
		entity *remove = (*path)->node;
		route *delete = (*path);
		*path = (*path)->next;
		(*path)->prev = NULL;
		free(delete);
		return (remove);
	}
	else
		return (NULL);
}

void add_branch(tree **search, entity *v, int direction) {
	tree *new = malloc(sizeof(tree));
	new->down = NULL;
	new->up = NULL;
	new->right = NULL;
	new->left = NULL;
	new->parent = *search;
	new->distance = 0;
	new->point = v;
	if (*search != NULL) {
		if (debug == 1)
			printf("\n--search: (%d, %d), v: (%d, %d)", (*search)->point->y, (*search)->point->x, v->y, v->x);
		switch (direction) {
			case 0: //up
				new->point->y--;
				if (debug == 1)
					printf("\n---adding branch up (%d, %d)", new->point->y, new->point->x);
				(*search)->up = new;
				if (debug == 1) {
					printf("\n---new: (%d, %d)", new->point->y, new->point->x);
					printf("\n---search: (%d, %d)", (*search)->point->y, (*search)->point->x);
					printf("\n---search->up: (%d, %d)", (*search)->up->point->y, (*search)->up->point->x);
				}
				break;
			case 1: //down
				new->point->y++;
				if (debug == 1)
					printf("\n---adding branch down (%d, %d)", new->point->y, new->point->x);
				(*search)->down = new;
				if (debug == 1) {
					printf("\n---new: (%d, %d)", new->point->y, new->point->x);
					printf("\n---search: (%d, %d)", (*search)->point->y, (*search)->point->x);
					printf("\n---search->up: (%d, %d)", (*search)->down->point->y, (*search)->down->point->x);
				}
				break;
			case 2: //left
				new->point->x--;
				if (debug == 1)
					printf("\n---adding branch left (%d, %d)", new->point->y, new->point->x);
				(*search)->left = new;
				if (debug == 1) {
					printf("\n---new: (%d, %d)", new->point->y, new->point->x);
					printf("\n---search: (%d, %d)", (*search)->point->y, (*search)->point->x);
					printf("\n---search->up: (%d, %d)", (*search)->left->point->y, (*search)->left->point->x);
				}
				break;
			case 3: //right
				new->point->x++;
				if (debug == 1)
					printf("\n---adding branch right (%d, %d)", new->point->y, new->point->x);
				(*search)->right = new;
				if (debug == 1) {
					printf("\n---new: (%d, %d)", new->point->y, new->point->x);
					printf("\n---search: (%d, %d)", (*search)->point->y, (*search)->point->x);
					printf("\n---search->up: (%d, %d)", (*search)->right->point->y, (*search)->right->point->x);
				}
				break;
		}
	}
	else {
		if (debug == 1)
			printf("\n|--ERROR: SEARCH IS NULL");
	}
}

tree *search_tree(tree *search, entity *v) {
	tree *branch = NULL;
	if (debug == 1)
		printf("\n|--current search: (%d, %d), current v: (%d, %d)", search->point->y, search->point->x, v->y, v->x);
	if (v->y == search->point->y && v->x == search->point->x) {
		if (debug == 1)
			printf("\n|---SEARCH COMPLETE at location (%d, %d)", v->y, v->x);
		return (search);
	}
	if (search->up != NULL && v->y < search->point->y) {
		if (debug == 1) {
			printf("\n|---searching up from (%d, %d) to (%d, %d)", search->point->y, search->point->x, v->y, v->x);
			printf("\n|----search: (%d, %d)\n|----search->up: (%d, %d)", search->point->y, search->point->x, search->up->point->y, search->up->point->x);
		}
		branch = search_tree(search->up, v);
	}
	if (search->down != NULL && v->y > search->point->y) {
		if (debug == 1) {
			printf("\n|---searching down from (%d, %d) to (%d, %d)", search->point->y, search->point->x, v->y, v->x);
			printf("\n|----search: (%d, %d)\n|----search->down: (%d, %d)", search->point->y, search->point->x, search->up->point->y, search->up->point->x);
		}
		branch = search_tree(search->down, v);
	}
	if (search->left != NULL && v->x < search->point->x) {
		if (debug == 1) {
			printf("\n|---searching left from (%d, %d) to (%d, %d)", search->point->y, search->point->x, v->y, v->x);
			printf("\n|----search: (%d, %d)\n|----search->left: (%d, %d)", search->point->y, search->point->x, search->up->point->y, search->up->point->x);
		}
		branch = search_tree(search->left, v);
	}
	if (search->right != NULL && v->x > search->point->x) {
		if (debug == 1) {
			printf("\n|---searching right from (%d, %d) to (%d, %d)", search->point->y, search->point->x, v->y, v->x);
			printf("\n|----search: (%d, %d)\n|----search->right: (%d, %d)", search->point->y, search->point->x, search->up->point->y, search->up->point->x);
		}
		branch = search_tree(search->right, v);
	}
	return (branch);
}