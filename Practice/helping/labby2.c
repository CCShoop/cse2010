#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (strcmp(argv[1], argv[2]) > 0 && strcmp(argv[1], argv[3]) > 0 && strcmp(argv[2], argv[3]) > 0) {
		printf("%s\n%s\n%s", argv[1], argv[2], argv[3]);
	}
	else if (strcmp(argv[1], argv[2]) > 0 && strcmp(argv[1], argv[3]) > 0 && strcmp(argv[3], argv[2]) > 0) {
		printf("%s\n%s\n%s\n", argv[1], argv[3], argv[2]);
	}
	else if (strcmp(argv[2], argv[1]) > 0 && strcmp(argv[2], argv[3]) > 0 && strcmp(argv[1], argv[3]) > 0) {
		printf("%s\n%s\n%s\n", argv[2], argv[1], argv[3]);
	}
	else if (strcmp(argv[2], argv[1]) > 0 && strcmp(argv[2], argv[3]) > 0 && strcmp(argv[3], argv[1]) > 0) {
		printf("%s\n%s\n%s\n", argv[2], argv[3], argv[1]);
	}
	else if (strcmp(argv[3], argv[1]) > 0 && strcmp(argv[3], argv[2]) > 0 && strcmp(argv[1], argv[2]) > 0) {
		printf("%s\n%s\n%s\n", argv[3], argv[1], argv[2]);
	}
	else if (strcmp(argv[3], argv[1]) > 0 && strcmp(argv[3], argv[2]) > 0 && strcmp(argv[2], argv[1]) > 0) {
		printf("%s\n%s\n%s\n", argv[3], argv[2], argv[1]);
	}

	return (0);
}