#include "../../headers/s21_stack.h"

void stack_printStack(const char *text, Stack *stack) {
  printf(YEL "<== %s ==>\n", text);
  Node *currentNode = stack->top;
  int elementCount = 0;
  while (currentNode != NULL) {
    Data data = currentNode->data;
    printf("\nelementNumber: %d\n", elementCount++);
    printf("data.dataType: %d\n", data.dataType);
    printf("data.operatorType: %d\n", data.operatorType);
    printf("data.functionType: %d\n", data.functionType);
    printf("data.bracketType: %d\n", data.bracketType);
    printf("data.value: %lf\n", data.value);
    currentNode = currentNode->next;
  }
  printf("\n<== Stack is end ==>\n" RESET);
}