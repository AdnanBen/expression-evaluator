#include <stdio.h>
#include <stdlib.h>
#include "evaluator.h"

void main_menu(double *variables, const int CHARACTER_LIMIT)
{
    Return_Elements return_variables;

    char *user_input_expression = (char*)malloc(sizeof(char)*CHARACTER_LIMIT);
    
    printf("Please enter expression or variable definition:\n");
    fgets(user_input_expression, CHARACTER_LIMIT, stdin);
    
    return_variables = get_answer(user_input_expression, variables, CHARACTER_LIMIT);

    if (return_variables.quit == 1)
    {
        exit(0);
    }

    else if (return_variables.any_errors == 0)
    {
        printf("%.*f \n", (int)variables[VARIABLE_LOWERCASE_P], return_variables.result);
    }

    free(user_input_expression);
    main_menu(variables, CHARACTER_LIMIT);
}

int main()

{
    double variables[4] = {0};
    int user_character_limit;
    char ch;

    printf("Please enter a character limit for expressions:\n");
    scanf("%d", &user_character_limit);
    while ((ch = getchar()) != '\n' && ch != EOF);

    main_menu(variables, user_character_limit);
}