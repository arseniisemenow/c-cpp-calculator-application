#include "../headers/s21_deposit_api.h"

void initInterestRate(DepositParameters *params) {
  InterestRateDataType initRateData = {0};

  for (int i = 0; i < S21_MAX_INTEREST_RATE_AMOUNT; ++i) {
    params->interestRate.interestRateData[i] = initRateData;
  }

  params->interestRate.interestRateAmount = 0;
}

void initDepositAmount(DepositParameters *params) {
  params->depositAmount = S21_INIT_DEPOSIT_AMOUNT_VALUE;
}

void initDepositPostingPeriod(DepositParameters *params) {
  params->depositPeriod.depositPostingPeriod =
      S21_INIT_DEPOSIT_POSTING_PERIOD_VALUE;
}

void initDepositDate(DepositParameters *params) {
  params->depositDates.depositStartDate = S21_INIT_DATE;
}

void initDepositFinishDate(DepositParameters *params) {
  params->depositDates.depositFinishDate = S21_INIT_DATE;
}

void initDepositTerm(DepositParameters *params) {
  params->depositPeriod.depositTerm = TermType_none;
}

void initPeriodicityOfPayments(DepositParameters *params) {
  params->periodicityOfPayments = IntervalType_none;
}

void initInterestValue(DepositParameters *params) { params->interestValue = 0; }

void initDate(DateType *date) {
  date->tm_sec = 0;
  date->tm_min = 0;
  date->tm_hour = 0;
  date->tm_mday = 0;
  date->tm_mon = 0;
  date->tm_year = 0;
  date->tm_wday = 0;
  date->tm_yday = 0;
  date->tm_zone = 0;
  date->tm_gmtoff = 0;
  date->tm_isdst = 0;
}

void initCapitalisationStatus(DepositParameters *params) {
  params->capitalisationStatus = CapitalisationStatus_none;
}

void initReplenishmentsList(DepositParameters *params) {
  TransactionData initRateData = {0};

  for (int i = 0; i < S21_MAX_TRANSACTIONS_AMOUNT; ++i) {
    params->depositTransactions.replenishmentsList.transactionsData[i] =
        initRateData;
  }
  params->depositTransactions.replenishmentsList.transactionsAmount =
      S21_INIT_TRANSACTIONS_AMOUNT_VALUE;
}

void initPartialWithdrawalsList(DepositParameters *params) {
  TransactionData initRateData = {0};

  for (int i = 0; i < S21_MAX_TRANSACTIONS_AMOUNT; ++i) {
    params->depositTransactions.partialWithdrawalsList.transactionsData[i] =
        initRateData;
  }
  params->depositTransactions.partialWithdrawalsList.transactionsAmount =
      S21_INIT_TRANSACTIONS_AMOUNT_VALUE;
}

void initMinimalBalance(DepositParameters *params) {
  params->minimalBalance = S21_INIT_MINIMAL_BALANCE_VALUE;
}

void initDepositParameters(DepositParameters *params) {
  initDepositAmount(params);
  initInterestValue(params);
  initDepositPostingPeriod(params);
  initDepositDate(params);
  initDepositFinishDate(params);
  initDepositTerm(params);
  initInterestRate(params);
  initPeriodicityOfPayments(params);
  initCapitalisationStatus(params);
  initReplenishmentsList(params);
  initPartialWithdrawalsList(params);
  initMinimalBalance(params);
}

void initDepositResults(DepositResult *result) {
  result->intermediateResults.lastAnnualTaxes = S21_INIT_VALUE_DOUBLE;
  result->intermediateResults.lastAnnualIncome = S21_INIT_VALUE_DOUBLE;
  result->allYearsIncome = S21_INIT_VALUE_DOUBLE;
  result->allYearsTaxes = S21_INIT_VALUE_DOUBLE;
  result->totalDeposit = S21_INIT_VALUE_DOUBLE;
  result->capitalGains = S21_INIT_VALUE_DOUBLE;
}

int setDepositAmount(DepositParameters *params, double value) {
  int errorCode = DepositErrorCode_none;

  if (value < S21_MIN_DEPOSIT_AMOUNT_VALUE) {
    errorCode = DepositErrorCode_depositAmountIsNegativeNumber;
  } else if (value > S21_MAX_DEPOSIT_AMOUNT_VALUE) {
    errorCode = DepositErrorCode_depositAmountIsTooBig;
  }
  if (!errorCode) {
    params->depositAmount = value;
  }
  if (!errorCode) {
    logging(params, params->depositDates.depositStartDate, value,
            LogType_balanceChanging);
  }

  return errorCode;
}

int setMinialBalance(DepositParameters *params, double value) {
  int errorCode = DepositErrorCode_none;

  if (value < S21_MIN_DEPOSIT_AMOUNT_VALUE) {
    errorCode = DepositErrorCode_depositAmountIsNegativeNumber;
  } else if (value > S21_MAX_DEPOSIT_AMOUNT_VALUE) {
    errorCode = DepositErrorCode_depositAmountIsTooBig;
  }
  if (!errorCode) {
    params->minimalBalance = value;
  }

  return errorCode;
}

void clearIntermediateResults(IntermediateResults *intermediateResults) {
  intermediateResults->incomeAfterDeduction = 0;
  intermediateResults->lastAnnualTaxes = 0;
  intermediateResults->taxAmount = 0;
}

int setDepositPostingPeriod(DepositParameters *params, int postingPeriod,
                            TermType term) {
  int errorCode = DepositErrorCode_none;
  int maxValueForCurrentTerm = getMaxValueForCurrentTermType(term);

  if (maxValueForCurrentTerm == S21_ZERO_DAYS) {
    errorCode = DepositErrorCode_postingPeriodIsIncorrect;
  } else if (postingPeriod < S21_MIN_DEPOSIT_POSTING_PERIOD_VALUE) {
    errorCode = DepositErrorCode_postingPeriodIsTooSmall;
  } else if (postingPeriod > maxValueForCurrentTerm) {
    errorCode = DepositErrorCode_postingPeriodIsTooGreat;
  }
  if (!errorCode) {
    params->depositPeriod.depositPostingPeriod = postingPeriod;
    params->depositPeriod.depositTerm = term;
  }

  return errorCode;
}

int setDepositDate(DepositParameters *params, RawDate rawDate) {
  int errorCode = DepositErrorCode_none;
  DateType date = S21_INIT_DATE;

  if (isNegativeDate(rawDate)) {
    errorCode = DepositErrorCode_dateIsNegativeNumber;
  }
  if (!errorCode) {
    errorCode = setDate(rawDate, &date);
  }
  if (!errorCode) {
    params->depositDates.depositStartDate = date;
  }

  return errorCode;
}

void setDepositFinishDate(DepositParameters *params) {
  DateType depositEnd = params->depositDates.depositStartDate;

  int depositPostingPeriod = params->depositPeriod.depositPostingPeriod;

  if (params->depositPeriod.depositTerm == TermType_days) {
    depositEnd.tm_mday += depositPostingPeriod;
  } else if (params->depositPeriod.depositTerm == TermType_months) {
    depositEnd.tm_mon += depositPostingPeriod;
  } else if (params->depositPeriod.depositTerm == TermType_years) {
    depositEnd.tm_year += depositPostingPeriod;
  }

  mktime(&depositEnd);
  copyDate(&params->depositDates.depositFinishDate, &depositEnd);
}

int addInterestRate(DepositParameters *params, InterestRateType type,
                    double aggregatedValue, double interestRate) {
  int errorCode = DepositErrorCode_none;
  int *pIndex = &params->interestRate.interestRateAmount;

  if (*pIndex >= S21_MAX_INTEREST_RATE_AMOUNT) {
    errorCode = DepositErrorCode_interestListIsFull;
  }
  if (!errorCode) {
    params->interestRate.interestRateData[*pIndex].type = type;
    params->interestRate.interestRateData[*pIndex].aggregatedValue =
        aggregatedValue;
    params->interestRate.interestRateData[*pIndex].interestRate = interestRate;
    (*pIndex)++;
  }
  return errorCode;
}

int setCapitalisationStatus(DepositParameters *params,
                            CapitalisationStatus capitalisationStatus) {
  int errorCode = DepositErrorCode_none;

  if (capitalisationStatus == CapitalisationStatus_none) {
    errorCode = DepositErrorCode_capitalisationStatusIsNotSet;
  }
  if (!errorCode) {
    params->capitalisationStatus = capitalisationStatus;
  }

  return errorCode;
}

int setTransactionType(TransactionData *data, TransactionType type) {
  int errorCode = DepositErrorCode_none;

  if (type == TransactionType_none) {
    errorCode = DepositErrorCode_transactionTypeIsNotSet;
  }
  if (!errorCode) {
    data->transactionType = type;
  }

  return errorCode;
}

int setTransactionDate(TransactionData *data, RawDate rawDate) {
  int errorCode = DepositErrorCode_none;

  DateType resultDate = {0};

  errorCode = setDate(rawDate, &resultDate);

  if (!errorCode) {
    data->transactionDate = resultDate;
  }

  return errorCode;
}

int setTransactionValue(TransactionData *data, double value) {
  int errorCode = DepositErrorCode_none;

  if (value < S21_MIN_TRANSACTION_VALUE) {
    errorCode = DepositErrorCode_valueForTransactionIsTooSmall;
  } else if (value > S21_MAX_TRANSACTION_VALUE) {
    errorCode = DepositErrorCode_valueForTransactionIsTooGreat;
  }

  if (!errorCode) {
    data->value = value;
  }

  return errorCode;
}

int setDate(RawDate rawDate, DateType *pDate) {
  int errorCode = DepositErrorCode_none;

  pDate->tm_mday = rawDate.day;
  pDate->tm_mon = rawDate.month;
  pDate->tm_year = rawDate.year - S21_YEAR_BASE;

  errorCode = isDateValid(*pDate);

  return errorCode;
}

void initTransactionData(TransactionData *data) {
  data->transactionType = TransactionType_none;
  data->value = S21_INIT_TRANSACTION_VALUE;
  data->transactionPeriodicity = IntervalType_none;
  data->transactionDate = S21_INIT_DATE;
}

int setTransactionInterval(TransactionData *data, IntervalType interval) {
  int errorCode = DepositErrorCode_none;

  if (interval == IntervalType_none) {
    errorCode = DepositErrorCode_intervalTypeIsNotSet;
  }
  if (interval & ~(IntervalType_transactions)) {
    errorCode = DepositErrorCode_intervalTypeIsIncorrectForThisCase;
  }

  if (!errorCode) {
    data->transactionPeriodicity = interval;
  }

  return errorCode;
}

int addRefillTransaction(DepositParameters *params, double value,
                         RawDate rawDate, IntervalType interval) {
  int errorCode = DepositErrorCode_none;
  int *pRefillAmount = getReplenishmentsListNextIndex(params);

  if (*pRefillAmount >= S21_MAX_TRANSACTIONS_AMOUNT) {
    errorCode = DepositErrorCode_refillListIsFull;
  }
  if (!errorCode) {
    TransactionData *newTransaction =
        &params->depositTransactions.replenishmentsList
             .transactionsData[*pRefillAmount];

    initTransactionData(newTransaction);

    errorCode = setTransactionType(newTransaction, TransactionType_refill);
    if (!errorCode) {
      errorCode = setTransactionDate(newTransaction, rawDate);
    }
    if (!errorCode) {
      errorCode = setTransactionInterval(newTransaction, interval);
    }
    if (!errorCode) {
      errorCode = setTransactionValue(newTransaction, value);
    }

    params->depositTransactions.replenishmentsList.transactionsAmount++;
  }

  return errorCode;
}

int addPartialWithdrawalTransaction(DepositParameters *params, double value,
                                    RawDate rawDate, IntervalType interval) {
  int errorCode = DepositErrorCode_none;

  int *pRefillAmount = getPartialWithdrawalsListNextIndex(params);

  TransactionData *transactionList =
      params->depositTransactions.partialWithdrawalsList.transactionsData;

  if (*pRefillAmount >= S21_MAX_TRANSACTIONS_AMOUNT) {
    errorCode = DepositErrorCode_refillListIsFull;
  }
  if (!errorCode) {
    TransactionData *newTransaction = &transactionList[*pRefillAmount];
    initTransactionData(newTransaction);

    errorCode = setTransactionType(newTransaction, TransactionType_withdraw);
    if (!errorCode) {
      errorCode = setTransactionDate(newTransaction, rawDate);
    }
    if (!errorCode) {
      errorCode = setTransactionInterval(newTransaction, interval);
    }
    if (!errorCode) {
      errorCode = setTransactionValue(newTransaction, value);
    }

    params->depositTransactions.partialWithdrawalsList.transactionsAmount++;
  }

  return errorCode;
}

int setTax(DepositParameters *params, double taxValue) {
  int errorCode = DepositErrorCode_none;

  if (taxValue < S21_MIN_TAX_VALUE) {
    errorCode = DepositErrorCode_valueForTaxIsTooSmall;
  } else if (taxValue >= S21_MAX_TAX_VALUE) {
    errorCode = DepositErrorCode_valueForTaxIsTooGreat;
  }

  if (!errorCode) {
    params->taxRate = taxValue;
  }

  return errorCode;
}

int getMaxValueForCurrentTermType(TermType term) {
  int returnValue = 0;

  if (term == TermType_days) {
    returnValue = S21_MAX_DEPOSIT_POSTING_PERIOD_DAYS_VALUE;
  } else if (term == TermType_months) {
    returnValue = S21_MAX_DEPOSIT_POSTING_PERIOD_MONTHS_VALUE;
  } else if (term == TermType_years) {
    returnValue = S21_MAX_DEPOSIT_POSTING_PERIOD_YEARS_VALUE;
  }

  return returnValue;
}

int areDatesNotEqual(DateType date1, DateType date2) {
  return !(areDatesEqual(date1, date2));
}

int areDatesEqual(DateType date1, DateType date2) {
  return (date1.tm_mday == date2.tm_mday && date1.tm_mon == date2.tm_mon &&
          date1.tm_year == date2.tm_year);
}

void copyDate(DateType *dateDest, DateType *dateSrc) {
  dateDest->tm_mday = dateSrc->tm_mday;
  dateDest->tm_mon = dateSrc->tm_mon;
  dateDest->tm_year = dateSrc->tm_year;
}

int isDateValid(DateType date) {
  int errorCode = DepositErrorCode_none;
  DateType dateCopy = {0};

  copyDate(&dateCopy, &date);

  time_t time = mktime(&date);

  DateType convertedDate = *localtime(&time); // TODO test

  if (time == S21_MKTIME_ERROR || areDatesNotEqual(dateCopy, convertedDate)) {
    errorCode = DepositErrorCode_dateIsInvalid;
  }
  return errorCode;
}

int isNegativeDate(RawDate rawDate) {
  return (rawDate.day < S21_MIN_VALUE_IN_DATE ||
          rawDate.month < S21_MIN_VALUE_IN_DATE ||
          rawDate.year < S21_MIN_VALUE_IN_DATE);
}

int isValidIntervalForPeriodicityOfPayments(IntervalType interval) {
  return !(interval & ~(IntervalType_periodicityOfPayments));
}

int setPeriodicityOfPayments(DepositParameters *params,
                             IntervalType periodicity) {
  int errorCode = DepositErrorCode_none;

  if (periodicity == IntervalType_none) {
    errorCode = DepositErrorCode_periodicityOfPaymentsIsNotSet;
  }
  if (!isValidIntervalForPeriodicityOfPayments(periodicity)) {
    errorCode =
        DepositErrorCode_periodicityOfPaymentsIsIncorrectForPeriodicityOfPayments;
  }
  if (!errorCode) {
    params->periodicityOfPayments = periodicity;
  }

  return errorCode;
}

int allocMemoryForDateArray(int count, DateType **dateArray) {
  int errorCode = DepositErrorCode_none;

  if (count < S21_MIN_VALUE_FOR_ALLOC_MEMORY) {
    errorCode = DepositErrorCode_memoryAllocationError;
  }
  if (!errorCode) {
    *dateArray = (DateType *)calloc(count, sizeof(DateType));
  }

  if (!dateArray) {
    errorCode = DepositErrorCode_memoryAllocationError;
  }

  return errorCode;
}

int allocMemoryForArrayOfTransactions(int count,
                                      TransactionDateType **dateArray) {
  int errorCode = DepositErrorCode_none;

  if (count < S21_MIN_VALUE_FOR_ALLOC_MEMORY) {
    errorCode = DepositErrorCode_memoryAllocationError;
  }
  if (!errorCode) {
    *dateArray =
        (TransactionDateType *)calloc(count, sizeof(TransactionDateType));
  }

  if (!dateArray) {
    errorCode = DepositErrorCode_memoryAllocationError;
  }

  return errorCode;
}

int *getReplenishmentsListNextIndex(DepositParameters *params) {
  return &params->depositTransactions.replenishmentsList.transactionsAmount;
}

int *getPartialWithdrawalsListNextIndex(DepositParameters *params) {
  return &params->depositTransactions.partialWithdrawalsList.transactionsAmount;
}

int getDayDifference(DateType date1, DateType date2, int *pDayDifference) {
  int errorCode = DepositErrorCode_none;

  time_t time1 = mktime(&date1);
  time_t time2 = mktime(&date2);

  if (time1 == S21_MKTIME_ERROR || time2 == S21_MKTIME_ERROR) {
    errorCode = DepositErrorCode_dateIsInvalid;
  }

  if (!errorCode) {
    double diffInSeconds = difftime(time1, time2);
    *pDayDifference = (int)(diffInSeconds / (S21_SEC_IN_DAY));
  }

  return errorCode;
}

int getTransactionsCount(TransactionsDataType *transactionsData) {
  return transactionsData->transactionsAmount;
}

void negateDouble(double *pValue) { *pValue *= S21_NEGATIVE_ONE; }

void addIntervalToTheDate(IntervalType interval, DateType *date,
                          DateType previousDate) {
  if (interval == IntervalType_oneInDay) {
    date->tm_mday = previousDate.tm_mday + (1);
  } else if (interval == IntervalType_oneInWeek) {
    date->tm_mday = previousDate.tm_mday + (1 * S21_DAY_IN_WEEK);
  } else if (interval == IntervalType_oneInMonth) {
    date->tm_mon = previousDate.tm_mon + (1);
  } else if (interval == IntervalType_oneInTwoMonth) {
    date->tm_mon = previousDate.tm_mon + (2);
  } else if (interval == IntervalType_oneInQuarter) {
    date->tm_mon = previousDate.tm_mon + (S21_MONTH_IN_QUARTER);
  } else if (interval == IntervalType_oneInHalfYear) {
    date->tm_mon = previousDate.tm_mon + (S21_MONTH_IN_HALF_OF_YEAR);
  } else if (interval == IntervalType_oneInYear) {
    date->tm_year = previousDate.tm_year + (1);
  } else if (interval == IntervalType_atOnce) {
    date->tm_year = previousDate.tm_year + (S21_YEAR_BASE);
  }

  mktime(date);
}
