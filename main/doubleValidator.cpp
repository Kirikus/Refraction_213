#include "doubleValidator.h"

betterDoubleValidator::betterDoubleValidator(double bottom, double top,
                                             int decimals, QObject *parent)
    : QDoubleValidator(bottom, top, decimals, parent) {}

QValidator::State betterDoubleValidator::validate(QString &s, int &i) const {
  if (s.isEmpty() || s == "-") {
    return QValidator::Intermediate;
  }
  if (s == "e" || s == ",") return QValidator::Invalid;

  QChar decimalPoint = QChar('.');

  if (s.indexOf(decimalPoint) != -1) {
    int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

    if (charsAfterPoint > decimals()) {
      return QValidator::Invalid;
    }
  }

  bool ok;
  double d = locale().toDouble(s, &ok);

  if (ok && d >= bottom() && d <= top()) {
    return QValidator::Acceptable;
  } else {
    return QValidator::Invalid;
  }
}
