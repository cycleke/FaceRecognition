/********************************************************************************
** Form generated from reading UI file 'aboutFaceRecognition.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTFACERECOGNITION_H
#define UI_ABOUTFACERECOGNITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutFaceRecognition
{
public:
    QTextBrowser *textBrowser_2;

    void setupUi(QDialog *AboutFaceRecognition)
    {
        if (AboutFaceRecognition->objectName().isEmpty())
            AboutFaceRecognition->setObjectName(QString::fromUtf8("AboutFaceRecognition"));
        AboutFaceRecognition->resize(326, 163);
        textBrowser_2 = new QTextBrowser(AboutFaceRecognition);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(10, 20, 301, 121));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        textBrowser_2->setFont(font);
        textBrowser_2->setAutoFillBackground(true);
        textBrowser_2->setFrameShape(QFrame::StyledPanel);

        retranslateUi(AboutFaceRecognition);

        QMetaObject::connectSlotsByName(AboutFaceRecognition);
    } // setupUi

    void retranslateUi(QDialog *AboutFaceRecognition)
    {
        AboutFaceRecognition->setWindowTitle(QApplication::translate("AboutFaceRecognition", "About Face Recognition", nullptr));
        textBrowser_2->setHtml(QApplication::translate("AboutFaceRecognition", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'WenQuanYi Micro Hei'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono'; font-size:10pt;\">Face Recognition</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono'; font-size:10pt;\">A Face Recognition Application</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mo"
                        "no'; font-size:10pt;\">Version 0.0.1</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'GoMono Nerd Font Mono'; font-size:10pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono'; font-size:10pt;\">Based On</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono'; font-size:10pt;\">Qt5 OpenCV4</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutFaceRecognition: public Ui_AboutFaceRecognition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTFACERECOGNITION_H
