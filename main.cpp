// Morgan Langlais
// CS 5389
// Summer 2020
// Homework 01

#include <QApplication>
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
    g.resize(100, 100);
    g.show();

    QWidget *window = new QWidget;
    window->setMinimumSize(800, 800);
    window->setWindowTitle("Morgan Langlais");

    // Create the layout boxes
    QVBoxLayout *layoutVert = new QVBoxLayout(window);
    QHBoxLayout *layoutShapes = new QHBoxLayout();
    QHBoxLayout *layoutMid = new QHBoxLayout();
    QHBoxLayout *layoutTop = new QHBoxLayout();
    QHBoxLayout *layoutLevel = new QHBoxLayout();
    QHBoxLayout *layoutBottom = new QHBoxLayout();
    QHBoxLayout *layoutExit = new QHBoxLayout();

    // Create volume slider and display and connect them
    QLabel *volumeLabel = new QLabel("Volume");
    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setRange(0,50);
    QLCDNumber *volumeDisplay = new QLCDNumber(5);
    volumeDisplay->setMaximumSize(QSize(50,50));
    volumeDisplay->display(10);

    // When the volume slider changes, the value is passed to the display
    QObject::connect(volume, SIGNAL(valueChanged(int)), volumeDisplay, SLOT(display(int)));

    // AM/FM and presets
    QRadioButton *amButton = new QRadioButton("AM");
    QRadioButton *fmButton = new QRadioButton("FM");
    QPushButton *preset1 = new QPushButton("1");
    QPushButton *preset2 = new QPushButton("2");
    QPushButton *preset3 = new QPushButton("3");
    QPushButton *preset4 = new QPushButton("4");
    QPushButton *preset5 = new QPushButton("5");

    // Create channel tuner and display and connect them
    QLabel *tunerLabel = new QLabel("Tuner");
    QLCDNumber *stationDisplay = new QLCDNumber(5);
    stationDisplay->setMinimumSize(QSize(200,200));
    QDial *stationScroll = new QDial();
    stationScroll->setMinimum(80);
    stationScroll->setMaximum(109);

    // When the dial changes, the value is passed to the display
    QObject::connect(stationScroll, SIGNAL(valueChanged(int)), stationDisplay, SLOT(display(int)));

    // Create bass and treble sliders
    QLabel *bassLabel = new QLabel("Bass");
    QSlider *bass = new QSlider(Qt::Vertical);
    QLabel *trebleLabel = new QLabel("Treble");
    QScrollBar *treble = new QScrollBar(Qt::Vertical);

    // Exit button
    QPushButton *quit = new QPushButton();
    quit->setText("Exit");
    // Exits the app
    QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));

    // Add tuner widgets to the top row
    layoutTop->addWidget(tunerLabel);
    layoutTop->addWidget(stationDisplay);
    layoutTop->addWidget(stationScroll);

    // Add AM and FM buttons to the middle row
    layoutMid->addWidget(amButton);
    layoutMid->addWidget(fmButton);
    layoutMid->addWidget(preset1);
    layoutMid->addWidget(preset2);
    layoutMid->addWidget(preset3);
    layoutMid->addWidget(preset4);
    layoutMid->addWidget(preset5);

    // Add volume widgets to the same row
    layoutLevel->addWidget(bass);
    layoutLevel->addWidget(bassLabel);
    layoutLevel->addWidget(treble);
    layoutLevel->addWidget(trebleLabel);
    layoutLevel->addWidget(&g);

    // Add bass and treble to the bottom row
    layoutBottom->addWidget(volumeLabel);
    layoutBottom->addWidget(volume);
    layoutBottom->addWidget(volumeDisplay);

    // add the exit button to the layout
    layoutExit->addWidget(quit);

    // add shapes
    layoutShapes->addWidget(&g);

    // Add inner layouts to outer layout
    layoutVert->addLayout(layoutTop);
    layoutVert->addLayout(layoutMid);
    layoutVert->addLayout(layoutLevel);
    layoutVert->addLayout(layoutBottom);
    layoutVert->addLayout(layoutExit);
    layoutVert->addLayout(layoutShapes);

    window->show();

    return app.exec();
}

