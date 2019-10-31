#include <stdio.h>

int main(void) {
	int input;
	printf("Enter a number: ");
	scanf("%d", &input);
	for (int i = input; i > 0; i--) {
		printf("%d ", i);
		if (i != 1)
			printf("x ");
	}
	printf("\nFactorial: %d\n", input);
	return (0);
}
