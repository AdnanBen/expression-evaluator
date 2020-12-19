#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "stack.h"

#define FUNCTION_SIN 100
#define FUNCTION_COS 101
#define FUNCTION_TAN 102
#define FUNCTION_LN 103
#define FUNCTION_LOG 104
#define FUNCTION_SQRT 105

#define VARIABLE_UPPERCASE_X 0
#define VARIABLE_UPPERCASE_Y 1
#define VARIABLE_UPPERCASE_Z 2
#define VARIABLE_LOWERCASE_P 3

typedef struct Return_Elements
{
    double result;
    int any_errors;
    int quit;

} Return_Elements;

enum token_types
{
    NONE,
    NUMBER,
    DECIMAL_NUMBER,
    OPERATOR,
    FUNCTION,
    L_PARENTHESIS,
    R_PARENTHESIS,
    VARIABLE,
    EQUALITY
};

double perform_operator_calculation(char operator, double operand_b, double operand_a);

double perform_unary_function_calculation(double function, double argument);

int get_precedence(char operator);

char get_associativity(char operator);

int is_function(double input);

int get_function_arity(double input);

int get_variable_index(char variable);

double get_variable_value(char variable, double *variables, int is_number_negative);

void check_stack_push_operator(Char_Stack *operator_stack, Double_Stack *calculation_stack, char operator);

Return_Elements get_answer(char* user_input_expression, double *variables, const int CHARACTER_LIMIT);

#endif