#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    // we start the timer with a timeout interval of 20ms
    animationTimer->start(20);

    connect(ui->oglwidget, SIGNAL(addedNewGeometry(std::string)), this, SLOT(newGeometryAdded(std::string)));
    connect(ui->oglwidget, SIGNAL(removedGeometry(std::string)), this, SLOT(geometryRemoved(std::string)));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addGeometry()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeGeometry()));

    Matrix4x4 *matrix1 = new Matrix4x4();
    Matrix3x3 *matrix2 = new Matrix3x3();

    for (int i = 0; i <= 15; i ++)
    {
        matrix1->elements[i] = i;
    }

    Matrix4x4 newMatrix1;
    newMatrix1 = *matrix1 * 2;
    newMatrix1.printMatrix();

    for (int i = 0; i <= 8; i ++)
    {
        matrix2->elements[i] = i;
    }

    Matrix3x3 newMatrix2;
    newMatrix2 = *matrix2 * 2;
    newMatrix2.printMatrix();

}

void MainWindow::drawOpenGL()
{
    // whenever drawOpenGL gets called, we only want to repaint our opengl widget
    ui->oglwidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

