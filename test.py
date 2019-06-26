# *-* coding: utf-8 *-*

import os
import sys
import time
import cv2
import dlib
import numpy as np


class Recognizer:
    """
    Recognise faces
    """

    def __init__(
        self,
        *,
        threshold=0.6,
        predictor_path="static/shape_predictor_68_face_landmarks.dat",
        face_rec_model_path="static/dlib_face_recognition_resnet_model_v1.dat",
    ):
        self.detector = dlib.get_frontal_face_detector()
        self.shape_predictor = dlib.shape_predictor(predictor_path)
        self.model = dlib.face_recognition_model_v1(face_rec_model_path)

        self.threshold = threshold
        self.face_descriptors = {}

    def load_data(self, dataset="dataset"):
        """
        Load dataset with .npz files

        :param dataset: the path of dataset
        :return: None
        """
        self.face_descriptors = {}
        if os.path.exists(dataset):
            for faces in os.listdir(dataset):
                file_name, extension = os.path.splitext(faces)
                if extension != ".npy":
                    continue
                descriptors = np.load(os.path.join(dataset, faces))
                if descriptors.any():
                    self.face_descriptors[file_name] = descriptors.copy()

    def find_match_face(self, face_descriptor):
        """
        Find the best matched face.
        :param face_descriptor: the descriptor of the face to match
        :return: the name of the face
        """
        min_dist = self.threshold + 1
        min_dist_face = "unknown"
        face_descriptor = np.array(face_descriptor)

        for iter in self.face_descriptors.items():
            dist = np.linalg.norm(
                iter[1] - face_descriptor, axis=1, keepdims=True
            ).sum() / len(iter[1])

            if dist < min_dist:
                min_dist = dist
                min_dist_face = iter[0]

        if min_dist < self.threshold:
            return min_dist_face
        else:
            return "unknown"

    def recognise_image(self, image):
        """
        Recognise the image

        :param image: the image to recognise
        :return: img the recognised image
        """
        img = image.copy()
        dets = self.detector(img, 1)

        max_d = None

        def area(rect):
            height = rect.top() - rect.bottom()
            width = rect.right() - rect.left()
            return height * width

        for k, d in enumerate(dets):
            if (not max_d) or (area(d) > area(max_d)):
                max_d = d

        if max_d == None:
            return ""
        shape = self.shape_predictor(img, max_d)
        face_descriptor = self.model.compute_face_descriptor(img, shape)
        return self.find_match_face(face_descriptor)

    def add_face(self, name, img_dir, count=4, dataset="dataset"):
        """
        Add some faces from camera with given name

        :param name: the name of adding faces
        :param count: the number of images array to save
        :param dataset: the path of the dataset
        :return: None
        """

        if not os.path.exists(dataset):
            os.mkdir(dataset)

        added = 0
        face_descriptors = []
        for img_file in os.listdir(img_dir):
            frame = cv2.imread(os.path.join(img_dir, img_file))

            dets = self.detector(frame, 1)

            if frame.shape[0] * frame.shape[1] > 500000:
                frame = cv2.resize(frame, (0, 0), fx=0.5, fy=0.5)

            max_d = None

            def area(rect):
                height = rect.top() - rect.bottom()
                width = rect.right() - rect.left()
                return height * width

            for k, d in enumerate(dets):
                if (not max_d) or (area(d) > area(max_d)):
                    max_d = d

            # print(type(max_d))
            if max_d:
                shape = self.shape_predictor(frame, max_d)
                descriptor = self.model.compute_face_descriptor(frame, shape)
                face_descriptors.append(descriptor)
                added += 1
                if added == count:
                    break

        self.face_descriptors[name] = face_descriptors
        # np.save(os.path.join(dataset, name), np.array(face_descriptors))


if __name__ == "__main__":
    recognition = Recognizer()

    count, limit = 0, 300

    persons = os.listdir("lfw_small")
    persons.sort()
    for person in persons:
        cnt = min(max(len(os.listdir(os.path.join("lfw_small", person))) / 2, 4), 20)
        recognition.add_face(person, os.path.join("lfw_small", person), cnt)
        sys.stdout.write("#" + "->" + "\b\b")
        sys.stdout.flush()
        count += 1
        #print(person, count)
        if count >= limit:
            break

    sys.stdout.write("\n")

    log = ""
    count = 0
    s_total, s_correct = 0, 0
    for person in persons:
        log += person + ": "
        total, correct = 0, 0
        for img_file in os.listdir(os.path.join("lfw_small", person)):
            image = os.path.join("lfw_small", person, img_file)
            image = cv2.imread(image)
            total += 1
            time1 = time.time()
            if recognition.recognise_image(image) == person:
                correct += 1
            time2 = time.time()
            log += "%gs " % (time2 - time1)
        log += "\n%d / %d\n" % (correct, total)
        s_total += total
        s_correct += correct
        sys.stdout.write("#" + "->" + "\b\b")
        sys.stdout.flush()
        count += 1
        #print(person, count)
        if count >= limit:
            break

    log += "total: %d / %d" % (s_correct, s_total)
    open("test.log", "w").write(log)
