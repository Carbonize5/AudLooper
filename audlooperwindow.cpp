#include "audlooperwindow.h"
#include "audioplayer.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMenuBar>
#include <iostream>

AudLooperWindow::AudLooperWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setup();
    this->initUI();
    this->eventHandler();
}

AudLooperWindow::~AudLooperWindow() {}

void AudLooperWindow::setup(){
    this->setWindowTitle("AudLoop");
    this->mimeTypeFilters.append("audio/mpeg");
    this->mimeTypeFilters.append("audio/ogg");
    this->mimeTypeFilters.append("audio/wav");
    /*this->mime_type_filters.push_back("audio/mpeg");
    this->mime_type_filters.push_back("audio/ogg");
    this->mime_type_filters.push_back("audio/wav");*/
}

void AudLooperWindow::initUI(){
    //QLabel *label = new QLabel("Hello World");

    // AudioPlayer Widget
    this->audioPlayer = new AudioPlayer(this);

    // Tag Manager Widget
    this->tagManager = new TagManager(this);

    // App Layout

    // // Menu Bar
    this->loadAudioAction = new QAction("Load File", this);
    this->loadAudioAction->setStatusTip("Load an Audio file int the player");

    QMenuBar *menu = this->menuBar();
    QMenu *file_menu = menu->addMenu("File");
    file_menu->addAction(this->loadAudioAction);

    // // Central Widget
    this->setCentralWidget(this->tagManager);

    // // Docker Widgets
    // // // Bottom Widget (Audio Player)


    std::cout << "run" << std::endl;
}

void AudLooperWindow::eventHandler(){
    //connect(this->loadAudioAction, SIGNAL(triggered(bool)), this, SLOT(loadAudioFile()));
}

void AudLooperWindow::loadAudioFile()
{
    std::cout << "clicked" << std::endl;
    QFileDialog *dialog = new QFileDialog(this, "Load Audio File");
    dialog->setMimeTypeFilters(this->mimeTypeFilters);
    dialog->setFileMode(QFileDialog::FileMode::ExistingFile);
    dialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    dialog->setDirectory(QStandardPaths::writableLocation(QStandardPaths::StandardLocation::MusicLocation));

    if (dialog->exec() == QFileDialog::DialogCode::Accepted){
        if (!dialog->selectedFiles().isEmpty()){
            QMediaPlayer *player = this->audioPlayer->getMediaPlayer();
            if (!player->source().isEmpty()) player->stop();
            player->setSource(QUrl::fromLocalFile(dialog->selectedFiles().at(0)));
            //player.
        }
    }
}
