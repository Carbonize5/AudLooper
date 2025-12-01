#include "tag.h"
#include <iostream>
#include <QMediaMetaData>

Tag::Tag(int pos) {
    this->position = pos;
}

int Tag::getPosition() const
{
    return position;
}

void Tag::setPosition(int newPosition)
{
    position = newPosition;
}

QString Tag::toUI()
{
    return "At " + QString::number(this->position);
}

void Tag::useTag(QMediaPlayer *mediaPlayer)
{
    QString str = "Tag Used, MediaPlayer is playing: " + mediaPlayer->metaData().stringValue(QMediaMetaData::Key::Title);
    std::cout << str.toStdString() << std::endl;
}

GoToTag::GoToTag(int pos, int dest) : Tag{pos}
{
    this->position = pos;
    this->destination = dest;
}

int GoToTag::getDestination() const
{
    return destination;
}

void GoToTag::setDestination(int newDestination)
{
    destination = newDestination;
}

QString GoToTag::toUI(){
    return "At " + QString::number(this->position) + " got to " + QString::number(this->destination);
}

void GoToTag::useTag(QMediaPlayer *mediaPlayer)
{
    Tag::useTag(mediaPlayer);
    mediaPlayer->setPosition(this->destination);
}
