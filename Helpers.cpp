//Librerias
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <boost/numeric/ublas/matrix.hpp> //matriz
#include <boost/numeric/ublas/io.hpp> //matriz
#include <iostream> //matriz

private:
    shape_predictor sp;

class Helpers{
    //Falta el tipo de shape
    public:
    shape_to_np(full_object_detection shape){
        //Crea matriz de 68 x 2 de tipo int llena de ceros y la llama coords
        boost::numeric::ublas::zero_matrix<int> coords(68, 2);
        std::cout << m << '\n';
        //Convierte las 68 marcas en una tupla de 2 de coordenadas
        for (i = 1; i<=68;++i){
            coords[i] = (shape.part(i).x , shape.part(i).y) //creo que está en la librería full object detection pero no se
        }
        return coords;
    }
    public:
        rect_to_bb(std::vector<rectangle> rect){
            //Convert to format (x,y,w,h)
            int x = rect.left();
            int y = rect.top();
            int w = rect.right() - x;
            int h = rect.bottom() - y;
            int vector[] = {x,y,w,h};
            return vector;
        }
}


