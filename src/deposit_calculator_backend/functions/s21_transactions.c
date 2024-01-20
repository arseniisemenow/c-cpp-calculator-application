#include "../headers/s21_transactions.h"

int makeAllTransactions(DepositParameters *params,
                        PaymentDateArrayType *datesPayments,
                        TransactionList *transactionList) {
  int errorCode = DepositErrorCode_none;

  errorCode = makeArrayOfPayments(params, datesPayments);

  DepositTransactions *depositTransactions = &params->depositTransactions;

  TransactionsDataType *replenishmentsList =
      &depositTransactions->replenishmentsList;
  TransactionsDataType *partialWithdrawalsList =
      &depositTransactions->partialWithdrawalsList;

  int transactionsCount = getTransactionsCount(replenishmentsList);

  for (int i = 0; i < transactionsCount && !errorCode; ++i) {
    TransactionDateArray dateArray = {0};

    errorCode = makeArrayOfTransactions(
        params, &dateArray, replenishmentsList->transactionsData[i]);
    if (!errorCode) {
      summarizeTransactions(transactionList, &dateArray,
                            TransactionType_refill);
    }
  }

  transactionsCount = getTransactionsCount(partialWithdrawalsList);

  for (int i = 0; i < transactionsCount && !errorCode; ++i) {
    TransactionDateArray dateArray = {0};

    errorCode = makeArrayOfTransactions(
        params, &dateArray, partialWithdrawalsList->transactionsData[i]);
    if (!errorCode) {
      summarizeTransactions(transactionList, &dateArray,
                            TransactionType_withdraw);
    }
  }
  if (!errorCode) {
    quickSortDates(transactionList->transactionArray, 0,
                   transactionList->realCount - 1);
  }

  return errorCode;
}

int makeArrayOfPayments(DepositParameters *params,
                        PaymentDateArrayType *dateArray) {
  int errorCode = DepositErrorCode_none;

  int numberOfRecords = getNumberOfRecordsInArrayOfPayments(params);

  errorCode = allocMemoryForDateArray(numberOfRecords, &dateArray->dateArray);

  if (!handleOnePaymentCase(params, dateArray)) {
    dateArray->numberOfRecords = numberOfRecords;

    DateType startDate = {0};
    DateType previousRecord = {0};

    copyDate(&startDate, &params->depositDates.depositStartDate);

    copyDate(&dateArray->dateArray[0], &startDate);

    addIntervalToTheDate(params->periodicityOfPayments,
                         &dateArray->dateArray[0], startDate);

    for (int i = 1; i < numberOfRecords && !errorCode; ++i) {
      copyDate(&previousRecord, &dateArray->dateArray[i - 1]);

      copyDate(&dateArray->dateArray[i], &previousRecord);

      addIntervalToTheDate(params->periodicityOfPayments,
                           &dateArray->dateArray[i], previousRecord);

      mktime(&dateArray->dateArray[i]);
    }

    handleCoefficientForLastPayment(params, dateArray);
  }

  return errorCode;
}

int makeArrayOfTransactions(DepositParameters *params,
                            TransactionDateArray *dateArray,
                            TransactionData transactionData) {
  int errorCode = DepositErrorCode_none;

  int numberOfRecords =
      getNumberOfRecordsInTransactionsArray(params, transactionData);

  dateArray->numberOfRecords = numberOfRecords;

  if (numberOfRecords > S21_ZERO_DAYS) {
    errorCode = allocMemoryForArrayOfTransactions(
        numberOfRecords, &dateArray->transactionDateArray);

    DateType startDate = {0};
    DateType previousRecord = {0};

    copyDate(&startDate, &transactionData.transactionDate);

    copyDate(&dateArray->transactionDateArray[0].date, &startDate);

    dateArray->transactionDateArray[0].value = transactionData.value;

    if (areDatesEqual(dateArray->transactionDateArray[0].date,
                      params->depositDates.depositStartDate)) {
      addIntervalToTheDate(transactionData.transactionPeriodicity,
                           &dateArray->transactionDateArray[0].date, startDate);
    }

    for (int i = 1; i < numberOfRecords; ++i) {
      copyDate(&previousRecord, &dateArray->transactionDateArray[i - 1].date);

      copyDate(&dateArray->transactionDateArray[i].date, &previousRecord);

      dateArray->transactionDateArray[i].value = transactionData.value;

      addIntervalToTheDate(transactionData.transactionPeriodicity,
                           &dateArray->transactionDateArray[i].date,
                           previousRecord);
    }
  }
  return errorCode;
}

int summarizeTransactions(TransactionList *transactionList,
                          TransactionDateArray *dateArray,
                          TransactionType transactionType) {
  int errorCode = DepositErrorCode_none;

  for (int i = 0; i < dateArray->numberOfRecords; ++i) {
    errorCode = pushTransactionList(
        transactionList, dateArray->transactionDateArray[i], transactionType);
  }

  return errorCode;
}

int getNumberOfRecordsInArrayOfPayments(DepositParameters *params) {
  if (params->periodicityOfPayments == IntervalType_atTheEndOfInterval) {
    return S21_ONE_PAYMENT;
  }

  int numberOfRecords = 0;
  int dayDifference = 0;

  int errorCode = DepositErrorCode_none;

  if (!isValidIntervalForPeriodicityOfPayments(params->periodicityOfPayments))
    errorCode =
        DepositErrorCode_periodicityOfPaymentsIsIncorrectForPeriodicityOfPayments;

  DateType depositStart = params->depositDates.depositStartDate;
  DateType depositIntermediate = depositStart;
  DateType depositEnd = {0};

  copyDate(&depositEnd, &params->depositDates.depositFinishDate);

  do {
    errorCode =
        getDayDifference(depositEnd, depositIntermediate, &dayDifference);

    if (dayDifference >= 0 && !errorCode) {
      numberOfRecords++;
    }
    if (!errorCode) {
      addIntervalToTheDate(params->periodicityOfPayments, &depositIntermediate,
                           depositIntermediate);
    }

  } while (dayDifference >= 0 && !errorCode);

  return numberOfRecords;
}

int getNumberOfRecordsInTransactionsArray(DepositParameters *params,
                                          TransactionData transactionData) {
  int numberOfRecords = 0;
  int dayDifference = 0;

  int errorCode = DepositErrorCode_none;
  DateType transactionStart = transactionData.transactionDate;
  DateType depositIntermediate = transactionStart;
  DateType depositEnd = params->depositDates.depositFinishDate;

  int areTransactionDepositDatesEqual =
      areDatesEqual(depositIntermediate, params->depositDates.depositStartDate);

  if (areTransactionDepositDatesEqual) {
    addIntervalToTheDate(transactionData.transactionPeriodicity,
                         &depositIntermediate, depositIntermediate);
  }

  do {
    errorCode =
        getDayDifference(depositEnd, depositIntermediate, &dayDifference);

    if (dayDifference > S21_ZERO_DAYS && !errorCode) {
      numberOfRecords++;
    }

    addIntervalToTheDate(transactionData.transactionPeriodicity,
                         &depositIntermediate, depositIntermediate);

  } while (dayDifference > S21_ZERO_DAYS &&
           transactionData.transactionPeriodicity != IntervalType_atOnce &&
           !errorCode);

  return numberOfRecords;
}

int handleOnePaymentCase(DepositParameters *params,
                         PaymentDateArrayType *dateArray) {
  int numberOfRecords = getNumberOfRecordsInArrayOfPayments(params);

  int isOnePayment = (numberOfRecords == S21_ONE_PAYMENT);
  int isPeriodicityAtTheEndOfInterval =
      (params->periodicityOfPayments == IntervalType_atTheEndOfInterval);

  int isOnePaymentCase = (isOnePayment && isPeriodicityAtTheEndOfInterval);

  if (isOnePaymentCase) {
    dateArray->numberOfRecords = S21_ONE_PAYMENT;
    dateArray->lastCoefficient = S21_MAX_COEFFICIENT;
    copyDate(&dateArray->dateArray[0], &params->depositDates.depositFinishDate);
  }

  return isOnePaymentCase;
}

double getTimeDifference(time_t startTime, time_t finishTime) {
  return (double)startTime - (double)finishTime;
}

double calculateCurrentCoefficient(double secondDifferenceLastFinish,
                                   double secondDifferencePenultimateLast) {
  return S21_INIT_VALUE_COEFFICIENT -
         (secondDifferenceLastFinish / secondDifferencePenultimateLast);
}

void handleCoefficientForLastPayment(DepositParameters *params,
                                     PaymentDateArrayType *dateArray) {
  DateType lastDate = {0};
  int numberOfRecords = getNumberOfRecordsInArrayOfPayments(params);

  copyDate(&lastDate, &dateArray->dateArray[numberOfRecords - 1]);

  dateArray->lastCoefficient = S21_MAX_COEFFICIENT;

  if (areDatesNotEqual(lastDate, params->depositDates.depositFinishDate)) {
    DateType datePenultimate = {0};
    DateType dateLast = {0};
    DateType dateFinishDeposit = {0};

    if (numberOfRecords > 1) {
      copyDate(&datePenultimate, &dateArray->dateArray[numberOfRecords - 2]);
    } else {
      copyDate(&datePenultimate, &params->depositDates.depositStartDate);
    }

    copyDate(&dateLast, &dateArray->dateArray[numberOfRecords - 1]);
    copyDate(&dateFinishDeposit, &params->depositDates.depositFinishDate);

    time_t timePenultimate = mktime(&datePenultimate);
    time_t timeLast = mktime(&dateLast);
    time_t timeFinishDeposit = mktime(&dateFinishDeposit);

    timeFinishDeposit -= timePenultimate;
    timeLast -= timePenultimate;
    timePenultimate -= timePenultimate;

    double secondDifferenceLastFinish =
        getTimeDifference(timeLast, timeFinishDeposit);
    double secondDifferencePenultimateLast =
        getTimeDifference(timeLast, timePenultimate);

    double coefficient = calculateCurrentCoefficient(
        secondDifferenceLastFinish, secondDifferencePenultimateLast);

    if (coefficient == S21_MIN_COEFFICIENT) {
      coefficient = S21_MAX_COEFFICIENT;
    }

    dateArray->lastCoefficient = coefficient;

    copyDate(&dateArray->dateArray[numberOfRecords - 1],
             &params->depositDates.depositFinishDate);
    mktime(&dateArray->dateArray[numberOfRecords - 1]);
  }
}