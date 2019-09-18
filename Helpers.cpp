//Librerias
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <boost/numeric/ublas/matrix.hpp> //matriz
#include <boost/numeric/ublas/io.hpp> //matriz
#include <iostream> //matriz

private:
    shapePredictor sp;

class Helpers{
    //Falta el tipo de shape
    public:
      //For dlib’s 68-point facial landmark detector:
      //Cambiar a mapa
      FACIAL_LANDMARKS_68_IDXS = OrderedDict([
      	("mouth", (48, 68)),
      	("inner_mouth", (60, 68)),
      	("right_eyebrow", (17, 22)),
      	("left_eyebrow", (22, 27)),
      	("right_eye", (36, 42)),
      	("left_eye", (42, 48)),
      	("nose", (27, 36)),
      	("jaw", (0, 17))
      ])

    int[][] shapeToNP(full_object_detection shape){
        //Crea matriz de 68 x 2 de tipo int llena de ceros y la llama coords
        boost::numeric::ublas::zero_matrix<int> coords(68, 2);
        std::cout << m << '\n';
        //Convierte las 68 marcas en una tupla de 2 de coordenadas
        for (i = 0; i<68;++i){
            //Regresa las coordenadas de cada rasgo de la cara
            for (j = 0; i<=1;++i){
                if(j == 0){
                  coords[i][j] = cv::Point landmark(shape.part(idx[i]).x());
                }
                else {
                  coords[i][j] = cv::Point landmark(shape.part(idx[i]).y());
                }
            }
        }
        return coords;
    }
    public:
        int[] rectToBB(Rect rect){ //puede ser tipo std::vector<rectangle>
            //Convert to format (x,y,w,h)
            int x = rect.left(); //depende de la librería que encontremos
            int y = rect.top();
            int w = rect.right() - x;
            int h = rect.bottom() - y;
            int vector[] = {x,y,w,h};
            return vector;
        }
}
