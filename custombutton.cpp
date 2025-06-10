#include "custombutton.h"

#include <QPainter>

CustomButton::CustomButton(QWidget* parent)
    : QPushButton(parent)
{
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  setFocusPolicy(Qt::ClickFocus);

  colorAnimation_ = new QPropertyAnimation(this, "currentColor", this);
  opacityAnimation_ = new QPropertyAnimation(this, "opacity", this);

  colorAnimation_->setDuration(200);
  colorAnimation_->setEasingCurve(QEasingCurve::OutQuad);

  opacityAnimation_->setDuration(400);
  opacityAnimation_->setEasingCurve(QEasingCurve::OutQuad);
  currentColor_ = defaultColor_;

  setCursor(Qt::PointingHandCursor);
}

void CustomButton::setDefaultColor(const QColor& color) {
  defaultColor_ = color;
  update();
}

void CustomButton::setHoverColor(const QColor& color) {
  hoverColor_ = color;
  update();
}

void CustomButton::setPressedColor(const QColor& color) {
  pressedColor_ = color;
  update();
}

void CustomButton::setTextColor(const QColor& color) {
  textColor_ = color;
  update();
}

QColor CustomButton::currentColor() const
{
  return currentColor_;
}

void CustomButton::setCurrentColor(const QColor& color)
{
  if (currentColor_ != color) {
    currentColor_ = color;
    update(); // Важно: принудительная перерисовка
  }}

qreal CustomButton::opacity() const
{
  return opacity_;
}

void CustomButton::setOpacity(qreal opacity)
{
  opacity_ = opacity;
}

void CustomButton::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing);
  painter.setOpacity(opacity_);

  QRect rect = this->rect();
  painter.setBrush(currentColor_);
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(rect, 8, 8);

  painter.setPen(textColor_);
  painter.drawText(rect, Qt::AlignCenter, text());
}

void CustomButton::mousePressEvent(QMouseEvent* mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton) {
      animateColor(pressedColor_);
      animateOpacity(0.8);
      mouseEvent->accept();
  } else {
    mouseEvent->ignore();
  }
}

void CustomButton::mouseReleaseEvent(QMouseEvent* mouseEvent) {
  if (mouseEvent->button() == Qt::LeftButton) {
      animateColor(underMouse() ? hoverColor_ : defaultColor_);
      animateOpacity(1.0);
    if (rect().contains(mouseEvent->pos())) {
      emit clicked();
    }
    mouseEvent->accept();
  } else {
    mouseEvent->ignore();
  }
}

void CustomButton::enterEvent(QEvent* event) {
  Q_UNUSED(event);
  QPushButton::enterEvent(event);
  animateColor(hoverColor_);
}

void CustomButton::leaveEvent(QEvent* event) {
 Q_UNUSED(event);
 QPushButton::leaveEvent(event);
 animateColor(defaultColor_);
}

void CustomButton::animateColor(const QColor &toColor) {
  if (colorAnimation_->state() == QPropertyAnimation::Running) {
    colorAnimation_->stop();
  }
  colorAnimation_->setStartValue(currentColor_);
  colorAnimation_->setEndValue(toColor);
  colorAnimation_->start();
}

void CustomButton::animateOpacity(const qreal toOpacity)
{
  if (opacityAnimation_->state() == QPropertyAnimation::Running) {
    opacityAnimation_->stop();
  }
  opacityAnimation_->setStartValue(opacity_);
  opacityAnimation_->setEndValue(toOpacity);
  opacityAnimation_->start();
}
