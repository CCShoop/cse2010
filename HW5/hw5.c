/*
	Author:		 Cael Shoop
	Email:		 cshoop2018@my.fit.edu
	Course:		 cse2010
	Section:	 06
	Description: Homework Assignment 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct c_node {
	char event_name[50];
	int time;
	struct c_node *right;
	struct c_node *left;
	struct c_node *up;
	struct c_node *down;
}c_node;

typedef struct calendars {
	int height;
	struct c_node *list;
}calendars;

calendars *calendar = NULL;

extern int getRandHeight();
int identify_command(char command[]);
void add_event(int time, char event[]);
void add_level(int height);
void cancel_event(int time);
void get_event(int time);
void between_times(int time1, int time2);
void one_day(int time);
void rest_of_day(int time);
void earlier_in_day(int time);
void print_skip_list();

int main(int argc, char* argv[]) {
	FILE *input = fopen(argv[1], "r");
	calendar = malloc(sizeof(calendars));
	calendar->height = 0;
	calendar->list = malloc(sizeof(c_node));
	calendar->list->time = -1;
	calendar->list->left = NULL;
	calendar->list->up = NULL;
	calendar->list->down = NULL;
	calendar->list->right = malloc(sizeof(c_node));
	calendar->list->right->time = 123124;
	calendar->list->right->left = calendar->list;
	calendar->list->right->right = NULL;
	calendar->list->right->down = NULL;
	calendar->list->right->up = NULL;
	char command[30], event[50];
	int time, time2, date;
	do {
		fscanf(input, "%s", command);
		if (feof(input))
			break;
		switch (identify_command(command)) {
			case 0:
				fscanf(input, "%d %s", &time, event);
				add_event(time, event);
				break;
			case 1:
				fscanf(input, "%d", &time);
				cancel_event(time);
				break;
			case 2:
				fscanf(input, "%d", &time);
				get_event(time);
				break;
			case 3:
				fscanf(input, "%d %d", &time, &time2);
				between_times(time, time2);
				break;
			case 4:
				fscanf(input, "%d", &time);
				one_day(time);
				break;
			case 5:
				fscanf(input, "%d", &time);
				rest_of_day(time);
				break;
			case 6:
				fscanf(input, "%d", &time);
				earlier_in_day(time);
				break;
			case 7:
				print_skip_list();
				break;
			default:
				printf("Error: Invalid Command: %s. Exiting Program.\n\n", command);
				return (1);
		}
	} while (!feof(input));
	fclose(input);
  	return (0);
}

int identify_command(char command[]) {
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

void add_event(int time, char event[]) {
	if (time < 100000)
		printf("AddEvent 0%d %s", time, event);
	else
		printf("AddEvent %d %s", time, event);
	int height = getRandHeight();
	if (calendar->height <= height)
		add_level(height);
	c_node *temp = calendar->list;
	while (temp->down != NULL)
		temp = temp->down;
	c_node *temp2 = temp;
	while (temp2->time < time) {
		temp2 = temp2->right;
		if (temp2->time == time) {
			printf(" ExistingEventError:%s\n", temp2->event_name);
			return;
		}
	}
	printf("\n");
	if (height >= 0) {
		c_node *new = malloc(sizeof(c_node));
		new->up = NULL;
		temp2->left->right = new;
		new->left = temp2->left;
		new->right = temp2;
		temp2->left = new;
		new->down = NULL;
		new->time = time;
		strcpy(new->event_name, event);
		if (height >= 1) {
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
			if (height >= 2) {
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
				if (height >= 3) {
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
					if (height >= 4) {
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
						if (height >= 5) {
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

void add_level(int height) {
	calendar->height = height;
	calendar->list->up = malloc(sizeof(c_node));
	calendar->list->up->time = -1;
	calendar->list->up->down = calendar->list;
	calendar->list = calendar->list->up;
	calendar->list->up = NULL;
	calendar->list->left = NULL;
	calendar->list->right = malloc(sizeof(c_node));
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

void cancel_event(int time) {
	if (time < 100000)
		printf("CancelEvent 0%d ", time);
	else
		printf("CancelEvent %d ", time);
	c_node *cancel = calendar->list;
	c_node *cancel2 = cancel;
	while (cancel2->down != NULL)
		cancel2 = cancel2->down;
	cancel = cancel2;
	while (cancel->right != NULL && cancel->right->time <= time)
		cancel = cancel->right;
	if (cancel->time == time) {
		printf("%s\n", cancel->event_name);
		if (cancel->up == NULL) {
			cancel->left->right = cancel->right;
			cancel->right->left = cancel->left;
			free(cancel);
		}
		else {
			cancel2 = cancel;
			while (cancel != NULL) {
				cancel->left->right = cancel->right;
				cancel->right->left = cancel->left;
				if (cancel->up != NULL) {
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
		printf("--before remove level\n");
		while (calendar->list->down->right->time == 123124) {
			printf("--removing level\n");
			cancel2 = calendar->list->right;
			cancel = calendar->list;
			calendar->list = calendar->list->down;

printf("--cancel: %d. cancel2: %d\n", cancel->time, cancel2->time);
printf("--calendar->list->down->right->time: %d\n", calendar->list->down->right->time);

			free(cancel);
			free(cancel2);
			calendar->list->up = NULL;
			calendar->list->right->up = NULL;
		}
		printf("--after remove level\n");
	}
	else
		printf("NoEventError\n");
}

void get_event(int time) {
	if (time < 100000)
		printf("GetEvent 0%d", time);
	else
		printf("GetEvent %d", time);
	c_node *event = calendar->list;
	while (event->time != time) {
		if (event->right->time <= time)
			event = event->right;
		else if (event->down != NULL && event->right->time > time && event->right->time != time)
			event = event->down;
		else
			break;

	}
	if (event->time == time)
		printf(" %s\n", event->event_name);
	else
		printf(" none\n");
}

void between_times(int time1, int time2) {
	int counter = 0;
	if (time1 < 100000 && time2 < 100000)
		printf("GetEventsBetweenTimes 0%d 0%d", time1, time2);
	else if (time1 >= 100000 && time2 < 100000)
		printf("GetEventsBetweenTimes %d 0%d", time1, time2);
	else if (time1 < 100000 && time2 >= 100000)
		printf("GetEventsBetweenTimes 0%d %d", time1, time2);
	else
		printf("GetEventsBetweenTimes %d %d", time1, time2);
	c_node *event = calendar->list;
	if (event->down != NULL) {
		while (event->down != NULL)
			event = event->down;
		while (event->time != 123124) {
			if (event->time > time1 && event->time < time2) {
				printf(" %d:%s", event->time, event->event_name);
				counter++;
			}
			if (event->right != NULL)
				event = event->right;
		}
		if (counter == 0)
			printf(" none");
	}
	else {
		printf("\n\nError: Empty list. Exiting.\n");
		exit(1);
	}
	printf("\n");
}

void one_day(int day) {
	printf("GetEventsForOneDay ");

printf("\n"); //temp formatting

	day *= 100;

}

void rest_of_day(int time) {
	printf("GetEventsForTheRestOfTheDay ");

printf("\n"); //temp formatting

}

void earlier_in_day(int time) {
	printf("GetEventsFromEarlierInTheDay ");

printf("\n"); //temp formatting

}

void print_skip_list() {
	printf("PrintSkipList\n");
	c_node *print = calendar->list;
	c_node *print2 = print;
	for (int i = calendar->height + 1; i >= 0; i--) {
		print = print2;
		if (print2->down != NULL)
			print2 = print2->down;
		printf("(S%d)", i);
		if (print->time == -1 && print->right->time == 123124)
			printf(" empty");
		else {
			while (print->right != NULL && print->right->time != 123124) {
				print = print->right;
				if (print->time < 100000)
					printf(" 0%d:%s", print->time, print->event_name);
				else
					printf(" %d:%s", print->time, print->event_name);
			}
		}
		printf("\n");
	}
}
