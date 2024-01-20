#include "../../headers/s21_calculation_handlers.h"

double fromRadToDegree(double radValue) { return radValue * M_PI / 180; }

int isValueInTheBoundsForInverseTrigonometryFunctions(Data data) {
  return fabs(data.value) <= S21_BOUND_VALUE_FOR_INVERSE_TRIGONOMETRY_FUNCTIONS;
}

int handleUnaryOperators(Data token, Data operand2, double *pResult) {
  int isUnaryOperator = 1;

  if (token.operatorType == OperatorType_unaryMinus) {
    *pResult = operand2.value * (-1);
  } else if (token.operatorType == OperatorType_unaryPlus) {
    *pResult = operand2.value;
  } else {
    isUnaryOperator = 0;
  }

  return isUnaryOperator;
}

void handleCalculationAddition(Data operand1, Data operand2, double *pResult) {
  *pResult = operand1.value + operand2.value;
}

void handleCalculationSubtraction(Data operand1, Data operand2,
                                  double *pResult) {
  *pResult = operand1.value - operand2.value;
}

void handleCalculationMultiplication(Data operand1, Data operand2,
                                     double *pResult) {
  *pResult = operand1.value * operand2.value;
}

void handleCalculationPower(Data operand1, Data operand2, double *pResult) {
  *pResult = pow(operand1.value, operand2.value);
}

int handleCalculationDivision(Data operand1, Data operand2, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand2.value == 0) {
    errorCode = ErrorCode_divisionByZero;
  } else {
    *pResult = operand1.value / operand2.value;
  }

  return errorCode;
}

int handleCalculationModulus(Data operand1, Data operand2, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand2.value == 0) {
    errorCode = ErrorCode_modulusByZero;
  } else {
    *pResult = fmod(operand1.value, operand2.value);
  }

  return errorCode;
}

int handleCalculationArcCosine(Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (isValueInTheBoundsForInverseTrigonometryFunctions(operand)) {
    *pResult = acos(operand.value);
  } else {
    errorCode = ErrorCode_indeterminateResultForArcCosine;
  }

  return errorCode;
}

int handleCalculationArcSine(Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (isValueInTheBoundsForInverseTrigonometryFunctions(operand)) {
    *pResult = asin(operand.value);
  } else {
    errorCode = ErrorCode_indeterminateResultForArcSine;
  }

  return errorCode;
}

void handleCalculationArcTangent(Data operand, double *pResult) {
  *pResult = atan(operand.value);
}

void handleCalculationCosine(Data token, Data operand, double *pResult) {
  if (token.functionType == FunctionType_cosine) {
    operand.value = fromRadToDegree(operand.value);
  }

  *pResult = cos(operand.value);
}

void handleCalculationSine(Data token, Data operand, double *pResult) {
  if (token.functionType == FunctionType_sine) {
    operand.value = fromRadToDegree(operand.value);
  }

  *pResult = sin(operand.value);
}

void handleCalculationTangent(Data token, Data operand, double *pResult) {
  if (token.functionType == FunctionType_tangent) {
    operand.value = fromRadToDegree(operand.value);
  }

  *pResult = tan(operand.value);
}

int handleCalculationSquareRoot(Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand.value < 0) {
    errorCode = ErrorCode_squareOfNegativeNumber;
  } else {
    *pResult = sqrt(operand.value);
  }

  return errorCode;
}

int handleCalculationNaturalLogarithm(Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand.value <= 0) {
    errorCode = ErrorCode_incorrectValueForNaturalLogarithm;
  } else {
    *pResult = log(operand.value);
  }

  return errorCode;
}

int handleCalculationCommonLogarithm(Data operand, double *pResult) {
  int errorCode = ErrorCode_noError;

  if (operand.value <= 0) {
    errorCode = ErrorCode_incorrectValueForCommonLogarithm;
  } else {
    *pResult = log10(operand.value);
  }

  return errorCode;
}
