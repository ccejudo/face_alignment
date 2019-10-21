//Librerias
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include "FaceAligner2.hpp"
#include <chrono>

//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>

using namespace dlib;
using namespace std;
using namespace std::chrono;

int midPoint(int x1, int x2){
  int midPoint = (x1 + x2)/2;

  return midPoint;
}

double printPosicionOjos(cv::Mat imageMat, std::vector<rectangle> dets){

  shape_predictor sp;
  deserialize("shape_predictor_5_face_landmarks.dat") >> sp;
  array2d<rgb_pixel> img;
  dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(imageMat));
  full_object_detection shape = sp(img, dets[0]); //la alineada
  double iX, iY, dX, dY;
  iX = midPoint(shape.part(2).x(), shape.part(3).x());
  iY = midPoint(shape.part(2).y(), shape.part(3).y());
  dX = midPoint(shape.part(1).x(), shape.part(0).x());
  dY = midPoint(shape.part(1).y(), shape.part(0).y());

  cout << iX << endl;
  cout << iY << endl;
  cout << dX << endl;
  cout << dY << endl;
  double acum = 0;

  if((iX<39) or (iX>41)){
    acum += .25;
  }
  if((iY<49) or (iY > 51)){
    acum += .25;
  }
  if((dX<109) or (dX > 111)){
    acum += .25;
  }
  if((dY<49) or (dY > 51)){ //+- 1 pixel de precision
    acum += .25;
  }
  return acum;
}

int main(int argc, char** argv) {

  dlib::array<array2d<rgb_pixel>> alignedImage;
  cv::Mat alignedImage2;
  frontal_face_detector detector;
  array2d<rgb_pixel> img;
  image_window window;
  image_window window_fixed;
  std::vector<rectangle> dets;

  cv::Mat imageMat;
  detector = get_frontal_face_detector();

  //Crear objeto Alineador
  FaceAligner2 faceA2(40.0, 50.0, 110.0,  50.0, 150, 150, "/Users/brias5/Desktop/face_alignment/build/shape_predictor_5_face_landmarks.dat"); //Especifica los valores del template (IzqX,IzqY,DerX,DerY,Width,Height)

  int imagenes = 10;
  double promTiempo = 0;
  double minTiempo = 300000;
  double maxTiempo = 0; //no debe ser mayor a 300 000 micro segundos
  double average = imagenes;

  for(int i = 1; i <= imagenes; i++){
    imageMat = cv::imread("part3/" + to_string(i) + ".jpg"); //quitar face dp de hacer python, faces/face
    //Cargar imagen a partir de su dirección de archivo
    load_image(img, "part3/" + to_string(i) + ".jpg");
    //window.set_image(img);

    //Detectar caras en imagen --> Esto lo hace el equipo 1
    dets = detector(img);
    cout << "Number of faces detected: " << dets.size() << endl;

    //Si se detectó al menos 1 cara --> De nuevo esto lo hace el equipo 1
    if(dets.size() > 0){
      //Llamada al método align
      auto start = high_resolution_clock::now();
      alignedImage2 = faceA2.alignCV(imageMat, dets[0]);
      //TIEMPO DE EJECUCIÓN
      auto stop = high_resolution_clock::now(); //termina tiempo
      auto duration = duration_cast<microseconds>(stop - start); //saca diferencia
      cout << "Image : " << i << endl;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
      cout << "Width : " << alignedImage2.size().width << endl;
      cout << "Height: " << alignedImage2.size().height << endl;
      cv::imwrite("Output/faceAligned" + to_string(i) + ".jpg", alignedImage2);
      load_image(img, "Output/faceAligned" + to_string(i) + ".jpg");
      dets = detector(img);
      imageMat = cv::imread("Output/faceAligned" + to_string(i) + ".jpg");
      double precision = printPosicionOjos(imageMat, dets);
      cout << "Precision : " << precision << endl;

      if(duration.count()>maxTiempo){ //si es mayor que el maximo es el nuevo maximo
        maxTiempo = duration.count();
      }
      if(duration.count()<minTiempo){ //si es menor que el minimo es el nuevo minimo
        minTiempo = duration.count();
      }
      average -= precision;
      promTiempo += duration.count();
    }
    else{
      cout << "No face detected" << endl;
    }
  }

  cout << "Average time : " << promTiempo/imagenes << endl;
  cout << "Min time : " << minTiempo << endl;
  cout << "Max time : " << maxTiempo << endl;
  cout << "Precision: " << (average*100)/imagenes << endl;


}
