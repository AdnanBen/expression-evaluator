#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "evaluator.h"

double perform_operator_calculation(char operator, double operand_b, double operand_a)
{
    switch(operator)
    {
        case '+':
            return operand_a+operand_b;
        case '-': 
            return operand_a-operand_b;
        case '*':
            return operand_a*operand_b;
        case '/':
            return operand_a/operand_b;
        case '^':
            return pow(operand_a,operand_b);
        default:
            return 0;
    }

}

double perform_unary_function_calculation(double function, double argument)
{
    switch((int)function)
    {
        case FUNCTION_SIN:
            return sin(argument);
        case FUNCTION_COS:
            return cos(argument);
        case FUNCTION_TAN:
            return tan(argument);
        case FUNCTION_LN:
            return log(argument);
        case FUNCTION_LOG:
            return log10(argument);
        case FUNCTION_SQRT:
            return sqrt(argument);
        default:
            return 0;
    }

}

int get_precedence(char operator)
{
    if (operator == '+' || operator == '-')
    {
        return 2;
    }
    if (operator == '*' || operator == '/')
    {
        return 3;
    }
    if (operator == '^')
    {
        return 4;
    }
    else
    {
        return -1;
    }
}

char get_associativity(char operator)
{
    if (operator == '+' || operator == '-' || operator == '*' || operator == '/')
    {
        return 'l';
    }
    else if (operator == '^')
    {
        return 'r';
    }
    else
    {
        return '\0';
    }
}

int is_function(double input)
{
    if (input >=100 && input <= 105)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int get_function_arity(double input)
{
    if (input >=100 && input <= 105)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    
}

int get_variable_index(char variable)
{
    if (variable == 'X')
    {
        return VARIABLE_UPPERCASE_X;
    }
    else if (variable == 'Y')
    {
        return VARIABLE_UPPERCASE_Y;
    }
    else if (variable == 'Z')
    {
        return VARIABLE_UPPERCASE_Z;
    }
    else if (variable == 'p')
    {
        return VARIABLE_LOWERCASE_P;
    }
    else
    {
        return -1;
    }
    
}


double get_variable_value(char variable, double *variables, int is_number_negative)
{
    if (is_number_negative == 1)
    {
        return variables[get_variable_index(variable)] * -1;
    }
    else
    {
        return variables[get_variable_index(variable)];
    }
    
}


void check_stack_push_operator(Char_Stack *operator_stack, Double_Stack *calculation_stack, char operator)
{   
    /* Performs all the neccessary checks that ensure an operator is only pushed to the operator stack
       once all the appropriate operators, according to the shunting yard algorithm, have been popped.
       As operators are popped, the results of their calculations with the relevant operands are determined
       and pushed into the calculation stack. */
    while (get_precedence(peek_char_stack(operator_stack)) > get_precedence(operator) 
            || (get_precedence(peek_char_stack(operator_stack)) == get_precedence(operator) 
            && get_associativity(peek_char_stack(operator_stack)) == 'l'))
    {
        push_double_stack(calculation_stack, perform_operator_calculation(pop_char_stack(operator_stack),
         pop_double_stack(calculation_stack), pop_double_stack(calculation_stack)));
    }
    push_char_stack(operator_stack, operator);
}

Return_Elements get_answer(char* user_input_expression, double *variables, const int CHARACTER_LIMIT)
{
    Char_Stack *operator_stack = (Char_Stack*)malloc(sizeof(Char_Stack));
    Double_Stack *calculation_stack = (Double_Stack*)malloc(sizeof(Double_Stack));
    Double_Stack *function_stack = (Double_Stack*)malloc(sizeof(Double_Stack));

    char *sub_user_input_expression = (char*)malloc(sizeof(char)*CHARACTER_LIMIT);

    init_char_stack(operator_stack, CHARACTER_LIMIT);
    init_double_stack(calculation_stack, CHARACTER_LIMIT);
    init_double_stack(function_stack, CHARACTER_LIMIT);

    Return_Elements return_variables;
    return_variables.any_errors = 0;
    return_variables.quit = 0;

    int i;
    double prev_number, current_number, current_digit;
    prev_number = current_number = current_digit = 0;
    
    int is_number_negative, is_number_decimal, is_parentheses_negative, decimal_place_value; 
    is_number_negative = is_number_decimal = is_parentheses_negative = decimal_place_value = 0;

    enum token_types previous_token_type;
    previous_token_type = NONE;

    char latest_variable;

    for (i = 0; i < strlen(user_input_expression); i++)
    {
        switch(user_input_expression[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // convert char representation to int equivalent
                current_digit = user_input_expression[i] - '0';
                if (is_number_negative == 1)
                {
                    current_digit = current_digit*-1;
                }
                if (is_number_decimal == 1)
                {
                    current_number = current_number + current_digit*(pow(10,-(++decimal_place_value)));
                    if (isdigit(user_input_expression[i+1]) == 0)
                    {
                        is_number_decimal = 0;
                        decimal_place_value = 0;
                        is_number_negative = 0;
                        push_double_stack(calculation_stack, current_number);
                    }
                }
                else
                {
                    // handle case where number is 2 digits or more
                    if (previous_token_type == NUMBER)
                    {
                        current_number = prev_number*10 + fmod(current_digit, 10);
                    }
                    else
                    { 
                        current_number = current_digit;
                    }
                    if (isdigit(user_input_expression[i+1]) == 0 && user_input_expression[i+1] != '.')
                    {
                        push_double_stack(calculation_stack, current_number);
                        is_number_negative = 0;
                    }
                }           
                previous_token_type = NUMBER;
                prev_number = current_number;
                break;
            case '.':
                is_number_decimal = 1;
            case ' ':
                break;
             case '\n':
                break;
            case '+':
                check_stack_push_operator(operator_stack, calculation_stack, user_input_expression[i]);
                previous_token_type = OPERATOR;
                break;
            case '-':
                if (previous_token_type == OPERATOR || previous_token_type == L_PARENTHESIS
                    || previous_token_type == R_PARENTHESIS)
                {
                    is_number_negative = 1;
                }
                else
                {
                    check_stack_push_operator(operator_stack, calculation_stack, user_input_expression[i]);
                }
                previous_token_type = OPERATOR;
                break;
            case '*':
                check_stack_push_operator(operator_stack, calculation_stack, user_input_expression[i]);
                previous_token_type = OPERATOR;
                break;
            case '/':
                check_stack_push_operator(operator_stack, calculation_stack, user_input_expression[i]);
                previous_token_type = OPERATOR;
                break;
            case '^':
                check_stack_push_operator(operator_stack, calculation_stack, user_input_expression[i]);
                previous_token_type = OPERATOR;
                break;
            case '(':
                if (is_number_negative == 1)
                {
                    is_number_negative = 0;
                    is_parentheses_negative = 1;
                }
                push_char_stack(operator_stack, '(');
                previous_token_type = L_PARENTHESIS;
                break;
            case ')':
                while (peek_char_stack(operator_stack) != '(')
                {   if (peek_char_stack(operator_stack) == '\0')
                    {
                        printf("\nMismatched parentheses in expression, please review\n\n");
                        return_variables.any_errors = 1;
                        return return_variables;
                    }               
                    push_double_stack(calculation_stack, perform_operator_calculation(pop_char_stack(operator_stack),
                     pop_double_stack(calculation_stack), pop_double_stack(calculation_stack)));
                }
                if (is_parentheses_negative == 1)
                {
                    push_double_stack(calculation_stack, pop_double_stack(calculation_stack)*-1);
                    is_parentheses_negative = 0;
                }
                pop_char_stack(operator_stack);
                if (is_function(peek_double_stack(function_stack)) == 1)
                {   if (get_function_arity(peek_double_stack(function_stack)) == 1)
                    {
                         push_double_stack(calculation_stack, perform_unary_function_calculation(
                             pop_double_stack(function_stack), pop_double_stack(calculation_stack)));
                    }
                    else
                    {
                        // potential support for different arity functions
                    }
                }
                previous_token_type = R_PARENTHESIS;
                break;
            case 's':
                // check that we don't look past the string size
                if ((i+2) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'i' && user_input_expression[i+2] == 'n')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_SIN);
                        // skip past iterations for other letters in function
                        i = i+2;
                    }
                }
                if ((i+3) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'q' && user_input_expression[i+2] == 'r'
                     && user_input_expression[i+3] == 't')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_SQRT);
                        i = i+3;
                    }
                }
                previous_token_type = FUNCTION;
                break;
            case 'c':
                if ((i+2) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'o' && user_input_expression[i+2] == 's')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_COS);
                        i = i+2;
                    }
                }
                previous_token_type = FUNCTION;
                break;
            case 't':
                if ((i+2) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'a' && user_input_expression[i+2] == 'n')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_TAN);
                        i = i+2;
                    }
                }
                previous_token_type = FUNCTION;
                break;
            case 'l':
                if ((i+1) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'n')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_LN);
                        i = i+1;
                    }
                }
                if ((i+2) < strlen(user_input_expression))
                {
                    if (user_input_expression[i+1] == 'o' && user_input_expression[i+2] == 'g')
                    {
                        push_double_stack(function_stack, (double)FUNCTION_LOG);
                        i = i+1;
                    }
                }
                previous_token_type = FUNCTION;
                break;
            case '=':
                if (previous_token_type == VARIABLE)
                {
                    pop_double_stack(calculation_stack);
                    strncpy(sub_user_input_expression, user_input_expression+(i+1), CHARACTER_LIMIT - (i+1));
                    return_variables = get_answer(sub_user_input_expression, variables, CHARACTER_LIMIT);
                    variables[get_variable_index(latest_variable)] = return_variables.result;
                    return return_variables;
                }
                previous_token_type = EQUALITY;
                break;        
            case 'X':
                push_double_stack(calculation_stack, get_variable_value(user_input_expression[i],
                 variables, is_number_negative));
                is_number_negative = 0;
                latest_variable = user_input_expression[i];
                previous_token_type = VARIABLE;
                break;
            case 'Y':
                push_double_stack(calculation_stack, get_variable_value(user_input_expression[i],
                 variables, is_number_negative));
                is_number_negative = 0;
                latest_variable = user_input_expression[i];
                previous_token_type = VARIABLE;
                break;
            case 'Z':
                push_double_stack(calculation_stack, get_variable_value(user_input_expression[i],
                 variables, is_number_negative));
                is_number_negative = 0;
                latest_variable = user_input_expression[i];
                previous_token_type = VARIABLE;
                break;
            case 'p':
                latest_variable = user_input_expression[i];
                previous_token_type = VARIABLE;
                break;
            case 'Q':
                return_variables.quit = 1;
            default:
                if (isalpha(user_input_expression[i]) == 0)
                {
                    return_variables.any_errors = 1;
                    printf("\nUnknown character detected, please review expression\n\n");
                    return return_variables;
                }
        }
      
    }
    
    while (peek_char_stack(operator_stack) != '\0')
    {
        if (peek_char_stack(operator_stack) == '(')
        {
            printf("\nMismatched parentheses in expression, please review\n\n");
            return_variables.any_errors = 1;
            return return_variables;
        }
        push_double_stack(calculation_stack, perform_operator_calculation(pop_char_stack(operator_stack),
         pop_double_stack(calculation_stack), pop_double_stack(calculation_stack)));
    }

    return_variables.result = pop_double_stack(calculation_stack);

    free_char_stack(operator_stack);
    free_double_stack(calculation_stack);

    return return_variables;
}