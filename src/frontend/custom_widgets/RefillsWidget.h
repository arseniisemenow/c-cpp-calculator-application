#ifndef REFILLSWIDGET_H_
#define REFILLSWIDGET_H_

#include "TransactionWidget.h"

class RefillsWidget : public TransactionWidget {
  Q_OBJECT

public:
  RefillsWidget(QWidget *parent = nullptr);
  int setTransactions(DepositParameters *depositParams) const;
};

#endif // REFILLSWIDGET_H_
