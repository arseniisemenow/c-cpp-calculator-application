#ifndef HANDLE_STYLES_H_
#define HANDLE_STYLES_H_

#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

void setStyleDefaultLineEditExpression(QLineEdit *lineEdit);

void setStyleIncorrectLineEditExpression(QLineEdit *lineEdit);

void setStyleDefaultLineEditVariable(QLineEdit *lineEdit);

void setStyleIncorrectLineEditVariable(QLineEdit *lineEdit);

void setStyleDefaultLineEditDomains(QLineEdit *lineEdit);

void setStyleIncorrectLineEditDomains(QLineEdit *lineEdit);

void setStyleDefaultLineEditCredit(QLineEdit *lineEdit);

void setStyleIncorrectLineEditCredit(QLineEdit *lineEdit);

void setStyleDefaultLineEditWidget(QLineEdit *lineEdit);

void setStyleIncorrectLineEditWidget(QLineEdit *lineEdit);

void setStyleDefaultPushButtonWidget(QPushButton *pushButton);

void setStyleIncorrectPushButtonWidget(QPushButton *pushButton);

void setStyleDefaultWidgetComboBox(QComboBox *comboBox);

void setStyleDefaultLineEditTransaction(QLineEdit *lineEdit);

void setStyleIncorrectLineEditRefill(QLineEdit *lineEdit);

void setStyleDefaultDateEditWidget(QDateEdit *dateEdit);

void setStyleDefaultPushButton(QPushButton *pushButton);

void setStyleDefaultLineEditDeposit(QLineEdit *lineEdit);

void setStyleIncorrectLineEditDeposit(QLineEdit *lineEdit);

void setStyleUnselectedTabButton(QPushButton *button);

void setStyleSelectedTabButton(QPushButton *button);

#endif // HANDLE_STYLES_H_
