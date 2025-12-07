#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QWidget>
#include <QValidator>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>

#include "tag.h"

class TagManager : public QWidget
{
    Q_OBJECT
public:
    explicit TagManager(QWidget *parent = nullptr);

private:
    QValidator *validator;
    QList<Tag> tagList;
    QList<bool> tagBooleanList;
    QListWidget *tagListUI;
    QPushButton *btnAddTag;
    QPushButton *btnModifyTag;
    QPushButton *btnDeleteTag;
    QPushButton *btnClearTag;
    QVBoxLayout *masterLayout;

    void initUI();
    void eventHandler();

private slots:
    void updateBtns();
    void addTagDialog();
    void modifyTag();
    void deleteTag();
    void clear();
    void clearAllBtn();
    void enableTagManager(QValidator *v);
    void onOffTag(QListWidgetItem *item);

signals:
};

#endif // TAGMANAGER_H
