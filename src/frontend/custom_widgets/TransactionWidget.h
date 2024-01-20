#ifndef TRANSACTIONWIDGET_H_
#define TRANSACTIONWIDGET_H_

#include <QComboBox>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "../../deposit_calculator_backend/headers/s21_deposit_calc_library.h"
#include "../headers/front_error_codes.h"
#include "../headers/get_interval_type.h"
#include "../headers/handle_styles.h"
#include "../headers/set_current_date.h"
#include "../headers/string_validator.h"

class TransactionWidget : public QWidget {
  Q_OBJECT

public:
  TransactionWidget(const QString &addButtonLabel,
                    const QString &removeButtonLabel,
                    QWidget *parent = nullptr);

  QVBoxLayout *getLayout() const;

  virtual int setTransactions(
      DepositParameters *depositParams,
      std::function<void(DepositParameters *, double, RawDate, IntervalType)>
          addTransaction) const;

  QList<QHBoxLayout *> layouts;

public slots:
  void addLayout();
  void removeLayout();

private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *buttonLayout;
  QPushButton *addButton;
  QPushButton *removeButton;
};

#endif // TRANSACTIONWIDGET_H_
