#include "../headers/parsing_helpers.h"

TermType getCreditTermType(char *string) {
  TermType resultValue = TermType_none;

  if (strcmp(string, "Year") == 0) {
    resultValue = TermType_years;
  } else if (strcmp(string, "Month") == 0) {
    resultValue = TermType_months;
  }

  return resultValue;
}

CreditPaymentType getCreditPaymentType(char *string) {
  CreditPaymentType resultValue = CreditPaymentType_none;

  if (strcmp(string, "Differential") == 0) {
    resultValue = CreditPaymentType_differential;
  } else if (strcmp(string, "Annual") == 0) {
    resultValue = CreditPaymentType_annual;
  }

  return resultValue;
}

IntervalType getPaymentPeriodicity(QString string) {
  IntervalType interval = IntervalType_none;

  if (string == "Every month") {
    interval = IntervalType_oneInMonth;
  } else if (string == "At the end") {
    interval = IntervalType_atTheEndOfInterval;
  } else if (string == "Every day") {
    interval = IntervalType_oneInDay;
  } else if (string == "Every week") {
    interval = IntervalType_oneInWeek;
  } else if (string == "Every quarter") {
    interval = IntervalType_oneInQuarter;
  } else if (string == "Every half of year") {
    interval = IntervalType_oneInHalfYear;
  } else if (string == "Every year") {
    interval = IntervalType_oneInYear;
  }

  return interval;
}

TermType getDepositTermType(QString string) {
  TermType resultValue = TermType_none;

  if (string == "Year") {
    resultValue = TermType_years;
  } else if (string == "Month") {
    resultValue = TermType_months;
  } else if (string == "Day") {
    resultValue = TermType_days;
  }

  return resultValue;
}

InterestRateType getInterestRate(QString string) {
  InterestRateType returnValue = InterestRateType_fix;

  if (string == "Fix") {
    returnValue = InterestRateType_fix;
  } else if (string == "Depends on sum") {
    returnValue = InterestRateType_dependsOnSum;
  } else if (string == "Depends on day") {
    returnValue = InterestRateType_dependsOnDayIndex;
  }

  return returnValue;
}

IntervalType getIntervalType(QString string) {
  IntervalType returnValue = IntervalType_oneInMonth;

  if (string == "Once") {
    returnValue = IntervalType_atOnce;
  } else if (string == "One in month") {
    returnValue = IntervalType_oneInMonth;
  } else if (string == "One in two months") {
    returnValue = IntervalType_oneInTwoMonth;
  } else if (string == "One in quarter") {
    returnValue = IntervalType_oneInQuarter;
  } else if (string == "One in half of year") {
    returnValue = IntervalType_oneInHalfYear;
  } else if (string == "One in year") {
    returnValue = IntervalType_oneInYear;
  }

  return returnValue;
}
