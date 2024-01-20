#include "../headers/string_processing_functions.h"

void copyCStringFromLineEdit(char *sourceString, QLineEdit *lineEdit) {
  QString qString = lineEdit->text();
  std::string string = qString.toStdString();
  strncpy(sourceString, string.c_str(), S21_BUFFER_SIZE_256 - 1);
}

void copyCStringFromComboBox(char *sourceString, QComboBox *comboBox) {
  QString qString = comboBox->currentText();
  std::string string = qString.toStdString();
  strncpy(sourceString, string.c_str(), S21_BUFFER_SIZE_256 - 1);
}
