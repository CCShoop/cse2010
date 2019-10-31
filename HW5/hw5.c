/*
	Author:		 Cael Shoop
	Email:		 cshoop2018@my.fit.edu
	Course:		 cse2010
	Section:	 06
	Description: Homework Assignment 5
*/

//required libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct c_node { //node structure for calendar events with quad pointer setup
	char event_name[50];
	int time;
	struct c_node *right;
	struct c_node *left;
	struct c_node *up;
	struct c_node *down;
}c_node;

typedef struct calendars { //calendar structure to represent entire calendar with height of skip list and pointer to skip list
	int height;
	struct c_node *list;
}calendars;

calendars *calendar = NULL; //globally declaring calendar struct

extern int getRandHeight(); //generates fixed heights for testing purposes
int identify_command(char command[]); //takes a command read from file and returns corresponding integer for switch statement
void add_event(int time, char event[]); //adds an event to the calendar skip list
void add_level(int height); //adds another level to skip list
void cancel_event(int time); //removes an event from the calendar
void get_event(int time); //retrieves an event with given time unless it does not exist
void between_times(int time1, int time2); //given 2 times, it prints which functions are between them
void one_day(int time); //prints all events on a certain day
void rest_of_day(int time); //prints all events after that time on that day
void earlier_in_day(int time); //prints all events before that time on that day
void print_skip_list(); //prints entire skip list

int main(int argc, char* argv[]) {
	FILE *input = fopen(argv[1], "r"); //opens file from command prompt input to read from
	calendar = malloc(sizeof(calendars)); //initializes calendar struct
	calendar->height = 0;
	calendar->list = malloc(sizeof(c_node)); //initializes left side event struct
	calendar->list->time = -1; //sets bottom value
	calendar->list->left = NULL; //sets pointers
	calendar->list->up = NULL;
	calendar->list->down = NULL;
	calendar->list->right = malloc(sizeof(c_node)); //initializes right side event struct
	calendar->list->right->time = 123124; //sets top value
	calendar->list->right->left = calendar->list; //sets pointers
	calendar->list->right->right = NULL;
	calendar->list->right->down = NULL;
	calendar->list->right->up = NULL;
	char command[30], event[50]; //command and event to read from file
	int time, time2, date; //times to read from file
	do { //reads through file and executes commands as they are read
		fscanf(input, "%s", command);
		if (feof(input)) //ends loop when end of file is reached because it likes to duplicate for my machine
			break;
		switch (identify_command(command)) { //command switch statement
			case 0: //add event case
				fscanf(input, "%d %s", &time, event);
				add_event(time, event);
				break;
			case 1: //cancel event case
				fscanf(input, "%d", &time);
				cancel_event(time);
				break;
			case 2: //get event case
				fscanf(input, "%d", &time);
				get_event(time);
				break;
			case 3: //between two times case
				fscanf(input, "%d %d", &time, &time2);
				between_times(time, time2);
				break;
			case 4: //all events in a day case
				fscanf(input, "%d", &time);
				one_day(time);
				break;
			case 5: //all events after a time on its day
				fscanf(input, "%d", &time);
				rest_of_day(time);
				break;
			case 6: //all events before a time on its day
				fscanf(input, "%d", &time);
				earlier_in_day(time);
				break;
			case 7: //prints skip list
				print_skip_list();
				break;
			default: //default if command is not recognized
				printf("Error: Invalid Command: %s. Exiting Program.\n\n", command);
				return (1);
		}
	} while (!feof(input));
	fclose(input); //closes the file
  	return (0);
}

int identify_command(char command[]) { //returns an integer based on the string provided
	if (strcmp(command, "AddEvent") == 0)
		return (0);
	else if (strcmp(command, "CancelEvent") == 0)
		return (1);
	else if (strcmp(command, "GetEvent") == 0)
		return (2);
	else if (strcmp(command, "GetEventsBetweenTimes") == 0)
		return (3);
	else if (strcmp(command, "GetEventsForOneDay") == 0)
		return (4);
	else if (strcmp(command, "GetEventsForTheRestOfTheDay") == 0)
		return (5);
	else if (strcmp(command, "GetEventsFromEarlierInTheDay") == 0)
		return (6);
	else if (strcmp(command, "PrintSkipList") == 0)
		return (7);
}

void add_event(int time, char event[]) { //adds an event to the calendar
	if (time < 100000)
		printf("AddEvent 0%d %s", time, event); //printing a 0 in front to maintain time length
	else
		printf("AddEvent %d %s", time, event);
	c_node *temp = calendar->list;
	while (temp->down != NULL) //moves temp node to bottom left
		temp = temp->down;
	c_node *temp2 = temp;
	while (temp2->time < time) { //moves temp2 node to node after where new event will go
		temp2 = temp2->right;
		if (temp2->time == time) {
			printf(" ExistingEventError:%s\n", temp2->event_name); //if there is an event at the provided time
			return;
		}
	}
	int height = getRandHeight(); //sets height according to precreated values
	if (calendar->height <= height)
		add_level(height + 1); //adds a level if the calendar is not tall enough already
	printf("\n");
	if (height >= 0) { //always runs, but keeps code neater and easier to edit
		c_node *new = malloc(sizeof(c_node)); //new node
		new->up = NULL;
		temp2->left->right = new; //lots of pointers to insert new node
		new->left = temp2->left;
		new->right = temp2;
		temp2->left = new;
		new->down = NULL;
		new->time = time;
		strcpy(new->event_name, event);
		if (height >= 1) { //moves up in list, inserting nodes at every height applicable
			temp = temp->up;
			temp2 = temp;
			while (temp2->time < time)
				temp2 = temp2->right;
			c_node *new1 = malloc(sizeof(c_node));
			new1->up = NULL;
			new1->down = new;
			new->up = new1;
			temp2->left->right = new1;
			new1->left = temp2->left;
			new1->right = temp2;
			temp2->left = new1;
			new1->time = time;
			strcpy(new1->event_name, event);
			if (height >= 2) { //etc.
				temp = temp->up;
				temp2 = temp;
				while (temp2->time < time)
					temp2 = temp2->right;
				c_node *new2 = malloc(sizeof(c_node));
				new2->up = NULL;
				new2->down = new;
				new1->up = new2;
				temp2->left->right = new2;
				new2->left = temp2->left;
				new2->right = temp2;
				temp2->left = new2;
				new2->time = time;
				strcpy(new2->event_name, event);
				if (height >= 3) { //etc.
					temp = temp->up;
					temp2 = temp;
					while (temp2->time < time)
						temp2 = temp2->right;
					c_node *new3 = malloc(sizeof(c_node));
					new3->up = NULL;
					new3->down = new;
					new2->up = new3;
					temp2->left->right = new3;
					new3->left = temp2->left;
					new3->right = temp2;
					temp2->left = new3;
					new3->time = time;
					strcpy(new3->event_name, event);
					if (height >= 4) { //etc.
						temp = temp->up;
						temp2 = temp;
						while (temp2->time < time)
							temp2 = temp2->right;
						c_node *new4 = malloc(sizeof(c_node));
						new4->up = NULL;
						new4->down = new;
						new3->up = new4;
						temp2->left->right = new4;
						new4->left = temp2->left;
						new4->right = temp2;
						temp2->left = new4;
						new4->time = time;
						strcpy(new4->event_name, event);
						if (height >= 5) { //etc.
							temp = temp->up;
							temp2 = temp;
							while (temp2->time < time)
								temp2 = temp2->right;
							c_node *new5 = malloc(sizeof(c_node));
							new5->up = NULL;
							new5->down = new;
							new4->up = new5;
							temp2->left->right = new5;
							new5->left = temp2->left;
							new5->right = temp2;
							temp2->left = new5;
							new5->time = time;
							strcpy(new5->event_name, event);
						}
					}
				}
			}
		}
	}
}

void add_level(int height) { //adds levels as required
	for (int i = calendar->height; i < height; i++) { //loop in case it needs multiple levels added
		calendar->height = height;
		calendar->list->up = malloc(sizeof(c_node));
		calendar->list->up->time = -1;
		calendar->list->up->down = calendar->list;
		calendar->list = calendar->list->up;
		calendar->list->up = NULL;
		calendar->list->left = NULL;
		calendar->list->right = malloc(sizeof(c_node)); //pointers to create double nodes at top for days
		calendar->list->right->time = 123124;
		calendar->list->right->left = calendar->list;
		calendar->list->right->up = NULL;
		calendar->list->right->right = NULL;
		c_node *temp = calendar->list;
		temp = temp->down;
		while (temp->right != NULL)
			temp = temp->right;
		calendar->list->right->down = temp;
		temp->up = calendar->list->right;
	}
	if (height > calendar->height)
		calendar->height = height;
}

void cancel_event(int time) { //removes all associated nodes of an event with provided time
	if (time < 100000)
		printf("CancelEvent 0%d ", time);
	else
		printf("CancelEvent %d ", time);
	c_node *cancel = calendar->list;
	c_node *cancel2 = cancel;
	while (cancel2->down != NULL) //moves cancel2 down to bottom
		cancel2 = cancel2->down;
	cancel = cancel2;
	while (cancel->right != NULL && cancel->right->time <= time) //moves cancel to node to cancel
		cancel = cancel->right;
	if (cancel->time == time) { //if it finds the node
		printf("%s\n", cancel->event_name);
		if (cancel->up == NULL) { //it is only one node for the event
			cancel->left->right = cancel->right; //sets pointers
			cancel->right->left = cancel->left;
			free(cancel);
		}
		else { //it is more than one node for the event
			cancel2 = cancel;
			while (cancel != NULL) {
				cancel->left->right = cancel->right;
				cancel->right->left = cancel->left;
				if (cancel->up != NULL) { //moves up to free all nodes
					cancel2 = cancel->up;
					free(cancel);
					cancel = cancel2;
				}
				else {
					free(cancel);
					break;
				}
			}
		}
		if (calendar->list->down->time == -1 && calendar->list->down->right->time == 123124) { //removes calendar level if it is extra
			calendar->height--;
			calendar->list = calendar->list->down;
			calendar->list->up = NULL;
			calendar->list->right->up = NULL;
		}
	}
	else
		printf("NoEventError\n"); //if event is not found
}

void get_event(int time) { //prints event at certain time
	if (time < 100000)
		printf("GetEvent 0%d", time);
	else
		printf("GetEvent %d", time);
	c_node *event = calendar->list;
	while (event->time != time) { //locates node
		if (event->right->time <= time)
			event = event->right;
		else if (event->down != NULL && event->right->time > time && event->right->time != time)
			event = event->down;
		else
			break;
	}
	if (event->time == time)
		printf(" %s\n", event->event_name); //if event is found
	else
		printf(" none\n"); //if there is no event at that time
}

void between_times(int time1, int time2) { //finds and prints events between two provided times
	int counter = 0;
	if (time1 < 100000 && time2 < 100000)
		printf("GetEventsBetweenTimes 0%d 0%d", time1, time2); //if elses to print 0s as required
	else if (time1 >= 100000 && time2 < 100000)
		printf("GetEventsBetweenTimes %d 0%d", time1, time2);
	else if (time1 < 100000 && time2 >= 100000)
		printf("GetEventsBetweenTimes 0%d %d", time1, time2);
	else
		printf("GetEventsBetweenTimes %d %d", time1, time2);
	c_node *event = calendar->list;
	if (event->down != NULL) { //scans skip list
		while (event->down != NULL)
			event = event->down;
		while (event->time != 123124) {
			if (event->time >= time1 && event->time <= time2) {
				if (event->time < 100000)
					printf(" 0%d:%s", event->time, event->event_name); //prints if event matches
				else
					printf(" %d:%s", event->time, event->event_name);
				counter++;
			}
			if (event->right != NULL)
				event = event->right;
		}
		if (counter == 0)
			printf(" none"); //if there are no events between provided times
	}
	else {
		printf("\n\nError: Empty list. Exiting.\n"); //If the list is empty
		exit(1);
	}
	printf("\n"); //formatting
}

void one_day(int day) { //finds and prints all events on a certain day
	int counter = 0;
	c_node *day_events = calendar->list;
	printf("GetEventsForOneDay %d", day);
	while (day_events->down != NULL) //moves to bottom of list
		day_events = day_events->down;
	while (day_events->right != NULL && day_events->time != 123124) { //moves over to find event
		day_events = day_events->right;
		if ((day_events->time / 100) == day && day_events->time != 123124) { //if events exist
			counter++;
			if (day_events->time < 100000)
				printf(" 0%d:%s", day_events->time, day_events->event_name);
			else
				printf(" %d:%s", day_events->time, day_events->event_name);
		}
	}
	if (counter == 0)
		printf(" none"); //if no events are found
	printf("\n");
}

void rest_of_day(int time) {
	int counter = 0;
	c_node *rest_of_day = calendar->list;
	if (time < 100000)
		printf("GetEventsForTheRestOfTheDay 0%d", time);
	else
		printf("GetEventsForTheRestOfTheDay %d", time);
	while (rest_of_day->down != NULL)
		rest_of_day = rest_of_day->down;
	while (rest_of_day->right != NULL && rest_of_day->right->time < time) //locates event
		rest_of_day = rest_of_day->right;
	time /= 100;
	while (rest_of_day->right->time != 123124 && (rest_of_day->right->time / 100) == time) { //searches for events on given day after given time
		rest_of_day = rest_of_day->right;
		if (rest_of_day->time < 100000) {
			printf(" 0%d:%s", rest_of_day->time, rest_of_day->event_name);
			counter++;
		}
		else {
			printf(" %d:%s", rest_of_day->time, rest_of_day->event_name);
			counter++;
		}
	}
	if (counter == 0)
		printf(" none"); //if no events are found
	printf("\n");
}

void earlier_in_day(int time) { //prints all events on given day before given time
	int counter = 0;
	c_node *earlier = calendar->list;
	if (time < 100000)
		printf("GetEventsFromEarlierInTheDay 0%d", time);
	else
		printf("GetEventsFromEarlierInTheDay %d", time);
	while (earlier->down != NULL)
		earlier = earlier->down;
	while (earlier->right != NULL && earlier->right->time < time) { //finds events
		earlier = earlier->right;
		if ((earlier->time / 100) == (time / 100)) { //meets criteria
			counter++;
			if (earlier->time < 100000)
				printf(" 0%d:%s", earlier->time, earlier->event_name);
			else
				printf(" %d:%s", earlier->time, earlier->event_name);
		}
	}
	if (counter == 0)
		printf(" none"); //if no events are found
	printf("\n");
}

void print_skip_list() { //prints skip list level by level
	printf("PrintSkipList\n");
	c_node *print = calendar->list;
	c_node *print2 = print;
	for (int i = calendar->height; i >= 0; i--) { //one iteration is one level
		print = print2;
		if (print2->down != NULL)
			print2 = print2->down; //moving down from top level by level
		printf("(S%d)", i);
		if (print->time == -1 && print->right->time == 123124) //if level is empty
			printf(" empty");
		else {
			while (print->right != NULL && print->right->time != 123124) { //if events exist to be printed
				print = print->right;
				if (print->time < 100000)
					printf(" 0%d:%s", print->time, print->event_name);
				else
					printf(" %d:%s", print->time, print->event_name);
			}
		}
		printf("\n"); //formatting
	}
}
