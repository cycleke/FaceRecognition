#include <iostream>

//#include "gui/mainwindow.cpp"
#include "src/core/Detector.cpp"
#include "src/core/FMTCNN.cpp"

const string keys = "{@method | recognise |}"
                    "{@name | <unknown> |}";

void help() {
  puts("This program is used to recognise faces\n\n"
       "usage: ./FaceRecognition METHOD...[NAME]\n\n"
       "METHOD:\n\n"
       "\trecognise(default) : Recognise faces with camera.\n"
       "\tadd : Add faces into database, with the given name.\n"
       "\thelp : Show the help message.\n");
}

int main(int argc, char *args[]) {

  /*
   QApplication main_app(argc, args);

  MainWindow main_win;
  main_win.show();

  return main_app.exec();
  */

  CommandLineParser parser(argc, args, keys);

  string method = parser.get<string>("@method");
  string name = parser.get<string>("@name");

  if (method == "help") {
    help();
    return 0;
  }

  if (method == "recognise" || argc == 1) {
    FMTCNN cnn;

    puts("Start loading.");
    cnn.loadFacesAndNames();
    puts("Finished loading.");

    cnn.recogniseWithCamera();
  } else if (method == "add") {
    Detector detector;
    detector.saveFacesFromCamera(name);
  } else {
    puts("Wrong Method!!!");
  }

  return 0;
}
