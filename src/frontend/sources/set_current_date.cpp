#include "../headers/set_current_date.h"

void setCurrentDate(QDateEdit *dateEdit) {
  QDate date = QDate::currentDate();
  dateEdit->setDate(date);
}
