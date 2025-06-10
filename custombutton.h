#pragma once

#include <QObject>
#include <QPushButton>
#include <QColor>
#include <QMouseEvent>
#include <QPropertyAnimation>

class CustomButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit CustomButton(QWidget *parent = nullptr);

    void setDefaultColor(const QColor& color);
    void setHoverColor(const QColor& color);
    void setPressedColor(const QColor& color);
    void setTextColor(const QColor& color);

   QColor currentColor() const;
   void setCurrentColor(const QColor& color);

   qreal opacity() const;
   void setOpacity(qreal scale);

protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;

  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

private:
  void animateColor(const QColor& toColor);
  void animateOpacity(const qreal toOpacity);

private:
  QColor defaultColor_{Qt::black};
  QColor hoverColor_{Qt::darkGray};
  QColor pressedColor_{Qt::blue};
  QColor textColor_{Qt::white};
  QColor currentColor_;
  qreal opacity_{1.0};
  QPropertyAnimation* colorAnimation_{nullptr};
  QPropertyAnimation* opacityAnimation_{nullptr};
};
