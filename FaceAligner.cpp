//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

class FaceAligner{
  //Atributos
  private:
     shape_predictor sp;
     double x_desired_left_eye;
     double y_desired_left_eye;
     int desiredFaceWidth;
     int desiredFaceHeight;

  public:
    FaceAligner(shape_predictor sp1, double x_desired_left_eye1, double y_desired_left_eye1, int desiredFaceWidth1, int desiredFaceHeight1){
      sp = sp1;
      x_desired_left_eye = x_desired_left_eye1;
      y_desired_left_eye = y_desired_left_eye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceHeight1;
    }

    //Falta el tipo de dato de rect
    void align(Mat img, Mat gray, std::vector<rectangle> rect){
       full_object_detection shape = sp(gray, rect);
       shape = 
    }
}
