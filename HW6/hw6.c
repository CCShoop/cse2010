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

typedef struct g_node {
	char occupied_by;
	struct g_node *right;
	struct g_node *left;
	struct g_node *up;
	struct g_node *down;
}g_node;

typedef struct world {
	int height;
	int width;
	struct g_node *grid;
}world;

world *map = NULL;
g_node *pacman = NULL;
g_node *ghost_g = NULL;
g_node *ghost_h = NULL;
g_node *ghost_o = NULL;
g_node *ghost_s = NULL;
int score = 0, debug = 0;

void create_grid(FILE *input);
void print_grid();


int main(int argc, char* argv[]) {
	char direction;
	int wall_or_ghost = 0;
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
	map = malloc(sizeof(world));
	int grid_height, grid_width;
	fscanf(input, "%d %d", &grid_height, &grid_width);
	if (grid_width == 0) {
		printf("\nGrid width is 0, program terminating.\n");
		return (1);
	}
	else if (grid_height == 0) {
		printf("\nGrid height is 0, program terminating.\n");
		return (1);
	}
	map->height = grid_height;
	map->width = grid_width;
	if (debug == 1)
		printf("---map->height: %d, map->width: %d\n", map->height, map->width);
	create_grid(input);
	do {
		print_grid();
		do {
			printf("\nPlease enter your move [u(p), d(own), l(eft), r(ight)]: ");
			scanf(" %c", &direction);
			printf("\n");
			if (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r')
				printf("Error: Invalid direction.\n");
			if (direction == 'u' && pacman->up != NULL)
				if (pacman->up->occupied_by == '#' || pacman->up->occupied_by == 'G' || pacman->up->occupied_by == 'H' || pacman->up->occupied_by == 'O' || pacman->up->occupied_by == 'S' || pacman->up->occupied_by == 'g' || pacman->up->occupied_by == 'h' || pacman->up->occupied_by == 'o' || pacman->up->occupied_by == 's') {
					wall_or_ghost = 1;
					direction = pacman->up->occupied_by;
				}
			else if (direction == 'd' && pacman->down != NULL)
				if (pacman->down->occupied_by == '#' || pacman->down->occupied_by == 'G' || pacman->down->occupied_by == 'H' || pacman->down->occupied_by == 'O' || pacman->down->occupied_by == 'S' || pacman->down->occupied_by == 'g' || pacman->down->occupied_by == 'h' || pacman->down->occupied_by == 'o' || pacman->down->occupied_by == 's') {
					wall_or_ghost = 1;
					direction = pacman->down->occupied_by;
				}
			else if (direction == 'l' && pacman->left != NULL)
				if (pacman->left->occupied_by == '#' || pacman->left->occupied_by == 'G' || pacman->left->occupied_by == 'H' || pacman->left->occupied_by == 'O' || pacman->left->occupied_by == 'S' || pacman->left->occupied_by == 'g' || pacman->left->occupied_by == 'h' || pacman->left->occupied_by == 'o' || pacman->left->occupied_by == 's') {
					wall_or_ghost = 1;
					direction = pacman->left->occupied_by;
				}
			else if (direction == 'r' && pacman->right != NULL)
				if (pacman->right->occupied_by == '#' || pacman->right->occupied_by == 'G' || pacman->right->occupied_by == 'H' || pacman->right->occupied_by == 'O' || pacman->right->occupied_by == 'S' || pacman->right->occupied_by == 'g' || pacman->right->occupied_by == 'h' || pacman->right->occupied_by == 'o' || pacman->right->occupied_by == 's') {
					wall_or_ghost = 1;
					direction = pacman->right->occupied_by;
				}
			else
				wall_or_ghost = 0;
			if (wall_or_ghost == 1)
				printf("Pacman can't move into a space containing %c!\n", direction);
			if (debug == 1)
				printf("--wall_or_ghost: %d\n", wall_or_ghost);
		} while ((direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r') || (wall_or_ghost == 1));
	} while (1);
	print_grid();
	printf("\nPoints: %d\n", score);
	if (ghost_g != NULL) {
		//generate shortest path
		printf("Ghost g: ");
		printf("\n");
	}
	if (ghost_h != NULL) {
		//generate shortest path
		printf("Ghost h: ");
		printf("\n");
	}
	if (ghost_o != NULL) {
		//generate shortest path
		printf("Ghost o: ");
		printf("\n");
	}
	if (ghost_s != NULL) {
		//generate shortest path
		printf("Ghost s: ");
		printf("\n");
	}
	fclose(input);
    return (0);
}

void create_grid(FILE *input) {
	if (debug == 1)
		printf("--in create_grid()\n"); //if debug is entered, it will show all debug information in this fashion
	char file[100];
	map->grid = malloc(sizeof(g_node));
	map->grid->left = NULL;
	map->grid->up = NULL;
	map->grid->right = NULL;
	map->grid->down = NULL;
	g_node *create = map->grid;
	g_node *create2 = create;
	fgets(file, 100, input);
	for (int i = 0; i < map->height; i++) {
		fgets(file, 100, input);
		strtok(file, "\n");
		if (debug == 1)
			printf("--occupier: %s\n", file);
		for (int j = 0; j < map->width; j++) {
			create->occupied_by = file[j];
			if (file[j] == 'P' || file[j] == 'p') {
				pacman = create;
				create->occupied_by = 'P';
			}
			else if (file[j] == 'G' || file[j] == 'g')
				ghost_g = create;
			else if (file[j] == 'H' || file[j] == 'h')
				ghost_h = create;
			else if (file[j] == 'O' || file[j] == 'o')
				ghost_o = create;
			else if (file[j] == 'S' || file[j] == 's')
				ghost_s = create;
			create->right = malloc(sizeof(g_node));
			create->right->left = create;
			create = create->right;
		}
		create2->down = malloc(sizeof(g_node));
		create2->down->up = create2;
		create2 = create2->down;
		create = create2;
	}
}

void print_grid() {
	if (debug == 1)
		printf("--in print_grid()\n\n");
	g_node *print = map->grid;
	g_node *print2 = print;
	printf("  ");
	for (int i = 0; i < map->width; i++)
		printf("%d", i);
	printf("\n");
	for (int i = 0; i < map->height; i++) {
		printf("%d ", i);
		for (int j = 0; j < map->width; j++) {
			printf("%c", print->occupied_by);
			if (print->right != NULL)
				print = print->right;
		}
		printf("\n");
		if (print2->down != NULL)
			print2 = print2->down;
		print = print2;
	}
}
