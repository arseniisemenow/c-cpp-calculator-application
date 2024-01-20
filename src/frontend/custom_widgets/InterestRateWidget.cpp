#include "InterestRateWidget.h"

int isEmptyInterestRate(DepositParameters *depositParams, int errorCode) {
  return depositParams->interestRate.interestRateAmount ==
             S21_INIT_TRANSACTIONS_AMOUNT_VALUE &&
         !errorCode;
}

InterestRateWidget::InterestRateWidget(QWidget *parent) : QWidget(parent) {
  mainLayout = new QVBoxLayout(this);

  buttonLayout = new QHBoxLayout();

  addButton = new QPushButton("Add interest rate", this);
  removeButton = new QPushButton("Remove interest rate", this);

  QPushButton *buttons[] = {addButton, removeButton};
  for (int i = 0; i < 2; i++) {
    buttons[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttons[i]->setFixedSize(120, 14);
    setStyleDefaultPushButtonWidget(buttons[i]);
  }

  connect(addButton, &QPushButton::clicked, this,
          &InterestRateWidget::addLayout);
  connect(removeButton, &QPushButton::clicked, this,
          &InterestRateWidget::removeLayout);

  connect(addButton, &QPushButton::clicked,
          [=]() { setStyleDefaultPushButtonWidget(addButton); });

  removeButton->setEnabled(false);

  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(removeButton);

  mainLayout->addLayout(buttonLayout);
}

QVBoxLayout *InterestRateWidget::getLayout() const { return mainLayout; }

int InterestRateWidget::setInterestRates(
    DepositParameters *depositParams) const {
  int errorCode = ErrorCodeFrontDeposit_noError;

  for (const QHBoxLayout *layout : layouts) {
    errorCode = ErrorCodeFrontDeposit_noError;
    QLineEdit *lineEdit1 =
        qobject_cast<QLineEdit *>(layout->itemAt(0)->widget());
    QLineEdit *lineEdit2 =
        qobject_cast<QLineEdit *>(layout->itemAt(1)->widget());
    QComboBox *qComboBox =
        qobject_cast<QComboBox *>(layout->itemAt(2)->widget());

    if (!lineEdit1 || !lineEdit2 || !qComboBox) {
      errorCode = ErrorCodeFrontDeposit_unableToFindChildren;
    }
    if (!errorCode) {
      QString interestRateString = lineEdit1->text();
      QString aggregatedValueString = lineEdit2->text();
      QString interestRateTypeString = qComboBox->currentText();

      if (!isDoubleNumber(interestRateString)) {
        errorCode |= ErrorCodeFrontDeposit_incorrectInterestValue;
        setStyleIncorrectLineEditWidget(lineEdit1);
      }

      if (!isDoubleNumber(aggregatedValueString) &&
          getInterestRate(interestRateTypeString) != InterestRateType_fix) {
        errorCode |= ErrorCodeFrontDeposit_incorrectInterestValue;
        setStyleIncorrectLineEditWidget(lineEdit2);
      }
      if (interestRateString.toDouble() < 0) {
        errorCode |= ErrorCodeFrontDeposit_incorrectInterestValue;
        setStyleIncorrectLineEditWidget(lineEdit1);
      }
      if (!errorCode) {
        InterestRateType interestRateType =
            getInterestRate(interestRateTypeString);
        double interestRateAggregatedValue = interestRateString.toDouble();
        double interestRateValue = interestRateString.toDouble();
        addInterestRate(depositParams, interestRateType,
                        interestRateAggregatedValue, interestRateValue);
      }
    }
  }

  int isEmptyInterestRateFlag = isEmptyInterestRate(depositParams, errorCode);

  if (isEmptyInterestRateFlag) {
    errorCode = ErrorCodeFrontDeposit_zeroInterestRateAmount;
    setStyleIncorrectPushButtonWidget(InterestRateWidget::addButton);
  }

  return errorCode;
}

void InterestRateWidget::addLayout() {
  buttonLayout->setSizeConstraint(QLayout::SetFixedSize);

  QHBoxLayout *layout = new QHBoxLayout;

  QLineEdit *lineEditInterestRateRatio = new QLineEdit();
  QLineEdit *lineEditAggregatedValue = new QLineEdit();
  QComboBox *comboBox = new QComboBox();

  QLineEdit *lineEditArray[] = {lineEditInterestRateRatio,
                                lineEditAggregatedValue};
  comboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  lineEditInterestRateRatio->setMaxLength(3);

  lineEditInterestRateRatio->setFixedSize(35, 14);
  lineEditAggregatedValue->setFixedSize(55, 14);

  connect(lineEditInterestRateRatio, &QLineEdit::textChanged,
          [=]() { setStyleDefaultLineEditWidget(lineEditInterestRateRatio); });

  connect(lineEditAggregatedValue, &QLineEdit::textChanged,
          [=]() { setStyleDefaultLineEditWidget(lineEditAggregatedValue); });

  comboBox->setFixedSize(85, 14);

  for (int i = 0; i < 2; i++) {
    lineEditArray[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setStyleDefaultLineEditWidget(lineEditArray[i]);
  }

  comboBox->addItems({"Fix", "Depends on sum", "Depends on day"});

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  connect(comboBox, &QComboBox::currentIndexChanged, this,
          [=]() { setStyleDefaultLineEditWidget(lineEditAggregatedValue); });
#endif

  setStyleDefaultWidgetComboBox(comboBox);

  layout->addWidget(lineEditInterestRateRatio);
  layout->addWidget(lineEditAggregatedValue);
  layout->addWidget(comboBox);

  layouts.append(layout);
  mainLayout->addLayout(layout);

  lineEditInterestRateRatio->setFocus();

  removeButton->setEnabled(true);

  if (layouts.length() > 2) {
    addButton->setEnabled(false);
    buttonLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

void InterestRateWidget::removeLayout() {
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
