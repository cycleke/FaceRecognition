//
// Created by cycleke on 19-3-11.
//

#include "FMTCNN.h"

FMTCNN::FMTCNN() {
  p_net = readNetFromCaffe(proto_model_dir + "/det1_.prototxt",
                           proto_model_dir + "/det1_.caffemodel");
  r_net = readNetFromCaffe(proto_model_dir + "/det2.prototxt",
                           proto_model_dir + "/det2_half.caffemodel");
  o_net = readNetFromCaffe(proto_model_dir + "/det3-half.prototxt",
                           proto_model_dir + "/det3-half.caffemodel");
  net = readNetFromCaffe(proto_model_dir + "/sphereface_deploy.prototxt",
                         proto_model_dir + "/sphereface_model.caffemodel");
}

FMTCNN::~FMTCNN() = default;

void FMTCNN::Detect(Mat image, vector<FaceInfo> &face_infos) {
  Mat copy_image;
  image.copyTo(copy_image);

  face_infos = DetectMTCNN(image, 3);

  for (auto &info : face_infos) {
    int x = int(info.box.x_min);
    int y = int(info.box.y_min);
    int w = int(info.box.x_max - info.box.x_min + 1);
    int h = int(info.box.y_max - info.box.y_min + 1);
    rectangle(copy_image, Rect(x, y, w, h), Scalar(255, 0, 0), 2);
  }
  // imshow("Face Detecting", copy_image);
  // waitKey(1);
}

vector<FaceInfo> FMTCNN::DetectMTCNN(const Mat &image, const int &stage) {
  vector<FaceInfo> p_net_res, r_net_res, o_net_res;
  if (stage >= 1) {
    p_net_res = ProposalNet(image, threshold[0]);
  }
  if (stage >= 2 && !p_net_res.empty()) {
    if (p_net_max_detect_num < p_net_res.size()) {
      p_net_res.resize((unsigned long)p_net_max_detect_num);
    }
    int num = static_cast<int>(p_net_res.size());
    int size = (int)ceil(1.0 * num / step_size);

    for (int iter = 0; iter < size; iter++) {
      int start = iter * step_size;
      int end = min(start + step_size, num);
      vector<FaceInfo> input(p_net_res.begin() + start,
                             p_net_res.begin() + end);
      vector<FaceInfo> res = nextStage(image, input, 24, 24, 2, threshold[1]);
      r_net_res.insert(r_net_res.end(), res.begin(), res.end());
    }
    r_net_res = NMS(r_net_res, 0.4f, 'm');
    BoxRegression(r_net_res);
    BoxPadSquare(r_net_res, image.cols, image.rows);
  }
  if (stage >= 3 && !r_net_res.empty()) {
    int num = static_cast<int>(r_net_res.size());
    int size = (int)ceil(1.0 * num / step_size);

    for (int iter = 0; iter < size; iter++) {
      int start = iter * step_size;
      int end = min(start + step_size, num);
      vector<FaceInfo> input(r_net_res.begin() + start,
                             r_net_res.begin() + end);
      vector<FaceInfo> res = nextStage(image, input, 48, 48, 3, threshold[2]);
      o_net_res.insert(o_net_res.end(), res.begin(), res.end());
    }
    BoxRegression(o_net_res);
    o_net_res = NMS(o_net_res, 0.4f, 'm');
    BoxPadSquare(o_net_res, image.cols, image.rows);
  }
  switch (stage) {
  case 1:
    return p_net_res;
  case 2:
    return r_net_res;
  case 3:
    return o_net_res;
  default:
    cout << "Wrong param: the stage is out of {1, 2, 3} in DetectMTCNN" << endl;
    return vector<FaceInfo>();
  }
}

vector<FaceInfo> FMTCNN::NMS(vector<FaceInfo> &boxes, float thresh,
                             char method_char) {
  vector<FaceInfo> boxes_nms;
  if (boxes.empty()) {
    return boxes_nms;
  }

  auto compareBox = [&](const FaceInfo &a, const FaceInfo &b) {
    return a.box.score > b.box.score;
  };
  sort(boxes.begin(), boxes.end(), compareBox);

  int select_idx = 0;
  int num_box = static_cast<int>(boxes.size());
  vector<int> mask_merged(num_box, 0);
  bool all_merged = false;

  while (!all_merged) {
    while (select_idx < num_box && mask_merged[select_idx] == 1) {
      select_idx++;
    }
    if (select_idx == num_box) {
      all_merged = true;
      continue;
    }

    boxes_nms.push_back(boxes[select_idx]);
    mask_merged[select_idx] = 1;

    auto select_box = boxes[select_idx].box;
    float x1 = select_box.x_min;
    float x2 = select_box.x_max;
    float y1 = select_box.y_min;
    float y2 = select_box.y_max;
    float area1 = (x2 - x1 + 1) * (y2 - y1 + 1);
    select_idx++;

    for (int i = select_idx; i < num_box; i++) {
      if (mask_merged[i] == 1) {
        continue;
      }
      FaceBox &box_i = boxes[i].box;
      float x = max(x1, box_i.x_min);
      float y = max(y1, box_i.y_min);
      float w = min(x2, box_i.x_max) - x + 1;
      float h = min(y2, box_i.y_max) - y + 1;
      if (w <= 0 || h <= 0) {
        continue;
      }

      float area2 =
          (box_i.x_max - box_i.x_min + 1) * (box_i.y_max - box_i.y_min + 1);
      float area = w * h;

      switch (method_char) {
      case 'u':
        if (area / (area1 + area2 - area) > thresh) {
          mask_merged[i] = 1;
        }
        break;
      case 'm':
        if (area / min(area1, area2) > thresh) {
          mask_merged[i] = 1;
        }
        break;
      default:
        break;
      }
    }
  }

  return boxes_nms;
}

void FMTCNN::BoxRegression(vector<FaceInfo> &boxes) {
  for (auto &i_box : boxes) {
    FaceBox &box = i_box.box;
    float *box_reg = i_box.box_reg;
    float w = box.x_max - box.x_min + 1;
    float h = box.y_max - box.y_min + 1;
    box.x_min += box_reg[0] * w;
    box.y_min += box_reg[1] * h;
    box.x_max += box_reg[2] * w;
    box.y_max += box_reg[3] * h;
  }
}

void FMTCNN::BoxPadSquare(vector<FaceInfo> &boxes, int width, int height) {
  for (auto &i_box : boxes) {
    FaceBox &box = i_box.box;
    float w = box.x_max - box.x_min + 1;
    float h = box.y_max - box.y_min + 1;
    float side = h > w ? h : w;
    box.x_min = round(max(box.x_min + (w - side) * 0.5f, 0.f));
    box.y_min = round(max(box.y_min + (h - side) * 0.5f, 0.f));
    box.x_max = round(min(box.x_min + side - 1, width - 1.f));
    box.y_max = round(min(box.y_min + side - 1, height - 1.f));
  }
}

void FMTCNN::BoxPad(vector<FaceInfo> &boxes, int width, int height) {
  for (auto &i_box : boxes) {
    FaceBox &box = i_box.box;
    box.x_min = round(max(box.x_min, 0.f));
    box.y_min = round(max(box.y_min, 0.f));
    box.x_max = round(min(box.x_max, width - 1.f));
    box.y_max = round(min(box.y_max, height - 1.f));
  }
}

void FMTCNN::generateBox(Mat *confidence, Mat *reg_box, float scale,
                         float thresh) {
  int feature_map_w = confidence->size[3];
  int feature_map_h = confidence->size[2];
  int spatical_size = feature_map_w * feature_map_h;

  const float *confidence_data = (float *)(confidence->data);
  confidence_data += spatical_size;

  const float *reg_data = (float *)(reg_box->data);
  candidate_boxes.clear();
  for (int i = 0; i < spatical_size; i++) {
    if (confidence_data[i] <= 1 - thresh) {
      int y = i / feature_map_w;
      int x = i - feature_map_w * y;
      FaceInfo face_info{};
      FaceBox &face_box = face_info.box;

      face_box.x_min = x * p_net_stride / scale;
      face_box.y_min = y * p_net_stride / scale;
      face_box.x_max = (x * p_net_stride + p_net_cell_size - 1.f) / scale;
      face_box.y_max = (y * p_net_stride + p_net_cell_size - 1.f) / scale;
      face_info.box_reg[0] = reg_data[i];
      face_info.box_reg[1] = reg_data[i + spatical_size];
      face_info.box_reg[2] = reg_data[i + 2 * spatical_size];
      face_info.box_reg[3] = reg_data[i + 3 * spatical_size];
      face_box.score = confidence_data[i];
      candidate_boxes.push_back(face_info);
    }
  }
}

vector<FaceInfo> FMTCNN::nextStage(const Mat &image,
                                   vector<FaceInfo> &pre_stage_res, int input_w,
                                   int input_h, int stage_num,
                                   float threshold) {
  vector<FaceInfo> res;
  int batch_size = (int)pre_stage_res.size();

  if (batch_size == 0) {
    return res;
  }

  Mat *input_layer = nullptr;
  Mat *confidence = nullptr;
  Mat *reg_box = nullptr;
  Mat *reg_landmark = nullptr;

  vector<Mat> targets_blobs;

  switch (stage_num) {
  case 2: {
  } break;
  case 3: {
  } break;
  default:
    return res;
    break;
  }
  int spatial_size = input_h * input_w;

  vector<Mat> inputs;

  for (int n = 0; n < batch_size; ++n) {
    FaceBox &box = pre_stage_res[n].box;
    Mat roi = image(Rect(Point((int)box.x_min, (int)box.y_min),
                         Point((int)box.x_max, (int)box.y_max)))
                  .clone();
    resize(roi, roi, Size(input_w, input_h));
    inputs.push_back(roi);
  }

  Mat blob_input = dnn::blobFromImages(
      inputs, std_val, Size(), Scalar(mean_val, mean_val, mean_val), false);

  switch (stage_num) {
  case 2: {
    r_net.setInput(blob_input, "data");
    const vector<String> targets_node{"conv5-2", "prob1"};
    r_net.forward(targets_blobs, targets_node);
    confidence = &targets_blobs[1];
    reg_box = &targets_blobs[0];

    auto *confidence_data = (float *)confidence->data;
  } break;
  case 3: {
    o_net.setInput(blob_input, "data");
    const vector<String> targets_node{"conv6-2", "conv6-3", "prob1"};
    o_net.forward(targets_blobs, targets_node);
    reg_box = &targets_blobs[0];
    reg_landmark = &targets_blobs[1];
    confidence = &targets_blobs[2];

  } break;
  default:
    break;
  }

  const float *confidence_data = (float *)confidence->data;

  const float *reg_data = (float *)reg_box->data;
  const float *landmark_data = nullptr;
  if (reg_landmark) {
    landmark_data = (float *)reg_landmark->data;
  }
  for (int k = 0; k < batch_size; ++k) {
    if (confidence_data[2 * k + 1] >= threshold) {
      FaceInfo info{};
      info.box.score = confidence_data[2 * k + 1];
      info.box.x_min = pre_stage_res[k].box.x_min;
      info.box.y_min = pre_stage_res[k].box.y_min;
      info.box.x_max = pre_stage_res[k].box.x_max;
      info.box.y_max = pre_stage_res[k].box.y_max;
      for (int i = 0; i < 4; ++i) {
        info.box_reg[i] = reg_data[4 * k + i];
      }
      if (reg_landmark) {
        float w = info.box.x_max - info.box.x_min + 1.f;
        float h = info.box.y_max - info.box.y_min + 1.f;
        for (int i = 0; i < 5; ++i) {
          info.landmark[2 * i] =
              landmark_data[10 * k + 2 * i] * w + info.box.x_min;
          info.landmark[2 * i + 1] =
              landmark_data[10 * k + 2 * i + 1] * h + info.box.y_min;
        }
      }
      res.push_back(info);
    }
  }
  return res;
}
vector<FaceInfo> FMTCNN::ProposalNet(const Mat &img, float threshold) {
  Mat resized;
  int width = img.cols;
  int height = img.rows;
  float scale = 12.f / min_size;
  float minWH = min(height, width) * scale;
  vector<float> scales;
  while (minWH >= 12) {
    scales.push_back(scale);
    minWH *= factor;
    scale *= factor;
  }

  total_boxes.clear();
  for (auto i_scale : scales) {
    int ws = (int)ceil(width * i_scale);
    int hs = (int)ceil(height * i_scale);
    resize(img, resized, Size(ws, hs), 0, 0, INTER_LINEAR);

    Mat inputBlob =
        dnn::blobFromImage(resized, 1 / 255.0, Size(), Scalar(0, 0, 0), false);

    auto *c = (float *)inputBlob.data;
    p_net.setInput(inputBlob, "data");
    const vector<String> targets_node{"conv4-2", "prob1"};
    vector<Mat> targets_blobs;
    p_net.forward(targets_blobs, targets_node);

    Mat prob = targets_blobs[1];
    Mat reg = targets_blobs[0];
    generateBox(&prob, &reg, i_scale, threshold);
    vector<FaceInfo> boxes_nms = NMS(candidate_boxes, 0.5, 'u');
    if (!boxes_nms.empty()) {
      total_boxes.insert(total_boxes.end(), boxes_nms.begin(), boxes_nms.end());
    }
  }
  int num_box = (int)total_boxes.size();

  vector<FaceInfo> res_boxes;
  if (num_box != 0) {
    res_boxes = NMS(total_boxes, 0.7f, 'u');
    BoxRegression(res_boxes);
    BoxPadSquare(res_boxes, width, height);
  }
  return res_boxes;
}
float FMTCNN::IoU(float x_min, float y_min, float x_max, float y_max,
                  float x_min_, float y_min_, float x_max_, float y_max_,
                  bool is_iom) {
  float iw = min(x_max, y_max) - max(x_min, y_min) + 1;
  float ih = min(y_max, y_max_) - max(y_min, y_min_) + 1;
  if (iw <= 0 || ih <= 0) {
    return 0;
  }
  float s = iw * ih;
  if (is_iom) {
    return s / min((x_max - x_min + 1) * (y_max - y_min + 1),
                   (x_max_ - x_min_ + 1) * (y_max_ - y_min_ + 1));
  } else {
    return s / ((x_max - x_min + 1) * (y_max - y_min + 1) +
                (x_max_ - x_min_ + 1) * (y_max_ - y_min_ + 1) - s);
  }
}

Mat FMTCNN::getTFormMatrix(float *std_points, float *feat_points) {
  int points_num_ = 5;
  float sum_x = 0, sum_y = 0;
  float sum_u = 0, sum_v = 0;
  float sum_xx_yy = 0;
  float sum_ux_vy = 0;
  float sum_vx__uy = 0;

  for (int c = 0; c < points_num_; ++c) {
    int x_off = c * 2;
    int y_off = x_off + 1;
    sum_x += std_points[x_off];
    sum_y += std_points[y_off];
    sum_u += feat_points[x_off];
    sum_v += feat_points[y_off];
    sum_xx_yy += std_points[x_off] * std_points[x_off] +
                 std_points[y_off] * std_points[y_off];
    sum_ux_vy += std_points[x_off] * feat_points[x_off] +
                 std_points[y_off] * feat_points[y_off];
    sum_vx__uy += feat_points[y_off] * std_points[x_off] -
                  feat_points[x_off] * std_points[y_off];
  }
  float q =
      sum_u - sum_x * sum_ux_vy / sum_xx_yy + sum_y * sum_vx__uy / sum_xx_yy;
  float p =
      sum_v - sum_y * sum_ux_vy / sum_xx_yy - sum_x * sum_vx__uy / sum_xx_yy;
  float r = points_num_ - (sum_x * sum_x + sum_y * sum_y) / sum_xx_yy;
  float a = (sum_ux_vy - sum_x * q / r - sum_y * p / r) / sum_xx_yy;
  float b = (sum_vx__uy + sum_y * q / r - sum_x * p / r) / sum_xx_yy;
  float c = q / r;
  float d = p / r;

  Mat t_inv = (cv::Mat_<float>(3, 3) << a, b, 0, -b, a, 0, c, d, 1);
  Mat t = t_inv.inv();
  Mat res = t.colRange(0, 2).clone();
  return res.t();
}

void FMTCNN::rotateFace(Mat img, FaceInfo face_info, Mat &dst_img) {
  float std_points[10] = {30.2946, 65.5318, 48.0252, 33.5493, 62.7299,
                          51.6963, 51.5014, 71.7366, 92.3655, 92.2041};

  float facial_points[10];
  for (int i = 0; i < 5; i++) {
    facial_points[2 * i] = face_info.landmark[2 * i];
    facial_points[2 * i + 1] = face_info.landmark[2 * i + 1];
  }
  Mat tFormMatrix = getTFormMatrix(std_points, facial_points);

  warpAffine(img, dst_img, tFormMatrix, dst_img.size(), 1, 0, Scalar(0));
}

void FMTCNN::normalizeFace(Mat dst_img, Mat &normalize_img) {
  Mat sub_factor = 127.5 * Mat(IMG_NORMAL_HEIGHT, IMG_NORMAL_WIDTH, CV_32FC3,
                               Scalar(1, 1, 1));
  dst_img.convertTo(normalize_img, CV_32FC3);
  normalize_img -= sub_factor;
  normalize_img /= 128;
}

void loadFacesAndNames(vector<FaceFeature> &face_names,
                       const string &data_path) {
  face_names.clear();

  FMTCNN cnn;
  if (!filesystem::exists(data_path)) {
    return;
  }
  for (auto &iter : filesystem::directory_iterator(data_path)) {
    auto dir = iter.path();
    string name = dir.stem().generic_string();
    if (name == "." || name == "..") {
      continue;
    }
    FaceFeature feature;
    feature.name = name;
    const string path = data_path + name + "/";
    for (int i = 0; i < IMG_NUMBER; i++) {
      string file_path = path + to_string(i) + DATA_FORMAT;
      cout << "Loading " << file_path << endl;
      Mat img = imread(file_path, 1);
      vector<FaceInfo> face_infos;
      cnn.Detect(img, face_infos);

      Mat face_img;
      FaceInfo face_info{};
      int max_size = 0;
      for (auto &info : face_infos) {
        int x = (int)info.box.x_min;
        int y = (int)info.box.y_min;
        int w = (int)(info.box.x_max - info.box.x_min + 1);
        int h = (int)(info.box.y_max - info.box.y_min + 1);
        if (w * h > max_size) {
          face_img = img(Range(y, y + h - 1), Range(x, x + w - 1));
          max_size = w * h;
          face_info = info;
        }
      }
      if (max_size == 0) {
        printf("%d\n", i);
        continue;
      }
      Mat dst_img(IMG_NORMAL_HEIGHT, IMG_NORMAL_WIDTH, CV_8UC3);
      cnn.rotateFace(face_img, face_info, dst_img);

      Mat normalize_img;
      normalize_img.create(dst_img.size(), CV_32FC3);
      cnn.normalizeFace(dst_img, normalize_img);

      Mat input_blob = blobFromImage(normalize_img);
      cnn.net.setInput(input_blob, "data");
      feature.feature[i] = cnn.net.forward("fc5");
    }
    face_names.push_back(feature);
  }
}

float CosineSimilarity(const Mat &a, const Mat &b) {
  if (a.empty() || b.empty()) {
    return -1.0;
  }
  float ab = a.dot(b);
  float norm_a = norm(a);
  float norm_b = norm(b);
  if (norm(a) != 0 && norm(b) != 0) {
    return ab / (norm_a * norm_b);
  } else {
    return -1.0;
  }
}

string FMTCNN::recogniseFace(Mat feature) {

  string res = "unknown";
  float max_similarity = -1;
  for (const auto &face : face_names) {
    float similarities[IMG_NUMBER];
    for (int i = 0; i < IMG_NUMBER; i++) {
      similarities[i] = CosineSimilarity(face.feature[i], feature);
    }
    sort(similarities, similarities + IMG_NUMBER);
    float similarity =
        accumulate(similarities, similarities + IMG_NUMBER,
                   -similarities[0] - similarities[IMG_NUMBER - 1]) /
        (IMG_NUMBER - 2);
    if (similarity > max_similarity) {
      res = face.name;
      max_similarity = similarity;
    }
  }
  if (max_similarity > SIMILARITY_BOUND) {
    printf("%f\n", max_similarity);
    return res;
  } else {
    return "unknown";
  }
}

void FMTCNN::recogniseWithCamera() {
  VideoCapture capture;
  capture.open(0);
  if (!capture.isOpened()) {
    puts("The camera is not open!!!");
    return;
  }

  while (true) {
    Mat frame;
    capture >> frame;

    Mat image = recogniseFrame(frame);

    imshow("Recognising Face", image);
    char c = (char)waitKey(1);
    if (c == 27 || c == 'q' || c == 'Q')
      break;
  }
}

Mat FMTCNN::recogniseFrame(const Mat &frame) {
  Mat image = frame.clone();
  vector<FaceInfo> face_infos;
  Detect(image, face_infos);

  for (auto &info : face_infos) {
    Mat dst_img(IMG_NORMAL_HEIGHT, IMG_NORMAL_WIDTH, CV_8UC3);
    rotateFace(image, info, dst_img);

    Mat normalize_img;
    normalize_img.create(dst_img.size(), CV_32FC3);
    normalizeFace(dst_img, normalize_img);

    Mat input_blob = blobFromImage(normalize_img);
    Mat feature_output;
    net.setInput(input_blob, "data");
    feature_output = net.forward("fc5");

    string name = recogniseFace(feature_output);
    int x = (int)info.box.x_min;
    int y = (int)info.box.y_min;
    int w = (int)(info.box.x_max - info.box.x_min + 1);
    int h = (int)(info.box.y_max - info.box.y_min + 1);
    rectangle(image, Rect(x, y, w, h), Scalar(0, 0, 255), 2);
    putText(image, name, Point(x, y - 20), FONT_HERSHEY_SIMPLEX, 0.8,
            Scalar(255, 255, 255), 2);
  }
  return image;
}
