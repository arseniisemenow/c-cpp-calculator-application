#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../headers/s21_calc_library.h"
#include "s21_test.h"

#endif

START_TEST(calculation_sin_test1) {
  char *expressionsArray[] = {
      "sin(1)",   "sin(20)",   "sin(1232)", "sin(547)",
      "sin(346)", "sin(6146)", "sin(754)",  "sin(67657)",
  };
  double expectedResultValueArray[] = {
      0.0174524,  0.3420201, 0.4694715, -0.1218693,
      -0.2419218, 0.4383711, 0.5591929, -0.3907311,
  };
  for (int i = 0; i < (int)(sizeof(expectedResultValueArray) /
                            sizeof(expectedResultValueArray[0]));
       ++i) {
    double resultValue = 0;
    char *expression = expressionsArray[i];

    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode) {
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    }
  }
}

END_TEST

START_TEST(calculation_cos_test2) {
  char *expressionsArray[] = {
      "cos(1)",   "cos(20)",   "cos(1232)", "cos(547)",
      "cos(346)", "cos(6146)", "cos(754)",
  };
  double expectedResultValueArray[] = {
      0.9998476, 0.9396926, -0.8829475, -0.9925461,
      0.9702957, 0.8987940, 0.8290375,
  };
  for (int i = 0; i < (int)(sizeof(expectedResultValueArray) /
                            sizeof(expectedResultValueArray[0]));
       ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode) {
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    }
  }
}

END_TEST

START_TEST(calculation_tan_test3) {
  char *expressionsArray[] = {
      "tan(1)",   "tan(20)",   "tan(1232)", "tan(547)",
      "tan(346)", "tan(6146)", "tan(754)",
  };
  double expectedResultValueArray[] = {
      0.0174550,  0.3639702, -0.5317094, 0.1227845,
      -0.2493280, 0.4877325, 0.6745085,
  };
  for (int i = 0; i < (int)(sizeof(expectedResultValueArray) /
                            sizeof(expectedResultValueArray[0]));
       ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode) {
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    }
  }
}

END_TEST

START_TEST(calculation_acos_test4) {
  char *expressionsArray[] = {
      "acos(x)",      "acos(0.1)",   "acos(0)",      "acos(1)",
      "acos(0.14)",   "acos(0.98)",  "acos(0.1245)", "acos(-1.1)",
      "acos(-10102)", "acos(10102)", "acos(1.1)",
  };
  double expectedResultValueArray[] = {
      1.5207754, 1.4706289, 1.5707963, 0.0, 1.4303349, 0.2003348, 1.4459724,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_indeterminateResultForArcCosine,
      ErrorCode_indeterminateResultForArcCosine,
      ErrorCode_indeterminateResultForArcCosine,
      ErrorCode_indeterminateResultForArcCosine,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0.05, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_asin_test5) {
  char *expressionsArray[] = {
      "asin(0.05)",   "asin(0.1)",   "asin(0)",      "asin(1)",
      "asin(0.14)",   "asin(0.98)",  "asin(0.1245)", "asin(-1.1)",
      "asin(-10102)", "asin(10102)", "asin(1.1)",
  };
  double expectedResultValueArray[] = {
      0.0500208, 0.1001674, 0, 1.5707963, 0.1404614, 1.3704614, 0.1248238,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_indeterminateResultForArcSine,
      ErrorCode_indeterminateResultForArcSine,
      ErrorCode_indeterminateResultForArcSine,
      ErrorCode_indeterminateResultForArcSine,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_atan_test6) {
  char *expressionsArray[] = {
      "atan(0.05)",   "atan(0.1)",   "atan(0)",      "atan(1)",
      "atan(0.14)",   "atan(0.98)",  "atan(0.1245)", "atan(-1.1)",
      "atan(-10102)", "atan(10102)", "atan(1.1)",
  };
  double expectedResultValueArray[] = {
      0.0499583, 0.0996686,  0,          0.7853981, 0.1390959, 0.7752974,
      0.1238626, -0.8329812, -1.5706973, 1.5706973, 0.8329812,
  };

  int errorCodeArray[] = {
      ErrorCode_noError, ErrorCode_noError, ErrorCode_noError,
      ErrorCode_noError, ErrorCode_noError, ErrorCode_noError,
      ErrorCode_noError, ErrorCode_noError, ErrorCode_noError,
      ErrorCode_noError, ErrorCode_noError,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_sqrt_test7) {
  char *expressionsArray[] = {
      "sqrt(0.05)", "sqrt(0.1)",  "sqrt(0)",      "sqrt(1)",
      "sqrt(0.14)", "sqrt(0.98)", "sqrt(0.1245)", "sqrt(10102)",
      "sqrt(1.1)",  "sqrt(-0)",   "sqrt(-0.005)", "sqrt(-1.005)",
  };
  double expectedResultValueArray[] = {
      0.2236067, 0.3162277, 0.0,         1.0,       0.3741657,
      0.9899494, 0.3528455, 100.5087060, 1.0488088, 0,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_squareOfNegativeNumber,
      ErrorCode_squareOfNegativeNumber,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_ln_test8) {
  char *expressionsArray[] = {
      "ln(0.05)", "ln(0.5)", "ln(1.5)", "ln(826.156)",
      "ln(15)",   "ln(1)",   "ln(0)",   "ln(-100)",
  };
  double expectedResultValueArray[] = {
      -2.9957322, -0.6931471, 0.4054651, 6.7167836, 2.7080502,
      0.0,        0.0,        0.0,       0.0,       0.0,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_incorrectValueForNaturalLogarithm,
      ErrorCode_incorrectValueForNaturalLogarithm,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_log_test9) {
  char *expressionsArray[] = {
      "log(0.05)", "log(0.5)", "log(1.5)", "log(826.156)",
      "log(15)",   "log(1)",   "log(0)",   "log(-100)",
  };
  double expectedResultValueArray[] = {
      -1.3010299, -0.3010299, 0.1760912, 2.9170620, 1.1760912, 0.0, 0.0, 0.0,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_incorrectValueForCommonLogarithm,
      ErrorCode_incorrectValueForCommonLogarithm,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_operators_test10) {
  char *expressionsArray[] = {
      "1+1",
      "1-1",
      "1235+12314-124124-1",
      "1235+1235*55*0/1000",
      "1235+123/1461",
      "1235+100*100",
      "1235/100000+0.00061*5235/111",
      "1-2-3-4-5-6-7-8-9",
      "1-2+3-4+5-6+7-8+9",
      "1-2/0",
      "0/0",
  };
  double expectedResultValueArray[] = {
      2, 0, -110576, 1235, 1235.0841889, 11235, 0.0411189, -43, 5, 0, 0,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,        ErrorCode_noError,        ErrorCode_noError,
      ErrorCode_noError,        ErrorCode_noError,        ErrorCode_noError,
      ErrorCode_noError,        ErrorCode_noError,        ErrorCode_noError,
      ErrorCode_divisionByZero, ErrorCode_divisionByZero,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_brackets_test11) {
  char *expressionsArray[] = {
      "(1+1)",
      "((1+1) / 2)",
      "(1+1*(100 + 100))",
      "(1+(5*(10*(25/5)-100)-500/5)*10)",
      "(1+(sin(1)*(911*(900/140)-cos(2*(sin(1))))-100*sin(11) / "
      "98765/sin(4))*(100 - (sin(1) ^ 2 + cos(1) ^ 2) + 100))",
      "(1+(sin(1 - (15 * 4) / 5 - (11 + "
      "15))*(911*(900/140)-cos(2*(sin(1))))-100*sin(11) / 98765/sin(4))*(100 - "
      "(sin(1) ^ 2 + cos(1) ^ 2) + 100))",
      "15/(30-39)*(39-30)+(18^2)^2+(((2)^2)^2)^2",
      "100^(15-14)-100^(sin(1-1+(11+11)))+2^(sin(1) ^ 2 + cos(1) ^ 2)",
      "2^(2^(2^2))",
  };
  double expectedResultValueArray[] = {
      2,      1,          201,     -3499, 20336.5213969, -701252.6425399,
      105217, 96.3867655, 65536.0,
  };

  int errorCodeArray[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_mod_test12) {
  char *expressionsArray[] = {
      "(15.15)%2",
      "(1.213 * 7.1793855-2354.1245)%11",
      "(1.213 * 7.1793855-2354.1245)^2",
      "-(1.213 * 7.1793855-2354.1245)^2",
      "-(1.213 * 7.1793855-(-2354.1245))%15",
      "-(1.213 * 7.1793855-(-2354.1245))%0",
  };
  double expectedResultValueArray[] = {
      1.15, -2.4159054, 5500975.7692494, 5500975.7692494, -7.8330946, 0};

  int errorCodeArray[] = {
      ErrorCode_noError, ErrorCode_noError, ErrorCode_noError,
      ErrorCode_noError, ErrorCode_noError, ErrorCode_modulusByZero,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

START_TEST(calculation_unary_operators_test13) {
  char *expressionsArray[] = {
      "-pi",
      "-(-100)",
      "+(-100)",
      "-(+100)",
      "-(-(-(-(100))))",
      "-(-100+(-100) + 100 - (- 100))",
      "-(100)",
      "+100+(+100-(+100))",
      "+100+(+100--(+100))",
      "+100+(+100-(++100))",
      "100++(+100-(+100))",
  };
  double expectedResultValueArray[] = {
      -M_PI, 100, -100, -100, 100, 0, -100, 100, 0, 0, 0,
  };

  int errorCodeArray[] = {
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_noError,
      ErrorCode_twoOperatorsInARow,
      ErrorCode_twoOperatorsInARow,
      ErrorCode_twoOperatorsInARow,
      ErrorCode_twoOperatorsInARow,
  };
  for (int i = 0;
       i < (int)(sizeof(expressionsArray) / sizeof(expressionsArray[0])); ++i) {
    double resultValue;
    char *expression = expressionsArray[i];
    double expectedResultValue = expectedResultValueArray[i];

    int errorCode = ErrorCode_noError;

    errorCode = fromExpressionToValue(expression, 0, &resultValue);
    if (!errorCode)
      ck_assert_double_eq_tol(resultValue, expectedResultValue, S21_EPSILON);
    else
      ck_assert_int_eq(errorCode, errorCodeArray[i]);
  }
}

END_TEST

Suite *calculation_test(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("calculation_test");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, calculation_sin_test1);
  tcase_add_test(tc_core, calculation_cos_test2);
  tcase_add_test(tc_core, calculation_tan_test3);
  tcase_add_test(tc_core, calculation_acos_test4);
  tcase_add_test(tc_core, calculation_asin_test5);
  tcase_add_test(tc_core, calculation_atan_test6);
  tcase_add_test(tc_core, calculation_sqrt_test7);
  tcase_add_test(tc_core, calculation_ln_test8);
  tcase_add_test(tc_core, calculation_log_test9);
  tcase_add_test(tc_core, calculation_operators_test10);
  tcase_add_test(tc_core, calculation_brackets_test11);
  tcase_add_test(tc_core, calculation_mod_test12);
  tcase_add_test(tc_core, calculation_unary_operators_test13);
  suite_add_tcase(s, tc_core);
  return s;
}
