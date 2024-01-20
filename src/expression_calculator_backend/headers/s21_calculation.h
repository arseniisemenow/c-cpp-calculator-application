#ifndef S21_CALCULATION_H_
#define S21_CALCULATION_H_

#include "s21_calculation_handlers.h"
#include "s21_libs.h"
#include "s21_stack.h"

void handleVariableX(Data *token, double value);

int performOperatorCalculations(Data token, Data operand1, Data operand2,
                                double *pResult);

void handlePushingResultValueInCalculationStack(Stack *calculationStack,
                                                double result, int errorCode);

int handleCalculationOperators(Stack *calculationStack, Data token);

int performFunctionCalculations(Data token, Data operand, double *pResult);

int handleCalculationFunctions(Stack *calculationStack, Data token);

int handleCalculationsOperatorsAndFunctions(Stack *calculationStack,
                                            Data token);

int handleFinalResultAssigning(Stack *calculationStack, double *pResult);

int calculateExpression(Stack *postfixNotation, double xVariable,
                        double *pResult);

#endif // S21_CALCULATION_H_