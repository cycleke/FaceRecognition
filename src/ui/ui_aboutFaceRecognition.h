/********************************************************************************
** Form generated from reading UI file 'aboutFaceRecognition.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTFACERECOGNITION_H
#define UI_ABOUTFACERECOGNITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutFaceRecognition
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser_2;

    void setupUi(QDialog *AboutFaceRecognition)
    {
        if (AboutFaceRecognition->objectName().isEmpty())
            AboutFaceRecognition->setObjectName(QStringLiteral("AboutFaceRecognition"));
        AboutFaceRecognition->resize(326, 163);
        verticalLayout = new QVBoxLayout(AboutFaceRecognition);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser_2 = new QTextBrowser(AboutFaceRecognition);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        textBrowser_2->setFont(font);
        textBrowser_2->setAutoFillBackground(true);
        textBrowser_2->setFrameShape(QFrame::StyledPanel);

        verticalLayout->addWidget(textBrowser_2);


        retranslateUi(AboutFaceRecognition);

        QMetaObject::connectSlotsByName(AboutFaceRecognition);
    } // setupUi

    void retranslateUi(QDialog *AboutFaceRecognition)
    {
        AboutFaceRecognition->setWindowTitle(QApplication::translate("AboutFaceRecognition", "About Face Recognition", Q_NULLPTR));
        textBrowser_2->setHtml(QApplication::translate("AboutFaceRecognition", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono';\">Face Recognition</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono';\">A Face Recognition Application</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono';\">Version 0.0.1</span></p>\n"
"<p al"
                        "ign=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'GoMono Nerd Font Mono';\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono';\">Based On</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'GoMono Nerd Font Mono';\">Qt5 OpenCV4</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AboutFaceRecognition: public Ui_AboutFaceRecognition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTFACERECOGNITION_H
