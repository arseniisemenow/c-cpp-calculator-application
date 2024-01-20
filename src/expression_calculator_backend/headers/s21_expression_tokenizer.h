#ifndef S21_EXPRESSION_TOKENIZER_H_
#define S21_EXPRESSION_TOKENIZER_H_

#include "s21_libs.h"
#include "s21_stack.h"

#define S21_MAX_EXPRESSION_LENGTH 256

#define S21_INIT_TOKEN_INDEX 0

#define S21_SYMBOL_PLUS '+'
#define S21_SYMBOL_DASH '-'
#define S21_SYMBOL_ASTERISK '*'
#define S21_SYMBOL_SLASH '/'
#define S21_SYMBOL_CIRCUMFLEX '^'
#define S21_SYMBOL_PERCENT '%'
#define S21_SYMBOL_OPEN_PARENTHESIS '('
#define S21_SYMBOL_CLOSE_PARENTHESIS ')'

#define S21_STRING_PI "pi"
#define S21_STRING_COS "cos"
#define S21_STRING_SIN "sin"
#define S21_STRING_TAN "tan"
#define S21_STRING_COS_RAD "Cos"
#define S21_STRING_SIN_RAD "Sin"
#define S21_STRING_TAN_RAD "Tan"
#define S21_STRING_ACOS "acos"
#define S21_STRING_ASIN "asin"
#define S21_STRING_ATAN "atan"
#define S21_STRING_SQRT "sqrt"
#define S21_STRING_LN "ln"
#define S21_STRING_LOG "log"
#define S21_STRING_X "x"

int isOperator(char c);

int isWhitespace(char c);

int handleTokenizeCurrentToken(Stack *stack, char *token, int *pTokenIndex,
                               TokenStatus *pTokenStatus);

int handleTokenizeCurrentOperator(Stack *stack, const char *expression,
                                  int symbolIndex, TokenStatus *pTokenStatus);

void writeTokenFromExpression(const char *expression, char *token,
                              int *pSymbolIndex, int *pTokenIndex);

int handleTokenizeCurrentFunction(char *token, Data *data);

int handleTokenizeLastToken(Stack *stack, char *token, int tokenIndex);

int fromExpressionToInfixNotation(const char *expression, Stack *infixNotation);

void pushShell(Stack *infixNotation, Data data, TokenStatus *pTokenStatus);

#endif // S21_EXPRESSION_TOKENIZER_H_