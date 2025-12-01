#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include "clickableslider.h"
#include "focuslineedit.h"

class AudioPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit AudioPlayer(QWidget *parent = nullptr);
    ~AudioPlayer();


    QMediaPlayer *getMediaPlayer() const;

private:
    QPushButton *btnPlayNPause;
    QPushButton *btnStop;
    FocusLineEdit *tickInput;
    ClickableSlider *mediaSlider;
    QLabel *maxTick;
    QAudioOutput *audioOutput;
    QMediaPlayer *mediaPlayer;
    QVBoxLayout *masterLayout;
    bool isPlaying;
    bool isDragging;
    QIntValidator *onlyTicks;
    void initUI();
    void eventHandler();

private slots:
    void updateSlider();
    void isMediaEnded(QMediaPlayer::PlaybackState playbackState);
    void sliderPressed();
    void sliderMoved(int v);
    void sliderReleased();
    void updateDuration();
    void newAudioFile();
    void playNPause();
    void stop();
    void onFocus(bool focus);
    void jump();


signals:
};

#endif // AUDIOPLAYER_H
