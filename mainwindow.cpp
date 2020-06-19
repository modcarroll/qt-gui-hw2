#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include <gl.h>
#include "globj.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Morgan Radio");
}

MainWindow::~MainWindow()
{
    delete ui;
}


GLobj::GLobj(QWidget *parent)
    : QGLWidget(parent)
{

}

GLobj::~GLobj()
{

}

//Initialize the GL settings
void GLobj::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

//Set up the viewport based on the screen dimentions
//Function is called implicitly by initializeGL and when screen is resized
void GLobj::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is streached
//    if(w>h)
//        glViewport((w-h)/2, 0, h, h);
//    else
//        glViewport(0, (h-w)/2, w, w);

    glViewport(0, 0, 500, 500);

    //setup the projection and switch to model view for transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //implicit call to paintGL after resized
}

//Paints the GL scene
void GLobj::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    float radius = 0.1;

    // draw a pentagon
    glTranslatef(-.4,.4,0);
    glColor3f(0, 1, 1);
    float rotate = 360.0/5;
    float degree = rotate/5 + 180;
    float degToRad = 180/3.14159;
    glBegin(GL_POLYGON);
        for(int i = 0; i < 5; i++, degree += rotate) {
            float vertx = 0.5 * sin(degree/degToRad);
            float verty = 0.5 * sin((90 - degree)/degToRad);
            glVertex3f(vertx, verty, 0); }
    glEnd();

    // draw a hexagon
    glTranslatef(0,-.9,0);
    glColor3f(1, 1, 0);
    rotate = 360.0/6;
    degree = rotate/6 + 180;
    degToRad = 180/3.14159;
    glBegin(GL_POLYGON);
        for(int i = 0; i < 5; i++, degree += rotate) {
            float vertx = 0.5 * sin(degree/degToRad);
            float verty = 0.5 * sin((90 - degree)/degToRad);
            glVertex3f(vertx, verty, 0); }
    glEnd();

    // draw a triangle
    glLoadIdentity();
    glPointSize(3);
    glTranslatef(.2,-.6,0);
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex3f(.3, 0.0, 0.0);
        glVertex3f(0.0, .3, 0.0);
        glVertex3f(0.0, 0.0, .3);
    glEnd();

    // draw a dotted line
    glLoadIdentity();
    glPointSize(4);
    glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
       for(float i = 0; i <= 50; ){
          glVertex2f(i,i);
          i+=radius/2;
       }
    glEnd();

    // draw a line
    glBegin(GL_POINTS);
    glPointSize(4);
    int samples = 1000;
        float mx = .002;
        float my = -.002;

        for (int i = 0; i < samples; i++)
        {
            glVertex2f(i*mx, i *my);
        }
    glEnd();

    // draw a circle
    glLoadIdentity();
    glPointSize(6);
    glColor3f(1, 0, 0);
    glTranslatef(.6,0,0);
    const float rads = 0.01745329;
    glBegin(GL_LINE_LOOP);
       for (int i=0; i < 360; i++)
       {
          float degInRad = i*rads;
          glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
       }
    glEnd();

    // draw a point
    glLoadIdentity();
    glPointSize(2);
    glTranslatef(.3,0,0);
    glBegin(GL_POINTS);
     glColor3f(0, 1, 1);
     glVertex2i(-0.75, 0);
    glEnd();

    // draw a quad
    glLoadIdentity();
    glBegin(GL_QUADS);
        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(-radius, -radius,  radius);
        glVertex3f( radius, -radius,  radius);
        glVertex3f( radius,  radius,  radius);
        glVertex3f(-radius,  radius,  radius);
    glEnd();
}
