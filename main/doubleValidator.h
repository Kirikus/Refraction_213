#ifndef DOUBLEVALIDATOR_H
#define DOUBLEVALIDATOR_H
#include "QValidator"

class betterDoubleValidator : public QDoubleValidator {
 public:
  betterDoubleValidator(double bottom, double top, int decimals,
                        QObject *parent);

  QValidator::State validate(QString &s, int &i) const;
};
#endif  // DOUBLEVALIDATOR_H
