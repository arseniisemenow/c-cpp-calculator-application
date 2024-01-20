#ifndef STRING_PROCESSING_FUNCTIONS_H_
#define STRING_PROCESSING_FUNCTIONS_H_

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>

#define S21_BUFFER_SIZE_256 (256)

void copyCStringFromLineEdit(char *sourceString, QLineEdit *lineEdit);

void copyCStringFromComboBox(char *sourceString, QComboBox *comboBox);

#endif // STRING_PROCESSING_FUNCTIONS_H_
