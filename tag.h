#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QList>

class Tag
{
public:
    Tag(int pos);
    Tag(QList<int> *values);
    virtual QString toUI();
    virtual void useTag(QMediaPlayer *mediaPlayer);
    virtual Tag* copy();

    int getPosition() const;
    void setPosition(int newPosition);

    QList<int> *getValues() const;
    QList<QString> *getValuesNames() const;

    void setValues(QList<int> *newValues);
    void setValuesNames(QList<QString> *newValuesNames);

protected:
    QList<int> *values;
    QList<QString> *valuesNames;
};

class GoToTag : Tag{
public:
    GoToTag(int pos, int dest);
    GoToTag(QList<int> *values);
    QString toUI() override;
    void useTag(QMediaPlayer *mediaPlayer) override;
    Tag* copy() override;
    int getDestination() const;
    void setDestination(int newDestination);
};

#endif // TAG_H
