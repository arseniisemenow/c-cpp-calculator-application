#ifndef S21_DEPOSIT_STRUCTS_H_
#define S21_DEPOSIT_STRUCTS_H_

#include "../../common/headers/s21_common_libs.h"
#include "../../common/headers/s21_common_structs.h"

typedef enum {
  DepositErrorCode_none = 0,
  DepositErrorCode_depositAmountIsNegativeNumber = 1 << 0,
  DepositErrorCode_depositAmountIsTooBig = 1 << 1,
  DepositErrorCode_postingPeriodIsTooSmall = 1 << 2,
  DepositErrorCode_postingPeriodIsTooGreat = 1 << 3,
  DepositErrorCode_depositTermIsNotSet = 1 << 4,
  DepositErrorCode_interestListIsFull = 1 << 5,
  DepositErrorCode_periodicityOfPaymentsIsNotSet = 1 << 6,
  DepositErrorCode_capitalisationStatusIsNotSet = 1 << 7,
  DepositErrorCode_valueForRefillTransactionIsTooSmall = 1 << 8,
  DepositErrorCode_valueForRefillTransactionIsTooGreat = 1 << 9,
  DepositErrorCode_intervalForRefillTransactionIsNotSet = 1 << 10,
  DepositErrorCode_refillListIsFull = 1 << 11,
  DepositErrorCode_valueForPartialWithdrawalTransactionIsTooSmall = 1 << 12,
  DepositErrorCode_intervalForPartialWithdrawalTransactionIsNotSet = 1 << 13,
  DepositErrorCode_partialWithdrawalListIsFull = 1 << 14,
  DepositErrorCode_transactionTypeIsNotSet = 1 << 15,
  DepositErrorCode_intervalTypeIsNotSet = 1 << 16,
  DepositErrorCode_valueForTransactionIsTooSmall = 1 << 17,
  DepositErrorCode_valueForTransactionIsTooGreat = 1 << 18,
  DepositErrorCode_valueForTaxIsTooSmall = 1 << 19,
  DepositErrorCode_valueForTaxIsTooGreat = 1 << 20,
  DepositErrorCode_dateIsNegativeNumber = 1 << 21,
  DepositErrorCode_dateIsInvalid = 1 << 22,
  DepositErrorCode_memoryAllocationError = 1 << 23,
  DepositErrorCode_intervalTypeIsIncorrectForThisCase = 1 << 24,
  DepositErrorCode_periodicityOfPaymentsIsIncorrectForPeriodicityOfPayments =
      1 << 25,
  DepositErrorCode_postingPeriodIsIncorrect = 1 << 26,
  DepositErrorCode_minimalValueIsNegativeNumber = 1 << 27,
  DepositErrorCode_minimalValueIsTooBig = 1 << 28,
} DepositErrorCode;

typedef enum {
  IntervalType_none = 0,
  IntervalType_oneInDay = 1 << 0,
  IntervalType_oneInWeek = 1 << 1,
  IntervalType_oneInMonth = 1 << 2,
  IntervalType_oneInTwoMonth = 1 << 3,
  IntervalType_oneInThreeMonth = 1 << 4,
  IntervalType_oneInQuarter = 1 << 4,
  IntervalType_oneInSixMonth = 1 << 5,
  IntervalType_oneInHalfYear = 1 << 5,
  IntervalType_oneInTwelveMonth = 1 << 6,
  IntervalType_oneInYear = 1 << 6,
  IntervalType_atTheEndOfInterval = 1 << 7,
  IntervalType_atOnce = 1 << 8,
  IntervalType_transactions =
      (IntervalType_atOnce | IntervalType_oneInMonth |
       IntervalType_oneInTwoMonth | IntervalType_oneInQuarter |
       IntervalType_oneInHalfYear | IntervalType_oneInYear),
  IntervalType_periodicityOfPayments =
      (IntervalType_atTheEndOfInterval | IntervalType_oneInDay |
       IntervalType_oneInMonth | IntervalType_oneInWeek |
       IntervalType_oneInQuarter | IntervalType_oneInHalfYear |
       IntervalType_oneInYear),
} IntervalType;

typedef enum {
  TransactionType_none = 0,
  TransactionType_refill = 1 << 0,
  TransactionType_withdraw = 1 << 1,
} TransactionType;

typedef enum {
  InterestRateType_none = 0,
  InterestRateType_fix = 1 << 0,
  InterestRateType_dependsOnSum = 1 << 1,
  InterestRateType_dependsOnDayIndex = 1 << 2,
} InterestRateType;

typedef enum {
  CapitalisationStatus_none = 0,
  CapitalisationStatus_on = 1 << 0,
  CapitalisationStatus_off = 1 << 1,
} CapitalisationStatus;

typedef struct tm DateType;

typedef struct {
  int day;
  int month;
  int year;
} RawDate;

typedef struct {
  InterestRateType type;
  double aggregatedValue;
  double interestRate;
} InterestRateDataType;

typedef struct {
  InterestRateDataType interestRateData[10];
  int interestRateAmount;
} InterestRateData;

typedef struct {
  TransactionType transactionType;
  DateType transactionDate;
  IntervalType transactionPeriodicity;
  double value;
} TransactionData;

typedef struct {
  TransactionData transactionsData[10];
  int transactionsAmount;
} TransactionsDataType;

typedef struct {
  DateType depositStartDate;
  DateType depositFinishDate;
} DepositDates;

typedef struct {
  int depositPostingPeriod;
  TermType depositTerm;
} DepositPeriod;

typedef struct {
  TransactionsDataType replenishmentsList;
  TransactionsDataType partialWithdrawalsList;
} DepositTransactions;

typedef struct {
  double depositAmount;
  double interestValue;
  DepositDates depositDates;
  DepositPeriod depositPeriod;
  InterestRateData interestRate;
  IntervalType periodicityOfPayments;
  CapitalisationStatus capitalisationStatus;
  DepositTransactions depositTransactions;
  double taxRate;
  double minimalBalance;
} DepositParameters;

typedef struct {
  double lastAnnualTaxes;
  double lastAnnualIncome;
  double taxDeduction;
  double incomeAfterDeduction;
  double taxAmount;
  double depositChanges;
} IntermediateResults;

typedef struct {
  IntermediateResults intermediateResults;
  double allYearsIncome;
  double allYearsTaxes;
  double totalDeposit;
  double capitalGains;
} DepositResult;

typedef struct {
  double lastCoefficient;
  int numberOfRecords;
  DateType *dateArray;
} PaymentDateArrayType;

typedef struct {
  TransactionType transactionType;
  DateType date;
  double value;
} TransactionDateType;

typedef struct {
  int numberOfRecords;
  TransactionDateType *transactionDateArray;
} TransactionDateArray;

typedef struct {
  DepositParameters params;
  DepositResult result;
} DepositConfig;

#endif // S21_DEPOSIT_STRUCTS_H_