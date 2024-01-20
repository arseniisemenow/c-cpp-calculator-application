#include "../../headers/s21_stack.h"

Node *stack_createNode(Data data) {
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (node == NULL)
    fprintf(stderr, "stack_createNode: failed to alloc memory for node\n");
  node->data = data;
  node->next = NULL;
  return node;
}

Stack *stack_initStack() {
  Stack *stack = (Stack *)calloc(1, sizeof(Stack));
  if (stack == NULL)
    fprintf(stderr,
            "stack_initStack: failed to alloc memory for s21_calculator\n");
  stack->top = NULL;
  return stack;
}

int stack_isEmpty(Stack *stack) { return stack->top == NULL; }

void stack_push(Stack *stack, Data data) {
  Node *newNode = stack_createNode(data);
  newNode->next = stack->top;
  stack->top = newNode;
}

Data stack_pop(Stack *stack) {
  Data data = {0};
  if (stack_isEmpty(stack))
    fprintf(stderr, "stack_pop: stack is empty\n");
  else {
    Node *topNode = stack->top;
    data = topNode->data;
    stack->top = topNode->next;
    free(topNode);
  }
  return data;
}

int stack_getLength(Stack *stack) {
  Node *currentNode = stack->top;
  int elementCount = 0;
  while (currentNode != NULL) {
    elementCount++;
    currentNode = currentNode->next;
  }
  return elementCount;
}

void stack_destroyStack(Stack *stack) {
  if (!stack)
    return;
  while (!stack_isEmpty(stack)) {
    stack_pop(stack);
  }
  free(stack);
}

/**
 * CAUTION!
 * This function is destroying original stack!
 * Be careful!
 **/
void stack_reverseStack(Stack *stack) {

  Stack *tempStack = stack_initStack();
  Stack *reverseStack = stack_initStack();

  while (!stack_isEmpty(stack)) {
    Data data = stack_pop(stack);
    stack_push(tempStack, data);
  }

  while (!stack_isEmpty(tempStack)) {
    Data data = stack_pop(tempStack);
    stack_push(reverseStack, data);
  }

  while (!stack_isEmpty(reverseStack)) {
    Data data = stack_pop(reverseStack);
    stack_push(stack, data);
  }

  stack_destroyStack(tempStack);
  stack_destroyStack(reverseStack);
}

Stack *stack_copyStack(Stack *sourceStack) {
  Stack *copiedStack = stack_initStack();

  Stack *tempStack = stack_initStack();

  while (!stack_isEmpty(sourceStack)) {
    Data data = stack_pop(sourceStack);
    stack_push(tempStack, data);
  }

  while (!stack_isEmpty(tempStack)) {
    Data data = stack_pop(tempStack);
    stack_push(copiedStack, data);
    stack_push(sourceStack, data);
  }

  stack_destroyStack(tempStack);

  return copiedStack;
}
