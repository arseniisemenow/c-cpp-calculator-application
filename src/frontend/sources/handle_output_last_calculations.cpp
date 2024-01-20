#include "../headers/handle_output_last_calculations.h"

void switchLastCalculationsResult(QLabel *QLabel_lastCalculations,
                                  QLabel *QLabel_penultimateCalculations,
                                  QLabel *QLabel_antePenultimateCalculations,
                                  const QString &currentResult) {
  QLabel_antePenultimateCalculations->setText(
      QLabel_penultimateCalculations->text());

  QLabel_penultimateCalculations->setText(QLabel_lastCalculations->text());

  QLabel_lastCalculations->setText(currentResult);
}
