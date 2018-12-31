#include <QApplication>

#include "core/core.cpp"
#include "gui/mainwindow.cpp"

int main(int argc, char *argv[]) {
  QApplication main_app(argc, argv);

  MainWindow main_win;
  main_win.show();

  return main_app.exec();
}
