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

    Matrix3x3 *m31 = new Matrix3x3();
    Matrix3x3 *m32 = new Matrix3x3();

    Matrix3x3 newMatrix;

    newMatrix = *m31 + *m32;
    newMatrix.printMatrix();

    newMatrix = newMatrix * newMatrix;
    newMatrix.printMatrix();

    newMatrix = newMatrix - *m32;
    newMatrix.printMatrix();


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

