#include "../headers/calculate_plot.h"

double calculateValue(int index, int pointCount, double domainInterval) {
  return (index / ((double)(pointCount / (domainInterval * 2)) - 1) -
          domainInterval);
}

int calculatePlot(QVector<double> &x, QVector<double> &y, int pointCount,
                  double domainInterval, const char *expressionString) {
  int errorCode = ErrorCode_noError;
  int errorCount = 0;

  for (int i = 0; i < pointCount; ++i) {
    double tempResult = 0;

    x[i] = calculateValue(i, pointCount, domainInterval);

    errorCode = fromExpressionToValue(expressionString, x[i], &tempResult);

    if (!errorCode) {
      y[i] = tempResult;
    } else {
      y[i] = 0;
      errorCount++;
    }
  }

  errorCode = ErrorCode_noError;

  if (errorCount == pointCount) {
    errorCode = ErrorCode_UnableToBuildGraph;
  }

  std::cerr << "errorCount: " << errorCount << std::endl;

  return errorCode;
}
