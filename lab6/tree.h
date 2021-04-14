#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    struct item* left;
    struct item* right;
    int data;
} node;

void insert(node* root, int data);
void ascending_order(node* root, FILE* file);
void descending_order(node* root, FILE* file);
void delete_tree(node* root);
void get_result(char input_f[11], char output_f[11]);

#endif
