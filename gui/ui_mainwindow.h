/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPreferencs;
    QAction *actionAbout_Face_Recognition;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *widget_ShowImg;
    QGridLayout *gridLayout_2;
    QLabel *label_CameraShow;
    QGroupBox *groupBox_Operation;
    QPushButton *pushButton_OpenCamera;
    QPushButton *pushButton_CloseCamera;
    QPushButton *pushButton_AddNewFaces;
    QPushButton *pushButton_DeleteFaces;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(796, 594);
        actionPreferencs = new QAction(MainWindow);
        actionPreferencs->setObjectName(QStringLiteral("actionPreferencs"));
        actionAbout_Face_Recognition = new QAction(MainWindow);
        actionAbout_Face_Recognition->setObjectName(QStringLiteral("actionAbout_Face_Recognition"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(9, 9, 775, 535));
        widget_ShowImg = new QWidget(groupBox);
        widget_ShowImg->setObjectName(QStringLiteral("widget_ShowImg"));
        widget_ShowImg->setGeometry(QRect(70, 60, 660, 280));
        widget_ShowImg->setMinimumSize(QSize(660, 280));
        widget_ShowImg->setMaximumSize(QSize(660, 280));
        gridLayout_2 = new QGridLayout(widget_ShowImg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_CameraShow = new QLabel(widget_ShowImg);
        label_CameraShow->setObjectName(QStringLiteral("label_CameraShow"));
        label_CameraShow->setEnabled(true);
        label_CameraShow->setMinimumSize(QSize(320, 240));
        label_CameraShow->setMaximumSize(QSize(320, 240));

        gridLayout_2->addWidget(label_CameraShow, 0, 0, 1, 1);

        groupBox_Operation = new QGroupBox(groupBox);
        groupBox_Operation->setObjectName(QStringLiteral("groupBox_Operation"));
        groupBox_Operation->setGeometry(QRect(5, 350, 765, 175));
        pushButton_OpenCamera = new QPushButton(groupBox_Operation);
        pushButton_OpenCamera->setObjectName(QStringLiteral("pushButton_OpenCamera"));
        pushButton_OpenCamera->setGeometry(QRect(110, 60, 165, 32));
        pushButton_CloseCamera = new QPushButton(groupBox_Operation);
        pushButton_CloseCamera->setObjectName(QStringLiteral("pushButton_CloseCamera"));
        pushButton_CloseCamera->setGeometry(QRect(110, 100, 165, 32));
        pushButton_AddNewFaces = new QPushButton(groupBox_Operation);
        pushButton_AddNewFaces->setObjectName(QStringLiteral("pushButton_AddNewFaces"));
        pushButton_AddNewFaces->setGeometry(QRect(490, 60, 165, 32));
        pushButton_DeleteFaces = new QPushButton(groupBox_Operation);
        pushButton_DeleteFaces->setObjectName(QStringLiteral("pushButton_DeleteFaces"));
        pushButton_DeleteFaces->setGeometry(QRect(490, 100, 165, 32));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 796, 28));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuSettings->addAction(actionPreferencs);
        menuAbout->addAction(actionAbout_Face_Recognition);
        menuAbout->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionPreferencs->setText(QApplication::translate("MainWindow", "&Preferencs", nullptr));
        actionAbout_Face_Recognition->setText(QApplication::translate("MainWindow", "&About Face Recognition", nullptr));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About &Qt", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Display", nullptr));
        label_CameraShow->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Display</span></p></body></html>", nullptr));
        groupBox_Operation->setTitle(QApplication::translate("MainWindow", "Operation", nullptr));
        pushButton_OpenCamera->setText(QApplication::translate("MainWindow", "Open Camera", nullptr));
        pushButton_CloseCamera->setText(QApplication::translate("MainWindow", "Close Camera", nullptr));
        pushButton_AddNewFaces->setText(QApplication::translate("MainWindow", "Add New Face(s)", nullptr));
        pushButton_DeleteFaces->setText(QApplication::translate("MainWindow", "Delete Face(s)", nullptr));
        menuSettings->setTitle(QApplication::translate("MainWindow", "&Settings", nullptr));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Abo&ut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
