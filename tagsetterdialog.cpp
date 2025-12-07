#include "tagsetterdialog.h"

/*QList<QVBoxLayout> TagSetterDialog::buildUI()
{
    // Do Layout Stuff
}*/

TagSetterDialog::TagSetterDialog(QIntValidator *tickValidator, Tag *tag, QWidget *parent) : QDialog{parent}
{
    this->tickValidator = tickValidator;
    this->tag = tag;
    this->initUI();
    this->eventHandler();
}

void TagSetterDialog::initUI()
{
    // Basic UI Elements
    QDialogButtonBox::StandardButtons btns = (QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    this->buttonBox = new QDialogButtonBox(btns);

    this->comboLabel = new QLabel("Tag Type");
    this->comboBox = new QComboBox();
    this->comboBox->addItem("Go To Tag");
    this->comboBox->setCurrentIndex(0);

    // Build First UI
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QHBoxLayout *row = new QHBoxLayout();
    QVBoxLayout *col0 = new QVBoxLayout();

    row->addLayout(col0);

    col0->addWidget(this->comboLabel);
    col0->addWidget(this->comboBox);

    if (this->tag == nullptr){
        for (int i=0;i<this->argsTitles->at(0)->size();i++){
            QVBoxLayout *col = new QVBoxLayout();
            col->addWidget(this->argsTitles->at(0)->at(i));
            col->addWidget(this->argsEdits->at(0)->at(i));
            row->addLayout(col);
        }
    }
    else{
        int index = 0;
        // Search for which Tag before
        for (int i=0;i<this->argsTitles->at(index)->size();i++){
            QVBoxLayout *col = new QVBoxLayout();
            col->addWidget(this->argsTitles->at(index)->at(i));
            QLineEdit* edit = this->argsEdits->at(index)->at(i);
            edit->setText(QString::number(this->tag->getValues()->at(i)));
            col->addWidget(edit);
            row->addLayout(col);
        }
        this->lastIndex = index;
    }

    masterLayout->addLayout(row);
    masterLayout->addWidget(this->buttonBox);
    this->setLayout(masterLayout);

}

void TagSetterDialog::eventHandler()
{
    connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(this->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(rebuildUI(int)));
}

void TagSetterDialog::accept()
{
    QList<int> *values = new QList<int>();
    for (int i=0;i<this->argsEdits->at(this->lastIndex)->size();i++){
        values->append(this->argsEdits->at(this->lastIndex)->at(i)->text().toInt());
    }
    this->tagTypes->at(this->lastIndex)->setValues(values);
    this->tag = this->tagTypes->at(this->lastIndex)->copy();
    for (int i=0;i<this->argsEdits->at(this->lastIndex)->size();i++){
        this->argsEdits->at(this->lastIndex)->at(i)->setText("");
    }
    QDialog::accept();
}

void TagSetterDialog::rebuildUI(int index)
{
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QHBoxLayout *row = new QHBoxLayout();
    QVBoxLayout *col0 = new QVBoxLayout();

    row->addLayout(col0);

    col0->addWidget(this->comboLabel);
    col0->addWidget(this->comboBox);

    for (int i=0;i<this->argsEdits->at(this->lastIndex)->size();i++){
        this->argsEdits->at(this->lastIndex)->at(i)->setText("");
    }

    for (int i=0;i<this->argsTitles->at(index)->size();i++){
        QVBoxLayout *col = new QVBoxLayout();
        col->addWidget(this->argsTitles->at(index)->at(i));
        col->addWidget(this->argsEdits->at(index)->at(i));
        row->addLayout(col);
    }

    masterLayout->addLayout(row);
    masterLayout->addWidget(this->buttonBox);
    this->setLayout(masterLayout);
    this->lastIndex = index;
}

QIntValidator *TagSetterDialog::getTickValidator() const
{
    return tickValidator;
}

Tag *TagSetterDialog::getTag() const
{
    return tag;
}

QComboBox *TagSetterDialog::getComboBox() const
{
    return comboBox;
}

void TagSetterDialog::setTagTypes(QList<Tag *> *newTagTypes)
{
    tagTypes = newTagTypes;
}

void TagSetterDialog::setArgsEdits(QList<QList<QLineEdit *> *> *newArgsEdits)
{
    argsEdits = newArgsEdits;
}

void TagSetterDialog::setArgsTitles(QList<QList<QLabel *> *> *newArgsTitles)
{
    argsTitles = newArgsTitles;
}
