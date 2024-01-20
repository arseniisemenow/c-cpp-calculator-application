#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "s21_libs.h"
#include "s21_structs.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct node {
  Data data;
  struct node *next;
} Node;

typedef struct {
  Node *top;
} Stack;

Node *stack_createNode(Data data);

Stack *stack_initStack();

int stack_isEmpty(Stack *stack);

void stack_push(Stack *stack, Data data);

Data stack_pop(Stack *stack);

void stack_printStack(const char *text, Stack *stack);

void stack_destroyStack(Stack *stack);

void stack_reverseStack(Stack *stack);

int stack_getLength(Stack *stack);

Stack *stack_copyStack(Stack *sourceStack);

#endif // S21_STACK_H_