#ifndef bst_h
#define bst_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 256
#define MAX_LINE_LEN 256

struct node
{
    int data;
    char* question;
    char* guess;
    struct node* left;
    struct node* right;
};

void insert(struct node** root, int data, char* question, char* guess);

void printNode(struct node* root);

void createNewNode();

struct node* create_game_tree();

#endif