#include <stdio.h>

int main(void) {
	int num = -1;
	printf("Welcome to Ordinal numbers!\n");
	while (num < 0 || num > 65535) {
		printf("Enter a value between 0 and 65535: ");
		scanf("%d", &num);
		if (num < 0 || num > 65535)
			printf("Input not allowed. Try again.\n\n");
	}
	for (int i = 0; i < num; i++) {
		printf("%d", i);
		switch (i % 10) {
			case 0:
				printf("th");
				break;
			case 1:
				printf("st");
				break;
			case 2:
				printf("nd");
				break;
			case 3:
				printf("rd");
				break;
			case 4:
				printf("th");
				break;
			case 5:
				printf("th");
				break;
			case 6:
				printf("th");
				break;
			case 7:
				printf("th");
				break;
			case 8:
				printf("th");
				break;
			case 9:
				printf("th");
				break;
		}
		printf(" Value\n");
	}
	return (0);
}
