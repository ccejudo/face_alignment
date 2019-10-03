//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>
#include <iostream>

using namespace dlib;
using namespace std;

class FaceAligner2{

  //Atributos de la clase
  private:
    shape_predictor sp;
    double xDesiredLeftEye;
    double yDesiredLeftEye;
    int desiredFaceWidth;
    int desiredFaceHeight;

  public:

    //Constructor
    FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, int desiredFaceWidth1){
      //Guardar modelo de puntos faciales en la variable sp
      deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
      xDesiredLeftEye = xDesiredLeftEye1;
   	  yDesiredLeftEye = yDesiredLeftEye1;
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



      return face_chips;
     }

     cv::Mat alignCV(array2d<rgb_pixel> &img, std::vector<rectangle> dets){

       int leftEyeCenter[2];
       int rightEyeCenter[2];
       int imageMidPoint[2];

       cv::Mat image_aligned;

       std::vector<full_object_detection> shapes;

       full_object_detection shape = sp(img, dets[0]);

       shapes.push_back(shape);

       leftEyeCenter[0] = midPoint(shape.part(2).x(), shape.part(3).x());
       leftEyeCenter[1] = midPoint(shape.part(2).y(), shape.part(3).y());

       rightEyeCenter[0] = midPoint(shape.part(1).x(), shape.part(0).x());
       rightEyeCenter[1] = midPoint(shape.part(1).y(), shape.part(0).y());

       imageMidPoint[0] = midPoint(leftEyeCenter[0], rightEyeCenter[0]);
       imageMidPoint[1] = midPoint(leftEyeCenter[1], rightEyeCenter[1]);



       return image_aligned;
     }

     int midPoint(int x1, int x2){
       int midPoint = (x1 + x2)/2;

       return midPoint;
     }
};
