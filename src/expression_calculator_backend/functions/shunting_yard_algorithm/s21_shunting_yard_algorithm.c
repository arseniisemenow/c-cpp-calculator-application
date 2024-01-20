#include "../../headers/s21_shunting_yard_algorithm.h"

void handleOpeningParenthesis(Data token, Stack *operatorStack) {
  stack_push(operatorStack, token);
}

int isOpenBracket(Data data) {
  return (data.dataType == DataType_bracketType &&
          data.bracketType == BracketType_opened);
}

int handleClosingParenthesis(Stack *operatorStack, Stack *postfixStack) {
  int errorCode = ErrorCode_noError;
  int foundOpeningParenthesis = 0;

  while (!stack_isEmpty(operatorStack) && !foundOpeningParenthesis) {
    Data topOperator = stack_pop(operatorStack);

    if (isOpenBracket(topOperator)) {
      foundOpeningParenthesis = 1;
    } else {
      stack_push(postfixStack, topOperator);
    }
  }

  if (!foundOpeningParenthesis) {
    errorCode = ErrorCode_mismatchedBrackets;
  }

  return errorCode;
}

void handleBinaryOperatorOrFunction(Data token, Stack *operatorStack,
                                    Stack *postfixStack) {
  int stopCycleFlag = 0;

  while (!stack_isEmpty(operatorStack) && !stopCycleFlag) {
    Data topOperator = stack_pop(operatorStack);

    if (isOpenBracket(topOperator)) {
      stack_push(operatorStack, topOperator);
      stopCycleFlag = 1;
    } else {
      int precedence1 = getOperatorPrecedence(token);
      int precedence2 = getOperatorPrecedence(topOperator);

      if (precedence1 > precedence2) {
        stack_push(operatorStack, topOperator);
        stopCycleFlag = 1;
      } else {
        stack_push(postfixStack, topOperator);
      }
    }
  }

  stack_push(operatorStack, token);
}

void handleUnaryOperatorOrFunction(Data token, Stack *operatorStack) {
  stack_push(operatorStack, token);
}

void handleBinaryAndUnaryOperators(int *pFlag, Data token, Stack *operatorStack,
                                   Stack *postfixStack) {
  if (*pFlag == lastTokenIsOperandOrFunction) {
    handleBinaryOperatorOrFunction(token, operatorStack, postfixStack);
  } else {
    handleUnaryOperatorOrFunction(token, operatorStack);
  }

  *pFlag = lastTokenIsNotOperandOrFunction;
}

int handleBrackets(int *pFlag, Data token, Stack *operatorStack,
                   Stack *postfixStack) {
  int errorCode = ErrorCode_noError;

  if (token.bracketType == BracketType_opened) {
    handleOpeningParenthesis(token, operatorStack);
    *pFlag = lastTokenIsNotOperandOrFunction;
  } else if (token.bracketType == BracketType_closed) {
    errorCode = handleClosingParenthesis(operatorStack, postfixStack);
    *pFlag = lastTokenIsOperandOrFunction;
  }

  return errorCode;
}

void handleEndOfExpression(Stack *operatorStack, Stack *postfixStack,
                           int *pErrorCode) {
  while (!stack_isEmpty(operatorStack) && !*pErrorCode) {
    Data topOperator = stack_pop(operatorStack);

    if (topOperator.dataType == DataType_bracketType) {
      *pErrorCode = ErrorCode_mismatchedBrackets;
    } else {
      stack_push(postfixStack, topOperator);
    }
  }
}

int isValueOrVariable(Data token) {
  return (token.dataType == DataType_value ||
          token.dataType == DataType_variable);
}

int isOperatorOrFunction(Data token) {
  return (token.dataType == DataType_operatorType ||
          token.dataType == DataType_functionType);
}

int isBracket(Data token) { return (token.dataType == DataType_bracketType); }

int fromInfixToPostfix(Stack *infixStack, Stack *postfixStack) {
  stack_reverseStack(infixStack);

  int errorCode = ErrorCode_noError;
  Stack *operatorStack = stack_initStack();
  int flag = lastTokenIsNotOperandOrFunction;

  while (!stack_isEmpty(infixStack) && !errorCode) {
    Data token = stack_pop(infixStack);

    if (isValueOrVariable(token)) {
      stack_push(postfixStack, token);
      flag = lastTokenIsOperandOrFunction;
    } else if (isOperatorOrFunction(token)) {
      handleBinaryAndUnaryOperators(&flag, token, operatorStack, postfixStack);
    } else if (isBracket(token)) {
      errorCode = handleBrackets(&flag, token, operatorStack, postfixStack);
    }
  }

  handleEndOfExpression(operatorStack, postfixStack, &errorCode);

  stack_destroyStack(operatorStack);
  return errorCode;
}

int isFunction(Data token) { return (token.dataType == DataType_functionType); }

int isAdditionOrSubtraction(Data token) {
  return (token.operatorType &
          (OperatorType_addition | OperatorType_subtraction)) > 0;
}

int isMultiplicationDivisionOrModulus(Data token) {
  return (token.operatorType & (OperatorType_multiplication |
                                OperatorType_division | OperatorType_modulus)) >
         0;
}

int isPower(Data token) {
  return (token.operatorType & (OperatorType_power)) > 0;
}

int isUnaryOperator(Data token) {
  return (token.operatorType &
          (OperatorType_unaryPlus | OperatorType_unaryMinus)) > 0;
}

int getOperatorPrecedence(Data token) {
  int precedenceValue = precedenceLevel_0;

  if (isFunction(token) || isUnaryOperator(token)) {
    precedenceValue = precedenceLevel_4;
  } else if (isAdditionOrSubtraction(token)) {
    precedenceValue = precedenceLevel_1;
  } else if (isMultiplicationDivisionOrModulus(token)) {
    precedenceValue = precedenceLevel_2;
  } else if (isPower(token)) {
    precedenceValue = precedenceLevel_3;
  }

  return precedenceValue;
}
