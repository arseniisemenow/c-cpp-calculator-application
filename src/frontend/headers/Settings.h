#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "../../expression_calculator_backend/headers/s21_calc_library.h"
#include "front_error_codes.h"

namespace Settings {
[[maybe_unused]] static int errorCodeExpression = ErrorCode_noError;
[[maybe_unused]] static int errorCodeVariable = ErrorCode_noError;

[[maybe_unused]] static int errorCodeDomain = ErrorCode_noError;
[[maybe_unused]] static int errorCodeCodomain = ErrorCode_noError;
[[maybe_unused]] static int errorCodeGraph = ErrorCode_noError;

[[maybe_unused]] static int errorCodeCreditAmount = ErrorCode_noError;
[[maybe_unused]] static int errorCodeCreditDeadline = ErrorCode_noError;
[[maybe_unused]] static int errorCodeCreditInterestValue = ErrorCode_noError;

[[maybe_unused]] static int errorCodeDepositAmount = ErrorCode_noError;
[[maybe_unused]] static int errorCodeDepositPlacementPeriod = ErrorCode_noError;
} // namespace Settings

#endif // SETTINGS_H_
