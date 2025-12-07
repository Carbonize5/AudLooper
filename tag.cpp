#include "tag.h"
#include <iostream>
#include <QMediaMetaData>

Tag::Tag(int pos) {
    this->values = new QList<int>();
    this->values->append(pos);
    this->valuesNames = new QList<QString>();
    this->valuesNames->append("Position");
}

Tag::Tag(QList<int> *values)
{
    assert(values->size() == 1);
    this->values = values;
}

int Tag::getPosition() const
{
    return this->values->at(0);
}

void Tag::setPosition(int newPosition)
{
    this->values->takeAt(0);
    this->values->insert(0, newPosition);
}

QList<int> *Tag::getValues() const
{
    return values;
}

QList<QString> *Tag::getValuesNames() const
{
    return valuesNames;
}

void Tag::setValues(QList<int> *newValues)
{
    values = newValues;
}

void Tag::setValuesNames(QList<QString> *newValuesNames)
{
    valuesNames = newValuesNames;
}

QString Tag::toUI()
{
    return "At " + QString::number(this->values->at(0));
}

void Tag::useTag(QMediaPlayer *mediaPlayer)
{
    QString str = "Tag Used, MediaPlayer is playing: " + mediaPlayer->metaData().stringValue(QMediaMetaData::Key::Title);
    std::cout << str.toStdString() << std::endl;
}

Tag *Tag::copy()
{
    return new Tag(this->values->at(0));
}

GoToTag::GoToTag(int pos, int dest) : Tag{pos}
{
    this->values->append(dest);
    this->valuesNames->append("Destination");
}

GoToTag::GoToTag(QList<int> *values) : GoToTag{values->at(0), values->at(1)} {assert(values->size() == 2);}

int GoToTag::getDestination() const
{
    return this->values->at(1);
}

void GoToTag::setDestination(int newDestination)
{
    this->values->takeAt(1);
    this->values->insert(1, newDestination);
}

QString GoToTag::toUI(){
    return Tag::toUI() + " go to " + QString::number(this->values->at(1));
}

void GoToTag::useTag(QMediaPlayer *mediaPlayer)
{
    Tag::useTag(mediaPlayer);
    mediaPlayer->setPosition(this->values->at(1));
}

Tag *GoToTag::copy()
{
    return new GoToTag(this->values);
}
