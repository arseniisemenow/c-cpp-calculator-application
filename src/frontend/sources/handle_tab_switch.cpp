#include "../headers/handle_tab_switch.h"

int handleTabSwitch(QPushButton **tabButtons, QPushButton *clickedButton) {
  int stackedIndex = TabIndex_calculator;

  for (int i = 0; i < S21_TAB_BUTTONS_COUNT; i++)
    setStyleUnselectedTabButton(tabButtons[i]);

  if (clickedButton == tabButtons[TabIndex_calculator]) {
    stackedIndex = TabIndex_calculator;
  } else if (clickedButton == tabButtons[TabIndex_graph]) {
    stackedIndex = TabIndex_graph;
  } else if (clickedButton == tabButtons[TabIndex_credit]) {
    stackedIndex = TabIndex_credit;
  } else if (clickedButton == tabButtons[TabIndex_deposit]) {
    stackedIndex = TabIndex_deposit;
  }

  setStyleSelectedTabButton(clickedButton);
  return stackedIndex;
}
