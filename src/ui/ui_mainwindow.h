/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPreferencs;
    QAction *actionAbout_Face_Recognition;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_ShowImg;
    QGridLayout *gridLayout_2;
    QLabel *label_CameraShow;
    QGroupBox *groupBox_Operation;
    QHBoxLayout *horizontalLayout;
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
        MainWindow->resize(688, 624);
        actionPreferencs = new QAction(MainWindow);
        actionPreferencs->setObjectName(QStringLiteral("actionPreferencs"));
        actionAbout_Face_Recognition = new QAction(MainWindow);
        actionAbout_Face_Recognition->setObjectName(QStringLiteral("actionAbout_Face_Recognition"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_ShowImg = new QWidget(groupBox);
        widget_ShowImg->setObjectName(QStringLiteral("widget_ShowImg"));
        widget_ShowImg->setMinimumSize(QSize(352, 240));
        widget_ShowImg->setMaximumSize(QSize(1580, 720));
        gridLayout_2 = new QGridLayout(widget_ShowImg);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_CameraShow = new QLabel(widget_ShowImg);
        label_CameraShow->setObjectName(QStringLiteral("label_CameraShow"));
        label_CameraShow->setEnabled(true);
        label_CameraShow->setMinimumSize(QSize(352, 240));
        label_CameraShow->setMaximumSize(QSize(1580, 720));

        gridLayout_2->addWidget(label_CameraShow, 0, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout_2->addWidget(widget_ShowImg, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout->addWidget(groupBox);

        groupBox_Operation = new QGroupBox(centralwidget);
        groupBox_Operation->setObjectName(QStringLiteral("groupBox_Operation"));
        horizontalLayout = new QHBoxLayout(groupBox_Operation);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_OpenCamera = new QPushButton(groupBox_Operation);
        pushButton_OpenCamera->setObjectName(QStringLiteral("pushButton_OpenCamera"));

        horizontalLayout->addWidget(pushButton_OpenCamera);

        pushButton_CloseCamera = new QPushButton(groupBox_Operation);
        pushButton_CloseCamera->setObjectName(QStringLiteral("pushButton_CloseCamera"));

        horizontalLayout->addWidget(pushButton_CloseCamera);

        pushButton_AddNewFaces = new QPushButton(groupBox_Operation);
        pushButton_AddNewFaces->setObjectName(QStringLiteral("pushButton_AddNewFaces"));

        horizontalLayout->addWidget(pushButton_AddNewFaces);

        pushButton_DeleteFaces = new QPushButton(groupBox_Operation);
        pushButton_DeleteFaces->setObjectName(QStringLiteral("pushButton_DeleteFaces"));

        horizontalLayout->addWidget(pushButton_DeleteFaces);


        verticalLayout->addWidget(groupBox_Operation);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 688, 30));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Face Recognition", Q_NULLPTR));
        actionPreferencs->setText(QApplication::translate("MainWindow", "&Preferencs", Q_NULLPTR));
        actionAbout_Face_Recognition->setText(QApplication::translate("MainWindow", "&About Face Recognition", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About &Qt", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        label_CameraShow->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Display</span></p></body></html>", Q_NULLPTR));
        groupBox_Operation->setTitle(QApplication::translate("MainWindow", "Operation", Q_NULLPTR));
        pushButton_OpenCamera->setText(QApplication::translate("MainWindow", "Open Camera", Q_NULLPTR));
        pushButton_CloseCamera->setText(QApplication::translate("MainWindow", "Close Camera", Q_NULLPTR));
        pushButton_AddNewFaces->setText(QApplication::translate("MainWindow", "Add New Face(s)", Q_NULLPTR));
        pushButton_DeleteFaces->setText(QApplication::translate("MainWindow", "Delete Face(s)", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "&Settings", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Abo&ut", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
