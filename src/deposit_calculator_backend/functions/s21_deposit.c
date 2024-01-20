#include "../headers/s21_deposit.h"

double fromTransactionDateTypeToValue(TransactionDateType *transaction) {
  double resultValue = transaction->value;

  if (transaction->transactionType == TransactionType_withdraw) {
    negateDouble(&resultValue);
  }

  return resultValue;
}

double getBalanceChangesForDate(DateType lastDay,
                                TransactionList *transactionList,
                                int *pTransactionIndex) {
  double balanceChanges = S21_INIT_VALUE_DOUBLE;

  TransactionDateType *transaction =
      &transactionList->transactionArray[*pTransactionIndex];

  while (areDatesEqual(lastDay, transaction->date)) {
    (*pTransactionIndex)++;

    balanceChanges += fromTransactionDateTypeToValue(transaction);

    transaction = &transactionList->transactionArray[*pTransactionIndex];
  }

  return balanceChanges;
}

int findFixInterestRate(InterestRateData *interestRateData) {
  int length = interestRateData->interestRateAmount;
  int returnIndex = -1;

  for (int index = 0; index < length && returnIndex == -1; ++index) {
    InterestRateDataType interestRate =
        interestRateData->interestRateData[index];
    if (interestRate.type == InterestRateType_fix) {
      returnIndex = index;
    }
  }

  return returnIndex;
}

double getInterestRateByIndex(InterestRateData *interestRateData, int index) {
  return interestRateData->interestRateData[index].interestRate;
}

int getInterestValueFix(InterestRateData *interestRateData,
                        double *pInterestRate) {
  int flagFound = S21_FLAG_FALSE;
  int index = findFixInterestRate(interestRateData);

  if (index != 1) {
    *pInterestRate = getInterestRateByIndex(interestRateData, index);

    flagFound = S21_FLAG_TRUE;
  }
  return flagFound;
}

double getCurrentInterestRateByIndex(InterestRateData *interestRateData,
                                     int index) {
  return interestRateData->interestRateData[index].aggregatedValue;
}

int isSuitableInterestRate(int isAggregatedValueGreater, int isFirstEntry,
                           double currentRateValue,
                           InterestRateData *interestRateData,
                           int closestIndex) {
  return (isAggregatedValueGreater && !isFirstEntry &&
          currentRateValue >
              interestRateData->interestRateData[closestIndex].aggregatedValue);
}

double getInterestRateAggregatedValue(InterestRateData *interestRateData,
                                      int index) {
  return interestRateData->interestRateData[index].aggregatedValue;
}

int getCurrentInterestValueIndexDependsOnAggregatedValue(
    InterestRateData *interestRateData, double aggregatedValue) {
  int closestIndex = -1;

  for (int index = 0; index < interestRateData->interestRateAmount; ++index) {
    double currentRateValue =
        getCurrentInterestRateByIndex(interestRateData, index);

    int isAggregatedValueGreater = aggregatedValue > currentRateValue;

    int isFirstEntry = closestIndex == -1;

    if (isAggregatedValueGreater && isFirstEntry) {
      closestIndex = index;
    }

    if (isSuitableInterestRate(isAggregatedValueGreater, isFirstEntry,
                               currentRateValue, interestRateData,
                               closestIndex)) {
      closestIndex = index;
    }
  }

  for (int index = 0; index < interestRateData->interestRateAmount; ++index) {
    double currentRateValue =
        getInterestRateAggregatedValue(interestRateData, index);
    double closestRateValue =
        getInterestRateAggregatedValue(interestRateData, index);

    int isAggregatedValueGreaterOrEquals = aggregatedValue >= currentRateValue;
    int isClosestValue = closestRateValue < currentRateValue;

    if (isAggregatedValueGreaterOrEquals && isClosestValue) {
      closestIndex = index;
    }
  }

  return closestIndex;
}

int isDependsOnDayIndexOrSum(InterestRateDataType data) {
  return (data.type &
          (InterestRateType_dependsOnDayIndex | InterestRateType_dependsOnSum));
}

int getInterestValueDependsOnAggregatedValue(InterestRateData *interestRateData,
                                             double *pInterestRate,
                                             double aggregatedValue) {
  int flagFound = S21_FLAG_FALSE;

  if (isDependsOnDayIndexOrSum(interestRateData->interestRateData[0])) {
    int currentRateIndex = getCurrentInterestValueIndexDependsOnAggregatedValue(
        interestRateData, aggregatedValue);

    *pInterestRate = getInterestRateByIndex(interestRateData, currentRateIndex);

    flagFound = S21_FLAG_TRUE;
  }

  return flagFound;
}

int isInterestRateDependsOnSum(InterestRateDataType data) {
  return (data.type == InterestRateType_dependsOnSum);
}

double getInterestRate(DepositParameters *params, int dayIndex) {
  double interestRate = S21_INIT_VALUE_DOUBLE;

  double aggregatedValue = dayIndex;
  if (isInterestRateDependsOnSum(params->interestRate.interestRateData[0])) {
    aggregatedValue = params->depositAmount;
  }

  getInterestValueFix(&params->interestRate, &interestRate);

  getInterestValueDependsOnAggregatedValue(&params->interestRate, &interestRate,
                                           aggregatedValue);

  return interestRate;
}

int getDaysInCurrentMonth(DateType date) {
  DateType startMonth = date;
  DateType startNextMonth = date;

  startMonth.tm_mon = date.tm_mon;
  startNextMonth.tm_mon = date.tm_mon + 1;

  int dayDifference = S21_ZERO_DAYS;

  getDayDifference(startNextMonth, startMonth, &dayDifference);

  return dayDifference;
}

int getDaysInPreviousMonth(DateType date) {
  DateType startMonth = date;
  DateType startNextMonth = date;

  startMonth.tm_mon = date.tm_mon - 1;
  startNextMonth.tm_mon = date.tm_mon;

  int dayDifference = S21_ZERO_DAYS;

  getDayDifference(startNextMonth, startMonth, &dayDifference);

  return dayDifference;
}

int getDaysInCurrentYear(DateType date) {
  DateType startMonth = date;
  DateType startNextMonth = date;

  startMonth.tm_year = date.tm_year;
  startNextMonth.tm_year = date.tm_year + 1;

  int dayDifference = S21_ZERO_DAYS;

  getDayDifference(startNextMonth, startMonth, &dayDifference);

  return dayDifference;
}

double getAverageMonthDurationInThisYear(DateType date) {
  double averageMonthDuration = S21_ZERO_DAYS;

  double daysInYear = getDaysInCurrentYear(date);

  averageMonthDuration = daysInYear / S21_MONTH_IN_YEAR;

  return averageMonthDuration;
}

double getPayment(DateType lastDay, int dayIndex, DepositParameters *params) {
  double resultPayment = S21_INIT_VALUE_DOUBLE;
  double currentInterestRate = getInterestRate(params, dayIndex);

  int daysInPreviousMonth = getDaysInPreviousMonth(lastDay);

  double averageMonthDuration = getAverageMonthDurationInThisYear(lastDay);

  double monthResultCoefficient = daysInPreviousMonth / averageMonthDuration;

  double dayCoefficient =
      (currentInterestRate / (100 * S21_MONTH_IN_YEAR * daysInPreviousMonth));

  double monthCoefficient = (dayCoefficient * daysInPreviousMonth);

  double actualCoefficient = monthCoefficient * monthResultCoefficient;

  if (params->periodicityOfPayments == IntervalType_oneInDay)
    actualCoefficient = dayCoefficient;
  else if (params->periodicityOfPayments == IntervalType_oneInWeek)
    actualCoefficient = dayCoefficient * S21_DAY_IN_WEEK;
  else if (params->periodicityOfPayments == IntervalType_oneInQuarter)
    actualCoefficient =
        dayCoefficient * averageMonthDuration * S21_MONTH_IN_QUARTER;
  else if (params->periodicityOfPayments == IntervalType_oneInHalfYear)
    actualCoefficient =
        dayCoefficient * averageMonthDuration * S21_MONTH_IN_HALF_OF_YEAR;
  else if (params->periodicityOfPayments == IntervalType_oneInYear)
    actualCoefficient =
        dayCoefficient * averageMonthDuration * S21_MONTH_IN_YEAR;
  else if (params->periodicityOfPayments == IntervalType_atTheEndOfInterval)
    actualCoefficient = dayCoefficient;

  resultPayment = params->depositAmount * (actualCoefficient);

  roundValue(&resultPayment, S21_ROUND_VALUE);

  return resultPayment;
}

void handleLastPayment(double *pPaymentSize, PaymentDateArrayType datesPayments,
                       int paymentIndex) {
  if (datesPayments.numberOfRecords - 1 == paymentIndex) {
    *pPaymentSize *= datesPayments.lastCoefficient;
  }
}

int handlePaymentMatch(DepositConfig *config,
                       PaymentDateArrayType datesPayments, DateType currentDay,
                       int *pPaymentIndex, int dayIndex) {
  DepositParameters *params = &config->params;
  DepositResult *result = &config->result;

  int handledFlag = S21_FLAG_FALSE;

  if (areDatesEqual(currentDay, datesPayments.dateArray[*pPaymentIndex])) {
    double paymentSize = 0;
    (*pPaymentIndex)++;
    handledFlag = S21_FLAG_TRUE;

    paymentSize = getPayment(currentDay, dayIndex, params);

    handleLastPayment(&paymentSize, datesPayments, *pPaymentIndex);

    params->interestValue += paymentSize;

    if (params->capitalisationStatus == CapitalisationStatus_on) {
      params->depositAmount += paymentSize;
    }

    logging(params, currentDay, paymentSize, LogType_payment);

    result->intermediateResults.lastAnnualIncome += paymentSize;
  }

  return handledFlag;
}

void performTransactionChanging(DepositParameters *params,
                                double balanceChanges, DateType currentDay) {
  if (params->depositAmount + balanceChanges >= params->minimalBalance) {
    params->depositAmount += balanceChanges;
    logging(params, currentDay, balanceChanges, LogType_balanceChanging);
  } else {
    logging(params, currentDay, balanceChanges,
            LogType_balanceChangingImpossible);
  }
}

int handleTransactionMatch(DepositConfig *depositConfig,
                           TransactionList *transactionList,
                           DateType currentDay, int *pTransactionIndex) {
  int handledFlag = S21_FLAG_FALSE;

  if (areDatesEqual(
          currentDay,
          transactionList->transactionArray[*pTransactionIndex].date)) {
    handledFlag = S21_FLAG_TRUE;

    double balanceChanges = getBalanceChangesForDate(
        currentDay, transactionList, pTransactionIndex);
    performTransactionChanging(&depositConfig->params, balanceChanges,
                               currentDay);
    depositConfig->result.intermediateResults.depositChanges += balanceChanges;
  }

  return handledFlag;
}

int handlePaymentAtTheEndOfInterval(DepositParameters *params,
                                    DateType currentDay, int dayIndex) {
  int handledFlag = S21_FLAG_FALSE;

  if (params->periodicityOfPayments == IntervalType_atTheEndOfInterval) {
    handledFlag = S21_FLAG_TRUE;
    double paymentSize = getPayment(currentDay, dayIndex, params);
    params->interestValue += paymentSize;
  }

  return handledFlag;
}

int isPaymentPeriodicityAtTheEndOfInterval(DepositParameters *params) {
  return params->periodicityOfPayments == IntervalType_atTheEndOfInterval;
}

void handleLastPaymentCapitalisation(DepositParameters *params, int errorCode) {
  if (isPaymentPeriodicityAtTheEndOfInterval(params) && !errorCode) {
    if (params->capitalisationStatus == CapitalisationStatus_on) {
      params->depositAmount += params->interestValue;
    }
    logging(params, params->depositDates.depositFinishDate,
            params->interestValue, LogType_payment);
  }
}

void handleDepositCalculations(DepositConfig *depositConfig,
                               TransactionList *transactionList) {
  DepositParameters *params = &depositConfig->params;

  int errorCode = DepositErrorCode_none;

  PaymentDateArrayType datesPayments = {0};
  DateType currentDay = params->depositDates.depositStartDate;

  DateType lastDay = currentDay;

  int paymentIndex = 0;
  int transactionIndex = 0;

  int depositDuration = 0;

  errorCode =
      getDayDifference(params->depositDates.depositFinishDate,
                       params->depositDates.depositStartDate, &depositDuration);

  if (!errorCode) {
    makeAllTransactions(params, &datesPayments, transactionList);
  }

  for (int dayIndex = 0; dayIndex < depositDuration + 2 && !errorCode;
       ++dayIndex) {
    if (!handlePaymentAtTheEndOfInterval(params, currentDay, dayIndex)) {
      handlePaymentMatch(depositConfig, datesPayments, currentDay,
                         &paymentIndex, dayIndex);

      handleTransactionMatch(depositConfig, transactionList, currentDay,
                             &transactionIndex);
    }

    handleTaxes(depositConfig, lastDay, currentDay);

    lastDay = currentDay;

    addIntervalToTheDate(IntervalType_oneInDay, &currentDay, currentDay);
  }

  handleLastPaymentCapitalisation(params, errorCode);
}

int handleAllTransactions(DepositConfig *depositConfig) {
  DepositParameters *params = &depositConfig->params;
  DepositResult *result = &depositConfig->result;

  int errorCode = DepositErrorCode_none;

  TransactionList transactionList = {0};

  errorCode = initTransactionList(&transactionList);

  if (!errorCode) {
    handleDepositCalculations(depositConfig, &transactionList);

    result->totalDeposit = params->depositAmount;
    if (params->capitalisationStatus == CapitalisationStatus_off) {
      result->totalDeposit += result->allYearsIncome;
    }
  }

  destroyTransactionList(&transactionList);

  return errorCode;
}
