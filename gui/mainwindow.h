#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  void openCamera();
  void closeCamera();
  void addNewFace();
  void deleteFaces();
  void openPreferences();
  void openAboutFaceRecognition();
  void openAboutQt();

private slots:
  void on_pushButton_OpenCamera_clicked();
  void on_pushButton_CloseCamera_clicked();
  void on_pushButton_AddNewFaces_clicked();
  void on_pushButton_DeleteFaces_clicked();
};

#endif // MAINWINDOW_H
