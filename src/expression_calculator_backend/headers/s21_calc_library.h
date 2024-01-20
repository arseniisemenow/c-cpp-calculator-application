#ifndef S21_CALC_LIBRARY_H_
#define S21_CALC_LIBRARY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "s21_calculation.h"
#include "s21_expression_tokenizer.h"
#include "s21_shunting_yard_algorithm.h"
#include "s21_validator.h"

int fromExpressionToPostfixStack(const char *expression, Stack *postfixStack);

int fromStackToValue(Stack *postfixStack, double xVariable, double *pResult);

int fromExpressionToValue(const char *expression, double xVariable,
                          double *result);

#ifdef __cplusplus
}
#endif

#endif // S21_CALC_LIBRARY_H_