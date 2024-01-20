#ifndef HANDLE_OUTPUT_LAST_CALCULATIONS_H_
#define HANDLE_OUTPUT_LAST_CALCULATIONS_H_

#include <QLabel>
#include <QMainWindow>

void switchLastCalculationsResult(QLabel *QLabel_lastCalculations,
                                  QLabel *QLabel_penultimateCalculations,
                                  QLabel *QLabel_antePenultimateCalculations,
                                  const QString &currentResult);

#endif // HANDLE_OUTPUT_LAST_CALCULATIONS_H_
