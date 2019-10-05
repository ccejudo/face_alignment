//Librerias
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include "FaceAligner2.cpp"

using namespace dlib;
using namespace std;

int main(int argc, char** argv) {

  dlib::array<array2d<rgb_pixel>> alignedImage;
  cv::Mat alignedImage2;
  frontal_face_detector detector;
  array2d<rgb_pixel> img;
  image_window window;
  image_window window_fixed;

  cv::Mat imageMat = cv::imread(argv[1]);

  detector = get_frontal_face_detector();

  //Crear objeto Alineador
  //Estos valores permiten que la imagen salga así
  FaceAligner2 faceA2(50.0, 600.0, 600.0,  600.0, 1500);
  //FaceAligner2 faceA2(5.0, 80.0, 60.0,  80.0, 150);

  //Cargar imagen a partir de su dirección de archivo
  load_image(img, argv[1]);
  //window.set_image(img);

  //Detectar caras en imagen --> Esto lo hace el equipo 1
  std::vector<rectangle> dets = detector(img);
  cout << "Number of faces detected: " << dets.size() << endl;

  //Si se detectó al menos 1 cara --> De nuevo esto lo hace el equipo 1
  if(dets.size() > 0){
    //Llamada al método align
    alignedImage2 = faceA2.alignCV(imageMat,img, dets);
    //Aquí recortamos la imagen al valor requerido pero debe ir en la clase
    cv::resize(alignedImage2, alignedImage2, cv::Size(150,150), 0, 0, cv::INTER_AREA);
    cv::imwrite("faceAligned.jpg", alignedImage2);

    //tile_images convierte un arreglo de imágenes en 1 solo
    //set_image muestra la imagen en pantalla
    //window_fixed.set_image(tile_images(alignedImage));
    //Suspender
    //cin.get();
  }
  else{
    cout << "No face detected" << endl;
  }
}
