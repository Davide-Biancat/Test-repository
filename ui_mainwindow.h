/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>
#include "libs/QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCustomPlot *plotWidget_2;
    QCustomPlot *plotWidget;
    QPushButton *changeGraph;
    QVBoxLayout *verticalLayout_2;
    QLabel *accX_label;
    QLabel *accY_label;
    QLabel *accZ_label;
    QLabel *gyroX_label;
    QLabel *gyroY_label;
    QLabel *gyroZ_label;
    QLabel *magX_label;
    QLabel *magY_label;
    QLabel *magZ_label;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    GLWidget *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(757, 416);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plotWidget_2 = new QCustomPlot(centralWidget);
        plotWidget_2->setObjectName(QStringLiteral("plotWidget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(plotWidget_2->sizePolicy().hasHeightForWidth());
        plotWidget_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(plotWidget_2, 6, 1, 2, 1);

        plotWidget = new QCustomPlot(centralWidget);
        plotWidget->setObjectName(QStringLiteral("plotWidget"));
        sizePolicy.setHeightForWidth(plotWidget->sizePolicy().hasHeightForWidth());
        plotWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(plotWidget, 5, 1, 1, 1);

        changeGraph = new QPushButton(centralWidget);
        changeGraph->setObjectName(QStringLiteral("changeGraph"));

        gridLayout->addWidget(changeGraph, 2, 1, 3, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        accX_label = new QLabel(centralWidget);
        accX_label->setObjectName(QStringLiteral("accX_label"));

        verticalLayout_2->addWidget(accX_label);

        accY_label = new QLabel(centralWidget);
        accY_label->setObjectName(QStringLiteral("accY_label"));

        verticalLayout_2->addWidget(accY_label);

        accZ_label = new QLabel(centralWidget);
        accZ_label->setObjectName(QStringLiteral("accZ_label"));

        verticalLayout_2->addWidget(accZ_label);

        gyroX_label = new QLabel(centralWidget);
        gyroX_label->setObjectName(QStringLiteral("gyroX_label"));

        verticalLayout_2->addWidget(gyroX_label);

        gyroY_label = new QLabel(centralWidget);
        gyroY_label->setObjectName(QStringLiteral("gyroY_label"));

        verticalLayout_2->addWidget(gyroY_label);

        gyroZ_label = new QLabel(centralWidget);
        gyroZ_label->setObjectName(QStringLiteral("gyroZ_label"));

        verticalLayout_2->addWidget(gyroZ_label);

        magX_label = new QLabel(centralWidget);
        magX_label->setObjectName(QStringLiteral("magX_label"));

        verticalLayout_2->addWidget(magX_label);

        magY_label = new QLabel(centralWidget);
        magY_label->setObjectName(QStringLiteral("magY_label"));

        verticalLayout_2->addWidget(magY_label);

        magZ_label = new QLabel(centralWidget);
        magZ_label->setObjectName(QStringLiteral("magZ_label"));

        verticalLayout_2->addWidget(magZ_label);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(pushButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        textEdit->setLineWrapMode(QTextEdit::NoWrap);

        horizontalLayout_2->addWidget(textEdit);

        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy2);
        textEdit_2->setLineWrapMode(QTextEdit::WidgetWidth);

        horizontalLayout_2->addWidget(textEdit_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 3);
        verticalLayout_2->setStretch(2, 3);
        verticalLayout_2->setStretch(3, 3);
        verticalLayout_2->setStretch(4, 3);
        verticalLayout_2->setStretch(5, 3);
        verticalLayout_2->setStretch(6, 3);
        verticalLayout_2->setStretch(7, 3);
        verticalLayout_2->setStretch(8, 3);
        verticalLayout_2->setStretch(10, 1);

        gridLayout->addLayout(verticalLayout_2, 2, 0, 6, 1);

        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 2, 2, 6, 1);

        gridLayout->setRowStretch(5, 2);
        gridLayout->setRowStretch(6, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 25);
        gridLayout->setColumnStretch(2, 25);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 757, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        changeGraph->setText(QApplication::translate("MainWindow", "Accelerometer", 0));
        accX_label->setText(QString());
        accY_label->setText(QString());
        accZ_label->setText(QString());
        gyroX_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gyroY_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gyroZ_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        magX_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        magY_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        magZ_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton->setText(QApplication::translate("MainWindow", "MysteriousButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
