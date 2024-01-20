#include "./s21_develop.h"

void printCreditParams(const char *text, CreditParameters *params) {
  printf("<== %s ==>\n", text);
  printf("params->sumOfCredit: %.2lf\n", params->creditAmount);
  printf("params->creditDeadline: %d\n", params->creditDeadline);
  printf("params->interestRate: %.2lf\n", params->interestRate);
  printf("params->paymentType: %d\n", params->paymentType);
  printf("params->TermType: %d\n", params->termType);
  printf("<== end ==>\n");
}

void printCreditResult(const char *text, CreditResult *result) {
  printf("<== %s ==>\n", text);
  printf("result->monthlyPaymentBegin: %.2lf\n", result->monthlyPaymentBegin);
  printf("result->monthlyPaymentEnd: %.2lf\n", result->monthlyPaymentEnd);
  printf("result->creditOverpayment: %.2lf\n", result->creditOverpayment);
  printf("result->totalPayment: %.2lf\n", result->totalPayment);
  printf("<== end ==>\n");
}

void writeStringPeriodicityOfPayments(char *outputString,
                                      IntervalType periodicity) {
  if (periodicity == IntervalType_atOnce)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_ONCE,
            strlen(S21_INTERVAL_TYPE_STRING_ONCE));
  else if (periodicity == IntervalType_oneInDay)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_DAY,
            strlen(S21_INTERVAL_TYPE_STRING_DAY));
  else if (periodicity == IntervalType_oneInWeek)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_WEEK,
            strlen(S21_INTERVAL_TYPE_STRING_WEEK));
  else if (periodicity == IntervalType_oneInMonth)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_MONTH,
            strlen(S21_INTERVAL_TYPE_STRING_MONTH));
  else if (periodicity == IntervalType_oneInTwoMonth)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_TWO_MONTH,
            strlen(S21_INTERVAL_TYPE_STRING_TWO_MONTH));
  else if (periodicity == IntervalType_oneInQuarter)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_QUARTER,
            strlen(S21_INTERVAL_TYPE_STRING_QUARTER));
  else if (periodicity == IntervalType_oneInHalfYear)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_HALF_YEAR,
            strlen(S21_INTERVAL_TYPE_STRING_HALF_YEAR));
  else if (periodicity == IntervalType_oneInYear)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_YEAR,
            strlen(S21_INTERVAL_TYPE_STRING_YEAR));
  else if (periodicity == IntervalType_atTheEndOfInterval)
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_END,
            strlen(S21_INTERVAL_TYPE_STRING_END));
  else
    strncpy(outputString, S21_INTERVAL_TYPE_STRING_NONE,
            strlen(S21_INTERVAL_TYPE_STRING_NONE));
}

void writeStringDepositTerm(char *outputString, TermType term) {
  if (term == TermType_days)
    strncpy(outputString, S21_DEPOSIT_TERM_STRING_DAY,
            strlen(S21_DEPOSIT_TERM_STRING_DAY));
  else if (term == TermType_months)
    strncpy(outputString, S21_DEPOSIT_TERM_STRING_MONTH,
            strlen(S21_DEPOSIT_TERM_STRING_MONTH));
  else if (term == TermType_years)
    strncpy(outputString, S21_DEPOSIT_TERM_STRING_YEAR,
            strlen(S21_DEPOSIT_TERM_STRING_YEAR));
  else
    strncpy(outputString, S21_DEPOSIT_TERM_STRING_NONE,
            strlen(S21_DEPOSIT_TERM_STRING_NONE));
}

void writeStringInterestRateType(char *outputString, InterestRateType type) {
  if (type == InterestRateType_fix)
    strncpy(outputString, S21_INTERESTED_RATE_TYPE_STRING_FIX,
            strlen(S21_INTERESTED_RATE_TYPE_STRING_FIX));
  else if (type == InterestRateType_dependsOnDayIndex)
    strncpy(outputString, S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_DATE,
            strlen(S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_DATE));
  else if (type == InterestRateType_dependsOnSum)
    strncpy(outputString, S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_VALUE,
            strlen(S21_INTERESTED_RATE_TYPE_STRING_DEPENDS_ON_VALUE));
  else
    strncpy(outputString, S21_INTERESTED_RATE_TYPE_STRING_NONE,
            strlen(S21_INTERESTED_RATE_TYPE_STRING_NONE));
}

void printInterestRate(DepositParameters *params) {
  InterestRateData *interestRate = &params->interestRate;
  int count = interestRate->interestRateAmount;

  if (count > 0)
    printf("Interest rate list:\n\n");
  else
    printf("No provided interest rate list\n");

  for (int i = 0; i < count; ++i) {
    char stringForInterestRateType[100] = {0}; // TODO move buff size
    writeStringInterestRateType(stringForInterestRateType,
                                interestRate->interestRateData[i].type);
    printf("\tInterest rate index [%d]\n", i);
    printf("\tinterest type: [%s]\n", stringForInterestRateType);
    printf("\tinterest rate: [%lf]\n",
           interestRate->interestRateData[i].interestRate);
    printf("\tinterest aggregated value: [%lf]\n",
           interestRate->interestRateData[i].aggregatedValue);
    putchar('\n');
  }
}

void printDateInString(char *stringDest, DateType date) {
  snprintf(stringDest, S21_BUFF_SIZE_64 - 1, "[%d/%d/%d]", date.tm_mday,
           date.tm_mon, date.tm_year);
}

void printDate(const char *text, DateType date) {
  char string[S21_BUFF_SIZE_64] = {'\0'};

  printDateInString(string, date);

  printf("%s: %s\n", text, string);
}

void printTransactions(const char *text,
                       TransactionsDataType transactionsData) {
  printf("<== %s ==>\n\n", text);

  int count = transactionsData.transactionsAmount;
  TransactionData *transactions = transactionsData.transactionsData;

  for (int i = 0; i < count; ++i) {
    char stringIntervalTime[S21_BUFF_SIZE_64] = {'\0'};
    char stringForDate[S21_BUFF_SIZE_64] = {'\0'};
    writeStringPeriodicityOfPayments(stringIntervalTime,
                                     transactions[i].transactionPeriodicity);
    printf("\ttransaction type: [%s]\n",
           transactions[i].transactionType == TransactionType_refill
               ? "Refill"
               : "Withdraw");
    printDateInString(stringForDate, transactions[i].transactionDate);
    printf("\tDate: %s\n", stringForDate);
    printf("\tinterval type: %s\n", stringIntervalTime);
    printf("\tvalue: %lf\n\n", transactions[i].value);
  }
}

void printDepositParams(const char *text, DepositParameters *params) {
  char stringForPeriodicityOfPayments[S21_BUFF_SIZE_128] = {'\0'};
  char stringForDepositTerm[S21_BUFF_SIZE_128] = {'\0'};
  char stringForDate[S21_BUFF_SIZE_128] = {'\0'};
  char stringForFinishDate[S21_BUFF_SIZE_128] = {'\0'};
  writeStringPeriodicityOfPayments(stringForPeriodicityOfPayments,
                                   params->periodicityOfPayments);
  writeStringDepositTerm(stringForDepositTerm,
                         params->depositPeriod.depositTerm);
  printf("<== %s ==>\n", text);
  printf("depositAmount: [%lf]\n", params->depositAmount);
  printf("depositPostingPeriod: [%d], [%s]\n",
         params->depositPeriod.depositPostingPeriod, stringForDepositTerm);
  printDateInString(stringForDate, params->depositDates.depositStartDate);
  printDateInString(stringForFinishDate,
                    params->depositDates.depositFinishDate);
  printf("deposit date: %s\n", stringForDate);
  printf("deposit finish date: %s\n", stringForFinishDate);
  printInterestRate(params);
  printf("periodicity of payments: [%s]\n", stringForPeriodicityOfPayments);
  printf("Capitalisation: [%s]\n",
         params->capitalisationStatus == CapitalisationStatus_on ? "on"
                                                                 : "off");
  printTransactions("refill transactions",
                    params->depositTransactions.replenishmentsList);
  printTransactions("withdrawal transactions",
                    params->depositTransactions.partialWithdrawalsList);

  printf("<== %s end ==>\n", text);
}

void printDepositResult(const char *text, DepositResult *result) {
  printf("<== %s ==>\n", text);
  printf("result->totalDeposit: %lf\n", result->totalDeposit);
  printf("result->allYearsIncome: %lf\n", result->allYearsIncome);
  printf("result->allYearsTaxes: %lf\n", result->allYearsTaxes);
  printf("result->capitalGains: %lf\n", result->capitalGains);
  printf("<== %s end  ==>\n", text);
}