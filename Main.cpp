#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include "FaceAligner.cpp"
#include <math.h> //para sacar el angulo
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/cmd_line_parser.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <dlib/opencv.h>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace dlib;
using namespace std;


int main(int argc, char** argv) {

	shape_predictor sp;

	//frontal_face_detector detector = get_frontal_face_detector();
	//deserialize(argv[1])>>sp;
	FaceAligner faceA(sp, 40, 40 ,500, 500);

	Mat image = imread(argv[1]);
	//Mat gray, faceAligned;

	//resize(image, image, Size(480, 640));
	//cvtColor(image, gray, COLOR_BGR2GRAY);



	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);


  Mat output = faceA.align(argv[1]);


	//vector<rectangle> dets = detector(img);

	//faceAligned = faceA.align(image, gray, dets[0]);
	//faceAligned = faceA.align(argv[2]);

//imshow("Aligned", output);

	waitKey(0);


	return 0;
}
