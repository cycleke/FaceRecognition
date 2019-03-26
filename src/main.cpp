#include "src/ui/mainwindow.h"

int main(int argc, char *args[]) {

  QApplication main_app(argc, args);

  MainWindow main_win;
  main_win.show();

  return main_app.exec();

}
