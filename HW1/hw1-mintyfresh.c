/*
    Author: Cael Shoop
    Email: cshoop2018@my.fit.edu
    Course: CSE 2010
    Section: 09
    Description: Homework Assignment 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //libraries (spooky)

typedef struct alice { //struct just for alice
	int timestamp, read;
	char message[100];
    char sender[15];
	struct alice *next;
}alice;

typedef struct bob { //bob the builder built a struct
	int timestamp, read;
	char message[100];
    char sender[15];
	struct bob *next;
}bob;

typedef struct carol { //struct for carol
	int timestamp, read;
	char message[100];
    char sender[15];
	struct carol *next;
}carol;

int determine_command(char command[]); //determines command and returns integer to represent which command is being entered
void receive_message(FILE *input, alice **a, bob **b, carol **c); //adds received messages as nodes in each list
void open_app(alice *a, bob *b, carol *c); //opens the app by displaying names and unread message count
void display_conversation(FILE *input, alice *a, bob *b, carol *c); //displays the conversation when displayconversation is first word in line
void show_conversation(char name[], alice *a, bob *b, carol *c); //shows the conversation after a message is sent or deleted
void send_message(FILE *input, alice **a, bob **b, carol **c); //adds a sent message to the struct of the respective person
void delete_message(FILE *input, alice **a, bob **b, carol **c); //deletes message with same timestamp as the timestamp provided

int main(int argc, char* argv[]) {
	char command[25]; //input command
	alice *a = NULL;  //head node of alice's struct
	bob *b = NULL;    //head node of bob's struct
	carol *c = NULL;  //head node of carol's struct
    FILE *input = fopen(argv[1], "r"); //Reads file
	printf("\n");
	while (!feof(input)) { //loops to read first word of each line until end of file
		fscanf(input, "%s", command); //reads first line of word
        if (feof(input)) //breaks loop at end of file before it prints CloseApp twice
			break;
		switch (determine_command(command)) { //switch that compares first line of word with various commands to execute each function
			case 0: //displays notifications of received messages
				printf("NotifyUser ");
				receive_message(input, &a, &b, &c);
				break;
			case 1: //opens app by displaying unread message count
				printf("OpenApp\n");
				open_app(a, b, c);
				break;
			case 2: //displays the entire linked list as a conversation in messages
				printf("DisplayConversation ");
				display_conversation(input, a, b, c);
				break;
			case 3: //adds a node to respective person as a message sent by user
                printf("SendMessage ");
                send_message(input, &a, &b, &c);
				break;
			case 4: //deletes message with the same timestamp
                printf("DeleteMessage ");
                delete_message(input, &a, &b, &c);
				break;
			case 5: //prints CloseApp
                printf("CloseApp\n");
				break;
			default: //default for switch
				printf("\nError, exiting.\n\n");
				return (1);
		}
	}
    fclose(input); //closes file
    return (0);
}

int determine_command(char command[]) { //self explanatory
    if (strcmp(command, "ReceiveMessage") == 0)
        return (0);
    else if (strcmp(command, "OpenApp") == 0)
        return (1);
    else if (strcmp(command, "DisplayConversation") == 0)
        return (2);
    else if (strcmp(command, "SendMessage") == 0)
        return (3);
	else if (strcmp(command, "DeleteMessage") == 0)
		return (4);
	else if (strcmp(command, "CloseApp") == 0)
		return (5);
}

void receive_message(FILE *input, alice **a, bob **b, carol **c) {
	int timestamp;
	char name[10], message[100];
	fscanf(input, "%d %s", &timestamp, name);
	fgets(message, 100, input);
	if (message[0] == ' ') { //removes space at beginning of string
		for (int i = 0; i < 100; i++) {
			message[i] = message[i + 1];
		}
	}
	for (int i = 0; i < 100; i++) { //removes newline character and sets the rest of the string to nulls
		if (message[i] == '\n') {
			message[i] = '\0';
			for (int j = i; j < 100; j++) {
				message[j] = '\0';
			}
			break;
		}
	}
	if (strcmp(name, "Alice") == 0) { //adds a received message from alice to node
		printf("Alice\n");
		if (*a == NULL) { //in case of first message of conversation
			*a = malloc(sizeof(alice));
			(*a)->next = NULL;
			(*a)->timestamp = timestamp;
			strcpy((*a)->message, message);
            (*a)->read = 0;
            strcpy((*a)->sender, "Alice");
		}
		else { //in case it is a continuing conversation
			alice *new, *temp;
			new = malloc(sizeof(alice));
			new->timestamp = timestamp;
			strcpy(new->message, message);
            new->read = 0;
            strcpy(new->sender, "Alice");
			if (timestamp < (*a)->timestamp) {
				new->next = *a;
				*a = new;
			}
			else {
				temp = *a;
				while (temp->timestamp < timestamp && temp->next != NULL)
					temp = temp->next;
				new->next = temp->next;
				temp->next = new;
			}
		}
	}
	else if (strcmp(name, "Bob") == 0) { //the same but for bob
		printf("Bob\n");
		bob *new, *temp;
		new = malloc(sizeof(bob));
		new->timestamp = timestamp;
		strcpy(new->message, message);
        new->read = 0;
        strcpy(new->sender, "Bob");
		if (*b == NULL) {
			*b = new;
			(*b)->next = NULL;
		}
		else { //still the same but for bob
			if (timestamp < (*b)->timestamp) {
				new->next = *b;
				*b = new;
			}
			else {
				temp = *b;
				while (temp->timestamp < timestamp && temp->next != NULL)
					temp = temp->next;
				new->next = temp->next;
				temp->next = new;
			}
		}
	}
	else { //yeah, you get the point
		printf("Carol\n");
		if (*c == NULL) {
			*c = malloc(sizeof(carol));
			(*c)->next = NULL;
			(*c)->timestamp = timestamp;
            (*c)->read = 0;
			strcpy((*c)->message, message);
            strcpy((*c)->sender, "Carol");
		}
		else { //yes this is code
			carol *new, *temp;
			new = malloc(sizeof(carol));
			new->timestamp = timestamp;
			strcpy(new->message, message);
            new->read = 0;
            strcpy(new->sender, "Carol");
			if (timestamp < (*c)->timestamp) {
				new->next = *c;
				*c = new;
			}
			else {
				temp = *c;
				while (temp->timestamp < timestamp && temp->next != NULL)
					temp = temp->next;
				new->next = temp->next;
				temp->next = new;
			}
		}
	}
}

void open_app(alice *a, bob *b, carol *c) {
	int acounter = 0, bcounter = 0, ccounter = 0;
	alice *atemp = a;
	while (atemp != NULL) { //counts unread messages from alice
        if (atemp->read == 0)
   			acounter++;
		atemp = atemp->next;        
	}
	printf("Alice %d\n", acounter);
	bob *btemp = b;
	while (btemp != NULL) { //counts unread messages from bob
        if (btemp->read == 0)
   			bcounter++;
		btemp = btemp->next;                
	}
	printf("Bob %d\n", bcounter);
	carol *ctemp = c;
	while (ctemp != NULL) { //counts unread messages from carol
        if (ctemp->read == 0)
   			ccounter++;
		ctemp = ctemp->next;                
	}
	printf("Carol %d\n", ccounter);
}

void display_conversation(FILE *input, alice *a, bob *b, carol *c) {
	char name[10];
	fscanf(input, "%s", name);
	if (strcmp(name, "Alice") == 0) { //displays conversation with alice
		printf("Alice\n");
		alice *temp = a;
		while (temp != NULL) {
			printf("%d %s %s\n", temp->timestamp, temp->sender, temp->message);
            temp->read = 1;
			temp = temp->next;
		}
	}
	else if (strcmp(name, "Bob") == 0) { //displays conversation with bob
		printf("Bob\n");
		bob *temp = b;
		while (temp != NULL) {
			printf("%d %s %s\n", temp->timestamp, temp->sender, temp->message);
            temp->read = 1;
			temp = temp->next;
		}
	}
	else { //displays conversation with carol
		printf("Carol\n");
		carol *temp = c;
		while (temp != NULL) {
			printf("%d %s %s\n", temp->timestamp, temp->sender, temp->message);
            temp->read = 1;
			temp = temp->next;
		}
	}
}

void show_conversation(char name[], alice *a, bob *b, carol *c) {
    if (strcmp(name, "Alice") == 0) { //shows conversation with alice after sending or deleting a message
        alice *show = a;
        while (show != NULL) {
            printf("%d %s %s\n", show->timestamp, show->sender, show->message);
            show = show->next;
        }
    }
    else if (strcmp(name,"Bob") == 0) { //shows conversation with bob after sending or deleting a message
        bob *show = b;
        while (show != NULL) {
            printf("%d %s %s\n", show->timestamp, show->sender, show->message);
            show = show->next;
        }
    }
    else if (strcmp(name, "Carol") == 0) { //shows conversation with carol after sending or deleting a message
        carol *show = c;
        while (show != NULL) {
            printf("%d %s %s\n", show->timestamp, show->sender, show->message);
            show = show->next;
        }
    }
}

void send_message(FILE *input, alice **a, bob **b, carol **c) {
    int timestamp;
    char name[10], sent_message[100];
    fscanf(input, "%d %s", &timestamp, name);
    fgets(sent_message, 100, input);
    if (sent_message[0] == ' ') { //removes space from beginning of string
		for (int i = 0; i < 100; i++) {
			sent_message[i] = sent_message[i + 1];
		}
	}
	for (int i = 0; i < 100; i++) { //removes newline and sets all following characters to null
		if (sent_message[i] == '\n') {
			sent_message[i] = '\0';
			for (int j = i; j < 100; j++) {
				sent_message[j] = '\0';
			}
			break;
		}
	}
    printf("%d %s %s\n", timestamp, name, sent_message);
    if (strcmp(name, "Alice") == 0) { //adds sent message to alice's linked list
        alice *new = malloc(sizeof(alice));
        new->next = NULL;
        new->timestamp = timestamp;
        new->read = 1;
        strcpy(new->message, sent_message);
        strcpy(new->sender, "Me");
        if ((*a) == NULL) { //if it is first message
            (*a) = new;
        }
        else { //as a reply
            alice *temp = (*a);
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new;
        }
        show_conversation("Alice", *a, *b, *c); //calls show_conversation to show updated conversation
    }
    else if (strcmp(name, "Bob") == 0) { //adds sent message to bob's linked list
        bob *new = malloc(sizeof(bob));
        new->next = NULL;
        new->timestamp = timestamp;
        new->read = 1;
        strcpy(new->message, sent_message);
        strcpy(new->sender, "Me");
        if ((*b) == NULL) { //if it is the first message
            (*b) = new;
        }
        else { //if it is a reply
            bob *temp = (*b);
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new;
        }
        show_conversation("Bob", *a, *b, *c); //calls show_conversation to show updated conversation
    }
    else if (strcmp(name, "Carol") == 0) { //adds sent message to carol's linked list
        carol *new = malloc(sizeof(carol));
        new->next = NULL;
        new->timestamp = timestamp;
        new->read = 1;
        strcpy(new->message, sent_message);
        strcpy(new->sender, "Me");
        if ((*c) == NULL) { //if it is first message
            (*c) = new;
        }
        else { //if it is a reply
            carol *temp = (*c);
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new;
        }
        show_conversation("Carol", *a, *b, *c); //calls show_conversation to show updated conversation
    }
}

void delete_message(FILE *input, alice **a, bob **b, carol **c) {
    char name[10];
    int timestamp;
    fscanf(input, "%d %s", &timestamp, name);
    printf("%d %s\n", timestamp, name);
    if (strcmp(name, "Alice") == 0) { //deletes message with identical timestamp from alice's linked list
        alice *delete = (*a);
        while (delete->next->timestamp != timestamp && delete->next != NULL) {
            delete = delete->next;
        }
        alice *temp;
        if (delete->next != NULL) {
            temp = delete->next;
            delete->next = temp->next;
            free(temp);
        }
        else
            printf("No message with that timestamp exists.\n");
        show_conversation("Alice", *a, *b, *c);
    }
    else if (strcmp(name, "Bob") == 0) { //deletes message with identical timestamp from bob's linked list
        bob *delete = (*b);
        while (delete->next->timestamp != timestamp && delete->next != NULL) {
            delete = delete->next;
        }
        bob *temp;
        if (delete->next != NULL) {
            temp = delete->next;
            delete->next = temp->next;
            free(temp);
        }
        else
            printf("No message with that timestamp exists.\n");
        show_conversation("Bob", *a, *b, *c);
    }
    else if (strcmp(name, "Carol") == 0) { //deletes message with identical timestamp from carol's linked list
        carol *delete = (*c);
        while (delete->next->timestamp != timestamp && delete->next != NULL) {
            delete = delete->next;
        }
        carol *temp;
        if (delete->next != NULL) {
            temp = delete->next;
            delete->next = temp->next;
            free(temp);
        }
        else
            printf("No message with that timestamp exists.\n");
        show_conversation("Carol", *a, *b, *c);
    }
}