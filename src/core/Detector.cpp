//
// Created by cycleke on 19-3-5.
//

#include "Detector.h"

#include <cstdio>
#include <opencv2/objdetect.hpp>
#include <random>

#define MAX_PATH_LEN 256
#define IMG_SIZE 128
#define IMG_NUMBER 20

#ifdef WIN32
#include <direct.h>
#include <io.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef WIN32
#define ACCESS(fileName, accessMode) _access(fileName, accessMode)
#define MKDIR(path) _mkdir(path)
#define FILE_SPLIT '\\'
#else
#define ACCESS(fileName, accessMode) access(fileName, accessMode)
#define MKDIR(path) mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#define FILE_SPLIT '/'
#endif

using namespace std;
using namespace cv;

int Detector::createDirectory(const string &directory_path) {
  int dir_path_length = static_cast<int>(directory_path.length());
  if (dir_path_length > MAX_PATH_LEN) {
    cerr << "Directory name is too long" << endl;
    return -1;
  }
  char temp_dir_path[MAX_PATH_LEN] = {0};
  for (int i = 0; i < dir_path_length; i++) {
    temp_dir_path[i] = directory_path[i];
    if (temp_dir_path[i] == FILE_SPLIT) {
      if (ACCESS(temp_dir_path, 0) != 0) {
        int ret = MKDIR(temp_dir_path);
        if (ret != 0) {
          return ret;
        }
      }
    }
  }
  return 0;
}
void Detector::getFacesFromCamera(const string &name) {
  /*
   * Get IMG_NUMBER photos of someone and save them.
   *
   * Param
   *   name: the name of someone
   */
  string data_path = this->data_path + name + string({FILE_SPLIT});
  createDirectory(data_path);
  VideoCapture capture;
  CascadeClassifier classifier = CascadeClassifier(this->cascade_path);

  default_random_engine random_engine(
      static_cast<unsigned long>(time(nullptr)));
  uniform_real_distribution<double> real_u(0.5, 1.5);
  uniform_int_distribution<int> int_u(-50, 50);

  capture.open(0);
  if (!capture.isOpened()) {
    puts("The camera is not open!!!");
    return;
  }

  int count = 0;
  while (count < IMG_NUMBER) {
    Mat frame, gray;
    vector<Rect> faces;

    capture >> frame;
    cvtColor(frame, gray, COLOR_RGB2GRAY);
    resize(frame, gray, Size(), 1, 1, INTER_LINEAR_EXACT);

    double t = getTickCount();
    classifier.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE,
                                Size(30, 30));
    t = getTickCount() - t;
    printf("detection time = %g ms\n", t * 1000 / getTickFrequency());

    int max_size = 0;
    Mat face_img;
    for (const Rect &face : faces) {
      int x = face.x;
      int y = face.y;
      int h = face.height;
      int w = face.width;
      if (h * w > max_size) {
        max_size = h * w;
        face_img = frame(Range(y, y + h - 1), Range(x, x + w - 1));
        resize(face_img, face_img, Size(IMG_SIZE, IMG_SIZE));
        face_img = face_img * real_u(random_engine) +
            Mat::ones(IMG_SIZE, IMG_SIZE, face_img.type());
      }
      rectangle(frame, Point(x, y), Point(x + w - 1, y + h - 1),
                Scalar(128, 23, 7), 2);
      putText(frame, "", Point(x, y - 20), FONT_HERSHEY_SIMPLEX, 0.8,
              Scalar(255, 255, 255), 2);
    }

    if (max_size > 0) {
      printf("It's processing %d image.\n", ++count);
      imwrite(data_path + to_string(count) + ".jpg", face_img);
    }

    imshow("Adding Face", frame);
    char c = (char) waitKey(1);
    if (c == 27 || c == 'q' || c == 'Q')
      break;
  }
  capture.release();
  destroyAllWindows();
}
Detector::~Detector() = default;
Detector::Detector(const string &data_path, const string &cascade_path)
    : data_path(data_path), cascade_path(cascade_path) {}
