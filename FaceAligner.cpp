//Librerias
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <math.h> //para sacar el angulo

using namespace dlib;
using namespace std;

class FaceAligner{
  //Atributos
  private:
     shapePredictor sp;
     double xDesiredLeftEye;
     double yDesiredLeftEye;
     int desiredFaceWidth;
     int desiredFaceHeight;

  public:
    FaceAligner(shapePredictor sp1, double xDesiredLeftEye1, double yDesiredLeftEye1, int desiredFaceWidth1, int desiredFaceHeight1){
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
    void align(Mat img, Mat gray, Rect rect){
		    full_object_detection shape = sp(gray, rect);
		    int[][] shapeNP = shapeToNP(shape);
        //Proximamente leerá de un mapa los datos,es el template creo
        int LeftX1 = 42;
        int LeftX2=48;
        int RightX1 = 36;
        int RightX2=42;
        
        //checa los puntos de la imagen para saber los puntos en los que están el ojo izq y der
        
        int[68][2] LeftEyePoints;
        for(i = Leftx1; i<=LeftX2; i++){
            for(j = 0; j<=1; j++){
                    LeftEyePoints[i][j] = shapeNP[i][j];
             }
        }
        
        int[68][2] RightEyePoints;
        for(i = Rightx1; i<=RightX2; i++){
            for(j = 0; j<=1; j++){
                Right   EyePoints[i][j] = shapeNP[i][j];
            }
        }
        
        //computar el centro de masa de cada ojo, saca el promedio de los puntos X y Y de cada ojo
        //para sacar el angulo
        
        int LeftEyeCenterX;
        int LeftEyeCenterY;
        int RightEyeCenterX;
        int RightEyeCenterY;
        
        for(i = Leftx1; i<=LeftX2; i++){
            for(j = 0; j<=1; j++){
                    LeftEyeCenterX = LeftEyeCenter + LeftEyePoints[i][0];
                    LeftEyeCenterY = LeftEyeCenter + LeftEyePoints[i][1];
                    RightEyeCenterX = RightEyeCenter + RightEyePoints[i][0];
                    RightEyeCenterY = RightEyeCenter + RightEyePoints[i][1];
                }
            }
        }
    
        int Dy = RightEyeCenterY - LeftEyeCenterY;
        int Dx = RightEyeCenterX - LeftEyeCenterX;
    
    double angulo = (atan2(Dy, Dx)*180/PI)-180;
    
    //computa donde quieres que este el ojo der basado en la coord del ojo izq
    double xDesiredRightEye = 1.0 - xDesiredLeftEye;
    //calcula la escala de la nueva imagen basado en la diferencia de ojos
    double distancia = sqrt(pow(Dx,2) + pow(Dy,2));
    double desiredDist = (xDesiredRightEye - xDesiredLeftEye);
    desiredDist *= desiredFaceWidth;
    double scale = desiredDist / distancia;
    }
}
