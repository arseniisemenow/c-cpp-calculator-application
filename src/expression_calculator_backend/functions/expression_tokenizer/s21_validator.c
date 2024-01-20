#include "../../headers/s21_validator.h"

int isTwoOperatorsInARow(Data currentToken, Data previousToken) {
  return (currentToken.dataType == DataType_operatorType &&
          previousToken.dataType == DataType_operatorType);
}

int isEmptyBrackets(Data currentToken, Data previousToken) {
  return (currentToken.bracketType == BracketType_closed &&
          previousToken.bracketType == BracketType_opened);
}

int validationExpression(const char *expression, Stack *infixNotation) {
  int errorCode = ErrorCode_noError;

  Stack *copyStack = stack_copyStack(infixNotation);

  stack_reverseStack(copyStack);

  Data previousToken = {0};

  if (strlen(expression) == 0) {
    errorCode = ErrorCode_emptyExpression;
  }

  while (!stack_isEmpty(copyStack) && !errorCode) {
    Data currentToken = stack_pop(copyStack);

    if (isTwoOperatorsInARow(currentToken, previousToken)) {
      errorCode = ErrorCode_twoOperatorsInARow;
    }
    if (isEmptyBrackets(currentToken, previousToken)) {
      errorCode = ErrorCode_emptyBrackets;
    }

    previousToken = currentToken;
  }

  stack_destroyStack(copyStack);

  return errorCode;
}
