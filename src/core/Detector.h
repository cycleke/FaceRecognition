//
// Created by cycleke on 19-3-5.
//

#ifndef FACERECOGNITION_RECOGNIZER_H
#define FACERECOGNITION_RECOGNIZER_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

#include <dirent.h>
#include <string>
#include <vector>

class Detector {
private:
  std::string data_path;
  std::string cascade_path;
  std::string model_txt;
  std::string model_bin;
  int createDirectory(const std::string &directory_path);

public:
  explicit Detector(
      const std::string &data_path = "imgs/",
      const std::string &cascade_path =
      "static/haarcascades/haarcascade_frontalface_default.xml");
  ~Detector();
  void saveFacesFromCamera(const std::string &name);
};

#endif // FACERECOGNITION_RECOGNIZER_H
