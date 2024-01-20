#ifndef S21_CALCULATION_HANDLERS_H_
#define S21_CALCULATION_HANDLERS_H_

#include "s21_libs.h"
#include "s21_stack.h"

int isValueInTheBoundsForInverseTrigonometryFunctions(Data data);

int handleUnaryOperators(Data token, Data operand2, double *pResult);

void handleCalculationAddition(Data operand1, Data operand2, double *pResult);

void handleCalculationSubtraction(Data operand1, Data operand2,
                                  double *pResult);

void handleCalculationMultiplication(Data operand1, Data operand2,
                                     double *pResult);

void handleCalculationPower(Data operand1, Data operand2, double *pResult);

int handleCalculationDivision(Data operand1, Data operand2, double *pResult);

int handleCalculationModulus(Data operand1, Data operand2, double *pResult);

int handleCalculationArcCosine(Data operand, double *pResult);

int handleCalculationArcSine(Data operand, double *pResult);

void handleCalculationArcTangent(Data operand, double *pResult);

double fromRadToDegree(double radValue);

void handleCalculationCosine(Data token, Data operand, double *pResult);

void handleCalculationSine(Data token, Data operand, double *pResult);

void handleCalculationTangent(Data token, Data operand, double *pResult);

int handleCalculationSquareRoot(Data operand, double *pResult);

int handleCalculationNaturalLogarithm(Data operand, double *pResult);

int handleCalculationCommonLogarithm(Data operand, double *pResult);

#endif // S21_CALCULATION_HANDLERS_H_