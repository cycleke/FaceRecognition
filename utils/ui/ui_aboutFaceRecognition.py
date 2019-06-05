# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'aboutFaceRecognition.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_AboutFaceRecognition(object):
    def setupUi(self, AboutFaceRecognition):
        AboutFaceRecognition.setObjectName("AboutFaceRecognition")
        AboutFaceRecognition.resize(326, 163)
        self.verticalLayout = QtWidgets.QVBoxLayout(AboutFaceRecognition)
        self.verticalLayout.setObjectName("verticalLayout")
        self.textBrowser_2 = QtWidgets.QTextBrowser(AboutFaceRecognition)
        font = QtGui.QFont()
        font.setBold(False)
        font.setWeight(50)
        font.setKerning(True)
        self.textBrowser_2.setFont(font)
        self.textBrowser_2.setAutoFillBackground(True)
        self.textBrowser_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.textBrowser_2.setObjectName("textBrowser_2")
        self.verticalLayout.addWidget(self.textBrowser_2)

        self.retranslateUi(AboutFaceRecognition)
        QtCore.QMetaObject.connectSlotsByName(AboutFaceRecognition)

    def retranslateUi(self, AboutFaceRecognition):
        _translate = QtCore.QCoreApplication.translate
        AboutFaceRecognition.setWindowTitle(_translate("AboutFaceRecognition", "About Face Recognition"))
        self.textBrowser_2.setHtml(_translate("AboutFaceRecognition", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Noto Sans\'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'GoMono Nerd Font Mono\';\">Face Recognition</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'GoMono Nerd Font Mono\';\">A Face Recognition Application</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'GoMono Nerd Font Mono\';\">Version 0.0.1</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:\'GoMono Nerd Font Mono\';\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'GoMono Nerd Font Mono\';\">Based On</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:\'GoMono Nerd Font Mono\';\">Qt5 OpenCV4</span></p></body></html>"))


