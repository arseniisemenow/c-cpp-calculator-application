#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QLineEdit>
#include <QMainWindow>
#include <QRegularExpression>
#include <QtGui>

#include "../../credit_calculator_backend/headers/s21_credit_calc_library.h"
#include "../../deposit_calculator_backend/headers/s21_deposit_calc_library.h"
#include "../../develop/s21_develop.h" // for develop needs
#include "../../expression_calculator_backend/headers/s21_calc_library.h"
#include "../custom_widgets/InterestRateWidget.h"
#include "../custom_widgets/PartialWithdrawalsWidget.h"
#include "../custom_widgets/RefillsWidget.h"
#include "../headers/Settings.h"
#include "./ui_mainwindow.h"
#include "calculate_plot.h"
#include "cross_platform_differences.h"
#include "error_code_to_error_string.h"
#include "handle_format_calculations_result.h"
#include "handle_output_last_calculations.h"
#include "handle_styles.h"
#include "handle_tab_switch.h"
#include "parsing_helpers.h"
#include "set_current_date.h"
#include "string_processing_functions.h"
#include "string_validator.h"

#define S21_MIN_DOMAIN_VALUE (1e-7)
#define S21_MAX_DOMAIN_VALUE (1000000)
#define S21_DOMAINS_COUNT (2)
#define S21_PLOT_POINT_COUNT (512)
#define S21_PURPLE_RGB_COLOR                                                   \
  { 148, 105, 255, 255 }
#define S21_DARK_GRAY_RGB_COLOR                                                \
  { 50, 50, 50, 255 }

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

  ~MainWindow();

  InterestRateWidget *interestRateWidget;
  RefillsWidget *refillsWidget;
  PartialWithdrawalsWidget *partialWithdrawalsWidget;

  CreditParameters creditParams{};
  CreditResult creditResult{};
  DepositConfig depositConfig{};

private:
  Ui::MainWindow *ui;

private slots:
  void setupUIElements();
  void setupConnections();
  void setupCustomWidgets();
  void configureUIElements();

  void connectCalculatorButtons();
  void connectTabButtons();
  void connectCalculatorFunctionsButtons();

  void setupGraphCalculatorElements();
  void connectCreditCalculatorElements();
  void connectDepositCalculatorElements();

  void initializeCustomWidgets();
  void configureCustomWidgetLayouts();
  void configureDateEditWidgets();
  void configureComboBoxes();

  void handleInsertButtonClick();
  void handleButtonEqualsClick();

  int handleCalculationDomain(double *pDomainValue, QLineEdit *lineEditDomain);

  void handleTextChanged_lineEdit(const QString &);
  void handleTextChanged_variable(const QString &);
  void handleTextChanged_domainEdit(const QString &);
  void handleTextChanged_codomainEdit(const QString &);
  void handleTextChanged_graphExpression(const QString &inputString);

  void handleTextChanged_creditAmount(const QString &inputString);
  void handleTextChanged_creditDeadline(const QString &inputString);
  void handleTextChanged_interestValue(const QString &inputString);

  void handleDrawPlot();
  int drawPlot(const char *expressionString);

  int getVariableLabelValue(double *pVariableValue);

  void handleTabClick();

  void assignValuesToCustomPlot(QVector<double> &x, QVector<double> &y,
                                double domainInterval, double codomainInterval);

  void clearCustomPlot();
  void handleClearGraphButton();
  void handleClearButtonClick();

  void handleTextChanged(QLineEdit *lineEdit, int *errorCode);

  void handleButtonCreditCalculate();

  int assignCreditParams(CreditParameters *creditParams);

  void clearCreditResult();

  void outputCreditResult(CreditResult *creditResult);

  void handleDepositCalculateButtonClick();

  void handleTextChanged_depositAmount(const QString &inputString);
  void handleTextChanged_depositPlacementPeriod(const QString &inputString);

  void clearDepositResult();
  void outputDepositResult(DepositResult *depositResult);

  void handleDepositClearButtonClick();

  void handleDepositTaxesLogsButtonClick();
  void handleDepositLogsButtonClick();
};

void handleClearLogFiles();

#endif // MAINWINDOW_H_
