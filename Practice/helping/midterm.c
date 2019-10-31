#include <stdio.h>

int main(void) {
	int input = 0, smallest_num, largest_num, counter = 0;
	while (input >=0 ) {
		printf("Enter a number (negative to quit): ");
		scanf("%d", &input);
		if (counter == 0) {
			smallest_num = input;
			largest_num = input;
			counter++;
		}
		if (input >= 0) {
			if (smallest_num > input)
				smallest_num = input;
			else if (largest_num < input)
				largest_num = input;
		}
	}
	printf("Smallest: %d\nLargest: %d\n", smallest_num, largest_num);
	return (0);
}
