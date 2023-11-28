#ifndef SECTION_H
#define SECTION_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <vector>

enum ModelType { Atmospheric, Refraction, Other };

constexpr QColor underlight_color = QColor(220, 249, 255, 100);
constexpr QColor default_color = QColor(239, 239, 239, 255);

namespace ui {
class Section : public QWidget {
  Q_OBJECT

 private:
  QGridLayout* mainLayout;
  QToolButton* toggleButton;
  QFrame* headerLine;
  QParallelAnimationGroup* toggleAnimation;
  QScrollArea* contentArea;
  int animationDuration;
  int collapsedHeight;
  bool isExpanded = false;

 public slots:
  void toggle(bool collapsed);

 public:
  static const int DEFAULT_DURATION = 0;

  // initialize section
  explicit Section(const QString& title = "",
                   const int animationDuration = DEFAULT_DURATION,
                   QWidget* parent = 0, bool need_backlight = false,
                   ModelType model_type = Other);

  // set layout of content
  void setContentLayout(QLayout& contentLayout);

  // set title
  void setTitle(QString title);

  // update animations and their heights
  void updateHeights();
};
}  // namespace ui

#endif  // SECTION_H
