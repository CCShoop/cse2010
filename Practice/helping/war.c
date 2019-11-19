#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *in_deck, int n);
int check_hand(int hand_size, int *hand);
void deal_hand(int *in_deck, int *hand1, int *hand2);
void print_card(int card);

int main(void) {
	int in_deck[52], hand1[52], hand2[52], n = 2;
	char input;
	for (int i = 0; i < 52; i++) {
		in_deck[i] = i;
	}
	printf("\nWelcome to War!\nShuffling deck...\n");
	shuffle(in_deck, n);
	printf("Dealing cards...\n\n");
	deal_hand(in_deck, hand1, hand2);
	do {
		printf("Would you like to play (p) or exit (e): ");
		scanf(" %c", &input);
		printf("\n");
		if (input == 'e' || input == 'E')
			break;
		
	} while (input == 'p' || input == 'P');
	return (0);
}

void shuffle(int *in_deck, int n) {
	srand((unsigned)time(NULL));
	if (n > 1) {
		int i, k, t;
		for (i = 0; i < (n - 1); i++) {
			k = i + rand() / (RAND_MAX / (n - i) + 1);
			t = in_deck[k];
			in_deck[k] = in_deck[i];
			in_deck[i] = t;
		}
	}
}

int check_hand(int hand_size, int *hand) {
	int unplayed_cards = 0;
	return (unplayed_cards);
}

void deal_hand(int *in_deck, int *hand1, int *hand2) {
	for (int i = 0; i < 52; i++) {
		if (i < 26)
			hand1[i] = in_deck[i];
		else
			hand2[i - 26] = in_deck[i];
	}
}

void print_card(int card) {
	if (card == 0)
		printf("2S");
	else if (card == 1)
		printf("3S");
	else if (card == 2)
		printf("4S");
	else if (card == 3)
		printf("5S");
	else if (card == 4)
		printf("6S");
	else if (card == 5)
		printf("7S");
	else if (card == 6)
		printf("8S");
	else if (card == 7)
		printf("9S");
	else if (card == 8)
		printf("10S");
	else if (card == 9)
		printf("JS");
	else if (card == 10)
		printf("QS");
	else if (card == 11)
		printf("KS");
	else if (card == 12)
		printf("AS");
	else if (card == 13)
		printf("2D");
	else if (card == 14)
		printf("3D");
	else if (card == 15)
		printf("4D");
	else if (card == 16)
		printf("5D");
	else if (card == 17)
		printf("6D");
	else if (card == 18)
		printf("7D");
	else if (card == 19)
		printf("8D");
	else if (card == 20)
		printf("9D");
	else if (card == 21)
		printf("10D");
	else if (card == 22)
		printf("JD");
	else if (card == 23)
		printf("QD");
	else if (card == 24)
		printf("KD");
	else if (card == 25)
		printf("AD");
	else if (card == 26)
		printf("2H");
	else if (card == 27)
		printf("3H");
	else if (card == 28)
		printf("4H");
	else if (card == 29)
		printf("5H");
	else if (card == 30)
		printf("6H");
	else if (card == 31)
		printf("7H");
	else if (card == 32)
		printf("8H");
	else if (card == 33)
		printf("9H");
	else if (card == 34)
		printf("10H");
	else if (card == 35)
		printf("JH");
	else if (card == 36)
		printf("QH");
	else if (card == 37)
		printf("KH");
	else if (card == 38)
		printf("AH");
	else if (card == 39)
		printf("2C");
	else if (card == 40)
		printf("3C");
	else if (card == 41)
		printf("4C");
	else if (card == 42)
		printf("5C");
	else if (card == 43)
		printf("6C");
	else if (card == 44)
		printf("7C");
	else if (card == 45)
		printf("8C");
	else if (card == 46)
		printf("9C");
	else if (card == 47)
		printf("10C");
	else if (card == 48)
		printf("JC");
	else if (card == 49)
		printf("QC");
	else if (card == 50)
		printf("KC");
	else if (card == 51)
		printf("AC");	
}