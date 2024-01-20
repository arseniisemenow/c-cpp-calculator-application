#include "headers/s21_aux_funcs.h"

void roundValue(double *pValue, int roundValue) {
  double roundPayment = *pValue;

  roundPayment *= roundValue;

  roundPayment = floor(roundPayment);

  roundPayment /= roundValue;

  *pValue = roundPayment;
}