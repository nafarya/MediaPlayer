#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QMediaPlaylist>
#include <QLabel>
#include <QtWidgets>
#include <player.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Player pl;
    pl.resize(350,175);
    pl.show();
    //MainWindow w;
    //w.show();
    /*QGridLayout *gridLayout = new QGridLayout;
    QSlider* slider = new QSlider();
    QLabel label1;
    label1.setText("Azaza");
    QPushButton* b1 = new QPushButton("StartStop");
    QPushButton* b2 = new QPushButton("Prev");
    QPushButton* b3 = new QPushButton("Next");
    QList<QString> content;

    //gridLayout->addWidget(slider,0,0,1,1);
    gridLayout->addWidget(b2,0,1,1,1);
    gridLayout->addWidget(b3,0,2,1,1);
    // Create a widget
       QWidget *w = new QWidget();

       // Set the grid layout as a main layout
       w->setLayout(gridLayout);

       // Window title
       w->setWindowTitle("Grid Layouts (3x4)");

       // Display
       w->show();
    */
    return a.exec();
}
