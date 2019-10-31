/*
Author:      Cael Shoop
Email:       cshoop2018@my.fit.edu
Course:      cse2010
Section:     09
Description: Homework Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hw2_crypto.h"
/*
Using encrypt from hw2_crypto.c:
char encrypted_string[41];
strcpy(encrypted_string, encrypt(plain_string));
*/

typedef struct encrypted {
    char encrypted_string[41];
    struct encrypted *next;
}encrypted;

int record_encrypted(FILE *input, encrypted **strings, int num_strings);       //reads encrypted strings from file using file, strings node, and number of strings to return number of strings
int delete_last(encrypted **strings, int num_strings);                         //deletes last encrypted string if it is a copy of the one before it using strings node and number of strings to return number of strings
void decrypt(encrypted *node, char encrypted_password[], char password[], int location, int length, int max_length);                        //recursive brute force decryption of a string using password 

int main(int argc, char* argv[]) {
    int length = 0, num_strings = 0, max_length = 0;   //length of passwords and number of encrypted passwords
    FILE *input = fopen(argv[1], "r"); //opening file to read input info
    fscanf(input, "%d", &length);      //scans password length integer to length
    max_length = length;
    encrypted *strings = NULL;         //creates encrypted node called strings
    while (!feof(input)) {
        num_strings = record_encrypted(input, &strings, num_strings); //reads all encrypted passwords and increments num_strings if it adds one
    }
    num_strings = delete_last(&strings, num_strings); //deletes last node if it is equivalent to the one before it, updating number of strings
    char encrypted_password[41];               //creates array of decrypted passwords
    encrypted *temp = strings;
    for (int i = 0; i < num_strings; i++) {
        char password[i + 1];
        password[i + 1] = '\0';
        decrypt(temp, encrypted_password, password, 0, length, max_length); //runs decryption for all nodes and therefore all encrypted strings
        temp = temp->next;
    }
    return(0);
}

int record_encrypted(FILE *input, encrypted **strings, int num_strings) {
    encrypted *new = malloc(sizeof(encrypted)); //creates a new node
    char string[41];                            //creates a string to read string into
    fscanf(input, "%s", string);                //reads string into string
    strtok(string, "\n");                       //removes newline character from string
    strcpy(new->encrypted_string, string);      //copies string into node's encrypted string data
    new->next = NULL;                           //sets next node to null
    if (*strings == NULL)                       //sets new as the head if there are no present nodes
        *strings = new;
    else {                                      //creates temp node to navigate to end of linked list, where new node is appended
        encrypted *temp = *strings;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
    num_strings++;                              //increments and returns number of strings
    return (num_strings);
}

int delete_last(encrypted **strings, int num_strings) {
    encrypted *remove = *strings;                    //creates node to navigate to near end of linked list
    while (remove->next->next != NULL)
        remove = remove->next;
    if (strcmp(remove->encrypted_string, remove->next->encrypted_string) == 0) { //compares last two node's strings. if they are equivalent, it deletes the last node.
        encrypted *temp = remove->next;
        free(temp);
        remove->next = NULL;
        num_strings--;
    }
    return (num_strings); //returns updated number of strings
}

void decrypt(encrypted *node, char encrypted_password[], char password[], int location, int length, int max_length) {
    if (strcmp(encrypted_password, node->encrypted_string) == 0) {
        printf("%s\n", password);
        return;
    }
    else {
        for (char letter = 'a'; letter <= 'z'; letter++) {
            if (location < max_length && strcmp(encrypted_password, node->encrypted_string) != 0) {
                password[location] = letter;
                password[location + 1] = '\0';
                strcpy(encrypted_password, encrypt(password));
                decrypt(node, encrypted_password, password, location + 1, length - 1, max_length);
            }
            else
                return;                   
        }
    }

}