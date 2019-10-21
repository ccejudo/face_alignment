#include <opencv2/opencv.hpp>
#include <iostream>

class FaceAligner2{
  //Atributos de la clase
    dlib::shape_predictor sp;
    double DesiredLeftEye[2];
    double DesiredRightEye[2];
    int desiredFaceWidth;
    int desiredFaceHeight;

  public:
    //Constructor
    FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, double xDesiredRightEye1, double yDesiredRightEye1, int desiredFaceWidth1, int desiredFaceHeight1);
    FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, double xDesiredRightEye1, double yDesiredRightEye1, int desiredFaceWidth1, int desiredFaceHeight1, std::string path);

    //Destructor
    ~FaceAligner2();
    //Funciones
    cv::Mat alignCV(cv::Mat imageMat, dlib::rectangle dets);
    int midPoint(int x1, int x2);

};
