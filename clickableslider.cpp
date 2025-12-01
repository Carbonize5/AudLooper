#include "clickableslider.h"

ClickableSlider::ClickableSlider(Qt::Orientation orientation, QWidget *parent) : QSlider{orientation, parent}{}

ClickableSlider::ClickableSlider(QWidget *parent) : QSlider{parent}{}

ClickableSlider::~ClickableSlider() {}

void ClickableSlider::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::MouseButton::LeftButton){
        int value = this->minimum() + ((this->maximum() - this->minimum()) * ev->position().x()) / this->width();
        this->setValue(value);
        emit this->sliderPressed();
    }
    QSlider::mousePressEvent(ev);
}
