#ifndef S21_TEST_H_
#define S21_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CASE_TEST
#define CASE_TEST

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  enum fork_status forkStatus = CK_NOFORK;
  srunner_set_fork_status(runner, forkStatus);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

#endif

#endif
