#ifndef HANDLE_TAB_SWITCH_H_
#define HANDLE_TAB_SWITCH_H_

#include <QMainWindow>
#include <QPushButton>

#include "handle_styles.h"

#define S21_TAB_BUTTONS_COUNT 4

typedef enum {
  TabIndex_calculator = 0,
  TabIndex_graph = 3,
  TabIndex_credit = 1,
  TabIndex_deposit = 2,
} TabIndex;

void setStyleUnselectedTabButton(QPushButton *button);

void setStyleSelectedTabButton(QPushButton *button);

int handleTabSwitch(QPushButton **tabButtons, QPushButton *clickedButton);

#endif // HANDLE_TAB_SWITCH_H_
