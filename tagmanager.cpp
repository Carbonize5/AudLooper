#include "tagmanager.h"

TagManager::TagManager(QWidget *parent)
    : QWidget{parent}
{
    this->tagList = QList<Tag>();
    this->tagBooleanList = QList<bool>();

    this->initUI();
    this->eventHandler();
}

void TagManager::initUI()
{
    // Basic UI elements
    QLabel *title = new QLabel("Tag List");
    this->tagListUI = new QListWidget();
    this->btnAddTag = new QPushButton("Add Tag");
    this->btnModifyTag = new QPushButton("Modify Tag");
    this->btnDeleteTag = new QPushButton("Delete Tag");
    this->btnClearTag = new QPushButton("Clear Tag List");

    this->tagListUI->setDisabled(true);
    this->btnAddTag->setDisabled(true);
    this->btnModifyTag->setDisabled(true);
    this->btnDeleteTag->setDisabled(true);
    this->btnClearTag->setDisabled(true);

    // Layout
    this->masterLayout = new QVBoxLayout();
    QHBoxLayout *row = new QHBoxLayout();
    QVBoxLayout *col1 = new QVBoxLayout();
    QVBoxLayout *col2 = new QVBoxLayout();

    row->addLayout(col1);
    row->addLayout(col2);

    col1->addWidget(title);
    col1->addWidget(this->tagListUI);

    col2->addWidget(this->btnAddTag);
    col2->addWidget(this->btnModifyTag);
    col2->addWidget(this->btnDeleteTag);
    col2->addWidget(this->btnClearTag);

    this->masterLayout->addLayout(row);
    this->setLayout(this->masterLayout);
}

void TagManager::eventHandler()
{
    connect(this->btnAddTag, SIGNAL(clicked(bool)), this, SLOT(addTagDialog()));
    connect(this->btnClearTag, SIGNAL(clicked(bool)), this, SLOT(clearAllBtn()));
    connect(this->btnDeleteTag, SIGNAL(clicked(bool)), this, SLOT(deleteTag()));
    connect(this->btnModifyTag, SIGNAL(clicked(bool)), this, SLOT(modifyTag()));
    connect(this->tagListUI, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateBtns()));
    connect(this->tagListUI, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onOffTag(QListWidgetItem*)));
}

void TagManager::updateBtns()
{
    this->btnDeleteTag->setEnabled(true);
    this->btnModifyTag->setEnabled(true);
}

void TagManager::addTagDialog()
{

}

void TagManager::modifyTag()
{

}

void TagManager::deleteTag()
{
    int index = this->tagListUI->currentRow();
    this->tagList.takeAt(index);
    this->tagBooleanList.takeAt(index);
    this->tagListUI->takeItem(index);
    this->tagListUI->setCurrentRow(-1);

    this->btnDeleteTag->setDisabled(true);
    this->btnModifyTag->setDisabled(true);
    if (this->tagList.isEmpty()) this->btnClearTag->setDisabled(true);
}

void TagManager::clear()
{
    this->tagList.clear();
    this->tagListUI->clear();

    this->btnClearTag->setDisabled(true);
    this->btnModifyTag->setDisabled(true);
    this->btnDeleteTag->setDisabled(true);
}

void TagManager::clearAllBtn()
{
    QMessageBox *dial = new QMessageBox();
    dial->setText("All Tags have been removed.");
    dial->setWindowTitle("Clear Message");

    this->clear();
    dial->exec();
}

void TagManager::enableTagManager(QValidator *v)
{
    this->validator = v;
    this->btnAddTag->setEnabled(true);
    this->tagListUI->setEnabled(true);
}

void TagManager::onOffTag(QListWidgetItem *item)
{
    int index = this->tagListUI->indexFromItem(item).row();
    this->tagBooleanList[index] = !this->tagBooleanList[index];
    if (!this->tagBooleanList[index]) item->setBackground(Qt::GlobalColor::red);
    else item->setBackground(Qt::GlobalColor::white);
}
