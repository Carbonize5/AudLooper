#include "focuslineedit.h"

FocusLineEdit::FocusLineEdit(QWidget *parent) : QLineEdit{parent} {
    this->b_focus = false;
    this->clearFocus();
}

FocusLineEdit::FocusLineEdit(const QString &contents, QWidget *parent) : QLineEdit{contents, parent}{
    this->b_focus = false;
    this->clearFocus();
}

FocusLineEdit::~FocusLineEdit(){}

void FocusLineEdit::focusInEvent(QFocusEvent *ev){
    this->b_focus = true;
    emit this->focusChanged(true);
    QLineEdit::focusInEvent(ev);
}

void FocusLineEdit::focusOutEvent(QFocusEvent *ev){
    this->b_focus = false;
    emit this->focusChanged(false);
    QLineEdit::focusOutEvent(ev);
}

//void FocusLineEdit::focusChanged(bool focus){}
