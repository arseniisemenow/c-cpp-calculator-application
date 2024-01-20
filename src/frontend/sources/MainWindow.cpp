#include "../headers/MainWindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setupUIElements();
  setupConnections();
  setupCustomWidgets();
  configureUIElements();
}

void MainWindow::setupUIElements() {
  ui->stackedWidget->setCurrentIndex(TabIndex_calculator);
  ui->lineEdit->setFocus();
  this->setFixedSize(310, 550);
  this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void MainWindow::setupConnections() {
  connectCalculatorButtons();
  connectTabButtons();
  setupGraphCalculatorElements();
  connectCreditCalculatorElements();
  connectCalculatorFunctionsButtons();
  connectDepositCalculatorElements();

  connect(ui->pushButton_clear, &QPushButton::clicked, this,
          &MainWindow::handleClearButtonClick);
  connect(ui->pushButton_equals, &QPushButton::clicked, this,
          &MainWindow::handleButtonEqualsClick);

  connect(ui->lineEdit, &QLineEdit::returnPressed, this,
          &MainWindow::handleButtonEqualsClick);
  connect(ui->lineEdit, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_lineEdit);

  connect(ui->lineEdit_X, &QLineEdit::returnPressed, this,
          &MainWindow::handleButtonEqualsClick);
  connect(ui->lineEdit_X, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_variable);
}

void MainWindow::setupGraphCalculatorElements() {
  connect(ui->lineEdit_domain, &QLineEdit::returnPressed, this,
          &MainWindow::handleDrawPlot);
  connect(ui->lineEdit_domain, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_domainEdit);

  connect(ui->lineEdit_codomain, &QLineEdit::returnPressed, this,
          &MainWindow::handleDrawPlot);
  connect(ui->lineEdit_codomain, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_codomainEdit);

  connect(ui->pushButton_graph_draw, &QPushButton::clicked, this,
          &MainWindow::handleDrawPlot);

  connect(ui->lineEdit_graph_expression, &QLineEdit::returnPressed, this,
          &MainWindow::handleDrawPlot);
  connect(ui->lineEdit_graph_expression, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_graphExpression);

  connect(ui->pushButton_graph_clear, &QPushButton::clicked, [&]() {
    handleClearGraphButton();
    ui->lineEdit_graph_expression->clear();
  });

  ui->customPlot->xAxis->setRange((-2) * M_PI, (2) * M_PI);
  ui->customPlot->yAxis->setRange((-2) * M_PI, (2) * M_PI);

  ui->customPlot->xAxis->setBasePen(QPen(Qt ::white, 2));
  ui->customPlot->xAxis->setTickPen(QPen(Qt ::gray, 1));
  ui->customPlot->xAxis->setTickLabelColor(Qt ::white);
  ui->customPlot->xAxis->setLabelColor(Qt ::white);
  ui->customPlot->xAxis->setTickLengthOut(1);
  ui->customPlot->xAxis->setTickLengthIn(0);

  ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 2));
  ui->customPlot->yAxis->setTickPen(QPen(Qt::gray, 1));
  ui->customPlot->yAxis->setTickLabelColor(Qt::white);
  ui->customPlot->yAxis->setLabelColor(Qt ::white);
  ui->customPlot->yAxis->setTickLengthOut(1);
  ui->customPlot->yAxis->setTickLengthIn(0);

  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");

  ui->customPlot->xAxis->grid()->setPen(QPen(Qt::gray));
  ui->customPlot->yAxis->grid()->setPen(QPen(Qt::gray));

  QBrush *brush = new QBrush(S21_DARK_GRAY_RGB_COLOR);
  QBrush &linkBrush = *brush;

  ui->customPlot->setBackground(QBrush((linkBrush)));
}

void MainWindow::connectCreditCalculatorElements() {
  connect(ui->pushButton_credit_calculate, &QPushButton::clicked, this,
          &MainWindow::handleButtonCreditCalculate);

  connect(ui->lineEdit_credit_creditAmount, &QLineEdit::returnPressed, this,
          &MainWindow::handleButtonCreditCalculate);
  connect(ui->lineEdit_credit_creditAmount, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_creditAmount);

  connect(ui->lineEdit_credit_creditDeadline, &QLineEdit::returnPressed, this,
          &MainWindow::handleButtonCreditCalculate);
  connect(ui->lineEdit_credit_creditDeadline, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_creditDeadline);

  connect(ui->lineEdit_credit_interestValue, &QLineEdit::returnPressed, this,
          &MainWindow::handleButtonCreditCalculate);
  connect(ui->lineEdit_credit_interestValue, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_interestValue);
  connect(ui->pushButton_credit_clear, &QPushButton::clicked, [=]() {
    clearCreditResult();
    ui->lineEdit_credit_creditAmount->clear();
    ui->lineEdit_credit_creditDeadline->clear();
    ui->lineEdit_credit_interestValue->clear();
    ui->comboBox_credit_paymentsType->setCurrentIndex(0);
  });
}

void MainWindow::connectDepositCalculatorElements() {
  connect(ui->pushButton_deposit_calculate, &QPushButton::clicked, this,
          &MainWindow::handleDepositCalculateButtonClick);

  connect(ui->lineEdit_deposit_depositAmount, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_depositAmount);
  connect(ui->lineEdit_deposit_placementPeriod, &QLineEdit::textChanged, this,
          &MainWindow::handleTextChanged_depositPlacementPeriod);

  connect(ui->lineEdit_deposit_placementPeriod, &QLineEdit::returnPressed, this,
          &MainWindow::handleDepositCalculateButtonClick);
  connect(ui->lineEdit_deposit_depositAmount, &QLineEdit::returnPressed, this,
          &MainWindow::handleDepositCalculateButtonClick);

  connect(ui->pushButton_deposit_clear, &QPushButton::clicked, this,
          &MainWindow::handleDepositClearButtonClick);

  connect(ui->pushButton_deposit_taxes_logs, &QPushButton::clicked, this,
          &MainWindow::handleDepositTaxesLogsButtonClick);
  connect(ui->pushButton_deposit_payments_logs, &QPushButton::clicked, this,
          &MainWindow::handleDepositLogsButtonClick);
  connect(ui->pushButton_deposit_clear, &QPushButton::clicked, [&]() {
    clearDepositResult();
    ui->lineEdit_deposit_depositAmount->clear();
    ui->lineEdit_deposit_placementPeriod->clear();
    setCurrentDate(ui->dateEdit_deposit_depositDate);
    interestRateWidget->removeLayout();
    interestRateWidget->removeLayout();
    interestRateWidget->removeLayout();
    refillsWidget->removeLayout();
    refillsWidget->removeLayout();
    refillsWidget->removeLayout();
    partialWithdrawalsWidget->removeLayout();
    partialWithdrawalsWidget->removeLayout();
    partialWithdrawalsWidget->removeLayout();
    ui->checkBox_deposit_capitalization->setCheckState(Qt::Unchecked);
    ui->comboBox_deposit_paymentsPeriodicity->setCurrentIndex(2);
    ui->comboBox_deposit_placementPeriod->currentIndexChanged(0);
    handleClearLogFiles();
  });
}

void MainWindow::connectCalculatorButtons() {
  QPushButton *expressionCalculatorButtons[] = {ui->pushButton_0,
                                                ui->pushButton_1,
                                                ui->pushButton_2,
                                                ui->pushButton_3,
                                                ui->pushButton_4,
                                                ui->pushButton_5,
                                                ui->pushButton_6,
                                                ui->pushButton_7,
                                                ui->pushButton_8,
                                                ui->pushButton_9,
                                                ui->pushButton_plus,
                                                ui->pushButton_minus,
                                                ui->pushButton_multiply,
                                                ui->pushButton_divide,
                                                ui->pushButton_power,
                                                ui->pushButton_mod,
                                                ui->pushButton_bracket_opened,
                                                ui->pushButton_bracket_closed,
                                                ui->pushButton_dot,
                                                ui->pushButton_variable};

  int buttonsCount = sizeof(expressionCalculatorButtons) /
                     sizeof(expressionCalculatorButtons[0]);

  for (int i = 0; i < buttonsCount; i++) {
    expressionCalculatorButtons[i]->setProperty("isFunction", 0);
    connect(expressionCalculatorButtons[i], &QPushButton::clicked, this,
            &MainWindow::handleInsertButtonClick);
  }
};

void MainWindow::connectTabButtons() {
  QPushButton *tabButtons[] = {
      ui->pushButton_calculator,
      ui->pushButton_credit,
      ui->pushButton_deposit,
      ui->pushButton_graph,
  };

  int buttonsCount = sizeof(tabButtons) / sizeof(tabButtons[0]);

  for (int i = 0; i < buttonsCount; ++i)
    connect(tabButtons[i], &QPushButton::clicked, this,
            &MainWindow::handleTabClick);
};

void MainWindow::connectCalculatorFunctionsButtons() {
  QPushButton *expressionCalculatorFunctionButtons[] = {
      ui->pushButton_cos,  ui->pushButton_sin,  ui->pushButton_tan,
      ui->pushButton_acos, ui->pushButton_asin, ui->pushButton_atan,
      ui->pushButton_sqrt, ui->pushButton_ln,   ui->pushButton_log};

  int buttonsCount = sizeof(expressionCalculatorFunctionButtons) /
                     sizeof(expressionCalculatorFunctionButtons[0]);

  for (int i = 0; i < buttonsCount; i++) {
    expressionCalculatorFunctionButtons[i]->setProperty("isFunction", 1);
    connect(expressionCalculatorFunctionButtons[i], &QPushButton::clicked, this,
            &MainWindow::handleInsertButtonClick);
  }
};

void MainWindow::initializeCustomWidgets() {
  interestRateWidget = new InterestRateWidget(this);
  refillsWidget = new RefillsWidget(this);
  partialWithdrawalsWidget = new PartialWithdrawalsWidget(this);
}

void MainWindow::configureCustomWidgetLayouts() {
  ui->widget_interest_rate->setLayout(interestRateWidget->getLayout());
  ui->widget_refills->setLayout(refillsWidget->getLayout());
  ui->widget_withdrawals->setLayout(partialWithdrawalsWidget->getLayout());
}

void MainWindow::setupCustomWidgets() {
  initializeCustomWidgets();
  configureCustomWidgetLayouts();
}

void MainWindow::configureDateEditWidgets() {
  setCurrentDate(ui->dateEdit_deposit_depositDate);
  ui->dateEdit_deposit_depositDate->setButtonSymbols(QDateEdit::NoButtons);
}

void MainWindow::configureComboBoxes() {
  ui->comboBox_deposit_paymentsPeriodicity->setCurrentIndex(2);
}

void MainWindow::configureUIElements() {
  handleClearLogFiles();
  configureDateEditWidgets();
  configureComboBoxes();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleDepositTaxesLogsButtonClick() {
  system(DEFAULT_OPEN_COMMAND S21_TAX_LOG_LOCATION S21_TAX_LOG_NAME);
}
void MainWindow::handleDepositLogsButtonClick() {
  system(DEFAULT_OPEN_COMMAND S21_LOG_LOCATION S21_LOG_NAME);
}

void MainWindow::handleTabClick() {
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

  QPushButton *tabButtons[] = {
      ui->pushButton_calculator,
      ui->pushButton_credit,
      ui->pushButton_deposit,
      ui->pushButton_graph,
  };

  int stackedIndex = handleTabSwitch(tabButtons, clickedButton);

  if (clickedButton == ui->pushButton_calculator)
    ui->lineEdit->setFocus();
  if (clickedButton == ui->pushButton_credit)
    ui->lineEdit_credit_creditAmount->setFocus();
  if (clickedButton == ui->pushButton_deposit)
    ui->lineEdit_deposit_depositAmount->setFocus();
  if (clickedButton == ui->pushButton_graph)
    ui->lineEdit_graph_expression->setFocus();

  ui->stackedWidget->setCurrentIndex(stackedIndex);
}

void MainWindow::handleDrawPlot() {
  char expressionString[S21_BUFFER_SIZE_256] = {0};
  copyCStringFromLineEdit(expressionString, ui->lineEdit_graph_expression);

  clearCustomPlot();

  int errorCode = ErrorCode_noError;

  errorCode = MainWindow::drawPlot(expressionString);

  if (errorCode) {
    Settings::errorCodeGraph = errorCode;
    setStyleIncorrectLineEditExpression(ui->lineEdit_graph_expression);
  } else {
    Settings::errorCodeGraph = ErrorCode_noError;
    setStyleDefaultLineEditExpression(ui->lineEdit_graph_expression);
  }
}

void MainWindow::handleButtonEqualsClick() {
  char expressionString[S21_BUFFER_SIZE_256] = {0};
  copyCStringFromLineEdit(expressionString, ui->lineEdit);
  int commonErrorCode = ErrorCode_noError;
  double result = 0;
  int errorCode = ErrorCode_noError;
  double variableValue = 0;
  errorCode = getVariableLabelValue(&variableValue);

  if (errorCode) {
    setStyleIncorrectLineEditVariable(ui->lineEdit_X);
    Settings::errorCodeVariable = errorCode;
    commonErrorCode |= errorCode;
  }

  errorCode = fromExpressionToValue(expressionString, variableValue, &result);

  if (errorCode) {
    setStyleIncorrectLineEditExpression(ui->lineEdit);
    Settings::errorCodeExpression = errorCode;
    commonErrorCode |= errorCode;
  }
  if (!commonErrorCode) {
    switchLastCalculationsResult(ui->label_lastCalculations,
                                 ui->label_penultimateCalculations,
                                 ui->label_antePenultimateCalculations,
                                 doubleToSignificantString(result));
    setStyleDefaultLineEditExpression(ui->lineEdit);
  }
}

void MainWindow::handleTextChanged(QLineEdit *lineEdit, int *errorCode) {
  if (*errorCode) {
    if (lineEdit == ui->lineEdit) {
      setStyleDefaultLineEditExpression(lineEdit);
    } else if (lineEdit == ui->lineEdit_X) {
      setStyleDefaultLineEditVariable(lineEdit);
    } else if (lineEdit == ui->lineEdit_domain ||
               lineEdit == ui->lineEdit_codomain) {
      setStyleDefaultLineEditDomains(lineEdit);
    } else if (lineEdit == ui->lineEdit_graph_expression) {
      setStyleDefaultLineEditExpression(lineEdit);
    } else if (lineEdit == ui->lineEdit_credit_creditAmount ||
               lineEdit == ui->lineEdit_credit_creditDeadline ||
               lineEdit == ui->lineEdit_credit_interestValue) {
      setStyleDefaultLineEditCredit(lineEdit);
    } else if (lineEdit == ui->lineEdit_deposit_depositAmount ||
               lineEdit == ui->lineEdit_deposit_placementPeriod)
      setStyleDefaultLineEditDeposit(lineEdit);

    *errorCode = ErrorCode_noError;
  }
}

void MainWindow::handleTextChanged_lineEdit(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit, &Settings::errorCodeExpression);
}

void MainWindow::handleTextChanged_variable(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_X, &Settings::errorCodeVariable);
}

void MainWindow::handleTextChanged_domainEdit(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_domain, &Settings::errorCodeDomain);
}

void MainWindow::handleTextChanged_codomainEdit(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_codomain, &Settings::errorCodeCodomain);
}

void MainWindow::handleTextChanged_graphExpression(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_graph_expression, &Settings::errorCodeGraph);
}

void MainWindow::handleTextChanged_creditAmount(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_credit_creditAmount,
                    &Settings::errorCodeCreditAmount);
}

void MainWindow::handleTextChanged_creditDeadline(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_credit_creditDeadline,
                    &Settings::errorCodeCreditDeadline);
}

void MainWindow::handleTextChanged_interestValue(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_credit_interestValue,
                    &Settings::errorCodeCreditInterestValue);
}
void MainWindow::handleTextChanged_depositAmount(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_deposit_depositAmount,
                    &Settings::errorCodeDepositAmount);
}

void MainWindow::handleTextChanged_depositPlacementPeriod(
    [[maybe_unused]] const QString &inputString) {
  handleTextChanged(ui->lineEdit_deposit_placementPeriod,
                    &Settings::errorCodeDepositPlacementPeriod);
}

int MainWindow::getVariableLabelValue(double *pVariableValue) {
  char expressionString[S21_BUFFER_SIZE_256] = {0};
  copyCStringFromLineEdit(expressionString, ui->lineEdit_X);

  int errorCode = ErrorCode_noError;

  double result = 0;

  if (strlen(expressionString) == 0) {
    errorCode = ErrorCode_invalidExpressionFormat;
  }
  if (!errorCode) {
    errorCode = fromExpressionToValue(expressionString, 0, &result);
  }
  if (!errorCode)
    *pVariableValue = result;

  return errorCode;
}

void MainWindow::handleInsertButtonClick() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());

  if (!button)
    return;

  QString buttonText = button->text();

  int isFunction = button->property("isFunction").toBool();

  QLineEdit *currentLineEdit = qobject_cast<QLineEdit *>(focusWidget());

  if (!currentLineEdit) {
    return;
  }

  if (isFunction) {
    buttonText += "(";
  }

  int cursorPos = currentLineEdit->cursorPosition();

  QString currentText = currentLineEdit->text();

  currentText.insert(cursorPos, buttonText);

  currentLineEdit->setText(currentText);

  currentLineEdit->setCursorPosition(cursorPos + buttonText.length());
}

void MainWindow::handleClearButtonClick() {
  QLineEdit *currentLineEdit = qobject_cast<QLineEdit *>(focusWidget());
  currentLineEdit->clear();
}

int MainWindow::handleCalculationDomain(double *pDomainValue,
                                        QLineEdit *lineEditDomain) {
  char expressionString[S21_BUFFER_SIZE_256] = {0};
  copyCStringFromLineEdit(expressionString, lineEditDomain);

  double result = 0;
  int errorCode = ErrorCode_noError;

  errorCode = fromExpressionToValue(expressionString, 0, &result);

  if (result > S21_MIN_DOMAIN_VALUE && result < S21_MAX_DOMAIN_VALUE &&
      !errorCode) {
    *pDomainValue = result;
  } else {
    errorCode |= ErrorCode_invalidExpressionFormat;
  }
  return errorCode;
}

void MainWindow::clearCustomPlot() {
  int pointCount = 1;
  QVector<double> x(pointCount);
  QVector<double> y(pointCount);
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y);
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");
  QBrush *brush = new QBrush(S21_PURPLE_RGB_COLOR);
  QBrush &linkBrush = *brush;
  ui->customPlot->graph()->setPen(QPen(linkBrush, 1.4));
  ui->customPlot->replot();
}

void MainWindow::handleClearGraphButton() { clearCustomPlot(); }

void MainWindow::assignValuesToCustomPlot(QVector<double> &x,
                                          QVector<double> &y,
                                          double domainInterval,
                                          double codomainInterval) {
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setData(x, y);
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");
  ui->customPlot->xAxis->setRange(-domainInterval, domainInterval);
  ui->customPlot->yAxis->setRange(-codomainInterval, codomainInterval);

  ui->customPlot->replot();
}

void setErrorCodeForDomains(int index, int errorCode) {
  if (index == 0) {
    Settings::errorCodeDomain = errorCode;
  } else if (index == 1) {
    Settings::errorCodeCodomain = errorCode;
  }
}

int areNoErrorsInExpression() { return !Settings::errorCodeGraph; }

int areNoErrorsInDomain() { return !Settings::errorCodeDomain; }

int areNoErrorsInCodomain() { return !Settings::errorCodeCodomain; }

int areNoErrorsInPlot() {
  return areNoErrorsInExpression() && areNoErrorsInDomain() &&
         areNoErrorsInCodomain();
}

int MainWindow::drawPlot(const char *expressionString) {
  int errorCode = ErrorCode_noError;
  if (areNoErrorsInPlot()) {
    QVector<double> x(S21_PLOT_POINT_COUNT);
    QVector<double> y(S21_PLOT_POINT_COUNT);

    double domains[S21_DOMAINS_COUNT] = {0, 0};
    QLineEdit *lineEditDomains[S21_DOMAINS_COUNT] = {ui->lineEdit_domain,
                                                     ui->lineEdit_codomain};

    for (int i = 0; i < S21_DOMAINS_COUNT; i++) {
      errorCode = handleCalculationDomain(&domains[i], lineEditDomains[i]);
      if (errorCode) {
        setStyleIncorrectLineEditDomains(lineEditDomains[i]);
        setErrorCodeForDomains(i, errorCode);
      }
    }

    errorCode =
        calculatePlot(x, y, S21_PLOT_POINT_COUNT, domains[0], expressionString);
    if (errorCode) {
      setStyleIncorrectLineEditExpression(ui->lineEdit_graph_expression);
      Settings::errorCodeGraph = errorCode;
    }

    if (!errorCode) {
      assignValuesToCustomPlot(x, y, domains[0], domains[1]);
    }
  }

  return errorCode;
}

int MainWindow::assignCreditParams(CreditParameters *creditParams) {
  QString creditAmountString = ui->lineEdit_credit_creditAmount->text();
  QString creditDeadlineString = ui->lineEdit_credit_creditDeadline->text();
  QString creditInterestValueString = ui->lineEdit_credit_interestValue->text();
  char creditTermTypeString[S21_BUFFER_SIZE_256]{};
  char creditPaymentTypeString[S21_BUFFER_SIZE_256]{};

  copyCStringFromComboBox(creditTermTypeString, ui->comboBox_credit_termType);
  copyCStringFromComboBox(creditPaymentTypeString,
                          ui->comboBox_credit_paymentsType);

  CreditPaymentType creditPaymentType =
      getCreditPaymentType(creditPaymentTypeString);
  TermType creditTermType = getCreditTermType(creditTermTypeString);

  int errorCode = ErrorCode_noError;

  double creditAmount = creditAmountString.toDouble();
  int creditDeadline = creditDeadlineString.toInt();
  double interestValue = creditInterestValueString.toDouble();

  int isCreditValueOk = isDoubleNumber(creditAmountString);
  int isCreditDeadlineOk = isIntNumber(creditDeadlineString);
  int isInterestValueOk = isDoubleNumber(creditInterestValueString);

  if (creditTermType == TermType_years) {
    creditDeadline *= S21_MONTH_IN_YEAR;
    creditTermType = TermType_months;
  }

  if (!isCreditValueOk || creditAmount <= S21_MIN_CREDIT_AMOUNT_VALUE ||
      creditAmount >= S21_MAX_CREDIT_AMOUNT_VALUE) {
    errorCode = ErrorCode_invalidExpressionFormat;
    Settings::errorCodeCreditAmount = ErrorCode_invalidExpressionFormat;
    setStyleIncorrectLineEditCredit(ui->lineEdit_credit_creditAmount);
  }

  if (!isCreditDeadlineOk || creditDeadline <= 0 ||
      creditDeadline > S21_MAX_MONTH_CREDIT_VALUE) {
    errorCode = ErrorCode_invalidExpressionFormat;
    Settings::errorCodeCreditDeadline = ErrorCode_invalidExpressionFormat;
    setStyleIncorrectLineEditCredit(ui->lineEdit_credit_creditDeadline);
  }

  if (!isInterestValueOk || interestValue <= S21_MIN_INTEREST_RATE ||
      interestValue > S21_MAX_INTEREST_RATE) {
    errorCode = ErrorCode_invalidExpressionFormat;
    Settings::errorCodeCreditInterestValue = ErrorCode_invalidExpressionFormat;
    setStyleIncorrectLineEditCredit(ui->lineEdit_credit_interestValue);
  }

  if (!errorCode) {
    creditParams->creditAmount = creditAmount;
    creditParams->creditDeadline = creditDeadline;
    creditParams->interestRate = interestValue;
    creditParams->paymentType = creditPaymentType;
    creditParams->termType = creditTermType;
  }

  return errorCode;
}

void MainWindow::clearCreditResult() {
  ui->label_credit_mothtlyPaymentResult_value->clear();
  ui->label_credit_interestCharges_value->clear();
  ui->label_credit_debtPlusCharges_value->clear();
}

QString formatMoney(double number, int decimalPlaces = 2) {
  QString formattedAmount = QString::number(number, 'f', decimalPlaces);

  QLocale locale(QLocale::English);
  formattedAmount =
      locale.toString(formattedAmount.toDouble(), 'f', decimalPlaces);

  return formattedAmount;
}

void MainWindow::outputCreditResult(CreditResult *creditResult) {
  QString montlyPaymentString = formatMoney(creditResult->monthlyPaymentBegin);

  if (creditResult->monthlyPaymentBegin != creditResult->monthlyPaymentEnd) {
    montlyPaymentString += "...";
    QString montlyPaymentEndString =
        formatMoney(creditResult->monthlyPaymentEnd);
    montlyPaymentString += montlyPaymentEndString;
  }
  QString chargesString = formatMoney(creditResult->creditOverpayment);

  QString overpaymentSizeString = formatMoney(creditResult->totalPayment);

  ui->label_credit_mothtlyPaymentResult_value->setText(montlyPaymentString);
  ui->label_credit_interestCharges_value->setText(chargesString);
  ui->label_credit_debtPlusCharges_value->setText(overpaymentSizeString);
}

void MainWindow::handleButtonCreditCalculate() {
  int errorCode = ErrorCode_noError;

  errorCode = assignCreditParams(&creditParams);

  if (!errorCode)
    errorCode = handleCalculateMonthlyPayment(&creditParams, &creditResult);

  clearCreditResult();

  if (!errorCode)
    outputCreditResult(&creditResult);
}
int handleSetDepositAmount(DepositParameters *depositParams,
                           QLineEdit *depositAmountElement) {
  QString depositAmountString = depositAmountElement->text();

  double depositAmount{};

  int errorCode = ErrorCodeFrontDeposit_noError;

  if (!isDoubleNumber(depositAmountString)) {
    errorCode = ErrorCodeFrontDeposit_incorrectDepositValue;
    setStyleIncorrectLineEditDeposit(depositAmountElement);
    Settings::errorCodeDepositAmount = errorCode;
  }

  if (!errorCode) {
    depositAmount = depositAmountString.toDouble();
    if (depositAmount <= S21_MIN_DEPOSIT_AMOUNT_VALUE) {
      errorCode = ErrorCodeFrontDeposit_incorrectDepositValue;
    }
    if (depositAmount > S21_MAX_DEPOSIT_AMOUNT_VALUE) {
      errorCode = ErrorCodeFrontDeposit_incorrectDepositValue;
    }
    if (errorCode) {
      Settings::errorCodeDepositAmount = errorCode;
      setStyleIncorrectLineEditDeposit(depositAmountElement);
    }
  }

  if (!errorCode) {
    depositParams->depositAmount = depositAmount;
  }

  return errorCode;
}

int testCorrectnessPlacementDepositPeriod(TermType termType,
                                          int placementPeriod) {
  int errorCode = ErrorCodeFrontDeposit_noError;

  if (termType == TermType_days)
    if (placementPeriod > S21_MAX_DEPOSIT_POSTING_PERIOD_DAYS_VALUE) {
      errorCode = ErrorCodeFrontDeposit_incorrectPlacementPeriod;
    }
  if (termType == TermType_months)
    if (placementPeriod > S21_MAX_DEPOSIT_POSTING_PERIOD_MONTHS_VALUE) {
      errorCode = ErrorCodeFrontDeposit_incorrectPlacementPeriod;
    }
  if (termType == TermType_years)
    if (placementPeriod > S21_MAX_DEPOSIT_POSTING_PERIOD_YEARS_VALUE) {
      errorCode = ErrorCodeFrontDeposit_incorrectPlacementPeriod;
    }
  if (placementPeriod < S21_MIN_DEPOSIT_POSTING_PERIOD_VALUE) {
    errorCode = ErrorCodeFrontDeposit_incorrectPlacementPeriod;
  }

  return errorCode;
}

int handleSetDepositPlacementPeriod(DepositParameters *depositParams,
                                    QLineEdit *depositPlacementPeriodElement,
                                    QComboBox *intervalType) {
  QString depositPlacementPeriodString = depositPlacementPeriodElement->text();

  int depositPlacementPeriod = 0;

  int errorCode = ErrorCodeFrontDeposit_noError;

  if (!isIntNumber(depositPlacementPeriodString)) {
    errorCode = ErrorCodeFrontDeposit_incorrectDepositValue;
    setStyleIncorrectLineEditDeposit(depositPlacementPeriodElement);
    Settings::errorCodeDepositPlacementPeriod = errorCode;
  }
  if (!errorCode) {
    depositPlacementPeriod = depositPlacementPeriodString.toInt();
  }

  TermType depositTermType = getDepositTermType(intervalType->currentText());

  errorCode = testCorrectnessPlacementDepositPeriod(depositTermType,
                                                    depositPlacementPeriod);

  if (errorCode) {
    errorCode = ErrorCodeFrontDeposit_incorrectDepositValue;
    setStyleIncorrectLineEditDeposit(depositPlacementPeriodElement);
    Settings::errorCodeDepositPlacementPeriod = errorCode;
  }
  if (!Settings::errorCodeDepositAmount &&
      !Settings::errorCodeDepositPlacementPeriod) {
    depositParams->depositPeriod.depositPostingPeriod = depositPlacementPeriod;
    depositParams->depositPeriod.depositTerm = depositTermType;
  }

  errorCode = Settings::errorCodeDepositAmount |
              Settings::errorCodeDepositPlacementPeriod;
  return errorCode;
}
int handleSetDepositDate(DepositParameters *depositParams,
                         QDateEdit *depositDate) {
  int errorCode = ErrorCodeFrontDeposit_noError;
  QDate transactionDate = depositDate->date();

  RawDate rawDate = {transactionDate.day(), transactionDate.month() - 1,
                     transactionDate.year()};

  errorCode = setDepositDate(depositParams, rawDate);

  return errorCode;
}
int handleSetPaymentPeriodicity(DepositParameters *depositParams,
                                QComboBox *paymentsPeriodicity) {
  int errorCode = ErrorCodeFrontDeposit_noError;

  QString paymentString = paymentsPeriodicity->currentText();

  IntervalType interval = getPaymentPeriodicity(paymentString);

  errorCode = setPeriodicityOfPayments(depositParams, interval);

  return errorCode;
}

void handleSetCapitalisationStatus(DepositParameters *depositParams,
                                   QCheckBox *checkBox) {
  CapitalisationStatus capitalisationStatus = CapitalisationStatus_off;

  int checkBoxStatus = checkBox->isChecked();

  if (checkBoxStatus)
    capitalisationStatus = CapitalisationStatus_on;

  setCapitalisationStatus(depositParams, capitalisationStatus);
}

void handleSetDepositFinishDate(DepositParameters *depositParams) {
  setDepositFinishDate(depositParams);
}

void handleFinishLogFile(DepositResult *depositResult, int errorCode) {
  if (!errorCode) {
    finishLogFile(depositResult);
  }
}

int handleSetTax(DepositParameters *depositParams, double taxValue) {
  return setTax(depositParams, taxValue);
}

void handleClearLogFiles() {
  clearLogFile();
  clearTaxesLogFile();
}

void MainWindow::clearDepositResult() {
  ui->label_deposit_interestCharges_value->clear();

  ui->label_deposit_depositPlusCharges_value->clear();

  ui->label_deposit_taxes_value->clear();
}

void MainWindow::outputDepositResult(DepositResult *depositResult) {
  QString allYearsIncomeString = formatMoney(depositResult->allYearsIncome);

  QString totalDepositString = formatMoney(depositResult->totalDeposit);

  QString allYearsTaxesString = formatMoney(depositResult->allYearsTaxes);

  ui->label_deposit_interestCharges_value->setText(allYearsIncomeString);

  ui->label_deposit_depositPlusCharges_value->setText(totalDepositString);

  ui->label_deposit_taxes_value->setText(allYearsTaxesString);
}

void MainWindow::handleDepositClearButtonClick() {
  setCurrentDate(ui->dateEdit_deposit_depositDate);
}

void MainWindow::handleDepositCalculateButtonClick() {
  int errorCode = ErrorCodeFrontDeposit_noError;

  initDepositParameters(&depositConfig.params);
  initDepositResults(&depositConfig.result);

  handleClearLogFiles();
  clearDepositResult();

  QLineEdit *depositAmount = ui->lineEdit_deposit_depositAmount;
  QLineEdit *depositPlacementPeriod = ui->lineEdit_deposit_placementPeriod;
  QComboBox *intervalType = ui->comboBox_deposit_placementPeriod;
  QDateEdit *depositDate = ui->dateEdit_deposit_depositDate;
  QComboBox *paymentsPeriodicity = ui->comboBox_deposit_paymentsPeriodicity;
  QCheckBox *capitalisationCheckBox = ui->checkBox_deposit_capitalization;

  errorCode |= handleSetDepositAmount(&depositConfig.params, depositAmount);
  errorCode |= handleSetDepositPlacementPeriod(
      &depositConfig.params, depositPlacementPeriod, intervalType);
  errorCode |= interestRateWidget->setInterestRates(&depositConfig.params);
  errorCode |= refillsWidget->setTransactions(&depositConfig.params);
  errorCode |= partialWithdrawalsWidget->setTransactions(&depositConfig.params);
  errorCode |= handleSetDepositDate(&depositConfig.params, depositDate);
  errorCode |=
      handleSetPaymentPeriodicity(&depositConfig.params, paymentsPeriodicity);
  handleSetCapitalisationStatus(&depositConfig.params, capitalisationCheckBox);
  handleSetDepositFinishDate(&depositConfig.params);
  errorCode |= handleSetTax(&depositConfig.params, 13);

  if (!errorCode) {
    errorCode |= handleAllTransactions(&depositConfig);
  }

  if (!errorCode) {
    printDepositParams("deposit result", &depositConfig.params);
    outputDepositResult(&depositConfig.result);
    handleFinishLogFile(&depositConfig.result, errorCode);
  }
}
