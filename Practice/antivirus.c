#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delete(int program);
int is_installed(int program);
void uninstall(int program);

int main(void) {
	srand(time(NULL));
	int program = rand() % 3, virus = rand() % 2;
	printf("\nWelcome to your antivirus!\n");
	if (program == virus) {
		printf("Virus found! Deleting...\n");
		delete(program);
	}
	else
		printf("No viruses found!\n\n");
	return (0);
}

void delete(int program) {
	char corrupt[1000];
	if (is_installed(program)) {
		printf("Program is installed, deleting.\n");
		uninstall(program);
		printf("Virus deleted!\n\n");
	}
	else
		printf("Program is not installed! Uh oh!\n%s\n", corrupt);
}

int is_installed(int program) {
	int installed = 1;
	if (program == installed)
		return (1);
	else
		return (0);
}

void uninstall(int program) {
	printf("Uninstalling program...\n");
	program = -1;
}
