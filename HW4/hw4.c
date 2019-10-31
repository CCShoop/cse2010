/*
Author:	   	 Cael Shoop
Email:	   	 cshoop2018@my.fit.edu
Course:	   	 cse2010
Section:	 06
Description: Homework Assignment 4
*/

//please compile with -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct patient {
	char name[15];
	int esi;
}patient[200];

typedef struct doctor {
	char name[15];
	int time;
	struct doctor *next;
	patient *treating;
}doctor;

patient patients[200];
doctor *doctors = NULL;

int patient_counter = 0;

//Description of the function, parameter, and return value (if any)
int code_file(char instruction[]);
void insert(int timestamp, char name[], int esi);
void treatment(int timestamp, char name[]);
void remove_min();
void get_min();
int is_full();
int is_empty();

int main(int argc, char* argv[]) {
	//description of declared variables, with meaningful names
	char prev_name[15], instruction[15], name[15];
	int timestamp, esi;
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		printf("Error with file.\n");
		return (1);
	}
	while (!feof(input)) {
		fscanf(input, "%s", instruction);
		switch (code_file(instruction)) {
			case 0:
				fscanf(input, "%d %s", &timestamp, name);
				strtok(name, "\n");
				if (strcmp(name, prev_name) == 0)
					break;
				strcpy(prev_name, name);
				if (is_full() != 1);
					insert(timestamp, name, 0);
				if (timestamp < 1000)
					printf("doctorArrives  0%d %s\n", timestamp, name);
				else
					printf("doctorArrives  %d %s\n", timestamp, name);
				break;
			case 1:
				fscanf(input, "%d %s %d", &timestamp, name, &esi);
				if (strcmp(name, prev_name) == 0)
					break;
				strcpy(prev_name, name);
				insert(timestamp, name, esi);
				doctor *temp = doctors;
				while (temp != doctors && temp != NULL) {
					if (temp->time < timestamp)
						temp->treating = NULL;
					temp = temp->next;
				}
				if (timestamp < 1000)
					printf("patientArrives 0%d %s %d\n", timestamp, name, esi);
				else
					printf("patientArrives %d %s %d\n", timestamp, name, esi);
					printf("doctorStartsTreatingPatient %d %s", timestamp, name);
					treatment(timestamp, name);
				break;
			default:
				printf("Error: Invalid Input. Exiting.\n");
				return (1);
		}
	}

	//description of each "block" (about 5 lines of instructions)
	fclose(input);
	return (0);
}

int code_file(char instruction[]) {
	if (strcmp(instruction, "doctorArrives") == 0)
		return (0);
	else
		return (1);
}

void insert(int timestamp, char name[], int esi) {
	if (esi == 0) { //doctorArrives
		doctor *new = malloc(sizeof(doctor));
		new->time = timestamp;
		strcpy(new->name, name);
		new->next = NULL;
		new->treating = NULL;
		if (doctors == NULL)
			doctors = new;
		else {
			doctor *temp = doctors;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
	}
	else { //patientArrives
		patients[patient_counter]->esi = esi;
		strcpy(patients[patient_counter]->name, name);
		patient_counter++;
	}
}

void treatment(int timestamp, char name[]) {
	int i;
	for (i = 0; i < 200; i++) {
		if (strcmp(patients[i]->name, name) == 0)
			break;
	}
	if (doctors->treating != NULL) {
		doctor *treater = doctors;
		
		printf(" %s\n", treater->name);
		treater->treating = patients[i];
		treater->time = timestamp + pow(2, (6-patients[i]->esi));
	}
	else {
		printf(" %s\n", doctors->name);
		doctors->treating = patients[i];
		doctors->time = timestamp + pow(2, (6-patients[i]->esi));
	}
}

void remove_min() {

}

void get_min() {

}

int is_full() {
	int counter = 0;
	if (doctors != NULL) {
		doctor *temp = doctors;
		while (temp->next != NULL) {
			if (counter > 49) {
				break;
			}
			temp = temp->next;
			counter++;
		}
		free(temp);
		if (counter <= 49)
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

int is_empty() {
	return (0);
	return (1);
}
