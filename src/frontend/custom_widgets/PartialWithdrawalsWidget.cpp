#include "PartialWithdrawalsWidget.h"

PartialWithdrawalsWidget::PartialWithdrawalsWidget(QWidget *parent)
    : TransactionWidget("Add withdrawal", "Remove withdrawal", parent) {}

int PartialWithdrawalsWidget::setTransactions(
    DepositParameters *depositParams) const {
  return TransactionWidget::setTransactions(depositParams,
                                            addPartialWithdrawalTransaction);
}
