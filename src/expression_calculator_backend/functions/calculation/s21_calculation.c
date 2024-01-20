#include "../../headers/s21_calculation.h"

void handleVariableX(Data *token, double value) {
  if (token->dataType == DataType_variable) {
    token->dataType = DataType_value;
    token->value = value;
  }
}

int performOperatorCalculations(Data token, Data operand1, Data operand2,
                                double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand1.dataType == DataType_none) {
    errorCode = ErrorCode_invalidExpressionFormat;
  } else if (token.operatorType == OperatorType_addition) {
    handleCalculationAddition(operand1, operand2, pResult);
  } else if (token.operatorType == OperatorType_subtraction) {
    handleCalculationSubtraction(operand1, operand2, pResult);
  } else if (token.operatorType == OperatorType_multiplication) {
    handleCalculationMultiplication(operand1, operand2, pResult);
  } else if (token.operatorType == OperatorType_power) {
    handleCalculationPower(operand1, operand2, pResult);
  } else if (token.operatorType == OperatorType_division) {
    errorCode = handleCalculationDivision(operand1, operand2, pResult);
  } else if (token.operatorType == OperatorType_modulus) {
    errorCode = handleCalculationModulus(operand1, operand2, pResult);
  } else {
    errorCode = ErrorCode_unknownOperator;
  }

  return errorCode;
}

void handlePushingResultValueInCalculationStack(Stack *calculationStack,
                                                double result, int errorCode) {
  if (!errorCode) {
    Data resultData = {0};
    resultData.dataType = DataType_value;
    resultData.value = result;
    stack_push(calculationStack, resultData);
  }
}

int handleCalculationOperators(Stack *calculationStack, Data token) {
  int errorCode = ErrorCode_noError;
  if (stack_isEmpty(calculationStack)) {
    errorCode = ErrorCode_insufficientOperandsForOperator;
  }

  double result = 0.0;

  if (!errorCode) {
    Data operand2 = stack_pop(calculationStack);
    if (operand2.dataType == DataType_none)
      errorCode = ErrorCode_invalidExpressionFormat;
    else if (!handleUnaryOperators(token, operand2, &result)) {
      Data operand1 = stack_pop(calculationStack);

      errorCode =
          performOperatorCalculations(token, operand1, operand2, &result);
    }
  }

  handlePushingResultValueInCalculationStack(calculationStack, result,
                                             errorCode);

  return errorCode;
}

int performFunctionCalculations(Data token, Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (token.functionType & (FunctionType_cosine | FunctionType_cosine_rad))
    handleCalculationCosine(token, operand, pResult);
  else if (token.functionType & (FunctionType_sine | FunctionType_sine_rad))
    handleCalculationSine(token, operand, pResult);
  else if (token.functionType &
           (FunctionType_tangent | FunctionType_tangent_rad))
    handleCalculationTangent(token, operand, pResult);
  else if (token.functionType == FunctionType_squareRoot)
    errorCode = handleCalculationSquareRoot(operand, pResult);
  else if (token.functionType == FunctionType_arcCosine)
    errorCode = handleCalculationArcCosine(operand, pResult);
  else if (token.functionType == FunctionType_arcSine)
    errorCode = handleCalculationArcSine(operand, pResult);
  else if (token.functionType == FunctionType_arcTangent)
    handleCalculationArcTangent(operand, pResult);
  else if (token.functionType == FunctionType_naturalLogarithm)
    errorCode = handleCalculationNaturalLogarithm(operand, pResult);
  else if (token.functionType == FunctionType_commonLogarithm)
    errorCode = handleCalculationCommonLogarithm(operand, pResult);
  else
    errorCode = ErrorCode_unknownFunction;

  return errorCode;
}

int handleCalculationFunctions(Stack *calculationStack, Data token) {
  int errorCode = ErrorCode_noError;
  if (stack_isEmpty(calculationStack)) {
    errorCode = ErrorCode_insufficientOperandsForOperator;
  }

  double result = 0.0;

  if (!errorCode) {
    Data operand = stack_pop(calculationStack);
    errorCode = performFunctionCalculations(token, operand, &result);
  }

  handlePushingResultValueInCalculationStack(calculationStack, result,
                                             errorCode);

  return errorCode;
}

int handleCalculationsOperatorsAndFunctions(Stack *calculationStack,
                                            Data token) {
  int errorCode = ErrorCode_noError;

  if (token.dataType == DataType_operatorType) {
    errorCode |= handleCalculationOperators(calculationStack, token);
  } else if (token.dataType == DataType_functionType) {
    errorCode |= handleCalculationFunctions(calculationStack, token);
  }

  return errorCode;
}

int handleFinalResultAssigning(Stack *calculationStack, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (stack_getLength(calculationStack) != 1) {
    errorCode = ErrorCode_invalidExpressionFormat;
  } else {
    Data finalResult = stack_pop(calculationStack);
    if (finalResult.dataType == DataType_none)
      errorCode = ErrorCode_invalidExpressionFormat;
    *pResult = finalResult.value;
    if (isnan(*pResult))
      errorCode = ErrorCode_resultCalculatedValueIsNan;
  }

  return errorCode;
}

int calculateExpression(Stack *postfixNotation, double xVariable,
                        double *pResult) {
  int errorCode = ErrorCode_noError;
  stack_reverseStack(postfixNotation);
  Stack *calculationStack = stack_initStack();

  *pResult = 0;

  while (!stack_isEmpty(postfixNotation) && !errorCode) {
    Data token = stack_pop(postfixNotation);
    if (token.dataType == DataType_none) {
      errorCode = ErrorCode_invalidExpressionFormat;
    } else if (token.dataType == DataType_value ||
               token.dataType == DataType_variable) {
      handleVariableX(&token, xVariable);
      stack_push(calculationStack, token);
    } else if (token.dataType == DataType_operatorType ||
               token.dataType == DataType_functionType) {
      errorCode =
          handleCalculationsOperatorsAndFunctions(calculationStack, token);
    }
  }

  if (!errorCode) {
    errorCode = handleFinalResultAssigning(calculationStack, pResult);
  }

  stack_destroyStack(calculationStack);

  return errorCode;
}
