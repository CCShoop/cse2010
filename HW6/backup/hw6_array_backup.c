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

typedef struct route {
	int distance;
	entity *node;
	struct route *next;
}route;

entity *pacman = NULL, *ghost_g = NULL, *ghost_h = NULL, *ghost_o = NULL, *ghost_s = NULL;
int score = 0, debug = 0;

void print_grid(int height, int width, char grid[height][width]);
void ghost_check(int ghost, int height, int width, char grid[height][width], int eligible[height][width]);
route *BFS(route *path, int y, int x, int height, int width, int eligible[height][width]);
void enqueue(route **path, entity *point);
entity *pop(route **path);

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
	char grid[height][width];
	int eligible[height][width];
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
			grid[i][j] = line[j];
			if (line[j] == '.' || line[j] == 'G' || line[j] == 'H' || line[j] == 'O' || line[j] == 'S')
				dots++;
			if (line[j] == 'P' || line[j] == 'p') {
				pacman = malloc(sizeof(entity));
				pacman->y = i;
				pacman->x = j;
				eligible[i][j] = 2;
			}
			else if (line[j] == 'G' || line[j] == 'g') {
				ghost_g = malloc(sizeof(entity));
				ghost_g->y = i;
				ghost_g->x = j;
				eligible[i][j] = 1;
			}
			else if (line[j] == 'H' || line[j] == 'h') {
				ghost_h = malloc(sizeof(entity));
				ghost_h->y = i;
				ghost_h->x = j;
				eligible[i][j] = 1;
			}
			else if (line[j] == 'O' || line[j] == 'o') {
				ghost_o = malloc(sizeof(entity));
				ghost_o->y = i;
				ghost_o->x = j;
				eligible[i][j] = 1;
			}
			else if (line[j] == 'S' || line[j] == 's') {
				ghost_s = malloc(sizeof(entity));
				ghost_s->y = i;
				ghost_s->x = j;
				eligible[i][j] = 1;
			}
			else if (line[j] == '#')
				eligible[i][j] = 1;
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
				if (grid[pacman->y - 1][pacman->x] == '#' || grid[pacman->y - 1][pacman->x] == 'G' || grid[pacman->y - 1][pacman->x] == 'g' || grid[pacman->y - 1][pacman->x] == 'H' || grid[pacman->y - 1][pacman->x] == 'h' || grid[pacman->y - 1][pacman->x] == 'O' || grid[pacman->y - 1][pacman->x] == 'o' || grid[pacman->y - 1][pacman->x] == 'S' || grid[pacman->y - 1][pacman->x] == 's') {
					printf("Error: Pac-man cannot move up!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'd') {
				if (grid[pacman->y + 1][pacman->x] == '#' || grid[pacman->y + 1][pacman->x] == 'G' || grid[pacman->y + 1][pacman->x] == 'g' || grid[pacman->y + 1][pacman->x] == 'H' || grid[pacman->y + 1][pacman->x] == 'h' || grid[pacman->y + 1][pacman->x] == 'O' || grid[pacman->y + 1][pacman->x] == 'o' || grid[pacman->y + 1][pacman->x] == 'S' || grid[pacman->y + 1][pacman->x] == 's') {
					printf("Error: Pac-man cannot move down!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'l') {
				if (grid[pacman->y][pacman->x - 1] == '#' || grid[pacman->y][pacman->x - 1] == 'G' || grid[pacman->y][pacman->x - 1] == 'g' || grid[pacman->y][pacman->x - 1] == 'H' || grid[pacman->y][pacman->x - 1] == 'h' || grid[pacman->y][pacman->x - 1] == 'O' || grid[pacman->y][pacman->x - 1] == 'o' || grid[pacman->y][pacman->x - 1] == 'S' || grid[pacman->y][pacman->x - 1] == 's') {
					printf("Error: Pac-man cannot move left!\n");
					move = 0;
				}
				else
					move = 1;
			}
			else if (direction == 'r') {
				if (grid[pacman->y][pacman->x + 1] == '#' || grid[pacman->y][pacman->x + 1] == 'G' || grid[pacman->y][pacman->x + 1] == 'g' || grid[pacman->y][pacman->x + 1] == 'H' || grid[pacman->y][pacman->x + 1] == 'h' || grid[pacman->y][pacman->x + 1] == 'O' || grid[pacman->y][pacman->x + 1] == 'o' || grid[pacman->y][pacman->x + 1] == 'S' || grid[pacman->y][pacman->x + 1] == 's') {
					printf("Error: Pac-man cannot move right!\n");
					move = 0;
				}
				else
					move = 1;
			}
		} while (move == 0);
		grid[pacman->y][pacman->x] = ' ';
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
		if (grid[pacman->y][pacman->x] == '.')
			score++;
		grid[pacman->y][pacman->x] = 'P';
		print_grid(height, width, grid);
		if (score == dots) {
			printf("\nPac-man is full!\n\n");
			return (0);
		}
		printf("\nPoints: %d\n", score);
		if (ghost_g != NULL) {
			ghost_check(0, height, width, grid, eligible);
		}
		if (ghost_h != NULL) {
			ghost_check(1, height, width, grid, eligible);
		}
		if (ghost_o != NULL) {
			ghost_check(2, height, width, grid, eligible);
		}
		if (ghost_s != NULL) {
			ghost_check(3, height, width, grid, eligible);
		}
		printf("\n");
		if (pacman == NULL) {
			printf("A ghost is not hungry anymore!\n\n");
			return (0);
		}
	} while (score != dots);
    return (0);
}

void print_grid(int height, int width, char grid[height][width]) {
	if (debug == 1)
		printf("--in print_grid()\n\n");
	printf("  ");
	for (int i = 0; i < width; i++)
		printf("%d", i);
	for (int i = 0; i < height; i++) {
		printf("\n%d ", i);
		for (int j = 0; j < width; j++) {
			printf("%c", grid[i][j]);
		}
	}
	printf("\n");
}

void ghost_check(int ghost, int height, int width, char grid[height][width], int eligible[height][width]) {
	int new_y, new_x;
	route *path = NULL;
	entity *point = NULL;
	switch (ghost) {
		case 0: //ghost_g
			printf("Ghost g: ");
			new_y = ghost_g->y;
			new_x = ghost_g->x;
			//BFS - eligible = 0: can go 1: can't go 2: target [pacman]
			path = BFS(path, new_y, new_x, height, width, eligible);
			while (path != NULL) {
				point = pop(&path);
				printf(" (%d, %d)", point->y, point->x);
			}
			//BFS - eligible = 0: can go 1: can't go 2: target [pacman]
			if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'g';
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'G';
			else
				grid[new_y][new_x] = 'g';
			break;
		case 1: //ghost_h
			printf("Ghost h: ");
			new_y = ghost_h->y;
			new_x = ghost_h->x;
			//BFS
			if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'h';
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'H';
			else
				grid[new_y][new_x] = 'h';
			break;
		case 2: //ghost_o
			printf("Ghost o: ");
			new_y = ghost_o->y;
			new_x = ghost_o->x;
			//BFS
			if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'o';
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'O';
			else
				grid[new_y][new_x] = 'o';
			break;
		case 3: //ghost_s
			printf("Ghost s: ");
			new_y = ghost_s->y;
			new_x = ghost_s->x;
			//BFS
			if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 's';
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'S';
			else
				grid[new_y][new_x] = 's';
			break;
		default:
			printf("Error: Ghost does not exist.\n");
			break;
	}
	printf("\n");
}

route *BFS(route *path, int y, int x, int height, int width, int eligible[height][width]) {
	if (debug == 1)
		printf("--in BFS\n");
	/*if (path->node->y == pacman->y && path->node->x == pacman->x)
		return (path);
	entity *current;
	current->y = y;
	current->x = x;
	enqueue(&path, current);*/
}

void enqueue(route **path, entity *point) {
	if (debug == 1)
		printf("--in enqueue\n");
	route *new = malloc(sizeof(route));
	new->node = point;
	new->next = *path;
	*path = new;
}

entity *pop(route **path) {
	if (debug == 1)
		printf("--in pop\n");
	entity *remove = (*path)->node;
	route *temp = *path;
	*path = (*path)->next;
	free(temp);
	return (remove);
}