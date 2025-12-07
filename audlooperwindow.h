#ifndef AUDLOOPERWINDOW_H
#define AUDLOOPERWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>

#include "audioplayer.h"
#include "tagmanager.h"

class AudLooperWindow : public QMainWindow
{
    Q_OBJECT

public:
    AudLooperWindow(QWidget *parent = nullptr);
    ~AudLooperWindow();

private:
    QStringList mimeTypeFilters;
    AudioPlayer *audioPlayer;
    TagManager *tagManager;
    QAction *loadAudioAction;
    QAction *saveAction;
    QAction *loadSaveAction;
    void setup();
    void initUI();
    void eventHandler();

private slots:
    void loadAudioFile();

};
#endif // AUDLOOPERWINDOW_H
