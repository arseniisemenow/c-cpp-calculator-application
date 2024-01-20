#include "../headers/get_interval_type.h"

IntervalType getIntervalType(QString string) {
  IntervalType returnValue = IntervalType_oneInMonth;

  if (string == "Once")
    returnValue = IntervalType_atOnce;
  else if (string == "One in month")
    returnValue = IntervalType_oneInMonth;
  else if (string == "One in two months")
    returnValue = IntervalType_oneInTwoMonth;
  else if (string == "One in quarter")
    returnValue = IntervalType_oneInQuarter;
  else if (string == "One in half of year")
    returnValue = IntervalType_oneInHalfYear;
  else if (string == "One in year")
    returnValue = IntervalType_oneInYear;

  return returnValue;
}
