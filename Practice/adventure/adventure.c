#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct players {
    char name[101];
    int health;
    int max_damage;
    int skill;
    char species[51];
    struct players *next;
    struct players *prev;
}players;

int recognize_players(char name[]);
void presets(players **list, int player_num);
void add_players(players **list, players **tail, char name[]);
int remove_players(players **list, players **tail, char name[]);
void events();

int main(void) {
    char name[101];
    int counter = 0, player_num, remove;
    players *head = NULL;
    players *tail = NULL;
    printf("Welcome to the adventure.\nPlease enter the names of the adventurers here. Enter \"end\" when everybody is entered.\n");
    do {
        printf("%d: ", counter + 1);
        fgets(name, 101, stdin);
        strtok(name, "\n");
        player_num = recognize_players(name);
        add_players(&head, &tail, name);
        presets(&tail, player_num);
        if (strcmp(name, "no") == 0 || strcmp(name, "No") == 0 || strcmp(name, "NO") == 0 || strcmp(name, "nO") == 0) {
            strcpy(name, "no");
            printf("No \"no,\" dummy.\n");
        }
        else if (strcmp(name, "end") == 0 || strcmp(name, "End") == 0 || strcmp(name, "ENd") == 0 || strcmp(name, "END") == 0 || strcmp(name, "eNd") == 0 || strcmp(name, "eND") == 0 || strcmp(name, "enD") == 0)
            strcpy(name, "end");
        else
            counter++;
    } while (strcmp(name, "end") != 0);
    printf("Would you like to remove any players? [name(s) or \"no\"]\n");
    do {
        fgets(name, 101, stdin);
        strtok(name, "\n");
        if (strcmp(name, "no") == 0 || strcmp(name, "No") == 0 || strcmp(name, "NO") == 0 || strcmp(name, "nO") == 0)
            strcpy(name, "no");
        else {
            remove = remove_players(&head, &tail, name);
            if (remove == 1) {
                counter--;
                printf("%s removed.\n", name);
            }
            else
                printf("\"%s\" not found. No players were removed.\n", name);            
        }
    } while (strcmp(name, "no") != 0);
    return (0);
}

int recognize_players(char name[]) {
    if (strcmp(name, "Cael") == 0)
        return (1);
    else if (strcmp(name, "Macayla") == 0)
        return (2);
    else if (strcmp(name, "Nick") == 0)
        return (3);
    else if (strcmp(name, "Brendan") == 0)
        return (4);
    else if (strcmp(name, "McKenna") == 0)
        return (5);
    else if (strcmp(name, "Maddie") == 0)
        return (6);
    else if (strcmp(name, "Josie") == 0)
        return (7);
    else if (strcmp(name, "Brian") == 0)
        return (8);
    else if (strcmp(name, "Mollie") == 0)
        return (9);
    else if (strcmp(name, "Lucy") == 0)
        return (10);
    else if (strcmp(name, "Koa") == 0)
        return (11);
    else
        return (0);    
}

void presets(players **tail, int player_num) {
    switch (player_num) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        default:
            break;
    }
}

void add_players(players **list, players **tail, char name[]) {
    players *new = malloc(sizeof(players));
    new->next = NULL;
    new->prev = NULL;
    strcpy(new->name, name);
    if (*list == NULL) {
        *list = new;
        *tail = new;
    }
    else {
        (*tail)->next = new;
        new->prev = *tail;
    }
}

int remove_players(players **list, players **tail, char name[]) {
    players *temp = *list;
    while (temp->next != NULL && strcmp(temp->name, name) != 0) {
        printf("incrementing\n");
        temp = temp->next;
    }
    if (strcmp(temp->name, name) == 0)
        return (1);
    return (0);
}

void events() {

}