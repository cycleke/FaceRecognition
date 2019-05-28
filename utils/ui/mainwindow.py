# -*- coding: utf-8 -*-

import cv2
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QDialog

from utils.core.recognizer import Recognizer
from utils.ui.ui_aboutFaceRecognition import Ui_AboutFaceRecognition
from utils.ui.ui_getName import Ui_getName
from utils.ui.ui_mainwindow import Ui_MainWindow


class MainWindow(QMainWindow):

    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent=parent)

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.label_CameraShow.setScaledContents(True)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.recognize_face)

        self.capture = cv2.VideoCapture()
        self.capture.release()

        self.recognizer = Recognizer()
        self.recognizer.load_data()

        self.ui.actionPreferencs.triggered.connect(self.open_preferences)
        self.ui.actionAbout_Face_Recognition.triggered.connect(self.open_about_face_recognition)
        self.ui.actionAbout_Qt.triggered.connect(self.open_about_qt)

        self.ui.pushButton_OpenCamera.clicked.connect(self.clicked_open_camera)
        self.ui.pushButton_CloseCamera.clicked.connect(self.clicked_close_camera)
        self.ui.pushButton_AddNewFaces.clicked.connect(self.clicked_add_new_faces)
        self.ui.pushButton_DeleteFaces.clicked.connect(self.clicked_delete_faces)

        self.ui.pushButton_OpenCamera.setDisabled(False)
        self.ui.pushButton_CloseCamera.setDisabled(True)
        self.ui.pushButton_AddNewFaces.setDisabled(False)
        self.ui.pushButton_DeleteFaces.setDisabled(False)

    def open_preferences(self):
        pass

    def open_about_face_recognition(self):
        dialog = QDialog(parent=self)
        ui = Ui_AboutFaceRecognition()
        ui.setupUi(dialog)
        dialog.setWindowTitle("About Face Recognition")
        dialog.exec()

    def open_about_qt(self):
        QMessageBox.aboutQt(self)

    def clicked_open_camera(self):
        self.ui.pushButton_OpenCamera.setDisabled(True)
        self.ui.pushButton_CloseCamera.setDisabled(False)

        if self.capture.isOpened():
            self.capture.release()

        self.capture.open(0)
        if self.capture.isOpened():
            rate = self.capture.get(cv2.CAP_PROP_FPS)

            success, frame = self.capture.read()
            if frame.any():
                img = self.recognizer.recognise_image(frame)
                cv2.cvtColor(img, cv2.COLOR_BGR2RGB, img)
                height, width, bytes_per_component = img.shape
                bytes_per_line = 3 * width
                q_img = QImage(img.data, width, height, bytes_per_line, QImage.Format_RGB888)
                pixel_map = QPixmap.fromImage(q_img)
                self.ui.label_CameraShow.setPixmap(pixel_map)
                self.timer.setInterval(1000 / rate)
                self.timer.start()

    def recognize_face(self):
        success, frame = self.capture.read()
        img = self.recognizer.recognise_image(frame)
        cv2.cvtColor(img, cv2.COLOR_BGR2RGB, img)
        height, width, bytes_per_component = img.shape
        bytes_per_line = 3 * width
        q_img = QImage(img.data, width, height, bytes_per_line, QImage.Format_RGB888)
        pixel_map = QPixmap.fromImage(q_img)
        self.ui.label_CameraShow.setPixmap(pixel_map)

    def clicked_close_camera(self):
        self.ui.pushButton_OpenCamera.setDisabled(False)
        self.ui.pushButton_CloseCamera.setDisabled(True)

        self.timer.stop()
        self.capture.release()
        self.ui.label_CameraShow.setPixmap(QPixmap())

    def clicked_add_new_faces(self):
        dialog = QDialog(self)
        ui = Ui_getName()
        ui.setupUi(dialog)
        dialog.setWindowTitle("Add New Faces")

        if dialog.exec():
            name = ui.lineEdit.text()
            if name:
                self.recognizer.add_face(name)

    def clicked_delete_faces(self):
        dialog = QDialog(self)
        ui = Ui_getName()
        ui.setupUi(dialog)
        dialog.setWindowTitle("Delete Faces")

        if dialog.exec():
            name = ui.lineEdit.text()
            if name in self.recognizer.face_descriptors.keys():
                self.recognizer.face_descriptors.pop(name)
