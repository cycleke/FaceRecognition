# FaceRecognition
The Face Recognition with OpenCV and Qt

![License](https://img.shields.io/github/license/cycleke/FaceRecognition.svg?style=flat-square)

## Introduction
This program is used to recognise faces with opencv.
The gui is based on Qt5.

## Requirements
Qt5, OpenCV4

## Build Steps
``` shell
git clone https://github.com/cycleke/FaceRecognition
cd FaceRecognition
cmake .
make
```

Note: Some of the files are tracked with lfs due to their size, please clone with lfs.

## TODOs
- [ ] Make GUI
  - [ ] Main Window
  - [ ] Settings
  - [ ] About
- [ ] Add and delete faces
  - [x] Detect faces
  - [x] Recognise different faces
- [ ] Import and export data
