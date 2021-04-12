#ifndef NUMBER_H
#define NUMBER_H
#endif
#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
    int digit;
    struct elem* prev;
    struct elem* next;
} node;

typedef struct list {
    node* head;
    node* tail;
    unsigned int size;
} number;

number* create_number(const char* value, int size);
char* to_string(number* num);
void multiply(number* num, const int multiplier);
void delete_number(number* num);
void add_front_node(number* num, int new_digit);
void power(int base, unsigned int power, number* num);
