#include "audioplayer.h"

AudioPlayer::AudioPlayer(QWidget *parent)
    : QWidget{parent}
{
    this->initUI();
    this->eventHandler();

}

AudioPlayer::~AudioPlayer(){}

QMediaPlayer *AudioPlayer::getMediaPlayer() const
{
    return mediaPlayer;
}

void AudioPlayer::initUI(){

    //Basic UI elements
    this->btnPlayNPause = new QPushButton("Play");
    this->btnStop = new QPushButton("Stop");
    this->tickInput = new FocusLineEdit();
    this->maxTick = new QLabel("--");

    this->btnPlayNPause->setDisabled(true);
    this->btnStop->setDisabled(true);
    this->tickInput->setDisabled(true);

    this->mediaSlider = new ClickableSlider(Qt::Orientation::Horizontal);
    this->mediaSlider->setMaximum(0);
    this->mediaSlider->setDisabled(true);

    // Specific audio elements
    this->audioOutput = new QAudioOutput();
    this->mediaPlayer = new QMediaPlayer();
    this->mediaPlayer->setAudioOutput(this->audioOutput);

    // Layout
    this->masterLayout = new QVBoxLayout();
    QHBoxLayout *row = new QHBoxLayout();
    QHBoxLayout *btnSubrow = new QHBoxLayout();

    row->addWidget(this->tickInput, 1);
    row->addWidget(this->mediaSlider,3);
    row->addWidget(this->maxTick);

    btnSubrow->addWidget(this->btnPlayNPause);
    btnSubrow->addWidget(this->btnStop);

    this->masterLayout->addLayout(row);
    this->masterLayout->addLayout(btnSubrow);
    this->setLayout(this->masterLayout);
}

void AudioPlayer::eventHandler()
{
    connect(this->btnPlayNPause, SIGNAL(clicked(bool)), this, SLOT(playNPause()));
    connect(this->btnStop, SIGNAL(clicked(bool)), this, SLOT(stop()));
    connect(this->mediaPlayer, SIGNAL(sourceChanged(QUrl)), this, SLOT(newAudioFile()));
    connect(this->mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration()));
    connect(this->mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(updateSlider()));
    connect(this->mediaPlayer, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)), this, SLOT(isMediaEnded(QMediaPlayer::PlaybackState)));
    connect(this->mediaSlider, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(this->mediaSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
    connect(this->mediaSlider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    connect(this->tickInput, SIGNAL(focusChanged(bool)), this, SLOT(onFocus(bool)));
    connect(this->tickInput, SIGNAL(returnPressed()), this, SLOT(jump()));
}

void AudioPlayer::updateSlider()
{
    if (!this->isDragging){
        this->mediaSlider->setValue(this->mediaPlayer->position());
        this->tickInput->setText(QString::number(this->mediaPlayer->position()));
    }
}

void AudioPlayer::isMediaEnded(QMediaPlayer::PlaybackState playbackState)
{
    if (playbackState == QMediaPlayer::PlaybackState::StoppedState){
        this->btnStop->setDisabled(true);
        this->mediaSlider->setValue(0);
        this->isPlaying = false;
        this->btnPlayNPause->setText("Play");
    }
    else this->btnStop->setEnabled(true);
}

void AudioPlayer::sliderPressed()
{
    this->isDragging = true;
    this->mediaPlayer->pause();
    this->mediaPlayer->setPosition(this->mediaSlider->value());
}

void AudioPlayer::sliderMoved(int v)
{
    this->tickInput->setText(QString::number(v));
    this->mediaPlayer->setPosition(v);
}

void AudioPlayer::sliderReleased()
{
    this->isDragging = false;
    this->mediaPlayer->setPosition(this->mediaSlider->value());
    if (this->isPlaying) this->mediaPlayer->play();
}

void AudioPlayer::updateDuration()
{
    int total = this->mediaPlayer->duration();
    this->mediaSlider->setMaximum(total);
    this->maxTick->setText(QString::number(total));
    this->onlyTicks = new QIntValidator();
    this->onlyTicks->setRange(0, total);
    this->tickInput->setValidator(this->onlyTicks);
}

void AudioPlayer::newAudioFile()
{
    this->mediaSlider->setEnabled(true);
    this->btnPlayNPause->setEnabled(true);
    this->btnStop->setDisabled(true);
    this->tickInput->setEnabled(true);
    this->tickInput->setText("0");
    this->clearFocus();
}

void AudioPlayer::playNPause()
{
    if (!this->isPlaying){
        this->mediaPlayer->play();
        this->btnPlayNPause->setText("Pause");
    }
    else{
        this->mediaPlayer->pause();
        this->btnPlayNPause->setText("Play");
    }
    this->isPlaying = !this->isPlaying;
    this->btnStop->setEnabled(true);
}

void AudioPlayer::stop()
{
    if (this->mediaPlayer->isPlaying()){
        this->mediaPlayer->stop();
    }

    this->mediaPlayer->setPosition(0);

    this->btnStop->setDisabled(true);
}

void AudioPlayer::onFocus(bool focus)
{
    if (focus && this->mediaPlayer->isPlaying()){
        this->mediaPlayer->pause();
        this->btnPlayNPause->setText("Play");
        this->isPlaying = !this->isPlaying;
        this->btnStop->setEnabled(true);
    }
}

void AudioPlayer::jump()
{
    int value;
    if (!this->tickInput->hasAcceptableInput()){
        value = abs(this->tickInput->text().toInt());
        this->tickInput->setText(QString::number(value%this->onlyTicks->top()));
    }
    else value = this->tickInput->text().toInt();
    this->mediaPlayer->setPosition(value);
}


