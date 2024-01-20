
#include "RefillsWidget.h"

RefillsWidget::RefillsWidget(QWidget *parent)
    : TransactionWidget("Add refill", "Remove refill", parent) {}

int RefillsWidget::setTransactions(DepositParameters *depositParams) const {
  return TransactionWidget::setTransactions(depositParams,
                                            addRefillTransaction);
}
