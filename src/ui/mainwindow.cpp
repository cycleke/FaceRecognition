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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), capture() {

  ui->setupUi(this);
  ui->label_CameraShow->setScaledContents(true);
  this->setWindowTitle(tr("Face Recognition"));

  timer = new QTimer(this);

  loadFacesAndNames(cnn.face_names, "imgs/");

  // Add MenuBar Action
  connect(ui->actionPreferencs, &QAction::triggered, this,
          &MainWindow::openPreferences);
  connect(ui->actionAbout_Face_Recognition, &QAction::triggered, this,
          &MainWindow::openAboutFaceRecognition);
  connect(ui->actionAbout_Qt, &QAction::triggered, this,
          &MainWindow::openAboutQt);

  // Init
  ui->pushButton_OpenCamera->setDisabled(false);
  ui->pushButton_CloseCamera->setDisabled(true);
  ui->pushButton_AddNewFaces->setDisabled(true);
  ui->pushButton_DeleteFaces->setDisabled(true);
}

MainWindow::~MainWindow() {
  delete ui;
  delete timer;
}

void MainWindow::openPreferences() {}

void MainWindow::openAboutFaceRecognition() {
  QDialog *dialog = new QDialog(this);
  auto *ui = new Ui::AboutFaceRecognition;

  ui->setupUi(dialog);
  dialog->setWindowTitle(tr("About Face Recognition"));
  dialog->exec();

  delete ui;
  delete dialog;
}

void MainWindow::openAboutQt() { QMessageBox::aboutQt(this); }

QImage Mat2QImage(cv::Mat cvImg) {
  QImage qImg;
  if (cvImg.channels() == 3) {
    cv::cvtColor(cvImg, cvImg, cv::COLOR_BGR2RGB);
    qImg = QImage((const unsigned char *) (cvImg.data), cvImg.cols, cvImg.rows,
                  cvImg.cols * cvImg.channels(), QImage::Format_RGB888);
  } else if (cvImg.channels() == 1) {
    qImg = QImage((const unsigned char *) (cvImg.data), cvImg.cols, cvImg.rows,
                  cvImg.cols * cvImg.channels(), QImage::Format_Indexed8);
  } else {
    qImg = QImage((const unsigned char *) (cvImg.data), cvImg.cols, cvImg.rows,
                  cvImg.cols * cvImg.channels(), QImage::Format_RGB888);
  }
  return qImg;
}

void MainWindow::on_pushButton_OpenCamera_clicked() {
  ui->pushButton_OpenCamera->setDisabled(true);
  ui->pushButton_CloseCamera->setDisabled(false);
  ui->pushButton_AddNewFaces->setDisabled(false);
  ui->pushButton_DeleteFaces->setDisabled(false);
  if (capture.isOpened()) {
    capture.release();
  }
  capture.open(0);
  if (capture.isOpened()) {
    double rate = capture.get(CAP_PROP_FPS);
    Mat frame;
    capture >> frame;
    if (!frame.empty()) {
      auto image = Mat2QImage(cnn.recogniseFrame(frame));
      ui->label_CameraShow->setPixmap(QPixmap::fromImage(image));
      timer->setInterval(static_cast<int>(1000 / rate));
      connect(timer, &QTimer::timeout, this, &MainWindow::recogniseFace);
      timer->start();
    }
  }
}

void MainWindow::recogniseFace() {
  Mat frame;
  capture >> frame;
  auto image = Mat2QImage(cnn.recogniseFrame(frame));
  ui->label_CameraShow->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_CloseCamera_clicked() {
  ui->pushButton_OpenCamera->setDisabled(false);
  ui->pushButton_CloseCamera->setDisabled(true);
  ui->pushButton_AddNewFaces->setDisabled(true);
  ui->pushButton_DeleteFaces->setDisabled(true);
}

void MainWindow::on_pushButton_AddNewFaces_clicked() {
  // todo
}

void MainWindow::on_pushButton_DeleteFaces_clicked() {
  // todo
}
