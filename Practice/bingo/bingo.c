#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct used {
    int gen_num;
    int num;
    struct used *next;
}used;

void print_nums(used *nums, int counter);
void save(used **nums, int bingo);
int previous_nums(used *nums, int bingo);
void fill_board(int board[10][5]);
void print_board(int board[10][5]);
int win(int board[10][5]);

int main(void) {
    srand(time(NULL));
    int continu = 1, bingo = 0, select_a = 0, select_b = 0, board[10][5], counter = 0;
    char call_bingo;
    fill_board(board);
    used *nums = NULL;
    printf("\nWelcome to Bingo! Let's learn how to play.\n");
    printf("There are 5 rows and 5 columns. They are filled with numbers between 1 and 50.\nWhen entering a board space's location, enter the column first and then the row (\"x y\").\nEnter \"0 0\" if you have no spaces with the Bingo value.\n\n");
    do {
        if (continu >= 1) {
            do {
                bingo = rand() % 49 + 1;
            } while (previous_nums(nums, bingo) == 1);
        }
        if (counter > 0)
            printf("\nUsed Numbers: ");
        if (nums != NULL)
            print_nums(nums, counter);
        printf("\n");
        save(&nums, bingo);
        printf("Round %d/40\n", counter + 1);
        printf("\nChosen number: %d\n\n", bingo);
        print_board(board);
        printf("Enter location: ");
        scanf("%d %d", &select_b, &select_a);
        if (select_a == 0 && select_b == 0) {
            printf("You entered 0 0, so a new number will be selected.\n\n");
            continu = 3;
        }
        else {
            select_a--;
            select_b--;
            if (select_a == 2 && select_b == 2) {
                printf("That is the free space! It is already selected.\n\n");
                continu = 0;
            }
            else if (bingo == board[select_a][select_b]) {
                printf("%d %d selected.\n\n", select_a + 1, select_b + 1);
                board[select_a + 5][select_b] = 1;
                continu = 1;
            }
            else {
                printf("%d is not equal to %d!\n\n", board[select_a][select_b], bingo);
                continu = 0;
            }        
        }
        if (continu == 1) {
            printf("Would you like to call Bingo? (Y/N): ");
            scanf(" %c", &call_bingo);
            if (call_bingo == 'Y' || call_bingo == 'y') {
                printf("\"Bingo!\"\nChecking your board for bingo...\n\n");
                if (win(board) == 1) {
                    printf("You have Bingo! You win!\n\n");
                    continu = 2;
                    counter = 40;
                    break;
                }
                else {
                    printf("No Bingo found. Continuing game and subtracting 5 moves.\n\n");
                    counter += 5;
                    continu = 1;
               }            
            }
        }
        call_bingo = 'n';
        if (continu >= 1)
            counter++;
        else if (continu == 2)
            counter = 40;
    } while (counter < 40);
    free(nums);
    return (0);
}

void print_nums(used *nums, int counter) {
    used *temp = nums;
    int count = 0;
    while (temp != NULL) {
        if (counter > 1 && count > 0)
            printf(", ");
        printf("%d", temp->num);
        temp = temp->next;
        count++;
    }
    printf("\n");
}

void save(used **nums, int bingo) {
    used *new = malloc(sizeof(used)), *temp;
    new->num = bingo;
    new->next = NULL;
    if ((*nums == NULL)) {
        *nums = new;
    }
    else {
        temp = *nums;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
}

int previous_nums(used *nums, int bingo) {
    if (nums != NULL) {
        used *temp = nums;
        while (temp->next != NULL && temp->num != bingo)
            temp = temp->next;
        if (temp->num == bingo)
            return (1);
        else
            return (0);
    }
}

void fill_board(int board[10][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 && j == 2) {
                board[i][j] = 0;
                board[i + 5][j] = 1;
            }
            else {
                board[i][j] = rand() % 49 + 1;
                board[i + 5][j] = 0;
            }
        }
    }
}

void print_board(int board[10][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0 && j == 0)
                printf("--------------------------\n");
            printf("|");
            if (board[i][j] != 0) {
                if (board[i][j] < 10) {
                    if (board[i + 5][j] == 0)
                        printf(" ");
                    else
                        printf("-");                    
                }
                if (board[i + 5][j] == 0)
                    printf(" ");
                else
                    printf("-");
                printf("%d", board[i][j]);
                if (board[i + 5][j] == 0)
                    printf(" ");
                else
                    printf("-");
            }
            else
                printf("--F-");
        }
        printf("|\n");
    }
    printf("--------------------------\n\n");
}

int win(int board[10][5]) {
    for (int i = 0; i < 5; i++) {
        if (board[5][i] == 1 && board[6][i] == 1 && board[7][i] == 1 && board[8][i] == 1 && board[9][i] == 1)
            return (1);
    }
    for (int i = 5; i < 10; i++) {
        if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1 && board[i][3] == 1 && board[i][4] == 1)
            return (1);
    }
    if (board[5][0] == 1 && board[6][1] == 1 && board[7][2] == 1 && board[8][3] == 1 && board[9][4] == 1)
        return (1);
    else if (board[9][0] == 1 && board[8][1] == 1 && board[7][2] == 1 && board[6][3] == 1 && board[5][4] == 1)
        return (1);
    return (0);
}