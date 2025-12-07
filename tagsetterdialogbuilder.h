#ifndef TAGSETTERDIALOGBUILDER_H
#define TAGSETTERDIALOGBUILDER_H

#include "tagsetterdialog.h"
#include <QComboBox>
#include <QList>

class TagSetterDialogBuilder
{
public:
    TagSetterDialogBuilder(QIntValidator *tickValidator);
    TagSetterDialog * build(Tag *tag = nullptr, QWidget *parent = nullptr);
    void addTag(Tag *tag, std::vector<QValidator *> *tagArgsValidatorsList = nullptr, QList<QString *> *argsTitlesList = nullptr);
    void removeAt(int index);
    void changeTagAt(Tag *tag, int index);
    void changeValidatorsListAt(int index, std::vector<QValidator *> *tagArgsValidatorsList = nullptr);
    void changeTitlesList(int index, QList<QString *> *argsTitlesList = nullptr);

private:
    QIntValidator *tickValidator;
    QList<Tag *> *tagTypeList;
    QList<std::vector<QValidator *>*> *tagArgsValidatorsList;
    QList<QList<QString *>*> *argsTitlesList;

    QList<QList<QLineEdit *>*> * buildEdits();
    QList<QList<QLabel *>*> * buildTitles();
};

#endif // TAGSETTERDIALOGBUILDER_H
