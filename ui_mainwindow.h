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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *accX_label;
    QLabel *kalmanX_label;
    QLabel *gyroX_label;
    QSpacerItem *verticalSpacer;
    QLabel *accY_label;
    QLabel *kalmanY_label;
    QLabel *gyroY_label;
    QSpacerItem *verticalSpacer_2;
    QLabel *accZ_label;
    QLabel *kalmanZ_label;
    QLabel *gyroZ_label;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    GLWidget *openGLWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *plotWidget_X;
    QCustomPlot *plotWidget_Y;
    QCustomPlot *plotWidget_Z;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1180, 611);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        accX_label = new QLabel(centralWidget);
        accX_label->setObjectName(QStringLiteral("accX_label"));

        verticalLayout_2->addWidget(accX_label);

        kalmanX_label = new QLabel(centralWidget);
        kalmanX_label->setObjectName(QStringLiteral("kalmanX_label"));

        verticalLayout_2->addWidget(kalmanX_label);

        gyroX_label = new QLabel(centralWidget);
        gyroX_label->setObjectName(QStringLiteral("gyroX_label"));

        verticalLayout_2->addWidget(gyroX_label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        accY_label = new QLabel(centralWidget);
        accY_label->setObjectName(QStringLiteral("accY_label"));

        verticalLayout_2->addWidget(accY_label);

        kalmanY_label = new QLabel(centralWidget);
        kalmanY_label->setObjectName(QStringLiteral("kalmanY_label"));

        verticalLayout_2->addWidget(kalmanY_label);

        gyroY_label = new QLabel(centralWidget);
        gyroY_label->setObjectName(QStringLiteral("gyroY_label"));

        verticalLayout_2->addWidget(gyroY_label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        accZ_label = new QLabel(centralWidget);
        accZ_label->setObjectName(QStringLiteral("accZ_label"));

        verticalLayout_2->addWidget(accZ_label);

        kalmanZ_label = new QLabel(centralWidget);
        kalmanZ_label->setObjectName(QStringLiteral("kalmanZ_label"));

        verticalLayout_2->addWidget(kalmanZ_label);

        gyroZ_label = new QLabel(centralWidget);
        gyroZ_label->setObjectName(QStringLiteral("gyroZ_label"));

        verticalLayout_2->addWidget(gyroZ_label);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

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
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy1);
        textEdit_2->setLineWrapMode(QTextEdit::WidgetWidth);

        horizontalLayout_2->addWidget(textEdit_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 3);
        verticalLayout_2->setStretch(2, 3);
        verticalLayout_2->setStretch(4, 3);
        verticalLayout_2->setStretch(5, 3);
        verticalLayout_2->setStretch(6, 3);
        verticalLayout_2->setStretch(8, 3);
        verticalLayout_2->setStretch(9, 3);
        verticalLayout_2->setStretch(10, 3);
        verticalLayout_2->setStretch(12, 1);

        gridLayout->addLayout(verticalLayout_2, 2, 0, 2, 1);

        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout->addWidget(openGLWidget, 2, 2, 2, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plotWidget_X = new QCustomPlot(centralWidget);
        plotWidget_X->setObjectName(QStringLiteral("plotWidget_X"));

        verticalLayout->addWidget(plotWidget_X);

        plotWidget_Y = new QCustomPlot(centralWidget);
        plotWidget_Y->setObjectName(QStringLiteral("plotWidget_Y"));

        verticalLayout->addWidget(plotWidget_Y);

        plotWidget_Z = new QCustomPlot(centralWidget);
        plotWidget_Z->setObjectName(QStringLiteral("plotWidget_Z"));

        verticalLayout->addWidget(plotWidget_Z);


        gridLayout->addLayout(verticalLayout, 2, 1, 2, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1180, 21));
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
        accX_label->setText(QString());
        kalmanX_label->setText(QString());
        gyroX_label->setText(QString());
        accY_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        kalmanY_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gyroY_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        accZ_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        kalmanZ_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gyroZ_label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton->setText(QApplication::translate("MainWindow", "MysteriousButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
