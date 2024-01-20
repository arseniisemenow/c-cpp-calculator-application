#include "../../headers/s21_calc_library.h"

int fromExpressionToPostfixStack(const char *expression, Stack *postfixStack) {
  int errorCode = ErrorCode_noError;
  Stack *infixNotation = stack_initStack();

  errorCode = fromExpressionToInfixNotation(expression, infixNotation);

  if (!errorCode) {
    errorCode = validationExpression(expression, infixNotation);
  }
  if (!errorCode) {
    errorCode = fromInfixToPostfix(infixNotation, postfixStack);
  }

  stack_destroyStack(infixNotation);

  return errorCode;
}

int fromStackToValue(Stack *postfixStack, double xVariable, double *pResult) {
  int errorCode = ErrorCode_noError;

  errorCode = calculateExpression(postfixStack, xVariable, pResult);

  return errorCode;
}

int fromExpressionToValue(const char *expression, double xVariable,
                          double *pResult) {
  setlocale(LC_ALL, "C");

  int errorCode = ErrorCode_noError;

  Stack *postfixStack = stack_initStack();

  errorCode = fromExpressionToPostfixStack(expression, postfixStack);

  if (!errorCode) {
    errorCode = fromStackToValue(postfixStack, xVariable, pResult);
  }

  stack_destroyStack(postfixStack);

  return errorCode;
}
