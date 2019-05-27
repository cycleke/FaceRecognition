//
// Created by cycleke on 19-3-5.
//

#include "Detector.h"

#include <random>

#define IMG_SIZE 128
#define IMG_NUMBER 20
#define DATA_FORMAT ".jpg"

using namespace std;
using namespace cv;

void Detector::saveFacesFromCamera(const string &name) {
  /*
   * Get IMG_NUMBER photos of someone and save them.
   *
   * Param
   *   name: the name of someone
   */
  string data_path = this->data_path + name + "/";
  if (!filesystem::exists(data_path)) {
    filesystem::create_directories(data_path);
  }

  VideoCapture capture;
  CascadeClassifier classifier = CascadeClassifier(this->cascade_path);

  if (capture.isOpened()) {
    capture.release();
  }
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
    Mat display_frame = frame.clone();
    for (const Rect &face : faces) {
      int x = face.x;
      int y = face.y;
      int h = face.height;
      int w = face.width;
      if (h * w > max_size) {
        max_size = h * w;
        face_img = frame(Range(y, y + h - 1), Range(x, x + w - 1));
        resize(face_img, face_img, Size(IMG_SIZE, IMG_SIZE));
      }
      rectangle(display_frame, Point(x, y), Point(x + w - 1, y + h - 1),
                Scalar(128, 23, 7), 2);
      putText(display_frame, "", Point(x, y - 20), FONT_HERSHEY_SIMPLEX, 0.8,
              Scalar(255, 255, 255), 2);
    }

    if (max_size > 0) {
      printf("It's processing %d image.\n", count);
      imwrite(data_path + to_string(count) + DATA_FORMAT, face_img);
      count++;
    }

    imshow("Adding Face", display_frame);
    char c = (char)waitKey(30);
    if (c == 27 || c == 'q' || c == 'Q')
      break;
  }
  capture.release();
  destroyWindow("Adding Face");
}
Detector::~Detector() = default;
Detector::Detector(const string &data_path, const string &cascade_path)
    : data_path(data_path), cascade_path(cascade_path) {}
