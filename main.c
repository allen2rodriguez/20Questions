#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

int main()
{
    struct node* game_tree = create_game_tree();

    char input;
    printf("Welcome! Press 'q' to quit or any other key to continue: ");
    scanf(" %c", &input);
    while(getchar() != '\n');

    while (input != 'q')
    { 
        printNode(game_tree);

        printf("Press 'q' to quit or any other key to continue: ");
        scanf(" %c", &input);
        while(getchar() != '\n');
    }
    
    printf("Bye Bye!");

    return 0;
}