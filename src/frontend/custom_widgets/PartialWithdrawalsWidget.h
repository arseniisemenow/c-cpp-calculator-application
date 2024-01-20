#ifndef PARTIALWITHDRAWALSWIDGET_H_
#define PARTIALWITHDRAWALSWIDGET_H_

#include "TransactionWidget.h"

class PartialWithdrawalsWidget : public TransactionWidget {
  Q_OBJECT

public:
  PartialWithdrawalsWidget(QWidget *parent = nullptr);
  int setTransactions(DepositParameters *depositParams) const;
};

#endif // PARTIALWITHDRAWALSWIDGET_H_
