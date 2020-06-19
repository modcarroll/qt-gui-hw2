// Morgan Langlais
// CS 5389
// Summer 2020
// Homework 01

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QLCDNumber>
#include <QRadioButton>
#include <QDial>
#include <QLabel>
#include <QScrollBar>
#include <globj.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GLobj g;
    g.show();

    QWidget *window = new QWidget;
    window->setMinimumSize(800, 800);
    window->setWindowTitle("Morgan Langlais");

    // Create the layout boxes
    QGridLayout *grid = new QGridLayout();
    window->setLayout(grid);

    // Create volume slider and display and connect them
    QLabel *volumeLabel = new QLabel("Volume");
    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setRange(0,50);
    QLCDNumber *volumeDisplay = new QLCDNumber(5);
    volumeDisplay->setMaximumSize(QSize(50,50));
    volumeDisplay->display(10);

    grid->addWidget(volumeLabel, 0, 0);
    grid->addWidget(volume, 0, 1);
    grid->addWidget(volumeDisplay, 0, 2);

    // When the volume slider changes, the value is passed to the display
    QObject::connect(volume, SIGNAL(valueChanged(int)), volumeDisplay, SLOT(display(int)));

    // AM/FM and presets
    QRadioButton *amButton = new QRadioButton("AM");
    QRadioButton *fmButton = new QRadioButton("FM");
    QPushButton *preset1 = new QPushButton("1");
    QPushButton *preset2 = new QPushButton("2");
//    QPushButton *preset3 = new QPushButton("3");
//    QPushButton *preset4 = new QPushButton("4");
//    QPushButton *preset5 = new QPushButton("5");

    grid->addWidget(amButton, 3, 0);
    grid->addWidget(fmButton, 3, 1);
    grid->addWidget(preset1, 3, 2);
    grid->addWidget(preset2, 3, 3);
//    grid->addWidget(preset3, 3, 3);
//    grid->addWidget(preset4, 3, 3);
//    grid->addWidget(preset5, 3, 3);

    // Create channel tuner and display and connect them
    QLabel *tunerLabel = new QLabel("Tuner");
    QLCDNumber *stationDisplay = new QLCDNumber(5);
    stationDisplay->setMinimumSize(QSize(50,50));
    QDial *stationScroll = new QDial();
    stationScroll->setMinimum(80);
    stationScroll->setMaximum(109);

    grid->addWidget(tunerLabel, 2, 0);
    grid->addWidget(stationDisplay, 2, 1);
    grid->addWidget(stationScroll, 2, 2);

    // When the dial changes, the value is passed to the display
    QObject::connect(stationScroll, SIGNAL(valueChanged(int)), stationDisplay, SLOT(display(int)));

    // Create bass and treble sliders
    QLabel *bassLabel = new QLabel("Bass");
    QSlider *bass = new QSlider(Qt::Vertical);
    QLabel *trebleLabel = new QLabel("Treble");
    QScrollBar *treble = new QScrollBar(Qt::Vertical);

    grid->addWidget(bassLabel, 1, 0);
    grid->addWidget(bass, 1, 1);
    grid->addWidget(trebleLabel, 1, 2);
    grid->addWidget(treble, 1, 3);

    // add shapes
    grid->addWidget(&g, 1, 4, -1, -1);
    grid->setColumnStretch(4, 1);

    // Exit button
    QPushButton *quit = new QPushButton();
    quit->setText("Exit");
    // Exits the app
    QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));
    grid->addWidget(quit, 4, 0, 4, 4);

    window->show();

    return app.exec();
}

