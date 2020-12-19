#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_char_stack(Char_Stack *stack, int max_size)
{
    stack->data = (char*)malloc(sizeof(char)*max_size);
    stack->top = -1;
    stack->max_size = max_size;
}

void push_char_stack(Char_Stack *stack, char token)
{  
    if ((stack->top)+1 == stack->max_size)
    {
        // stack is full, do nothing
    }
    else if (stack->top+1 > stack->max_size)
    {
        // stack overflow, shouldn't occur
    }
    else
    {
        stack->data[++(stack->top)] = token;
    }
}

char pop_char_stack(Char_Stack *stack)
{
    if (stack->top < 0)
    {
        return '\0';
    }
    else
    {
        return stack->data[(stack->top)--];
    }

}

char peek_char_stack(Char_Stack *stack)
{
    if (stack->top < 0)
    {
        return '\0';
    }
    else
    {
        return stack->data[stack->top];
    }
}

void free_char_stack(Char_Stack *stack)
{
    free(stack -> data);
    free(stack);
}

void init_double_stack(Double_Stack *stack, int max_size)
{
    stack->data = (double*)malloc(sizeof(double)*max_size);
    stack->top = -1;
    stack->max_size = max_size;
}

void push_double_stack(Double_Stack *stack, double token)
{  
    if ((stack->top)+1 == stack->max_size)
    {
        // stack is full, do nothing
    }
    else if (stack->top+1 > stack->max_size)
    {
        // stack overflow, shouldn't occur
    }
    else
    {
        stack->data[++(stack->top)] = token;
    }
}

double pop_double_stack(Double_Stack *stack)
{
    if (stack->top < 0)
    {
        // if stack empty return default 0, should only occur if user input empty or starts with negative number
        return 0.0;
    }
    else
    {   
        return stack->data[(stack->top)--];
    }

}

double peek_double_stack(Double_Stack *stack)
{
    if (stack->top < 0)
    {
        // if stack empty return default 0, should only occur if user input empty or starts with negative number
        return 0.0;
    }
    else
    {
        return stack->data[stack->top];
    }
}

void free_double_stack(Double_Stack *stack)
{
    free(stack -> data);
    free(stack);
}
