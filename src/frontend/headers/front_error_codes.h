#ifndef FRONT_ERROR_CODES_H_
#define FRONT_ERROR_CODES_H_

typedef enum {
  ErrorCodeFrontDeposit_noError = 0,
  ErrorCodeFrontDeposit_incorrectInterestValue = 1 << 0,
  ErrorCodeFrontDeposit_incorrectInterestRateType = 1 << 1,
  ErrorCodeFrontDeposit_unableToFindChildren = 1 << 2,
  ErrorCodeFrontDeposit_incorrectTransactionValue = 1 << 3,
  ErrorCodeFrontDeposit_zeroInterestRateAmount = 1 << 4,
  ErrorCodeFrontDeposit_incorrectDepositValue = 1 << 5,
  ErrorCodeFrontDeposit_incorrectPlacementPeriod = 1 << 6,
} ErrorCodeFrontDeposit;

typedef enum {
  ErrorCodeFrontGraph_none = 0,
  ErrorCodeFrontGraph_invalidValueForDomain = 1 << 0,
  ErrorCodeFrontGraph_invalidValueForCodomain = 1 << 1,
} ErrorCodeFrontGraph;

#endif // FRONT_ERROR_CODES_H_
