#ifndef S21_SHUNTING_YARD_ALGORITHM_H_
#define S21_SHUNTING_YARD_ALGORITHM_H_

#include "s21_libs.h"
#include "s21_stack.h"

typedef enum {
  precedenceLevel_0 = 0,
  precedenceLevel_1 = 1,
  precedenceLevel_2 = 2,
  precedenceLevel_3 = 3,
  precedenceLevel_4 = 4,
} precedenceLevels;

typedef enum {
  lastTokenIsNotOperandOrFunction = 0,
  lastTokenIsOperandOrFunction = 1
} isLastTokenIsOperandOrFunction;

void handleOpeningParenthesis(Data token, Stack *operatorStack);

int handleClosingParenthesis(Stack *operatorStack, Stack *postfixStack);

void handleBinaryOperatorOrFunction(Data token, Stack *operatorStack,
                                    Stack *postfixStack);

void handleUnaryOperatorOrFunction(Data token, Stack *operatorStack);

int fromInfixToPostfix(Stack *infixStack, Stack *postfixStack);

int getOperatorPrecedence(Data token);

#endif // S21_SHUNTING_YARD_ALGORITHM_H_