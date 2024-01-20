#ifndef S21_CREDIT_H_
#define S21_CREDIT_H_

#include "../../common/headers/s21_aux_funcs.h"
#include "../../common/headers/s21_common_libs.h"
#include "s21_credit_structs.h"

#define S21_MIN_CREDIT_AMOUNT_VALUE (0.0)
#define S21_MAX_CREDIT_AMOUNT_VALUE (999999999999999.0)

#define S21_MIN_INTEREST_RATE (0.0)
#define S21_MAX_INTEREST_RATE (999.0)
#define S21_AVERAGE_DAYS_IN_MONTH (30.45)

#define S21_MAX_YEAR_CREDIT_VALUE (50)
#define S21_MONTH_IN_YEAR (12)
#define S21_MAX_MONTH_CREDIT_VALUE                                             \
  (S21_MAX_YEAR_CREDIT_VALUE * S21_MONTH_IN_YEAR)

int normalizeCreditParameters(CreditParameters *params);

void calculateMonthlyPayment(CreditParameters *params,
                             CreditResult *monthlyPaymentResult);

int handleCalculateMonthlyPayment(CreditParameters *params,
                                  CreditResult *result);

#endif // S21_CREDIT_H_