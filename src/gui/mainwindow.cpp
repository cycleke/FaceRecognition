/*
          __   _,--="=--,_   __
         /  \."    .-.    "./  \
        /  ,/  _   : :   _  \/` \
        \  `| /o\  :_:  /o\ |\__/
         `-'| :="~` _ `~"=: |
            \`     (_)     `/
     .-"-.   \      |      /   .-"-.
.---{     }--|  /,.-'-.,\  |--{     }---.
 )  (_)_)_)  \_/`~-===-~`\_/  (_(_(_)  (
(      Coding like a dog @cycleke       )
 )                                     (
'---------------------------------------'
  */

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include "mainwindow.h"
#include "ui_aboutFaceRecognition.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  this->setWindowTitle(tr("Face Recognition"));

  // Add MenuBar Action
  connect(ui->actionPreferencs, &QAction::triggered, this,
          &MainWindow::openPreferences);
  connect(ui->actionAbout_Face_Recognition, &QAction::triggered, this,
          &MainWindow::openAboutFaceRecognition);
  connect(ui->actionAbout_Qt, &QAction::triggered, this,
          &MainWindow::openAboutQt);

  // Add PushButton Action

  // Init
  ui->pushButton_OpenCamera->setDisabled(false);
  ui->pushButton_CloseCamera->setDisabled(true);
  ui->pushButton_AddNewFaces->setDisabled(true);
  ui->pushButton_DeleteFaces->setDisabled(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::openPreferences() {}

void MainWindow::openAboutFaceRecognition() {
  QDialog *dialog = new QDialog(this);
  Ui::AboutFaceRecognition *ui = new Ui::AboutFaceRecognition;

  ui->setupUi(dialog);
  dialog->setWindowTitle(tr("About Face Recognition"));
  dialog->exec();

  delete ui;
  delete dialog;
}

void MainWindow::openAboutQt() { QMessageBox::aboutQt(this); }

void MainWindow::on_pushButton_OpenCamera_clicked() {
  ui->pushButton_OpenCamera->setDisabled(true);
  ui->pushButton_CloseCamera->setDisabled(false);
  ui->pushButton_AddNewFaces->setDisabled(false);
  ui->pushButton_DeleteFaces->setDisabled(false);
}

void MainWindow::on_pushButton_CloseCamera_clicked() {
  ui->pushButton_OpenCamera->setDisabled(false);
  ui->pushButton_CloseCamera->setDisabled(true);
  ui->pushButton_AddNewFaces->setDisabled(true);
  ui->pushButton_DeleteFaces->setDisabled(true);
}

void MainWindow::on_pushButton_AddNewFaces_clicked() {}

void MainWindow::on_pushButton_DeleteFaces_clicked() {}