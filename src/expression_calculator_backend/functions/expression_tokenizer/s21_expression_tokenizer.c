#include "../../headers/s21_expression_tokenizer.h"

int isOperator(char c) {
  return (c == S21_SYMBOL_PLUS || c == S21_SYMBOL_DASH ||
          c == S21_SYMBOL_ASTERISK || c == S21_SYMBOL_SLASH ||
          c == S21_SYMBOL_CIRCUMFLEX || c == S21_SYMBOL_PERCENT ||
          c == S21_SYMBOL_OPEN_PARENTHESIS ||
          c == S21_SYMBOL_CLOSE_PARENTHESIS);
}

int isWhitespace(char c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int isValidNumber(const char *str) {
  if (str == NULL || strlen(str) == 0) {
    return 0;
  }

  int hasDecimal = 0;
  int hasDigits = 0;
  int index = 0;

  if (str[index] == '+' || str[index] == '-') {
    index++;
  }

  if (str[index] == '.') {
    return 0;
  }

  if (str[index] == '0' && strlen(str) > 1 && str[index + 1] != '.') {
    return 0;
  }
  while (str[index] != '\0') {
    if (str[index] == '.') {
      if (hasDecimal) {
        return 0;
      }
      hasDecimal = 1;
    } else if (str[index] >= '0' && str[index] <= '9') {
      hasDigits = 1;
    } else {
      return 0;
    }
    index++;
  }

  return hasDigits;
}

int handleTokenizeCurrentToken(Stack *stack, char *token, int *pTokenIndex,
                               TokenStatus *pTokenStatus) {
  int errorCode = ErrorCode_noError;

  if (*pTokenIndex > 0) {
    token[*pTokenIndex] = '\0';
    if (!isValidNumber(token)) {
      errorCode = ErrorCode_invalidExpressionFormat;
    }
    if (!errorCode) {
      Data data = {0};
      data.dataType = DataType_value;
      data.value = strtod(token, NULL);
      pushShell(stack, data, pTokenStatus);
      *pTokenIndex = 0;
    }
  }

  return errorCode;
}

int handleTokenizeCurrentOperator(Stack *stack, const char *expression,
                                  int symbolIndex, TokenStatus *pTokenStatus) {
  int errorCode = ErrorCode_noError;
  Data data = {0};
  data.dataType = DataType_operatorType;
  data.operatorType = OperatorType_none;

  if (expression[symbolIndex] == S21_SYMBOL_PLUS) {
    data.operatorType = OperatorType_addition;
  } else if (expression[symbolIndex] == S21_SYMBOL_DASH) {
    data.operatorType = OperatorType_subtraction;
  } else if (expression[symbolIndex] == S21_SYMBOL_ASTERISK) {
    data.operatorType = OperatorType_multiplication;
  } else if (expression[symbolIndex] == S21_SYMBOL_SLASH) {
    data.operatorType = OperatorType_division;
  } else if (expression[symbolIndex] == S21_SYMBOL_CIRCUMFLEX) {
    data.operatorType = OperatorType_power;
  } else if (expression[symbolIndex] == S21_SYMBOL_PERCENT) {
    data.operatorType = OperatorType_modulus;
  } else if (expression[symbolIndex] == S21_SYMBOL_OPEN_PARENTHESIS) {
    data.dataType = DataType_bracketType;
    data.bracketType = BracketType_opened;
  } else if (expression[symbolIndex] == S21_SYMBOL_CLOSE_PARENTHESIS) {
    data.dataType = DataType_bracketType;
    data.bracketType = BracketType_closed;
  } else {
    data.dataType = DataType_none;
    errorCode = ErrorCode_unknownOperatorInTokenizer;
  }

  pushShell(stack, data, pTokenStatus);

  return errorCode;
}

void writeTokenFromExpression(const char *expression, char *token,
                              int *pSymbolIndex, int *pTokenIndex) {

  while (isalpha(expression[*pSymbolIndex])) {
    token[(*pTokenIndex)++] = expression[(*pSymbolIndex)++];
  }

  token[*pTokenIndex] = '\0';
}

int handleTokenizeCurrentFunction(char *token, Data *data) {
  int errorCode = ErrorCode_noError;

  if (strcmp(token, S21_STRING_COS) == 0) {
    data->functionType = FunctionType_cosine;
  } else if (strcmp(token, S21_STRING_COS_RAD) == 0) {
    data->functionType = FunctionType_cosine_rad;
  } else if (strcmp(token, S21_STRING_SIN) == 0) {
    data->functionType = FunctionType_sine;
  } else if (strcmp(token, S21_STRING_SIN_RAD) == 0) {
    data->functionType = FunctionType_sine_rad;
  } else if (strcmp(token, S21_STRING_TAN) == 0) {
    data->functionType = FunctionType_tangent;
  } else if (strcmp(token, S21_STRING_TAN_RAD) == 0) {
    data->functionType = FunctionType_tangent_rad;
  } else if (strcmp(token, S21_STRING_ACOS) == 0) {
    data->functionType = FunctionType_arcCosine;
  } else if (strcmp(token, S21_STRING_ASIN) == 0) {
    data->functionType = FunctionType_arcSine;
  } else if (strcmp(token, S21_STRING_ATAN) == 0) {
    data->functionType = FunctionType_arcTangent;
  } else if (strcmp(token, S21_STRING_SQRT) == 0) {
    data->functionType = FunctionType_squareRoot;
  } else if (strcmp(token, S21_STRING_LN) == 0) {
    data->functionType = FunctionType_naturalLogarithm;
  } else if (strcmp(token, S21_STRING_LOG) == 0) {
    data->functionType = FunctionType_commonLogarithm;
  } else if (strcmp(token, S21_STRING_X) == 0) {
    data->dataType = DataType_variable;
  } else if (strcmp(token, S21_STRING_PI) == 0) {
    data->dataType = DataType_value;
    data->value = M_PI;
  } else {
    data->dataType = DataType_none;
    errorCode = ErrorCode_unknownFunctionInTokenizer;
  }

  return errorCode;
}

OperatorType fromBinaryToUnaryCode(OperatorType operatorCode) {
  OperatorType unaryCode = OperatorType_none;

  if (operatorCode == OperatorType_addition) {
    unaryCode = OperatorType_unaryPlus;
  }
  if (operatorCode == OperatorType_subtraction) {
    unaryCode = OperatorType_unaryMinus;
  }

  return unaryCode;
}

void handleUnaryOperatorsAfterOpenBracket(Stack *infixNotation) {
  Data binaryOperator = stack_pop(infixNotation);

  Data bracket = stack_pop(infixNotation);

  binaryOperator.operatorType =
      fromBinaryToUnaryCode(binaryOperator.operatorType);

  stack_push(infixNotation, bracket);
  stack_push(infixNotation, binaryOperator);
}

void handleUnaryOperatorsStartExpression(Stack *infixNotation) {
  Data binaryOperator = stack_pop(infixNotation);

  binaryOperator.operatorType =
      fromBinaryToUnaryCode(binaryOperator.operatorType);

  stack_push(infixNotation, binaryOperator);
}

int isUnaryOperatorAfterOpenBracket(Data *lastToken, Data *currentToken) {
  return (lastToken->bracketType == BracketType_opened &&
          currentToken->operatorType &
              (OperatorType_subtraction | OperatorType_addition));
}

int isUnaryOperatorStartExpression(Data *lastToken, Data *currentToken) {
  return (lastToken->dataType == DataType_none &&
          currentToken->operatorType &
              (OperatorType_subtraction | OperatorType_addition));
}

void tokenizeImplicitOperators(Stack *infixNotation,
                               TokenStatus *pTokenStatus) {
  Data *currentToken = &pTokenStatus->currentToken;
  Data *lastToken = &pTokenStatus->lastToken;

  if (isUnaryOperatorAfterOpenBracket(lastToken, currentToken)) {
    handleUnaryOperatorsAfterOpenBracket(infixNotation);
  } else if (isUnaryOperatorStartExpression(lastToken, currentToken)) {
    handleUnaryOperatorsStartExpression(infixNotation);
  }
}

void pushShell(Stack *infixNotation, Data data, TokenStatus *pTokenStatus) {
  pTokenStatus->lastToken = pTokenStatus->currentToken;
  pTokenStatus->currentToken = data;

  stack_push(infixNotation, data);

  tokenizeImplicitOperators(infixNotation, pTokenStatus);
}

int fromExpressionToInfixNotation(const char *expression,
                                  Stack *infixNotation) {
  int expressionLength = (int)strlen(expression);
  char tokenString[S21_MAX_EXPRESSION_LENGTH] = {0};
  int tokenStringIndex = S21_INIT_TOKEN_INDEX;
  int errorCode = ErrorCode_noError;
  TokenStatus tokenStatus = {0};

  for (int symbolIndex = 0; symbolIndex < expressionLength && !errorCode;
       symbolIndex++) {
    if (isWhitespace(expression[symbolIndex]))
      continue;
    if (isOperator(expression[symbolIndex])) {
      errorCode = handleTokenizeCurrentToken(infixNotation, tokenString,
                                             &tokenStringIndex, &tokenStatus);

      handleTokenizeCurrentOperator(infixNotation, expression, symbolIndex,
                                    &tokenStatus);

    } else if (isalpha(expression[symbolIndex])) {
      writeTokenFromExpression(expression, tokenString, &symbolIndex,
                               &tokenStringIndex);

      Data data = {0};
      data.dataType = DataType_functionType;

      errorCode = handleTokenizeCurrentFunction(tokenString, &data);

      if ((data.functionType != FunctionType_none ||
           data.dataType &
               (DataType_variable | DataType_value | DataType_operatorType)) &&
          !errorCode) {
        pushShell(infixNotation, data, &tokenStatus);
      }

      symbolIndex--;
      tokenStringIndex = S21_INIT_TOKEN_INDEX;
    } else {
      tokenString[tokenStringIndex++] = expression[symbolIndex];
    }
  }

  if (!errorCode) {
    errorCode = handleTokenizeCurrentToken(infixNotation, tokenString,
                                           &tokenStringIndex, &tokenStatus);
  }

  return errorCode;
}
