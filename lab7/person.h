#ifndef PERSON_H
#define PERSON_H

#define NAME_SIZE 60
#define CITY_SIZE 30
#define EDUCATION_SIZE 100
#define JOB_SIZE 70
#define INTERESTS_SIZE 100
#define FILE_NAME_SIZE 40

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct person* person;
    struct node* next;
    struct node* prev;
} node_t;

typedef struct list {
    struct node* head;
    struct node* tail;
    unsigned int size;
} list_t;

typedef struct person {
    char name[NAME_SIZE];
    list_t contacts;
    char city[CITY_SIZE];
    char education[EDUCATION_SIZE];
    char job[JOB_SIZE];
    char interests[INTERESTS_SIZE];
} person_t;

void add_contact(person_t* person1, person_t* person2);
void remove_contact(person_t* person1, person_t* person2);
list_t* find_by_interest(list_t* list, char interest[]);
list_t* find_by_location(list_t* list, char city[]);
list_t* find_by_education(list_t* list, char education[]);
list_t* find_by_job(list_t* list, char job[]);
person_t* find_person(list_t* list, char name[]);

void add_to_list(list_t* list, person_t* subject);
void remove_from_list(list_t* list, person_t* subject);
list_t* read_from_file(char file_name[FILE_NAME_SIZE]);
void print_list(list_t* list, FILE* file);
void print_person(person_t* person, FILE* file);
void destroy_list(list_t* list);

#endif