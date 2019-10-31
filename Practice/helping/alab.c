#include <stdio.h>

int main(void) {

    char letter;
    int num = 0;

    do {
        printf("Enter a character: ");
        scanf(" %c", &letter);
		if (letter == '-') {
            printf("This is my sentinal!\n");
			num = 1;
        }
        else if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U' || letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
            printf("It is a vowel!\n");
        }
        else if (letter == 'B' || letter == 'C' || letter == 'D' || letter == 'F' || letter == 'G' || letter == 'H' || letter == 'J' || letter == 'K' || letter == 'L' || letter == 'M' || letter == 'N' || letter == 'P' || letter == 'Q' || letter == 'R' || letter == 'S' || letter == 'T' || letter == 'V' || letter == 'W' || letter == 'X' || letter == 'Y' || letter == 'Z' || letter == 'b' || letter == 'c' || letter == 'd' || letter == 'f' || letter == 'g' || letter == 'h' || letter == 'j' || letter == 'k' || letter == 'l' || letter == 'm' || letter == 'n' || letter == 'p' || letter == 'q' || letter == 'r' || letter == 's' || letter == 't' || letter == 'v' || letter == 'w' || letter == 'x' || letter == 'y' || letter == 'z') {
            printf("It is a consonant!\n");
        }
        else {
            printf("Try again.");
        }
    } while (num == 0);

    return 0;
}
