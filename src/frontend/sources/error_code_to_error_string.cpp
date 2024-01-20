#include "../headers/error_code_to_error_string.h"

QString errorCodeToErrorString(int code) {
  QString errorMessage{};

  switch (code) {
  case ErrorCode_noError:
    errorMessage = "No error.";
    break;
  case ErrorCode_mismatchedBrackets:
    errorMessage = "Error. Mismatched brackets.";
    break;
  case ErrorCode_resultCalculatedValueIsNan:
    errorMessage = "Error. Result is not a number (NaN).";
    break;
  case ErrorCode_insufficientOperandsForOperator:
    errorMessage = "Error. Insufficient operands for an operation.";
    break;
  case ErrorCode_divisionByZero:
    errorMessage = "Error. Division by zero.";
    break;
  case ErrorCode_incorrectValueForNaturalLogarithm:
    errorMessage = "Error. Invalid value for natural logarithm.";
    break;
  case ErrorCode_incorrectValueForCommonLogarithm:
    errorMessage = "Error. Invalid value for common logarithm.";
    break;
  case ErrorCode_indeterminateResultForArcCosine:
    errorMessage = "Error. Invalid value for arc cosine";
    break;
  case ErrorCode_indeterminateResultForArcSine:
    errorMessage = "Error. Invalid value for arc sine";
    break;
  case ErrorCode_squareOfNegativeNumber:
    errorMessage = "Error. Square of negative number.";
    break;
  case ErrorCode_invalidExpressionFormat:
    errorMessage = "Error. Invalid expression format.";
    break;
  case ErrorCode_emptyExpression:
    errorMessage = "Error. Expression is empty.";
    break;
  default:
    errorMessage = "Error. Invalid input.";
    break;
  }

  return errorMessage;
}
