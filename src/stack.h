#ifndef STACK_H
#define STACK_H

 typedef struct Char_Stack
{
    char *data;
    int top;
    int max_size;

} Char_Stack;

void init_char_stack(Char_Stack *stack, int max_size);

void push_char_stack(Char_Stack *stack, char token);

char pop_char_stack(Char_Stack *stack);

char peek_char_stack(Char_Stack *stack);

void free_char_stack(Char_Stack *stack);

typedef struct Double_Stack
{
    double *data;
    int top;
    int max_size;

} Double_Stack;

void init_double_stack(Double_Stack *stack, int max_size);

void push_double_stack(Double_Stack *stack, double token);

double pop_double_stack(Double_Stack *stack);

double peek_double_stack(Double_Stack *stack);

void free_double_stack(Double_Stack *stack);

#endif