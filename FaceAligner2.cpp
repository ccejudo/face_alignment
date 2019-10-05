//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <iostream>
#include <math.h>

using namespace dlib;
using namespace std;

class FaceAligner2{

  //Atributos de la clase
  private:
    shape_predictor sp;
    double DesiredLeftEye[2];
    double DesiredRightEye[2];
    int desiredFaceWidth;
    int desiredFaceHeight;

  public:

    //Constructor
    FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, double xDesiredRightEye1, double yDesiredRightEye1, int desiredFaceWidth1){
      //Guardar modelo de puntos faciales en la variable sp
      deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
      DesiredLeftEye[0] = xDesiredLeftEye1;
   	  DesiredLeftEye[1] = yDesiredLeftEye1;
      DesiredRightEye[0] = xDesiredRightEye1;
   	  DesiredRightEye[1] = yDesiredRightEye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceWidth1;
    }

    //Destructor
    ~FaceAligner2(){
      cout << "Bye" << '\n';
    }

    //Función para alinear --> Retorna un arreglo de pixeles
    //img es pasada por referencia

    dlib::array<array2d<rgb_pixel>> align(array2d<rgb_pixel> &img, std::vector<rectangle> dets){
      //Vector de objetos full_object_detection
      std::vector<full_object_detection> shapes;

      //Vector de pixeles
      dlib::array<array2d<rgb_pixel>> face_chips;

      //Obtener landmarks faciales de la cara detectada en la imagen
      full_object_detection shape = sp(img, dets[0]);

      //Añade el objeto shape al vector full_object_detection
      shapes.push_back(shape);

      //Función para escalar y rotar la imágen
      extract_image_chips(img, get_face_chip_details(shapes, desiredFaceWidth, 0.25), face_chips);

      //Muestra las posiciones de la imagen original
      cout << "Original Positions" << '\n';
      cout << "left eye start pixel position: " << shape.part(2).x() << endl;
      cout << "left eye end pixel position: " << shape.part(3) << endl;

      cout << "right eye start pixel position: " << shape.part(1) << endl;
      cout << "right eye end pixel position: " << shape.part(0) << endl;
      return face_chips;
     }

     //Función de alinear con Open CV
     cv::Mat alignCV(cv::Mat imageMat,array2d<rgb_pixel> &img, std::vector<rectangle> dets){

       int leftEyeCenter[2];
       int rightEyeCenter[2];
       int imageMidPoint[2];

       cv::Mat image_aligned;

       //std::vector<full_object_detection> shapes;

       full_object_detection shape = sp(img, dets[0]);

       //Puntos de los ojos
       leftEyeCenter[0] = midPoint(shape.part(2).x(), shape.part(3).x());
       leftEyeCenter[1] = midPoint(shape.part(2).y(), shape.part(3).y());

       rightEyeCenter[0] = midPoint(shape.part(1).x(), shape.part(0).x());
       rightEyeCenter[1] = midPoint(shape.part(1).y(), shape.part(0).y());

       imageMidPoint[0] = midPoint(leftEyeCenter[0], rightEyeCenter[0]);
       imageMidPoint[1] = midPoint(leftEyeCenter[1], rightEyeCenter[1]);

       //Escala
       double scale;
       double Op[2];
       double Oi[2];
       double Opmagnitud;
       double Oimagnitud;


       Op[0] = DesiredLeftEye[0] - DesiredRightEye[0];
       Op[1] = DesiredLeftEye[1] - DesiredRightEye[1];

       Oi[0] = leftEyeCenter[0] - rightEyeCenter[0];
       Oi[1] = leftEyeCenter[1] - rightEyeCenter[1];

       Opmagnitud = sqrt(pow(Op[0],2) + pow(Op[1],2));
       Oimagnitud = sqrt(pow(Oi[0],2) + pow(Oi[1],2));

       scale = Opmagnitud / Oimagnitud;

       //Ángulo
       double dY, dX;
       double angle;
       dY = rightEyeCenter[1] - leftEyeCenter[1];
       dX = rightEyeCenter[0] - leftEyeCenter[0];
       angle = (atan2(dY, dX)*180/M_PI);


      //Traslación
      double traslacion[2];
      //traslacion[0] = abs(DesiredLeftEye[0] - leftEyeCenter[0]);
      //traslacion[1] = abs(DesiredLeftEye[1] - leftEyeCenter[1]);

      //las traslaciones de arriba son las que importan, esto fue para probar
      traslacion[0] = 0; //suma izquierda, menos derecha
      traslacion[1] =400; //mas arriba derecha, menos abajo a la izq

      //No sabemoos bien como funcione eyesCenterPoints
      cv::Point2f eyesCenterPoints(traslacion[0],traslacion[1]);
      //getRotationMatrix2D
      cv::Mat imgMatrix = cv::getRotationMatrix2D(eyesCenterPoints, angle, scale);
      //warpAffine
      cv::warpAffine(imageMat, image_aligned, imgMatrix, cv::Size(desiredFaceWidth,desiredFaceHeight), cv::INTER_LINEAR, cv::BORDER_CONSTANT);


      return image_aligned;
     }

//Funcion para sacar punto medio
     int midPoint(int x1, int x2){
       int midPoint = (x1 + x2)/2;

       return midPoint;
     }
};


//Para ver donde quedan los ojos de la nueva imagen

/*frontal_face_detector detector;
matrix<rgb_pixel> aligned = tile_images(face_chips);

std::vector<rectangle> dets2 = detector(aligned);
shape = sp(aligned, dets2[0]);

//Muestra las nuevas posiciones de los ojos

cout << "New Positions" << '\n';
cout << "left eye start pixel position: " << shape.part(2) << endl;
cout << "left eye end pixel position: " << shape.part(3) << endl;

cout << "right eye start pixel position: " << shape.part(1) << endl;
cout << "right eye end pixel position: " << shape.part(0) << endl;*/
