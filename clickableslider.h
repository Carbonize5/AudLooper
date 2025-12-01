#ifndef CLICKABLESLIDER_H
#define CLICKABLESLIDER_H

#include <QSlider>
#include <QWidget>
#include <QMouseEvent>

class ClickableSlider : public QSlider
{
    Q_OBJECT
public:
    ClickableSlider(QWidget * parent=nullptr);
    ClickableSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~ClickableSlider();

protected:
    void mousePressEvent(QMouseEvent *ev) override;
};

#endif // CLICKABLESLIDER_H
