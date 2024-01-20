#ifndef S21_CREDIT_STRUCTS_H_
#define S21_CREDIT_STRUCTS_H_

#include "../../common/headers/s21_common_structs.h"

typedef enum {
  CreditErrorCode_none = 0,
  CreditErrorCode_invalidInput = 1 << 0,
  CreditErrorCode_deadlineIsTooLong = 1 << 1,
  CreditErrorCode_deadlineIsNegativeNumber = 1 << 2,
  CreditErrorCode_invalidCreditValue = 1 << 3,
  CreditErrorCode_invalidInterestRateValue = 1 << 4,
} CreditErrorCode;

typedef enum {
  CreditPaymentType_none = 0,
  CreditPaymentType_annual = 1 << 0,
  CreditPaymentType_differential = 1 << 1,
} CreditPaymentType;

typedef struct {
  double creditAmount;
  int creditDeadline;
  double interestRate;
  CreditPaymentType paymentType;
  TermType termType;
} CreditParameters;

typedef struct {
  double monthlyPaymentBegin;
  double monthlyPaymentEnd;
  double creditOverpayment;
  double totalPayment;
} CreditResult;

#endif // S21_CREDIT_STRUCTS_H_