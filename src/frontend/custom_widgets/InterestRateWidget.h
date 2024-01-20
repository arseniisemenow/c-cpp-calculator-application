#ifndef INTERESTRATEWIDGET_H_
#define INTERESTRATEWIDGET_H_

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "../../deposit_calculator_backend/headers/s21_deposit_calc_library.h"
#include "../headers/front_error_codes.h"
#include "../headers/handle_styles.h"
#include "../headers/parsing_helpers.h"
#include "../headers/string_validator.h"

struct InterestRate {
  QString value1{};
  QString value2{};
  QString comboBoxValue{};

  InterestRate(const QString &v1, const QString &v2, const QString &comboValue)
      : value1(v1), value2(v2), comboBoxValue(comboValue) {}
};

class InterestRateWidget : public QWidget {
  Q_OBJECT

public:
  InterestRateWidget(QWidget *parent = nullptr);

  QVBoxLayout *getLayout() const;

  int setInterestRates(DepositParameters *depositParams) const;

public slots:
  void addLayout();
  void removeLayout();

private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *buttonLayout;
  QPushButton *addButton;
  QPushButton *removeButton;
  QList<QHBoxLayout *> layouts;
};
#endif // INTERESTRATEWIDGET_H_
