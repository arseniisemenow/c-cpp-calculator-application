#include "../headers/s21_log.h"

void writeFileOperation(DateType date, double accruedInterestValue,
                        double refillValue, double depositActualValue) {
  FILE *fPtr = fopen(S21_LOG_LOCATION S21_LOG_NAME, "a+");
  fprintf(fPtr, "%d.%d.%d", date.tm_mday, date.tm_mon, date.tm_year);
  fprintf(fPtr, "%30lf", accruedInterestValue);
  fprintf(fPtr, "%+30lf", refillValue);
  fprintf(fPtr, "%30lf\n", depositActualValue);
  fclose(fPtr);
}

void clearLogFile() {
  FILE *fPtr = fopen(S21_LOG_LOCATION S21_LOG_NAME, "w+");
  fclose(fPtr);
}

void fromDoubleToString(char *string, double value) {
  sprintf(string, "%+.2lf", value);
}

void finishLogFile(DepositResult *result) {
  FILE *fPtr = fopen(S21_LOG_LOCATION S21_LOG_NAME, "a+");

  char allYearsIncomeString[S21_BUFF_SIZE_64] = {'\0'};
  char depositBalanceString[S21_BUFF_SIZE_64] = {'\0'};

  fromDoubleToString(allYearsIncomeString, result->allYearsIncome);
  fromDoubleToString(depositBalanceString, result->totalDeposit);

  fprintf(fPtr, "%s%30s%25s%19s\n", "Summary: ", allYearsIncomeString, "",
          depositBalanceString);

  fclose(fPtr);
}

void clearTaxesLogFile() {
  FILE *fPtr = fopen(S21_TAX_LOG_LOCATION S21_TAX_LOG_NAME, "w+");
  fclose(fPtr);
}

void printDateInStringHuman(char *stringDest, DateType date) {
  snprintf(stringDest, S21_BUFF_SIZE_64, "[%02d.%02d.%d]", date.tm_mday,
           date.tm_mon + 1, date.tm_year + 1900);
}

void writeImpossibleWithdraw(char *string, double value1, double value2) {
  sprintf(string,
          "Withdraw in size %.2lf is impossible - minimal balance (%.2lf)",
          fabs(value1), value2);
}

void fromYearToString(char *string, int value) {
  sprintf(string, "%d", value + 1900);
}

void fromYearToDeadlineString(char *string, int value) {
  sprintf(string, "1 December %d", value + 1 + 1900);
}

void writeEmptyDash(char *string) { sprintf(string, "–"); }

void logging(DepositParameters *params, DateType currentDate,
             double aggregatedValue, LogType logType) {
  char dateString[S21_BUFF_SIZE_64] = {'\0'};
  char paymentString[S21_BUFF_SIZE_64] = {'\0'};
  char balanceChangingString[S21_BUFF_SIZE_128] = {'\0'};
  char depositBalanceString[S21_BUFF_SIZE_64] = {'\0'};

  printDateInStringHuman(dateString, currentDate);

  if (logType == LogType_payment) {
    fromDoubleToString(paymentString, aggregatedValue);
  } else {
    writeEmptyDash(paymentString);
  }

  if (logType == LogType_balanceChanging) {
    fromDoubleToString(balanceChangingString, aggregatedValue);
  } else {
    writeEmptyDash(balanceChangingString);
  }

  if (logType == LogType_balanceChanging) {
    fromDoubleToString(depositBalanceString, params->depositAmount);
  } else if (logType == LogType_balanceChangingImpossible) {
    writeImpossibleWithdraw(balanceChangingString, aggregatedValue,
                            params->minimalBalance);
  } else {
    writeEmptyDash(balanceChangingString);
  }

  FILE *fPtr = fopen(S21_LOG_LOCATION S21_LOG_NAME, "a+");
  fprintf(fPtr, "%s%25s%25s%25s\n", dateString, paymentString,
          balanceChangingString, depositBalanceString);

  fclose(fPtr);
}

void taxesLogging(int year, DepositResult *result, TaxesLogStatus logStatus) {
  char yearString[S21_BUFF_SIZE_64] = {'\0'};
  char incomeString[S21_BUFF_SIZE_64] = {'\0'};
  char taxDeductionString[S21_BUFF_SIZE_64] = {'\0'};
  char incomeAfterDeductionString[S21_BUFF_SIZE_64] = {'\0'};
  char taxAmountString[S21_BUFF_SIZE_64] = {'\0'};
  char deadlineString[S21_BUFF_SIZE_64] = {'\0'};

  fromYearToString(yearString, year);

  fromDoubleToString(incomeString,
                     result->intermediateResults.lastAnnualIncome);

  fromDoubleToString(taxDeductionString,
                     result->intermediateResults.taxDeduction);

  if (logStatus == TaxesLogStatus_yes) {
    fromDoubleToString(incomeAfterDeductionString,
                       result->intermediateResults.incomeAfterDeduction);

    fromDoubleToString(taxAmountString, result->intermediateResults.taxAmount);

    fromYearToDeadlineString(deadlineString, year);

  } else {
    fromDoubleToString(incomeAfterDeductionString, 0);
    fromDoubleToString(taxAmountString, 0);
  }

  FILE *fPtr = fopen(S21_TAX_LOG_LOCATION S21_TAX_LOG_NAME, "a+");

  fprintf(fPtr, "%s%25s%25s%25s%25s%25s\n", yearString, incomeString,
          taxDeductionString, incomeAfterDeductionString, taxAmountString,
          deadlineString);

  fclose(fPtr);
}
