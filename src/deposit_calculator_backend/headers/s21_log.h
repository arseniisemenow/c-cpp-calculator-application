#ifndef S21_LOG_H_
#define S21_LOG_H_

#include "../../common/headers/s21_common_libs.h"
#include "s21_deposit_structs.h"

#define S21_LOG_NAME "deposit.log"
#define S21_LOG_LOCATION "./"

#define S21_TAX_LOG_NAME "taxes.log"
#define S21_TAX_LOG_LOCATION "./"

typedef enum {
  LogType_none = 0,
  LogType_payment = 1 << 0,
  LogType_balanceChanging = 1 << 1,
  LogType_balanceChangingImpossible = 1 << 2,
} LogType;

typedef enum {
  TaxesLogStatus_none = 0,
  TaxesLogStatus_yes = 1 << 1,
  TaxesLogStatus_no = 1 << 2,
} TaxesLogStatus;

void writeFileOperation(DateType date, double accruedInterestValue,
                        double refillValue, double depositActualValue);

void clearLogFile();

void clearTaxesLogFile();

void printDateInStringHumanFormat(char *stringDest, DateType date);

void logging(DepositParameters *params, DateType currentDate,
             double aggregatedValue, LogType logType);

void taxesLogging(int year, DepositResult *result, TaxesLogStatus);

void finishLogFile(DepositResult *result);

#endif // S21_LOG_H_