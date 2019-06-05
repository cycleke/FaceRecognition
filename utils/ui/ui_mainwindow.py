# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(688, 624)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.widget_ShowImg = QtWidgets.QWidget(self.groupBox)
        self.widget_ShowImg.setMinimumSize(QtCore.QSize(352, 240))
        self.widget_ShowImg.setMaximumSize(QtCore.QSize(1580, 720))
        self.widget_ShowImg.setObjectName("widget_ShowImg")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.widget_ShowImg)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label_CameraShow = QtWidgets.QLabel(self.widget_ShowImg)
        self.label_CameraShow.setEnabled(True)
        self.label_CameraShow.setMinimumSize(QtCore.QSize(352, 240))
        self.label_CameraShow.setMaximumSize(QtCore.QSize(1580, 720))
        self.label_CameraShow.setObjectName("label_CameraShow")
        self.gridLayout_2.addWidget(self.label_CameraShow, 0, 0, 1, 1, QtCore.Qt.AlignHCenter|QtCore.Qt.AlignVCenter)
        self.verticalLayout_2.addWidget(self.widget_ShowImg, 0, QtCore.Qt.AlignHCenter|QtCore.Qt.AlignVCenter)
        self.verticalLayout.addWidget(self.groupBox)
        self.groupBox_Operation = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_Operation.setObjectName("groupBox_Operation")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox_Operation)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.pushButton_OpenCamera = QtWidgets.QPushButton(self.groupBox_Operation)
        self.pushButton_OpenCamera.setObjectName("pushButton_OpenCamera")
        self.horizontalLayout.addWidget(self.pushButton_OpenCamera)
        self.pushButton_CloseCamera = QtWidgets.QPushButton(self.groupBox_Operation)
        self.pushButton_CloseCamera.setObjectName("pushButton_CloseCamera")
        self.horizontalLayout.addWidget(self.pushButton_CloseCamera)
        self.pushButton_AddNewFaces = QtWidgets.QPushButton(self.groupBox_Operation)
        self.pushButton_AddNewFaces.setObjectName("pushButton_AddNewFaces")
        self.horizontalLayout.addWidget(self.pushButton_AddNewFaces)
        self.pushButton_DeleteFaces = QtWidgets.QPushButton(self.groupBox_Operation)
        self.pushButton_DeleteFaces.setObjectName("pushButton_DeleteFaces")
        self.horizontalLayout.addWidget(self.pushButton_DeleteFaces)
        self.verticalLayout.addWidget(self.groupBox_Operation)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 688, 30))
        self.menubar.setObjectName("menubar")
        self.menuSettings = QtWidgets.QMenu(self.menubar)
        self.menuSettings.setObjectName("menuSettings")
        self.menuAbout = QtWidgets.QMenu(self.menubar)
        self.menuAbout.setObjectName("menuAbout")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionPreferencs = QtWidgets.QAction(MainWindow)
        self.actionPreferencs.setObjectName("actionPreferencs")
        self.actionAbout_Face_Recognition = QtWidgets.QAction(MainWindow)
        self.actionAbout_Face_Recognition.setObjectName("actionAbout_Face_Recognition")
        self.actionAbout_Qt = QtWidgets.QAction(MainWindow)
        self.actionAbout_Qt.setObjectName("actionAbout_Qt")
        self.menuSettings.addAction(self.actionPreferencs)
        self.menuAbout.addAction(self.actionAbout_Face_Recognition)
        self.menuAbout.addAction(self.actionAbout_Qt)
        self.menubar.addAction(self.menuSettings.menuAction())
        self.menubar.addAction(self.menuAbout.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Face Recognition"))
        self.groupBox.setTitle(_translate("MainWindow", "Display"))
        self.label_CameraShow.setText(_translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600;\">Display</span></p></body></html>"))
        self.groupBox_Operation.setTitle(_translate("MainWindow", "Operation"))
        self.pushButton_OpenCamera.setText(_translate("MainWindow", "Open Camera"))
        self.pushButton_CloseCamera.setText(_translate("MainWindow", "Close Camera"))
        self.pushButton_AddNewFaces.setText(_translate("MainWindow", "Add New Face(s)"))
        self.pushButton_DeleteFaces.setText(_translate("MainWindow", "Delete Face(s)"))
        self.menuSettings.setTitle(_translate("MainWindow", "&Settings"))
        self.menuAbout.setTitle(_translate("MainWindow", "Abo&ut"))
        self.actionPreferencs.setText(_translate("MainWindow", "&Preferencs"))
        self.actionAbout_Face_Recognition.setText(_translate("MainWindow", "&About Face Recognition"))
        self.actionAbout_Qt.setText(_translate("MainWindow", "About &Qt"))


