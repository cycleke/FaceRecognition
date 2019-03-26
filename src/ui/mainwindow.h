//
// Created by cycleke on 19-3-5.
//

#ifndef FACERECOGNITION_MAINWINDOW_H
#define FACERECOGNITION_MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTimer>
#include "src/core/Detector.h"
#include "src/core/FMTCNN.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  FMTCNN cnn;
  VideoCapture capture;
  QTimer *timer;

  void openPreferences();
  void openAboutFaceRecognition();
  void openAboutQt();

private slots:
  void on_pushButton_OpenCamera_clicked();
  void on_pushButton_CloseCamera_clicked();
  void on_pushButton_AddNewFaces_clicked();
  void on_pushButton_DeleteFaces_clicked();

  void recogniseFace();
};

#endif // FACERECOGNITION_MAINWINDOW_H
