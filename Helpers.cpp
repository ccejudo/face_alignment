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
    int[][] shapeToNP(full_object_detection shape){
        //Crea matriz de 68 x 2 de tipo int llena de ceros y la llama coords
        boost::numeric::ublas::zero_matrix<int> coords(68, 2);
        std::cout << m << '\n';
        //Convierte las 68 marcas en una tupla de 2 de coordenadas
        for (i = 1; i<=68;++i){
            //Regresa las coordenadas de cada rasgo de la cara
            coords[i] = cv::Point landmark(shape.part(idx[i]).x(),shape.part(idx[i]).y());
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


