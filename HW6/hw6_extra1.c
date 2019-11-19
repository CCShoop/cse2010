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
int score = 0, debug = 0, up_or_down = 0;

void print_grid(int height, int width, char grid[height][width]);
void ghost_check(int ghost, int height, int width, char grid[height][width]);
route *BFS(route *path, int y, int x, int height, int width, char grid[height][width]);
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

void ghost_check(int ghost, int height, int width, char grid[height][width]) {
	int new_y, new_x;
	route *path = NULL;
	entity *point = NULL;
	switch (ghost) {
		case 0: //ghost_g
			printf("Ghost g:"); // move (u/l/d/r), distance, points on path
			new_y = ghost_g->y;
			new_x = ghost_g->x;
			//BFS
			path = BFS(path, new_y, new_x, height, width, grid);
			if (path != NULL) {
				if (grid[new_y][new_x] == 'g')
					grid[new_y][new_x] = ' ';
				else
					grid[new_y][new_x] = '.';
				if (path->next != NULL && path->distance != 0) {
					if (path->next->node->y < path->node->y) {
						printf(" u");
						new_y--;
						ghost_g->y--;
					}
					else if (path->next->node->y > path->node->y) {
						printf(" d");
						new_y++;
						ghost_g->y++;
					}
					else if (path->next->node->x < path->node->x) {
						printf(" l");
						new_x--;
						ghost_g->x--;
					}
					else if (path->next->node->x > path->node->x) {
						printf(" r");
						new_x++;
						ghost_g->x++;
					}
				}
				printf(" %d", path->distance);
				while (path->next != NULL) {
					point = pop(&path);
					printf(" (%d, %d)", point->y, point->x);
				}
				printf(" (%d, %d)", pacman->y, pacman->x);
			}
			if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'g';
				return;
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
			
			/*if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'h';
				return;
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'H';
			else
				grid[new_y][new_x] = 'h';*/
			break;
		case 2: //ghost_o
			printf("Ghost o: ");
			new_y = ghost_o->y;
			new_x = ghost_o->x;

			/*if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 'o';
				return;
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'O';
			else
				grid[new_y][new_x] = 'o';*/
			break;
		case 3: //ghost_s
			printf("Ghost s: ");
			new_y = ghost_s->y;
			new_x = ghost_s->x;

			/*if (grid[new_y][new_x] == 'P') {
				pacman = NULL;
				grid[new_y][new_x] = 's';
				return;
			}
			else if (grid[new_y][new_x] == '.')
				grid[new_y][new_x] = 'S';
			else
				grid[new_y][new_x] = 's';*/
			break;
		default:
			printf("Error: Ghost does not exist.\n");
			break;
	}
	printf("\n");
}

route *BFS(route *path, int y, int x, int height, int width, char grid[height][width]) {
	if (debug == 1)
		printf("\n--in BFS");
	if (path != NULL) {
		route *temp = path;
		while (temp->next != NULL)
			temp = temp->next;
		if (((temp->node->y == pacman->y - 1 || temp->node->y == pacman->y + 1) && temp->node->x == pacman->x) || (temp->node->y == pacman->y && (temp->node->x == pacman->x - 1 || temp->node->x == pacman->x + 1))) {
			if (debug == 1)
				printf("\n--ghost would be at pacman");
			enqueue(&path, pacman);
			return (path);
		}
	}
	entity *current = malloc(sizeof(entity));
	current->y = y;
	current->x = x;
	if (path == NULL) {
		path = malloc(sizeof(route));
		path->node = current;
		path->distance = 0;
	}
	else
		enqueue(&path, current);
	if (debug == 1)
		printf("\n--ghost would be at: %d, %d", y, x);
	if (up_or_down == 0) {
		up_or_down = 1;
		if (y < pacman->y) {
			if (debug == 1)
				printf("\n--moving down");
			if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
		}
		else if (y > pacman->y) {
			if (debug == 1)
				printf("\n--moving up");
			if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
		}
		else if (x < pacman->x) {
			if (debug == 1)
				printf("\n--moving right");
			if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
		}
		else if (x > pacman->x) {
			if (debug == 1)
				printf("\n--moving left");
			if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
		}
	}
	else {
		up_or_down = 0;
		if (x < pacman->x) {
			if (debug == 1)
				printf("\n--moving right");
			if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
		}
		else if (x > pacman->x) {
			if (debug == 1)
				printf("\n--moving left");
			if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
		}
		if (y < pacman->y) {
			if (debug == 1)
				printf("\n--moving down");
			if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
		}
		else if (y > pacman->y) {
			if (debug == 1)
				printf("\n--moving up");
			if (grid[y - 1][x] != '#' && grid[y - 1][x] != 'G' && grid[y - 1][x] != 'g' && grid[y - 1][x] != 'H' && grid[y - 1][x] != 'h' && grid[y - 1][x] != 'O' && grid[y - 1][x] != 'o' && grid[y - 1][x] != 'S' && grid[y - 1][x] != 's')
				path = BFS(path, y - 1, x, height, width, grid);
			else if (grid[y][x + 1] != '#' && grid[y][x + 1] != 'G' && grid[y][x + 1] != 'g' && grid[y][x + 1] != 'H' && grid[y][x + 1] != 'h' && grid[y][x + 1] != 'O' && grid[y][x + 1] != 'o' && grid[y][x + 1] != 'S' && grid[y][x + 1] != 's')
				path = BFS(path, y, x + 1, height, width, grid);
			else if (grid[y][x - 1] != '#' && grid[y][x - 1] != 'G' && grid[y][x - 1] != 'g' && grid[y][x - 1] != 'H' && grid[y][x - 1] != 'h' && grid[y][x - 1] != 'O' && grid[y][x - 1] != 'o' && grid[y][x - 1] != 'S' && grid[y][x - 1] != 's')
				path = BFS(path, y, x - 1, height, width, grid);
			else if (grid[y + 1][x] != '#' && grid[y + 1][x] != 'G' && grid[y + 1][x] != 'g' && grid[y + 1][x] != 'H' && grid[y + 1][x] != 'h' && grid[y + 1][x] != 'O' && grid[y + 1][x] != 'o' && grid[y + 1][x] != 'S' && grid[y + 1][x] != 's')
				path = BFS(path, y + 1, x, height, width, grid);
		}
	}
	return (path);
}

void enqueue(route **path, entity *point) {
	route *new = malloc(sizeof(route)), *temp = *path;
	while (temp->next != NULL)
		temp = temp->next;
	new->node = point;
	new->next = NULL;
	temp->next = new;
	(*path)->distance++;
}

entity *pop(route **path) {
	entity *remove = (*path)->node;
	if ((*path)->next != NULL) {
		(*path)->next->distance = (*path)->distance - 1;
		*path = (*path)->next;
	}
	else {
		free(path);
	}
	return (remove);
}