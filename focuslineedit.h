#ifndef FOCUSLINEEDIT_H
#define FOCUSLINEEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QFocusEvent>

class FocusLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    FocusLineEdit(QWidget *parent =nullptr);
    FocusLineEdit(const QString &contents, QWidget *parent = nullptr);
    ~FocusLineEdit();
    bool focus() const {return b_focus;}

protected:
    void focusInEvent(QFocusEvent *ev) override;
    void focusOutEvent(QFocusEvent *ev) override;


private:
    bool b_focus;

signals:
    void focusChanged(bool focus);
};

#endif // FOCUSLINEEDIT_H
