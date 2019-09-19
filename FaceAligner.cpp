//Librerias
#include <opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
//#include <boost/numeric/ublas/matrix.hpp> //matriz
//#include <boost/numeric/ublas/io.hpp> //matriz

#include <math.h> //para sacar el angulo

#include <iostream>

using namespace dlib;
using namespace std;

class FaceAligner{
  //Atributos
  private:
     shape_predictor sp;
     double xDesiredLeftEye;
     double yDesiredLeftEye;
     int desiredFaceWidth;
     int desiredFaceHeight;

  public:
    FaceAligner(shape_predictor sp1, double xDesiredLeftEye1, double yDesiredLeftEye1, int desiredFaceWidth1, int desiredFaceHeight1){
      sp = sp1;
	    xDesiredLeftEye = xDesiredLeftEye1;
	    yDesiredLeftEye = yDesiredLeftEye1;
      desiredFaceWidth = desiredFaceWidth1;
      desiredFaceHeight = desiredFaceHeight1;
    }

    //Falta el tipo de dato de rect
	//Rect creo que ya viene con opencv/c++
	/*
	https://docs.microsoft.com/en-us/windows/win32/api/gdiplustypes/nf-gdiplustypes-rect-rect(inint_inint_inint_inint)

	void Rect(
	  IN INT x,
	  IN INT y,
	  IN INT width,
	  IN INT height
	);
*/

    cv::Mat align(string imagen){
        frontal_face_detector detector = get_frontal_face_detector();

        deserialize("shape_predictor_68_face_landmarks.dat") >> sp;

        cv::Mat imageMat = cv::imread(imagen);

        array2d<rgb_pixel> img;
        load_image(img, imagen);

        std::vector<dlib::rectangle> dets = detector(img);

		    full_object_detection shape = sp(img, dets[0]);

        int coords[68][2];

        for (int i = 0; i < 68; i++) {
          for (int j = 0; j < 2; j++) {
            coords[i][j] = 0;
          }
        }

        for (int i = 0; i<68;i++){
            //Regresa las coordenadas de cada rasgo de la cara
            for (int j = 0; i<=1;i++){
                if(j == 0){
                  coords[i][j] = shape.part(i).x();
                }
                else {
                  coords[i][j] = shape.part(i).y();
                }
            }
        }

        //Proximamente leerá de un mapa los datos
        int LeftX1 = 42;
        int LeftX2=48;
        int RightX1 = 36;
        int RightX2=42;

        //checa los puntos de la imagen para saber los puntos en los que están el ojo izq y der

        int LeftEyePoints[68][2];
        for(int i = LeftX1; i<=LeftX2; i++){
            for(int j = 0; j<=1; j++){
                    LeftEyePoints[i][j] = coords[i][j];
             }
        }

        int RightEyePoints[68][2];
        for(int i = RightX1; i<=RightX2; i++){
            for(int j = 0; j<=1; j++){
                RightEyePoints[i][j] = coords[i][j];
            }
        }

       //computar el centro de masa de cada ojo, saca el promedio de los puntos X y Y de cada ojo
        //para sacar el angulo

        int LeftEyeCenterX;
        int LeftEyeCenterY;
        int RightEyeCenterX;
        int RightEyeCenterY;

        for(int i = LeftX1; i<=LeftX2; i++){
            for(int j = 0; j<=1; j++){
                    LeftEyeCenterX = LeftEyeCenterX + LeftEyePoints[i][0];
                    LeftEyeCenterY = LeftEyeCenterY + LeftEyePoints[i][1];
                    RightEyeCenterX = RightEyeCenterX + RightEyePoints[i][0];
                    RightEyeCenterY = RightEyeCenterY + RightEyePoints[i][1];
            }
        }


        int Dy = RightEyeCenterY - LeftEyeCenterY;
        int Dx = RightEyeCenterX - LeftEyeCenterX;

    double angulo = (atan2(Dy, Dx)*180/M_PI)-180;

    //computa donde quieres que este el ojo der basado en la coord del ojo izq
    double xDesiredRightEye = 1.0 - xDesiredLeftEye;
    //calcula la escala de la nueva imagen basado en la diferencia de ojos
    double distancia = sqrt(pow(Dx,2) + pow(Dy,2));
    double desiredDist = (xDesiredRightEye - xDesiredLeftEye);
    desiredDist *= desiredFaceWidth;
    double scale = desiredDist / distancia;

    //computa coordinadas xy en los dos ojos
    float eyesCenter[2];
    eyesCenter[0] = (floor((LeftEyeCenterX + RightEyeCenterX) /2));
    eyesCenter[1] = (floor((LeftEyeCenterX + RightEyeCenterX) /2));

    cv::Point2f eyesCenterPoints(eyesCenter[0],eyesCenter[1]);


    cv::Mat imgMatrix = cv::getRotationMatrix2D(eyesCenterPoints, angulo, scale); //podría jalar error porque no sabemos si eyesCenter es aceptado como matriz en C++

    //Actualizar el componente de traslación de la matriz
    double Tx = desiredFaceWidth * 0.5;
    double Ty = desiredFaceHeight * yDesiredLeftEye;
    imgMatrix.row(2) += (Tx - eyesCenter[0]);
    imgMatrix.col(1) += (Ty - eyesCenter[1]); //Revisón!!!!


    double vector[1][2];
    vector[0][0] = desiredFaceWidth;
    vector[0][1] = desiredFaceHeight;

    cv::Mat rotated_img(cv::Size(desiredFaceHeight, desiredFaceWidth), imageMat.type());

    //no sabemos que hace, vector se cambió por size pero no sabemos si es el mismo tipo
    cv::warpAffine(imageMat, rotated_img, imgMatrix, rotated_img.size());

    return rotated_img;

    }


};
