/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Jan 18 23:26:26 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "basicopenglview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Model;
    QAction *actionRemove_Selected;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    BasicOpenGLView *oglwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QLabel *label;
    QSlider *scaleSlider;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(770, 549);
        MainWindow->setMaximumSize(QSize(770, 16777215));
        actionAdd_Model = new QAction(MainWindow);
        actionAdd_Model->setObjectName(QString::fromUtf8("actionAdd_Model"));
        actionRemove_Selected = new QAction(MainWindow);
        actionRemove_Selected->setObjectName(QString::fromUtf8("actionRemove_Selected"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setMinimumSize(QSize(500, 300));

        horizontalLayout->addWidget(oglwidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(230, 0));
        groupBox->setMaximumSize(QSize(230, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(200, 300));
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setAlternatingRowColors(true);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setSelectionRectVisible(true);

        verticalLayout->addWidget(listWidget);

        addButton = new QPushButton(groupBox);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        removeButton = new QPushButton(groupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        scaleSlider = new QSlider(groupBox);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        scaleSlider->setMinimum(10);
        scaleSlider->setMaximum(100);
        scaleSlider->setValue(100);
        scaleSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(scaleSlider);


        horizontalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionAdd_Model);
        menuEdit->addAction(actionRemove_Selected);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAdd_Model->setText(QApplication::translate("MainWindow", "Add Model...", 0, QApplication::UnicodeUTF8));
        actionRemove_Selected->setText(QApplication::translate("MainWindow", "Remove Selected", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Models", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("MainWindow", "Add...", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
