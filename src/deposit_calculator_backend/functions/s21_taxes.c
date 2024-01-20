#include "../headers/s21_taxes.h"

int handleTaxes(DepositConfig *depositConfig, DateType lastDay,
                DateType currentDay) {
  DepositParameters *params = &depositConfig->params;
  DepositResult *result = &depositConfig->result;

  int flagYearChange = S21_FLAG_FALSE;

  int isNewYearHasCome = lastDay.tm_year != currentDay.tm_year;

  int isTheEndOfDeposit =
      areDatesEqual(lastDay, params->depositDates.depositFinishDate);

  if (isNewYearHasCome || isTheEndOfDeposit) {
    calculateTaxesFromAnnualInterestValue(depositConfig, lastDay.tm_year);

    double taxAmount = result->intermediateResults.taxAmount;

    if (taxAmount > 0) {
      taxesLogging(lastDay.tm_year, result, TaxesLogStatus_yes);
    } else {
      taxesLogging(lastDay.tm_year, result, TaxesLogStatus_no);
    }

    flagYearChange = S21_FLAG_TRUE;
    result->intermediateResults.lastAnnualIncome = S21_INIT_ANNUAL_INCOME_VALUE;
  }

  return flagYearChange;
}

int isFirstTaxForYear(DepositParameters *params, int year) {
  return params->depositDates.depositStartDate.tm_year == year;
}

double getTaxDeductionForYear(DepositParameters *params, int year) {
  int isFirstTax = isFirstTaxForYear(params, year);

  double taxDeduction = 0;

  if (isFirstTax)
    taxDeduction = 75000;
  else
    taxDeduction = 130000;

  return taxDeduction;
}

double calculateTaxesFromAnnualInterestValue(DepositConfig *depositConfig,
                                             int year) {
  DepositParameters *params = &depositConfig->params;
  DepositResult *result = &depositConfig->result;

  double taxPercentage = getTaxPercentage(params->taxRate);

  double interestAnnualIncome = result->intermediateResults.lastAnnualIncome;

  double taxDeduction = getTaxDeductionForYear(params, year);

  double incomeAfterDeduction = interestAnnualIncome - taxDeduction;

  double taxAmount = incomeAfterDeduction * taxPercentage;

  result->intermediateResults.taxDeduction = taxDeduction;
  result->intermediateResults.incomeAfterDeduction = incomeAfterDeduction;
  result->intermediateResults.taxAmount = taxAmount;
  if (taxAmount > 0)
    result->allYearsTaxes += taxAmount;

  result->allYearsIncome += interestAnnualIncome;

  return taxAmount;
}

double getTaxPercentage(double taxRate) { return (taxRate / 100); }
