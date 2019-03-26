//
// Created by cycleke on 19-3-11.
//

#ifndef FACERECOGNITION_FMTCNN_H
#define FACERECOGNITION_FMTCNN_H

#include <algorithm>
#include <cstdio>
#include <dirent.h>
#include <iostream>
#include <memory>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <string>
#include <vector>

#define IMG_NORMAL_HEIGHT 112
#define IMG_NORMAL_WIDTH 96
#define IMG_NUMBER 10
#define DATA_FORMAT ".jpeg"
#define SIMILARITY_BOUND 0.3
/*
#define IMG_SIZE 128
#define MAX_PATH_LEN 256
 */

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
using namespace dnn;

struct FaceBox {
  float x_min, y_min;
  float x_max, y_max;
  float score;
};

struct FaceInfo {
  float box_reg[4];
  float landmark_reg[10];
  float landmark[10];
  FaceBox box;
};

struct FaceFeature {
  string name;
  Mat feature[IMG_NUMBER];
};

class FMTCNN {
public:
  Net p_net, r_net, o_net, net;
  vector<FaceInfo> candidate_boxes, total_boxes;
  vector<FaceFeature> face_names;

  FMTCNN();
  ~FMTCNN();

  void Detect(Mat image, vector<FaceInfo> &face_infos);
  vector<FaceInfo> DetectMTCNN(const Mat &image, const int &stage);
  vector<FaceInfo> ProposalNet(const Mat &image, float threshold);
  vector<FaceInfo> nextStage(const Mat &image, vector<FaceInfo> &pre_stage_res,
                             int input_w, int input_h, int stage_num,
                             float threshold);
  vector<FaceInfo> NMS(vector<FaceInfo> &boxes, float thresh, char method_char);
  void BoxRegression(vector<FaceInfo> &boxes);
  void BoxPadSquare(vector<FaceInfo> &boxes, int width, int height);
  void BoxPad(vector<FaceInfo> &boxes, int width, int height);
  void generateBox(Mat *confidence, Mat *reg_box, float scale, float thresh);
  float IoU(float x_min, float y_min, float x_max, float y_max, float x_min_,
            float y_min_, float x_max_, float y_max_, bool is_iom = false);
  Mat getTFormMatrix(float *std_points, float *feat_points);
  void rotateFace(Mat img, FaceInfo face_info, Mat &dst_img);
  void normalizeFace(Mat dst_img, Mat &normalize_img);

  string recogniseFace(Mat img);
  void recogniseWithCamera();
  Mat recogniseFrame(const Mat &frame);
  // int createDirectory(const string &directory_path);
  // void saveFacesFromCamera(const std::string &name);

private:
  const float factor = 0.709f;
  const float threshold[3] = {0.7, 0.6, 0.6};
  const int min_size = 12;

  const float p_net_stride = 2;
  const float p_net_cell_size = 12;
  const int p_net_max_detect_num = 5000;
  const int step_size = 128;

  const float mean_val = 127.5f;
  const float std_val = 0.0078125f;

  const string proto_model_dir = "static/model";
};

void loadFacesAndNames(vector<FaceFeature> &face_names, const string &data_path);
double CosineSimilarity(const Mat &a, const Mat &b);

#endif // FACERECOGNITION_FMTCNN_H
