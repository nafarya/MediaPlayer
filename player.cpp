#include "player.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QTime>

Player::Player(QWidget *parent) : QWidget(parent)
{
    openButton = new QPushButton();
    openButton->setText("Add song");

    delButton = new QPushButton();
    delButton->setText("Delete Song");

    addImgButton = new QPushButton();
    addImgButton->setText("Add Img");

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

    sliderVol = new QSlider();
    mediaPlayer->setVolume(50);
    sliderVol->setRange(0, 100);
    sliderVol->setValue(50);

    sliderPos = new QSlider(Qt::Horizontal);
    sliderPos->setMinimumWidth(100);

    currentTime  = new QLabel(msecsToString(0));
    remainingTime = new QLabel(msecsToString(0));
    currentSong = new QLabel("CurrentSong");
    currentSong->resize(70, currentSong->height());
    currentSong->setWordWrap(true);

    currentImage = new QLabel();
    currentImage->setScaledContents(true);
    currentImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);
    currentImage->setMinimumSize(450, 250);

    comboBox = new QComboBox();
    comboBox->addItem("15", 15);
    comboBox->addItem("30", 30);
    comboBox->addItem("45", 45);

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateImageTime()));
    connect(sliderPos, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
    connect(sliderVol, SIGNAL(valueChanged(int)), mediaPlayer, SLOT(setVolume(int)));
    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openFile()));
    connect(playPauseButton, SIGNAL(clicked(bool)), this, SLOT(playPauseMusic()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopMusic()));
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(nextSong()));
    connect(prevButton, SIGNAL(clicked(bool)), this, SLOT(prevSong()));
    connect(delButton, SIGNAL(clicked(bool)), this, SLOT(delSong()));
    connect(addImgButton, SIGNAL(clicked(bool)), this, SLOT(addImage()));

    connect(mediaPlayer, SIGNAL(currentMediaChanged(QMediaContent)), SLOT());
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));

    createLayout();

}

void Player::createLayout()
{
    QVBoxLayout* verLayout1 = new QVBoxLayout;

    QVBoxLayout* verLayout2 = new QVBoxLayout;

    QHBoxLayout* horLayout3 = new QHBoxLayout;
    horLayout3->addWidget(openButton);
    horLayout3->addWidget(delButton);
    horLayout3->addWidget(addImgButton);
    horLayout3->addWidget(comboBox);
    verLayout2->addLayout(horLayout3);
    verLayout2->addWidget(listwidget);

    QHBoxLayout* horLayout1 = new QHBoxLayout;
    horLayout1->addWidget(currentImage);
    horLayout1->addWidget(sliderVol);

    QHBoxLayout* horLayout2 = new QHBoxLayout;
    horLayout2->addWidget(prevButton);
    horLayout2->addWidget(playPauseButton);
    horLayout2->addWidget(stopButton);
    horLayout2->addWidget(currentTime);
    horLayout2->addWidget(sliderPos);
    horLayout2->addWidget(remainingTime);
    horLayout2->addWidget(nextButton);

    verLayout1->addLayout(horLayout1);
    verLayout1->addLayout(horLayout2);

    mainLayout = new QVBoxLayout;

    QHBoxLayout* mainHorLayout = new QHBoxLayout;
    mainHorLayout->addLayout(verLayout1);
    mainHorLayout->addLayout(verLayout2);
    mainLayout->addLayout(mainHorLayout);
    setLayout(mainLayout);


    /*QHBoxLayout* horLayout = new QHBoxLayout;
    horLayout->addWidget(addImgButton);
    horLayout->addWidget(currentImage);
    horLayout->addWidget(openButton);
    horLayout->addWidget(delButton);
    horLayout->addWidget(currentSong);
    horLayout->addWidget(currentTime);
    horLayout->addWidget(sliderPos);
    horLayout->addWidget(remainingTime);
    horLayout->addWidget(playPauseButton);
    horLayout->addWidget(stopButton);
    horLayout->addWidget(prevButton);
    horLayout->addWidget(nextButton);
    horLayout->addWidget(sliderVol);
    horLayout->addWidget(listwidget);
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horLayout);
    setLayout(mainLayout);
    */
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
    playlist->setCurrentIndex(listwidget->currentRow());
    listwidget->setCurrentRow(playlist->currentIndex());
    currentSong->setText(listwidget->currentItem()->text());
    if (mediaPlayer->state() == 1) {
        mediaPlayer->pause();
        timer->stop();
        playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else {
        mediaPlayer->play();
        timer->start(1000);
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
    listwidget->setCurrentRow(listwidget->currentRow() + 1);
    setCurrentNameOfSong();
}

void Player::prevSong()
{
    playlist->previous();
    listwidget->setCurrentRow(listwidget->currentRow() - 1);
    setCurrentNameOfSong();
}

void Player::delSong()
{
    playlist->removeMedia(listwidget->currentRow());
    qDeleteAll(listwidget->selectedItems());
}

void Player::slotSetMediaPosition(int p)
{
    mediaPlayer->setPosition(p);

}

QString Player::msecsToString(qint64 n)
{
    int nHours = (n/(60*60*1000));
    int nMinutes = ((n % (60*60*1000)) / (60*1000));
    int nSeconds = ((n % (60*1000)) / 1000);
    return QTime (nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void Player::slotSetDuration(qint64 n)
{
    sliderPos->setRange(0,n);
    currentTime->setText(msecsToString(0));
    remainingTime->setText(msecsToString(n));
}

void Player::slotSetSliderPosition(qint64 n)
{
    sliderPos->setValue(n);
    currentTime->setText(msecsToString(n));
    int nDuration = sliderPos->maximum();
    remainingTime->setText(msecsToString(nDuration-n));
}

void Player::setCurrentNameOfSong()
{
    currentSong->setText(listwidget->currentItem()->text());
}

void Player::addImage()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Browse","C://","Image Files (*.png *.jpg *.bmp *.jpeg)");

    for(const QString& f:files)
    {
        images.push_back(f);
    }
    nextPic();
}

void Player::nextPic()
{
    QPixmap pic;
    pic.load(images.at(currentIndexOfPic));
    currentImage->setPixmap(pic.scaled(pic.height()*0.5, pic.width()*0.5, Qt::KeepAspectRatio));
    currentIndexOfPic++;
    if (currentIndexOfPic == images.size()) {
        currentIndexOfPic = 0;
    }
}

void Player::updateImageTime()
{
    currentImageTime++;
    if (currentImageTime == comboBox->currentData()) {
        currentImageTime = 0;
        nextPic();
    }
}
