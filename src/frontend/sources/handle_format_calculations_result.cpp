#include "../headers/handle_format_calculations_result.h"

QString doubleToSignificantString(double value) {
  QString str = QString::number(value, 'f', 15);
  bool isDotMatched = false;

  if (str.contains('.')) {
    while ((str.endsWith('0') || str.endsWith('.')) && !isDotMatched) {
      if (str.endsWith('.')) {
        str.chop(1);
        isDotMatched = true;
      }
      if (!isDotMatched) {
        str.chop(1);
      }
    }
  }

  return str;
}
