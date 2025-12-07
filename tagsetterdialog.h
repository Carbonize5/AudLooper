#ifndef TAGSETTERDIALOG_H
#define TAGSETTERDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QValidator>
#include <QIntValidator>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>

#include "tag.h"

class TagSetterDialog : public QDialog
{
    Q_OBJECT
public:
    TagSetterDialog(QIntValidator *tickValidator, Tag *tag = nullptr, QWidget *parent = nullptr);

    QIntValidator *getTickValidator() const;
    Tag *getTag() const;
    QComboBox *getComboBox() const;

    void setTagTypes(QList<Tag *> *newTagTypes);

    void setArgsEdits(QList<QList<QLineEdit *> *> *newArgsEdits);

    void setArgsTitles(QList<QList<QLabel *> *> *newArgsTitles);

private:
    QIntValidator *tickValidator;
    Tag *tag;
    QLabel * comboLabel;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;
    QList<Tag *> *tagTypes;
    QList<QList<QLabel *>*> *argsTitles;
    QList<QList<QLineEdit *>*> *argsEdits;
    int lastIndex=0;

    void initUI();
    void eventHandler();
    //QList<QVBoxLayout> buildUI();

public slots:
    void accept() override;

private slots:
    void rebuildUI(int index);

};

#endif // TAGSETTERDIALOG_H
