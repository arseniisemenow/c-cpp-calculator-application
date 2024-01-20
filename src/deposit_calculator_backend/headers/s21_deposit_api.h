#ifndef S21_DEPOSIT_API_H_
#define S21_DEPOSIT_API_H_

#include "../../common/headers/s21_common_libs.h"
#include "s21_deposit_structs.h"
#include "s21_log.h"

#define S21_FLAG_FALSE (0)
#define S21_FLAG_TRUE (1)

#define S21_DAY_IN_WEEK (7)
#define S21_MONTH_IN_QUARTER (3)
#define S21_MONTH_IN_HALF_OF_YEAR (6)
#define S21_MONTH_IN_YEAR (12)

#define S21_YEAR_BASE (1900)
#define S21_MKTIME_ERROR (-1)

#define S21_SEC_IN_MIN (60)
#define S21_MIN_IN_HOUR (60)
#define S21_HOUR_IN_DAY (24)
#define S21_SEC_IN_DAY (S21_SEC_IN_MIN * S21_MIN_IN_HOUR * S21_HOUR_IN_DAY)

#define S21_MIN_DAY_VALUE_IN_DATE (1)
#define S21_MIN_VALUE_IN_DATE (0)

#define S21_MIN_VALUE_FOR_ALLOC_MEMORY (1)

#define S21_MIN_TRANSACTION_VALUE (1)
#define S21_MAX_TRANSACTION_VALUE (S21_MAX_DEPOSIT_AMOUNT_VALUE)

#define S21_NEGATIVE_ONE (-1.0)

#define S21_MAX_INTEREST_RATE_AMOUNT (10)
#define S21_MAX_TRANSACTIONS_AMOUNT (10)

#define S21_INIT_VALUE (0)
#define S21_INIT_VALUE_DOUBLE (0)

#define S21_INIT_DEPOSIT_AMOUNT_VALUE (S21_INIT_VALUE)
#define S21_INIT_TRANSACTION_VALUE (S21_INIT_VALUE)
#define S21_INIT_DEPOSIT_POSTING_PERIOD_VALUE (S21_INIT_VALUE)
#define S21_INIT_TRANSACTIONS_AMOUNT_VALUE (S21_INIT_VALUE)
#define S21_INIT_MINIMAL_BALANCE_VALUE (S21_INIT_VALUE_DOUBLE)

#define S21_MIN_TRANSACTION_AMOUNT_VALUE (0.0)
#define S21_MAX_TRANSACTION_AMOUNT_VALUE (999999999999999.0)

#define S21_MIN_DEPOSIT_AMOUNT_VALUE (S21_MIN_TRANSACTION_AMOUNT_VALUE)
#define S21_MAX_DEPOSIT_AMOUNT_VALUE (S21_MAX_TRANSACTION_AMOUNT_VALUE)

#define S21_ZERO_DAYS (0)

#define S21_MIN_DEPOSIT_POSTING_PERIOD_VALUE (1)
#define S21_MAX_DEPOSIT_POSTING_PERIOD_DAYS_VALUE (18250)
#define S21_MAX_DEPOSIT_POSTING_PERIOD_MONTHS_VALUE (600)
#define S21_MAX_DEPOSIT_POSTING_PERIOD_YEARS_VALUE (50)

#define S21_MIN_TAX_VALUE (1e-6)
#define S21_MAX_TAX_VALUE (100)

static const DateType S21_INIT_DATE = {
    .tm_sec = 0,
    .tm_min = 0,
    .tm_hour = 0,
    .tm_mday = 0,
    .tm_mon = 0,
    .tm_year = 0,
    .tm_wday = 0,
    .tm_yday = 0,
    .tm_isdst = 0,
    .tm_gmtoff = 0,
    .tm_zone = 0,
};

void initInterestRate(DepositParameters *params);

void initDepositAmount(DepositParameters *params);

void initDepositPostingPeriod(DepositParameters *params);

void initDepositDate(DepositParameters *params);

void initDepositTerm(DepositParameters *params);

void initPeriodicityOfPayments(DepositParameters *params);

void initCapitalisationStatus(DepositParameters *params);

void initReplenishmentsList(DepositParameters *params);

void initPartialWithdrawalsList(DepositParameters *params);

void initMinimalBalance(DepositParameters *params);

void initDepositParameters(DepositParameters *params);

int setDepositDate(DepositParameters *params, RawDate rawDate);

int setDepositAmount(DepositParameters *params, double value);

int setDepositPostingPeriod(DepositParameters *params, int postingPeriod,
                            TermType term);

int addInterestRate(DepositParameters *params, InterestRateType type,
                    double aggregatedValue, double interestRate);

void initTransactionData(TransactionData *data);

int setPeriodicityOfPayments(DepositParameters *params,
                             IntervalType periodicity);

int setCapitalisationStatus(DepositParameters *params,
                            CapitalisationStatus capitalisationStatus);

int setTransactionType(TransactionData *data, TransactionType type);

int setTransactionDate(TransactionData *data, RawDate rawDate);

int setTransactionInterval(TransactionData *data, IntervalType interval);

int setTransactionValue(TransactionData *data, double value);

int addRefillTransaction(DepositParameters *params, double value,
                         RawDate rawDate, IntervalType interval);

int setDate(RawDate rawDate, DateType *pDate);

int setTax(DepositParameters *params, double taxValue);

void initDepositFinishDate(DepositParameters *params);

void setDepositFinishDate(DepositParameters *params);

void initDate(DateType *date);

void initDepositResults(DepositResult *result);

int getMaxValueForCurrentTermType(TermType term);

int *getReplenishmentsListNextIndex(DepositParameters *params);

int *getPartialWithdrawalsListNextIndex(DepositParameters *params);

int addPartialWithdrawalTransaction(DepositParameters *params, double value,
                                    RawDate rawDate, IntervalType interval);

int getDayDifference(DateType date1, DateType date2, int *pDayDifference);

int getTransactionsCount(TransactionsDataType *transactionsData);

int areDatesNotEqual(DateType date1, DateType date2);

int areDatesEqual(DateType date1, DateType date2);

void copyDate(DateType *dateDest, DateType *dateSrc);

int isDateValid(DateType date);

int isNegativeDate(RawDate rawDate);

int isValidIntervalForPeriodicityOfPayments(IntervalType interval);

int allocMemoryForDateArray(int count, DateType **dateArray);

int allocMemoryForArrayOfTransactions(int count,
                                      TransactionDateType **dateArray);

void negateDouble(double *pValue);

void addIntervalToTheDate(IntervalType interval, DateType *date,
                          DateType previousDate);

int setMinialBalance(DepositParameters *params, double value);

void clearIntermediateResults(IntermediateResults *intermediateResults);

#endif // S21_DEPOSIT_API_H_