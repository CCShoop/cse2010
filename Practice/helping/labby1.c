#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	char sentence[100], words[100][100], letter;
	int j = 0, k = 0, i = 0;

	printf("Enter a sentence: ");
	fgets(sentence, 100, stdin);

	printf("Enter a character: ");
	scanf(" %c", &letter);

	for (i = 0; i < strlen(sentence); i++) {
		if (sentence[i] == ' ' || sentence[i] == '\0') {
			words[k][j] = '\0';
			k++;
			j = 0;
		}
		else {
			words[k][j] = sentence[i];
			j++;
		}
	}
	
	for (i = 0; i <= k; i++) {
		if (words[i][0] == letter) {
			printf("%s\n", words[i]);
		}
	}

	return (0);
}