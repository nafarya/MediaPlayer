#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMediaPlaylist>
#include <QSlider>
#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QTimer>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    void createLayout();


signals:

public slots:
    void openFile();
    void playPauseMusic();
    void stopMusic();
    void nextSong();
    void prevSong();
    void delSong();
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64 n);
    void slotSetSliderPosition(qint64 n);
    void setCurrentNameOfSong();
    void addImage();
    void nextPic();
    void updateImageTime();
    void addSongToMyPlaylist();
    void startMyPLaylist();
    void updatePlayPauseButton();

private:
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* playlist;
    QMediaPlaylist* myPlaylist;

    QListWidget* listwidget;
    QListWidget* listwidgetForMyPLaylist;

    QVBoxLayout* mainLayout;

    QPushButton* addToMyPlaylist;

    QPushButton* startMyPLaylistButton;
    QPushButton* openButton;
    QPushButton* playPauseButton;
    QPushButton* stopButton;
    QPushButton* prevButton;
    QPushButton* nextButton;
    QPushButton* delButton;
    QPushButton* addImgButton;

    QSlider* sliderVol;
    QSlider* sliderPos;

    QLabel* currentTime;
    QLabel* remainingTime;
    QLabel* currentSong;
    QLabel* currentImage;

    QComboBox* comboBox;
    QTimer* timer;
    QImage img;
    QPixmap pixmap;
    int currentImageTime = 0;

    QList<QMediaContent> contentForPlaylist;

    QString msecsToString(qint64 n);

    QList<QString> images;
    int currentIndexOfPic = 0;
};

#endif // PLAYER_H
