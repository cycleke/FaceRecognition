# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QApplication
from utils.ui.mainwindow import MainWindow

if __name__ == '__main__':
    app = QApplication(sys.argv)

    main_win = MainWindow()
    main_win.show()

    app.exec()
