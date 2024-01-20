#ifndef S21_STRUCTS_H_
#define S21_STRUCTS_H_

#define S21_EPSILON 1e-7
#define S21_BOUND_VALUE_FOR_INVERSE_TRIGONOMETRY_FUNCTIONS 1

typedef enum {
  DataType_none = 0,
  DataType_value = 1 << 1,
  DataType_operatorType = 1 << 2,
  DataType_functionType = 1 << 3,
  DataType_bracketType = 1 << 4,
  DataType_variable = 1 << 5,
} DataType;

typedef enum {
  OperatorType_none = 0,
  OperatorType_addition = 1 << 1,
  OperatorType_subtraction = 1 << 2,
  OperatorType_multiplication = 1 << 3,
  OperatorType_division = 1 << 4,
  OperatorType_power = 1 << 5,
  OperatorType_modulus = 1 << 6,
  OperatorType_unaryPlus = 1 << 7,
  OperatorType_unaryMinus = 1 << 8
} OperatorType;

typedef enum {
  FunctionType_none = 0,
  FunctionType_cosine = 1 << 1,
  FunctionType_sine = 1 << 2,
  FunctionType_tangent = 1 << 3,
  FunctionType_cosine_rad = 1 << 4,
  FunctionType_sine_rad = 1 << 5,
  FunctionType_tangent_rad = 1 << 6,
  FunctionType_arcCosine = 1 << 7,
  FunctionType_arcSine = 1 << 8,
  FunctionType_arcTangent = 1 << 9,
  FunctionType_squareRoot = 1 << 10,
  FunctionType_naturalLogarithm = 1 << 11,
  FunctionType_commonLogarithm = 1 << 12,
} FunctionType;

typedef enum {
  BracketType_none = 0,
  BracketType_opened = 1 << 1,
  BracketType_closed = 1 << 2
} BracketType;

typedef struct {
  DataType dataType;
  double value;
  OperatorType operatorType;
  FunctionType functionType;
  BracketType bracketType;
} Data;

typedef struct {
  Data currentToken;
  Data lastToken;
} TokenStatus;

typedef enum {
  ErrorCode_noError = 0 << 0,
  ErrorCode_mismatchedBrackets = 1 << 1,
  ErrorCode_invalidExpressionFormat = 1 << 2,
  ErrorCode_resultCalculatedValueIsNan = 1 << 3,
  ErrorCode_insufficientOperandsForOperator = 1 << 4,
  ErrorCode_divisionByZero = 1 << 5,
  ErrorCode_modulusByZero = 1 << 6,
  ErrorCode_unknownOperator = 1 << 7,
  ErrorCode_unknownFunction = 1 << 8,
  ErrorCode_incorrectValueForNaturalLogarithm = 1 << 9,
  ErrorCode_incorrectValueForCommonLogarithm = 1 << 10,
  ErrorCode_squareOfNegativeNumber = 1 << 11,
  ErrorCode_indeterminateResultForArcCosine = 1 << 12,
  ErrorCode_indeterminateResultForArcSine = 1 << 13,
  ErrorCode_unknownFunctionInTokenizer = 1 << 14,
  ErrorCode_unknownOperatorInTokenizer = 1 << 15,
  ErrorCode_twoOperatorsInARow = 1 << 16,
  ErrorCode_emptyBrackets = 1 << 17,
  ErrorCode_emptyExpression = 1 << 18,
  ErrorCode_UnableToBuildGraph = 1 << 19,
} ErrorCode;

#endif // S21_STRUCTS_H_