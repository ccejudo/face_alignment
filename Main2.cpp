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

  shape_predictor sp;
  dlib::array<array2d<rgb_pixel>> alignedImage;
  frontal_face_detector detector;
  array2d<rgb_pixel> img;
  image_window window;

  //Guardar modelo de puntos faciales en la variable sp
  deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
  detector = get_frontal_face_detector();

  //Crear objeto Alineador
  FaceAligner2 faceA2(250.0, 750.0 ,900.0, 700.0, sp);

  //Cargar imagen a partir de su dirección de archivo
  load_image(img, argv[1]);

  //Detectar caras en imagen --> Esto lo hace el equipo 1
  std::vector<rectangle> dets = detector(img);
  cout << "Number of faces detected: " << dets.size() << endl;

  //Si se detectó al menos 1 cara --> De nuevo esto lo hace el equipo 1
  if(dets.size() > 0){
    //Llamada al método align
    alignedImage = faceA2.align(img, dets);

    //tile_images convierte un arreglo de imágenes en 1 sola
    //set_image muestra la imagen en pantalla
    window.set_image(tile_images(alignedImage));


    //Suspender
    cin.get();
  }
  else{
    cout << "No se detectó ninguna cara" << endl;
  }
}
