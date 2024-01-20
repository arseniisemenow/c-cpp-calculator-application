#include "main_test.h"

int main() {
  int errcode = 0;
  case_test(calculation_test(), &errcode);
  return errcode;
}
