#include "tree.h"

void insert(node* root, int data) {
    if (root == NULL) {
        root = (node*)malloc(sizeof(node));
        root->data = data;
        root->left = root->right = NULL;
        return;
    }
    node* current = root;
    while (1) {
        if (data > current->data) {
            if (current->right == NULL) {
                current->right = (node*)malloc(sizeof(node));
                current->right->data = data;
                current->right->right = current->right->left = NULL;
                return;
            }
            current = current->right;
        }
        else if (data < current->data) {
            if (current->left == NULL) {
                current->left = (node*)malloc(sizeof(node));
                current->left->data = data;
                current->left->right = current->left->left = NULL;
                return;
            }
            current = current->left;
        }
        else {
            return;
        }
    }
}

void ascending_order(node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        ascending_order(root->left, file);
    }
    if (fprintf(file, "%d ", root->data) == 0) {
        printf("Cannot write into file\n");
        exit(-1);
    }
    if (root->right != NULL) {
        ascending_order(root->right, file);
    }
}

void descending_order(node* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    if (root->right != NULL) {
        descending_order(root->right, file);
    }
    if (fprintf(file, "%d ", root->data) == 0) {
        printf("Cannot write into file\n");
        exit(-1);
    }
    if (root->left != NULL) {
        descending_order(root->left, file);
    }
}

void delete_tree(node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        delete_tree(root->left);
    }
    if (root->right != NULL) {
        delete_tree(root->right);
    }
    free(root);
}

void get_result(char input_file[11], char output_file[11]) {
    FILE* fin = fopen(input_file, "r");
    if (fin == NULL) {
        printf("Cannot open the file\n");
        exit(-1);
    }
    int num;
    while (fscanf(fin, "%d", &num) != 1) {
        char ch;
        do {
            fscanf(fin, "%c", &ch);
        } while (ch != '\n');
        printf("Incorrect input\n");
    }
    node* root = (node*)malloc(sizeof(node));
    root->data = num;
    root->left = root->right = NULL;
    char ch;
    fscanf(fin, "%c", &ch);
    if (ch != '\n') {
        while (fscanf(fin, "%d", &num) == 1) {
            insert(root, num);
            fscanf(fin, "%c", &ch);
            if (ch == '\n') {
                break;
            }
        }
    }
    fclose(fin);
    FILE* fout = fopen(output_file, "w");
    if (fout == NULL) {
        printf("Cannot open the file\n");
        exit(-1);
    }
    ascending_order(root, fout);
    fprintf(fout, "\n");
    descending_order(root, fout);
    fclose(fout);
    delete_tree(root);
}
