#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QtMultimedia/QMediaPlayer>

class Tag
{
public:
    Tag(int pos);
    int getPosition() const;
    void setPosition(int newPosition);
    QString toUI();
    void useTag(QMediaPlayer *mediaPlayer);

protected:
    int position;
};

class GoToTag : Tag{
public:
    GoToTag(int pos, int dest);
    int getDestination() const;
    void setDestination(int newDestination);
    QString toUI();
    void useTag(QMediaPlayer *mediaPlayer);

protected:
    int destination;
};

#endif // TAG_H
