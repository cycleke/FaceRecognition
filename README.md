# FaceRecognition
The Face Recognition with OpenCV and Qt

![License](https://img.shields.io/github/license/cycleke/FaceRecognition.svg?style=flat-square)

## Introduction
This program is used to recognise faces with opencv.
The gui is based on Qt5.

## Requirements
PyQt5, OpenCV4, dlib

## Build Steps
``` shell
git clone https://github.com/cycleke/FaceRecognition
cd FaceRecognition
pip install -r requirements.txt
python main.py
```

Note: Some of the files are tracked with lfs due to their size, please clone with lfs.

## TODOs
- [x] Make GUI
  - [x] Main Window
  - [ ] Settings
  - [x] About
- [x] Add and delete faces
  - [x] Detect faces
  - [x] Recognise different faces
- [ ] Import and export data
