#ifndef S21_TAXES_H_
#define S21_TAXES_H_

#include "s21_deposit_api.h"
#include "s21_deposit_structs.h"

#define S21_INIT_ANNUAL_INCOME_VALUE (0)

int handleTaxes(DepositConfig *depositConfig, DateType lastDay,
                DateType currentDay);

double calculateTaxesFromAnnualInterestValue(DepositConfig *depositConfig,
                                             int year);

double getTaxPercentage(double taxRate);

#endif // S21_TAXES_H_