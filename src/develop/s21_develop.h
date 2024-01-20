#ifndef S21_CALC_DEVELOP_H_
#define S21_CALC_DEVELOP_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "../credit_calculator_backend/headers/s21_credit_calc_library.h"
#include "../deposit_calculator_backend/headers/s21_deposit.h"

#define S21_INTERVAL_TYPE_STRING_NONE "Periodicity of payments is not set"
#define S21_INTERVAL_TYPE_STRING_ONCE "Once"
#define S21_INTERVAL_TYPE_STRING_DAY "One in a day"
#define S21_INTERVAL_TYPE_STRING_WEEK "One in a week"
#define S21_INTERVAL_TYPE_STRING_MONTH "One in a month"
#define S21_INTERVAL_TYPE_STRING_TWO_MONTH "One in a two month"
#define S21_INTERVAL_TYPE_STRING_QUARTER "One in a quarter"
#define S21_INTERVAL_TYPE_STRING_HALF_YEAR "One in a half of year"
#define S21_INTERVAL_TYPE_STRING_YEAR "One in a year"
#define S21_INTERVAL_TYPE_STRING_END "At the end of interval"

#define S21_DEPOSIT_TERM_STRING_NONE "Not set"
#define S21_DEPOSIT_TERM_STRING_DAY "Day"
#define S21_DEPOSIT_TERM_STRING_MONTH "Month"
#define S21_DEPOSIT_TERM_STRING_YEAR "Year"

#define S21_INTERESTED_RATE_TYPE_STRING_NONE "Not set"
#define S21_INTERESTED_RATE_TYPE_STRING_FIX "Fix"
#define S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_DATE "Depends on date"
#define S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_VALUE                       \
  "Depends on deposit value"

void printCreditParams(const char *text, CreditParameters *params);

void printCreditResult(const char *text, CreditResult *result);

void writeStringInterestRateType(char *outputString, InterestRateType type);

void printInterestRate(DepositParameters *params);

void printDate(const char *text, DateType date);

void printDateInString(char *stringDest, DateType date);

void writeStringPeriodicityOfPayments(char *outputString,
                                      IntervalType periodicity);

void writeStringDepositTerm(char *outputString, TermType term);

void printDepositParams(const char *text, DepositParameters *params);
void printDepositResult(const char *text, DepositResult *result);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // S21_CALC_DEVELOP_H_
