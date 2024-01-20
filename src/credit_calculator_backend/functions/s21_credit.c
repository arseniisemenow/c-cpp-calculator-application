#include "../headers/s21_credit.h"

int isInvalidCreditAmountValue(double amountValue) {
  return (amountValue <= S21_MIN_CREDIT_AMOUNT_VALUE ||
          amountValue >= S21_MAX_CREDIT_AMOUNT_VALUE);
}

int isInvalidCreditInterestRate(double interestRate) {
  return (interestRate <= S21_MIN_INTEREST_RATE);
}

int isInvalidCreditDeadline(int deadline) {
  return (deadline > S21_MAX_MONTH_CREDIT_VALUE);
}

int normalizeCreditParameters(CreditParameters *params) {
  int errorCode = CreditErrorCode_none;

  if (isInvalidCreditAmountValue(params->creditAmount)) {
    errorCode = CreditErrorCode_invalidCreditValue;
  }

  if (isInvalidCreditInterestRate(params->interestRate)) {
    errorCode |= CreditErrorCode_invalidInterestRateValue;
  }

  if (params->termType == TermType_years && !errorCode) {
    params->creditDeadline *= S21_MONTH_IN_YEAR;
    params->termType = TermType_months;
  }

  if (isInvalidCreditDeadline(params->creditDeadline)) {
    errorCode |= CreditErrorCode_deadlineIsTooLong;
  }

  if (!errorCode) {
    params->interestRate /= 100.0;
  }

  return errorCode;
}

double getMonthlyPaymentDifferential(CreditParameters *params) {
  return (params->creditAmount / params->creditDeadline);
}

double getMonthlyInterestPayment(double remainingCredit,
                                 CreditParameters *params) {
  return (remainingCredit * (params->interestRate / S21_MONTH_IN_YEAR));
}

void calculateMonthlyPaymentDifferential(CreditParameters *params,
                                         double *monthlyPayments) {
  double monthlyPrincipalPayment = getMonthlyPaymentDifferential(params);

  double remainingCredit = params->creditAmount;

  for (int monthIndex = 0; monthIndex < params->creditDeadline; monthIndex++) {
    double monthlyInterestPayment =
        getMonthlyInterestPayment(remainingCredit, params);

    monthlyPayments[monthIndex] =
        monthlyPrincipalPayment + monthlyInterestPayment;

    remainingCredit -= monthlyPrincipalPayment;
  }
}

double calculateTotalPayment(CreditParameters *params,
                             const double *monthlyPayments) {
  double totalPayment = 0.0;

  for (int monthIndex = 0; monthIndex < params->creditDeadline; monthIndex++) {
    totalPayment += monthlyPayments[monthIndex];
  }

  return totalPayment;
}

void initCreditResult(CreditResult **result) {
  if (*result) {
    (*result)->monthlyPaymentBegin = 0;
    (*result)->monthlyPaymentEnd = 0;
    (*result)->creditOverpayment = 0;
    (*result)->totalPayment = 0;
  }
};

double getMonthlyInterestRate(CreditParameters *params) {
  return (params->interestRate / S21_MONTH_IN_YEAR);
}

double getBaseForMonthlyPayment(double monthlyInterestRate,
                                int numberOfPayments) {
  return (pow(1.0 + monthlyInterestRate, numberOfPayments));
}

double calculateMonthlyPaymentAnnual(CreditParameters *params,
                                     double monthlyInterestRate, double base) {
  return ((params->creditAmount * monthlyInterestRate * base) / (base - 1.0));
}

void calculateMonthlyPayment(CreditParameters *params, CreditResult *result) {
  initCreditResult(&result);

  double monthlyInterestRate = getMonthlyInterestRate(params);

  int numberOfPayments = params->creditDeadline;

  double *monthlyPayments = calloc(numberOfPayments, sizeof(double));

  if (params->paymentType == CreditPaymentType_annual) {
    double base =
        getBaseForMonthlyPayment(monthlyInterestRate, numberOfPayments);

    result->monthlyPaymentBegin =
        calculateMonthlyPaymentAnnual(params, monthlyInterestRate, base);
    result->monthlyPaymentEnd = result->monthlyPaymentBegin;

    for (int month = 0; month < numberOfPayments; month++) {
      monthlyPayments[month] = result->monthlyPaymentBegin;
    }

  } else if (params->paymentType == CreditPaymentType_differential) {
    calculateMonthlyPaymentDifferential(params, monthlyPayments);
    result->monthlyPaymentBegin = monthlyPayments[0];
    result->monthlyPaymentEnd = monthlyPayments[params->creditDeadline - 1];
  }

  result->totalPayment = calculateTotalPayment(params, monthlyPayments);
  result->creditOverpayment = result->totalPayment - params->creditAmount;

  roundValue(&result->totalPayment, S21_ROUND_VALUE);
  roundValue(&result->creditOverpayment, S21_ROUND_VALUE);
  roundValue(&result->monthlyPaymentBegin, S21_ROUND_VALUE);
  roundValue(&result->monthlyPaymentEnd, S21_ROUND_VALUE);

  free(monthlyPayments);
}

int handleCalculateMonthlyPayment(CreditParameters *params,
                                  CreditResult *result) {
  int errorCode = CreditErrorCode_none;

  errorCode = normalizeCreditParameters(params);

  if (!errorCode) {
    calculateMonthlyPayment(params, result);
  }

  return errorCode;
}
