# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'getName.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_getName(object):
    def setupUi(self, getName):
        getName.setObjectName("getName")
        getName.resize(273, 136)
        self.verticalLayout = QtWidgets.QVBoxLayout(getName)
        self.verticalLayout.setObjectName("verticalLayout")
        self.lineEdit = QtWidgets.QLineEdit(getName)
        self.lineEdit.setObjectName("lineEdit")
        self.verticalLayout.addWidget(self.lineEdit)
        self.buttonBox = QtWidgets.QDialogButtonBox(getName)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(getName)
        self.buttonBox.accepted.connect(getName.accept)
        self.buttonBox.rejected.connect(getName.reject)
        QtCore.QMetaObject.connectSlotsByName(getName)

    def retranslateUi(self, getName):
        _translate = QtCore.QCoreApplication.translate
        getName.setWindowTitle(_translate("getName", "Dialog"))


