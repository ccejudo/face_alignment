//Librerias
#include <dlib/image_processing.h>
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
    FaceAligner2(double xDesiredLeftEye1, double yDesiredLeftEye1, int desiredFaceWidth1, int desiredFaceHeight1, shape_predictor sp1){
      sp = sp1;
      xDesiredLeftEye = xDesiredLeftEye1;
   	  yDesiredLeftEye = yDesiredLeftEye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceHeight1;
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
      extract_image_chips(img, get_face_chip_details(shapes), face_chips);
      return face_chips;
     }
};
