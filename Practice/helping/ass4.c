#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

void print_board(int card_1_row, int card_1_col, int card_2_row, int card_2_col, int matches[4][4], char in_board[5][5]);
void fill_board(char in_board[5][5]);

int main(void) {
    char choice, in_board[5][5];
    int card_1_row = -1, card_1_col, card_2_row , card_2_col, points = 0, matches[4][4];
    srand(time(NULL));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            in_board[i][j] = '$';
            matches[i][j] = 0;
        }
    }

    printf("Welcome to Memory! Ready Player One...\n");
    fill_board(in_board);
do {
        if (card_1_row == -1) {
            printf("Here's the board: \n");
            print_board(-1, -1, -1, -1, matches, in_board);
            printf("Choose an option:\n(F) Find a match\n(Q) Quit\nChoice: ");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }
        else {
            printf("Here's the board: \n");
            print_board(card_1_row, card_1_col, card_2_row, card_2_col, matches, in_board);
            printf("Choose an option:\n(F) Find a match\n(Q) Quit\nChoice: ");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }
        if (choice == 'F') {
            printf("Pick first card(row, column): ");
            scanf("%d,%d", &card_1_row, &card_1_col);
            printf("Pick second card(row, column): ");
            scanf("%d,%d", &card_2_row, &card_2_col);
            if (card_1_row == card_2_row && card_1_col == card_2_col) {
                printf("\nPlease enter two different cards.\n\n");
                printf("Pick first card(row, column): ");
                scanf("%d,%d", &card_1_row, &card_1_col);
                printf("Pick second card(row, column): ");
                scanf("%d,%d", &card_2_row, &card_2_col);
            }
			else if (matches[card_1_row][card_1_col] == 1 || matches[card_2_row][card_2_col] == 1) {
                printf("\nThere is already a match with one of these cards. Please try again.\n\n");
                printf("Pick first card(row, column): ");
                scanf("%d,%d", &card_1_row, &card_1_col);
                printf("Pick second card(row, column): ");
                scanf("%d,%d", &card_2_row, &card_2_col);
            }
            else if (card_1_row > 3 || card_1_col > 3 || card_2_row > 3 || card_2_col > 3 || card_1_row < 0 || card_1_col < 0 || card_2_row < 0 || card_2_col < 0) {
                printf("\nInvalid Entry. Please try again...\n\n");
                printf("Pick first card(row, column): ");
                scanf("%d,%d", &card_1_row, &card_1_col);
                printf("Pick second card(row, column): ");
                scanf("%d,%d", &card_2_row, &card_2_col);
            }
            if (in_board[card_1_row][card_1_col] == in_board[card_2_row][card_2_col]) {
                matches[card_1_row][card_1_col] = 1;
                matches[card_2_row][card_2_col] = 1;
                printf("\nCards match! You get a point!\n");
                points++;
                printf("Your current points: %d\n\n", points);
            }
            else {
                printf("\nCards do not match! Try again!\n");
            }
        }
		else if (choice == 'Q') {
            printf("Your total points: %d. Goodbye!\n", points);
            break;
        }
        else {
            printf("\nInvalid entry. Please try again.\n");
        }
    } while (choice != 'Q' && points < 8);
    if (points == 8) {
        printf("You win!\n");
    }
    return 0;
}

void print_board(int card_1_row, int card_1_col, int card_2_row, int card_2_col, int matches[4][4], char in_board[5][5]) {
    printf("\n    0   1   2   3\n");
    for (int i = 0; i < 4; i++) {
        printf("%d |", i);
        for (int j = 0; j < 4; j++) {
            if (matches[i][j] == 1 || ((i == card_1_row && j == card_1_col) || (i == card_2_row && j == card_2_col))) {
                printf(" %c", in_board[i][j]);
            }
            else {
                printf(" $");
            }
            if (j < 3) {
                printf(" |");
            }
        }
        printf("\n-----------------\n");
    }
}

void fill_board(char in_board[5][5]) {
    char letter, used_letters[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int check = 0, random, counter = 0, unused_letters[8] = {2, 2, 2, 2, 2, 2, 2, 2};
    do {
        letter = rand() % 26 + 65;
        for (int i = 0; i < counter; i++) {
            if (used_letters[i] == letter) {
                check = -1;
            }
        }
        if (check == 0) {
            used_letters[counter] = letter;
            counter++;
        }
        else if (check == -1) {
            check = 0;
        }
    } while (counter < 8);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            random = rand() % 8;
            if (unused_letters[random] > 0) {
                in_board[i][j] = used_letters[random];
                unused_letters[random]--;
            }
            else if (in_board[i][j] == '$') {
                j--;
            }
        }
    }
}