#include "TransactionWidget.h"

TransactionWidget::TransactionWidget(const QString &addButtonLabel,
                                     const QString &removeButtonLabel,
                                     QWidget *parent)
    : QWidget(parent) {
  mainLayout = new QVBoxLayout(this);

  buttonLayout = new QHBoxLayout();

  addButton = new QPushButton(addButtonLabel, this);
  removeButton = new QPushButton(removeButtonLabel, this);

  QPushButton *buttons[] = {addButton, removeButton};

  for (int i = 0; i < 2; i++) {
    buttons[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttons[i]->setFixedSize(120, 14);
    setStyleDefaultPushButtonWidget(buttons[i]);
  }

  connect(addButton, &QPushButton::clicked, this,
          &TransactionWidget::addLayout);
  connect(removeButton, &QPushButton::clicked, this,
          &TransactionWidget::removeLayout);

  removeButton->setEnabled(false);

  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(removeButton);

  mainLayout->addLayout(buttonLayout);
}

QVBoxLayout *TransactionWidget::getLayout() const { return mainLayout; }

void TransactionWidget::addLayout() {
  buttonLayout->setSizeConstraint(QLayout::SetFixedSize);

  QHBoxLayout *layout = new QHBoxLayout;

  QComboBox *comboBox = new QComboBox();
  QDateEdit *transactionDate = new QDateEdit();
  QLineEdit *transactionAmount = new QLineEdit();

  comboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  transactionDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  transactionAmount->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  transactionAmount->setMaxLength(25);

  comboBox->setFixedSize(90, 14);
  transactionDate->setFixedSize(55, 14);
  transactionAmount->setFixedSize(90, 14);

  transactionDate->setButtonSymbols(QAbstractSpinBox::NoButtons);
  setStyleDefaultDateEditWidget(transactionDate);
  setCurrentDate(transactionDate);

  connect(transactionAmount, &QLineEdit::textChanged,
          [=]() { setStyleDefaultLineEditTransaction(transactionAmount); });

  setStyleDefaultLineEditTransaction(transactionAmount);

  comboBox->addItems({"Once", "One in month", "One in two months",
                      "One in quarter", "One in half of year", "One in year"});
  comboBox->setCurrentIndex(1);

  setStyleDefaultWidgetComboBox(comboBox);

  layout->addWidget(comboBox);
  layout->addWidget(transactionDate);
  layout->addWidget(transactionAmount);

  layouts.append(layout);
  mainLayout->addLayout(layout);

  transactionAmount->setFocus();

  removeButton->setEnabled(true);

  if (layouts.length() > 2) {
    addButton->setEnabled(false);
    buttonLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

void TransactionWidget::removeLayout() {
  if (!layouts.isEmpty()) {
    QLayout *layout = layouts.takeLast();

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
      QWidget *widget = item->widget();
      if (widget) {
        widget->hide();
        delete widget;
      }
      delete item;
    }
    mainLayout->removeItem(layout);
    delete layout;

    if (layouts.isEmpty()) {
      removeButton->setEnabled(false);

      buttonLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    }
  }
  if (layouts.length() < 3) {
    addButton->setEnabled(true);
    buttonLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

int TransactionWidget::setTransactions(
    DepositParameters *depositParams,
    std::function<void(DepositParameters *, double, RawDate, IntervalType)>
        addTransaction) const {
  int errorCode = ErrorCodeFrontDeposit_noError;
  int returnErrorCode = ErrorCodeFrontDeposit_noError;

  for (const QHBoxLayout *layout : layouts) {
    auto *transactionPeriodicityElement =
        qobject_cast<QComboBox *>(layout->itemAt(0)->widget());
    auto *transactionDateElement =
        qobject_cast<QDateEdit *>(layout->itemAt(1)->widget());
    auto *transactionAmountElement =
        qobject_cast<QLineEdit *>(layout->itemAt(2)->widget());

    if (!transactionPeriodicityElement || !transactionDateElement ||
        !transactionAmountElement) {
      errorCode = ErrorCodeFrontDeposit_unableToFindChildren;
    }

    if (!errorCode) {
      QString transactionPeriodicityString =
          transactionPeriodicityElement->currentText();
      QDate transactionDate = transactionDateElement->date();
      RawDate rawDate = {transactionDate.day(), transactionDate.month() - 1,
                         transactionDate.year()};
      QString transactionAmount = transactionAmountElement->text();

      if (!isDoubleNumber(transactionAmount)) {
        errorCode = ErrorCodeFrontDeposit_incorrectTransactionValue;
        setStyleIncorrectLineEditWidget(transactionAmountElement);
      }

      if (!errorCode) {
        double transactionAmountValue = transactionAmount.toDouble();
        if (transactionAmountValue < S21_MIN_TRANSACTION_AMOUNT_VALUE ||
            transactionAmountValue > S21_MAX_TRANSACTION_AMOUNT_VALUE) {
          errorCode = ErrorCodeFrontDeposit_incorrectTransactionValue;
          setStyleIncorrectLineEditWidget(transactionAmountElement);
        } else {
          IntervalType interval = getIntervalType(transactionPeriodicityString);
          addTransaction(depositParams, transactionAmountValue, rawDate,
                         interval);
        }
      }
    }
    returnErrorCode |= errorCode;
  }

  return returnErrorCode;
}
