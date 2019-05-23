/********************************************************************************
** Form generated from reading UI file 'getName.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETNAME_H
#define UI_GETNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_getName
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *getName)
    {
        if (getName->objectName().isEmpty())
            getName->setObjectName(QStringLiteral("getName"));
        getName->resize(273, 136);
        verticalLayout = new QVBoxLayout(getName);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(getName);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        buttonBox = new QDialogButtonBox(getName);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(getName);
        QObject::connect(buttonBox, SIGNAL(accepted()), getName, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), getName, SLOT(reject()));

        QMetaObject::connectSlotsByName(getName);
    } // setupUi

    void retranslateUi(QDialog *getName)
    {
        getName->setWindowTitle(QApplication::translate("getName", "Dialog", Q_NULLPTR));
        plainTextEdit->setPlainText(QApplication::translate("getName", "Please write down your name.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class getName: public Ui_getName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETNAME_H
