#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMediaPlaylist>
#include <QSlider>

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

private:
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* playlist;

    QListWidget* listwidget;

    QVBoxLayout* mainLayout;

    QPushButton* openButton;
    QPushButton* playPauseButton;
    QPushButton* stopButton;
    QPushButton* prevButton;
    QPushButton* nextButton;
    QSlider* slider;
};

#endif // PLAYER_H
