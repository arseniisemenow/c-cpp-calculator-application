#ifndef PARSING_HELPERS_H_
#define PARSING_HELPERS_H_

#include "../../credit_calculator_backend/headers/s21_credit_calc_library.h"
#include "../../deposit_calculator_backend/headers/s21_deposit_calc_library.h"
#include "QMainWindow"

TermType getCreditTermType(char *string);

CreditPaymentType getCreditPaymentType(char *string);

IntervalType getPaymentPeriodicity(QString string);

TermType getDepositTermType(QString string);

InterestRateType getInterestRate(QString string);

IntervalType getIntervalType(QString string);

#endif // PARSING_HELPERS_H_
