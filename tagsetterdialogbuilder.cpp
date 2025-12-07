#include "tagsetterdialogbuilder.h"

TagSetterDialogBuilder::TagSetterDialogBuilder(QIntValidator *tickValidator)
{
    this->tickValidator = tickValidator;
    this->tagTypeList = new QList<Tag *>();
    this->argsTitlesList = new QList<QList<QString *>*>();
    this->tagArgsValidatorsList = new QList<std::vector<QValidator *>*>();
}

TagSetterDialog * TagSetterDialogBuilder::build(Tag *tag, QWidget *parent)
{
    TagSetterDialog *dialog = new TagSetterDialog(this->tickValidator, tag, parent);
    dialog->setTagTypes(this->tagTypeList);
    QList<QList<QLineEdit *>*> *argsEdits = this->buildEdits();
    dialog->setArgsEdits(argsEdits);
    QList<QList<QLabel *>*> *argsTitles = this->buildTitles();
    dialog->setArgsTitles(argsTitles);
    return dialog;
}

void TagSetterDialogBuilder::addTag(Tag *tag, std::vector<QValidator *> *tagArgsValidatorsList, QList<QString*> *argsTitlesList)
{
    this->tagTypeList->append(tag);
    this->tagArgsValidatorsList->append(tagArgsValidatorsList);
    this->argsTitlesList->append(argsTitlesList);
}

void TagSetterDialogBuilder::removeAt(int index)
{
    this->tagTypeList->takeAt(index);
    this->tagArgsValidatorsList->takeAt(index);
    this->argsTitlesList->takeAt(index);
}

void TagSetterDialogBuilder::changeTagAt(Tag *tag, int index)
{
    this->tagTypeList->takeAt(index);
    this->tagTypeList->insert(index, tag);
}

void TagSetterDialogBuilder::changeValidatorsListAt(int index, std::vector<QValidator *> *tagArgsValidatorsList)
{
    this->tagArgsValidatorsList->takeAt(index);
    this->tagArgsValidatorsList->insert(index, tagArgsValidatorsList);
}

void TagSetterDialogBuilder::changeTitlesList(int index, QList<QString *> *argsTitlesList)
{
    this->argsTitlesList->takeAt(index);
    this->argsTitlesList->insert(index, argsTitlesList);
}

QList<QList<QLineEdit *> *> *TagSetterDialogBuilder::buildEdits()
{
    QList<QList<QLineEdit *> *> *result = new QList<QList<QLineEdit*>*>();
    for(int i=0; i<this->tagArgsValidatorsList->size();i++){
        result->append(new QList<QLineEdit*>());
        for(int j=0; j<this->tagArgsValidatorsList->at(i)->size();j++){
            QLineEdit* edit = new QLineEdit();
            if (this->tagArgsValidatorsList->at(i)->at(j) != nullptr) edit->setValidator(this->tagArgsValidatorsList->at(i)->at(j));
            result->at(i)->append(edit);
        }
    }
    return result;
}

QList<QList<QLabel *> *> *TagSetterDialogBuilder::buildTitles()
{
    QList<QList<QLabel *> *> *result =  new QList<QList<QLabel *> *>();
    for(int i=0; i<this->argsTitlesList->size();i++){
        result->append(new QList<QLabel*>());
        for(int j=0; j<this->argsTitlesList->at(i)->size();j++){
            QLabel* label = new QLabel();
            if (this->argsTitlesList->at(i)->at(j) != nullptr) label->setText("Argument "+QString::number(j));
            result->at(i)->append(label);
        }
    }
    return result;
}
