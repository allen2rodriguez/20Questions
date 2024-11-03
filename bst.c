#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

/*========================= 
    Inserts new node 
=========================*/
void insert(struct node** root, int data, char* question, char* guess)
{
    /* create new node */
    struct node* temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->question = strdup(question); 
    temp->guess = strdup(guess);       
    temp->left = temp->right = NULL;

    /* if tree is empty */
    if (*root == NULL)
    {
        *root = temp;
        return;
    }

    //---- search for new node's parent
    struct node* current = *root;
    struct node* parent = *root;
    
    while( current != NULL )
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    
    //---- insert the node
    if (data < parent->data)
        parent->left = temp;
    else
        parent->right = temp;
}

/*==================================================================
    Traverses the tree depending on user input and print it out
==================================================================*/
void printNode(struct node* root)
{
    struct node* current = root;

    printf("Think of a living thing (non-fictional too) I'll try to guess it in 20 questions or less\n");

    while (current != NULL) 
    {
        // Print the current node (question)
        printf("%s\n", current->question);
        
        char input;
        printf("y/n: ");
        scanf(" %c", &input);

        if (input == 'y') {
            current = current->right; //Flip flopped from the original 
        } else if (input == 'n') {
            current = current->left;
        } else {
            printf("Invalid input. y/n: \n");
        }

        // Print out guess 
        if (current != NULL && current->left == NULL && current->right == NULL) 
        {
            printf("%s\n", current->guess);
            printf("y/n: ");
            scanf(" %c", &input);

            if (input == 'y') //---Correct Guess
                printf("I win!\n");

            if (input == 'n') { //---Incorrect guess
                printf("You win!\n");
                
                createNewNode(current);
            }

            break;
        }
    }
}

/*=================================================================
    update the file with a the new node if computer was wrong 
=================================================================*/
void createNewNode(struct node* parent)
{
    struct node* root;

    int newData1 = parent->data / 2 - parent->data;
    int newData2 = newData1 / 2 + newData1;

    char newAnswer[MAX_STR_LEN];
    char newQuestion[MAX_STR_LEN];

    printf("What was it? ");
    scanf(" %s", &newAnswer);

    printf("What would would have been a good quesiton to ask? ");
    scanf(" %s", &newQuestion);

    //Write to the file
    char filename[] = "nouns.txt";
    FILE* fp = fopen(filename, "a");

    fprintf(fp, "%d %s\n", newData1, newQuestion);
    fprintf(fp, "%d %s\n", newData2, newAnswer);

    fclose(fp);
}

/*===================================================
    Creates the instance of the tree to be used 
===================================================*/
struct node* create_game_tree()
{
    char filename[] = "nouns.txt";
    FILE* fp = fopen(filename, "r");

    struct node* root = NULL;

    char line[MAX_LINE_LEN];
    int data;
    char node[MAX_STR_LEN];

    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        if (sscanf(line, "%d %[^\n]", &data, node) == 2) 
        {
            if (strchr(node, '?') != NULL)  // Check if it's a question
                insert(&root, data, node, "");  // Insert the question node
            else 
                insert(&root, data, "", node);  // Insert the guess node
        }
    }

    fclose(fp);
    return root;  // Return the tree's root
}