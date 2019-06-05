# *-* coding: utf-8 *-*

import os

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
            threshold=0.54,
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
        for k, d in enumerate(dets):
            shape = self.shape_predictor(img, d)
            face_descriptor = self.model.compute_face_descriptor(img, shape)

            class_pre = self.find_match_face(face_descriptor)
            cv2.rectangle(
                img, (d.left(), d.top() + 10), (d.right(), d.bottom()), (0, 255, 0), 2
            )
            cv2.putText(
                img,
                class_pre,
                (d.left(), d.top()),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.7,
                (0, 255, 0),
                2,
                cv2.LINE_AA,
            )
        return img

    def add_face(self, name, count=20, dataset="dataset"):
        """
        Add some faces from camera with given name

        :param name: the name of adding faces
        :param count: the number of images array to save
        :param dataset: the path of the dataset
        :return: None
        """

        if not os.path.exists(dataset):
            os.mkdir(dataset)

        capture = cv2.VideoCapture(0)

        if not capture.isOpened():
            raise RuntimeError("Unable to open the camera")

        added = 0
        face_descriptors = []
        while added < count:
            success, frame = capture.read()

            if not success:
                continue

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
                cv2.rectangle(
                    frame,
                    (max_d.left(), max_d.top() + 10),
                    (max_d.right(), max_d.bottom()),
                    (0, 255, 0),
                    2,
                )
            cv2.imshow("Adding Faces", frame)
            cv2.waitKey(1)

        self.face_descriptors[name] = face_descriptors

        np.save(os.path.join(dataset, name), np.array(face_descriptors))
        cv2.destroyAllWindows()
        capture.release()


if __name__ == "__main__":
    recognition = Recognizer()
    recognition.add_face("TEST")

    capture = cv2.VideoCapture(0)

    while True:
        success, frame = capture.read()
        image = recognition.recognise_image(frame)

        cv2.imshow("images", image)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
