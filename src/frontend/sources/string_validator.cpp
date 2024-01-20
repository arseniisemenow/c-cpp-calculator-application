#include "../headers/string_validator.h"

bool isDoubleNumber(const QString &input) {
  QRegularExpression pattern("^[-+]?[0-9]*\\.?[0-9]+$");

  QRegularExpressionMatch match = pattern.match(input);

  return match.hasMatch() && match.captured(0) == input;
}

bool isIntNumber(const QString &input) {
  QRegularExpression pattern("^[-+]?\\d+$");

  QRegularExpressionMatch match = pattern.match(input);

  return match.hasMatch() && match.captured(0) == input;
}
