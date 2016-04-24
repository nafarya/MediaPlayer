#include "player.h"

#include <QFileDialog>
#include <QHBoxLayout>

Player::Player(QWidget *parent) : QWidget(parent)
{
    openButton = new QPushButton();
    openButton->setText("Open");

    playPauseButton = new QPushButton();
    playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    stopButton = new QPushButton();
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    prevButton = new QPushButton();
    prevButton->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));

    nextButton = new QPushButton();
    nextButton->setIcon(style()->standardIcon(QStyle::SP_ArrowForward));

    listwidget = new QListWidget();
    mediaPlayer = new QMediaPlayer();

    playlist = new QMediaPlaylist(mediaPlayer);
    mediaPlayer->setPlaylist(playlist);

    slider = new QSlider();
    mediaPlayer->setVolume(50);
    slider->setRange(0, 100);
    slider->setValue(50);


    connect(slider, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));
    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openFile()));
    connect(playPauseButton, SIGNAL(clicked(bool)), this, SLOT(playPauseMusic()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopMusic()));
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(nextSong()));
    connect(prevButton, SIGNAL(clicked(bool)), this, SLOT(prevSong()));

    createLayout();

}

void Player::createLayout()
{
    QHBoxLayout* horLayout = new QHBoxLayout;
    horLayout->addWidget(openButton);
    horLayout->addWidget(playPauseButton);
    horLayout->addWidget(stopButton);
    horLayout->addWidget(prevButton);
    horLayout->addWidget(nextButton);
    horLayout->addWidget(slider);
    horLayout->addWidget(listwidget);
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horLayout);
    setLayout(mainLayout);
}

void Player::openFile()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open File");
    QList<QMediaContent> content;
    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(f));
        QFileInfo fi(f);
        listwidget->addItem(fi.fileName());
    }
    playlist->addMedia(content);


}

void Player::playPauseMusic()
{
    if (mediaPlayer->state() == 1) {
        mediaPlayer->pause();
        playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else {
        mediaPlayer->play();
        playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }

}

void Player::stopMusic()
{
    mediaPlayer->stop();
}

void Player::nextSong()
{
    playlist->next();
}

void Player::prevSong()
{
    playlist->previous();
}
