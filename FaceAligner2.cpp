//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <iostream>
#include <math.h>
#include "FaceAligner2.hpp"

    //Constructor
    FaceAligner2::FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, double xDesiredRightEye1, double yDesiredRightEye1, int desiredFaceWidth1, int desiredFaceHeight1){
      //Guardar modelo de puntos faciales en la variable sp
      dlib::deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
      DesiredLeftEye[0] = xDesiredLeftEye1;
   	  DesiredLeftEye[1] = yDesiredLeftEye1;
      DesiredRightEye[0] = xDesiredRightEye1;
   	  DesiredRightEye[1] = yDesiredRightEye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceHeight1;
    }

    FaceAligner2::FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, double xDesiredRightEye1, double yDesiredRightEye1, int desiredFaceWidth1, int desiredFaceHeight1, std::string path){
      //Guardar modelo de puntos faciales en la variable sp
      dlib::deserialize(path) >> sp;
      DesiredLeftEye[0] = xDesiredLeftEye1;
      DesiredLeftEye[1] = yDesiredLeftEye1;
      DesiredRightEye[0] = xDesiredRightEye1;
      DesiredRightEye[1] = yDesiredRightEye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceHeight1;
    }

    //Destructor
    FaceAligner2::~FaceAligner2(){
      std::cout << "Bye" << '\n';
    }

     //Función de alinear con OPEN CV
     cv::Mat FaceAligner2::alignCV(cv::Mat imageMat, dlib::rectangle dets){
       //Variables
       int leftEyeCenter[2];
       int rightEyeCenter[2];
       int imageMidPoint[2];
       cv::Mat image_aligned;
       dlib::array2d<dlib::rgb_pixel> img;
       dlib::full_object_detection shape;
       double scale;
       double Op[2];
       double Oi[2];
       double Opmagnitud;
       double Oimagnitud;
       double dY, dX;
       double angle;
       double traslacion[2];
       cv::Mat imgMatrix;

       //Transforma Mat a array2d
       dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(imageMat));

       //Objeto que guarda los puntos
       shape = sp(img, dets);

       //Puntos de los ojos
       leftEyeCenter[0] = midPoint(shape.part(2).x(), shape.part(3).x());
       leftEyeCenter[1] = midPoint(shape.part(2).y(), shape.part(3).y());

       rightEyeCenter[0] = midPoint(shape.part(1).x(), shape.part(0).x());
       rightEyeCenter[1] = midPoint(shape.part(1).y(), shape.part(0).y());

       imageMidPoint[0] = midPoint(leftEyeCenter[0], rightEyeCenter[0]);
       imageMidPoint[1] = midPoint(leftEyeCenter[1], rightEyeCenter[1]);

       //Escala
       Op[0] = DesiredLeftEye[0] - DesiredRightEye[0];
       Op[1] = DesiredLeftEye[1] - DesiredRightEye[1];

       Oi[0] = leftEyeCenter[0] - rightEyeCenter[0];
       Oi[1] = leftEyeCenter[1] - rightEyeCenter[1];

       Opmagnitud = sqrt((Op[0]*Op[0]) + (Op[1]*Op[1])); //No usar pow porque implica más pasos
       Oimagnitud = sqrt((Oi[0]*Oi[0]) + (Oi[1]*Oi[1]));

       scale = Opmagnitud / Oimagnitud;

       //Ángulo
       dY = rightEyeCenter[1] - leftEyeCenter[1];
       dX = rightEyeCenter[0] - leftEyeCenter[0];
       angle = (atan2(dY, dX)*180/M_PI);

      //Traslación
      traslacion[0] = DesiredLeftEye[0] - leftEyeCenter[0];
      traslacion[1] = DesiredLeftEye[1] - leftEyeCenter[1];

      //Se calcula el centro donde se va a rotar
      cv::Point2f eyesCenterPoints(leftEyeCenter[0],leftEyeCenter[1]);

      //Calcula el mat de la matriz rotada
      imgMatrix = cv::getRotationMatrix2D(eyesCenterPoints, angle, scale);

      //Se especifica la traslación en la matriz mat
      imgMatrix.at<double>(0,2) += traslacion[0];
      imgMatrix.at<double>(1,2) += traslacion[1];

      //warpAffine
      cv::warpAffine(imageMat, image_aligned, imgMatrix, cv::Size(desiredFaceWidth,desiredFaceHeight), cv::INTER_LINEAR, cv::BORDER_CONSTANT);
      return image_aligned;
     }

     //Funcion para sacar punto medio
     int FaceAligner2::midPoint(int x1, int x2){
       int midPoint = (x1 + x2)/2;
       return midPoint;
     }
