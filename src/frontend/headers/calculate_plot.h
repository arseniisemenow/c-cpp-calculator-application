#ifndef CALCULATE_PLOT_H_
#define CALCULATE_PLOT_H_

#include <QDebug>
#include <QMainWindow>
#include <iostream>

#include "../../expression_calculator_backend/headers/s21_calc_library.h"

int calculatePlot(QVector<double> &x, QVector<double> &y, int pointCount,
                  double domainInterval, const char *expressionString);

#endif // S21_CALCULATE_PLOT_H_
