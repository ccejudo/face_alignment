#include <opencv2/opencv.hpp> //cvui
#define CVUI_IMPLEMENTATION //cvui
#include "cvui.h" //cvui
#include <opencv2/core.hpp> //video
#include <opencv2/videoio.hpp> //video
#include <opencv2/highgui.hpp> //video

#include <iostream>
#include <stdio.h>

#define WINDOW_NAME "Menu"

//To add a new user
void pedirDatos(cv::Mat save_img) {
  std::string nombre, apellido, matricula, genero;
  std::cout << "Dame el nombre: ";
  std::cin >> nombre;
  std::cout << "Dame el apellido: ";
  std::cin >> apellido;
  std::cout << "Dame la matricula: ";
  std::cin >> matricula;
  std::cout << "Dame tu genero (basado en tus cromosomas maldito homosexual): ";
  std::cin >> genero;

  //Addperson(save_img,matricula);

  namedWindow( "Display window", cv::WINDOW_AUTOSIZE ); // Create a window for display.
  imshow( "Display window", save_img);
}
void oneToOne(cv::Mat save_img){
  std::string matricula;
  std::cout << "Dame la matricula (credencial): ";
  std::cin >> matricula;
  namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", save_img);
  std::cout << "Verificando . . . ";
  //Verify();
  cv::Mat imgDB = cv::imread("/Users/brias5/Desktop/face_alignment/CVUI/Sampleimages/1.jpg"); //funcion que llama a 1 to 1, simulacion
  cv::Mat dst;
  cv::Mat save_img_dst;
  cv::Mat imgDB_dst;
  cv::Size size(150,150);
  resize(save_img,save_img_dst,size);
  resize(imgDB,imgDB_dst,size);
  //cv::hconcat(save_img_dst, imgDB, dst); // horizontal
  namedWindow( "Display window database", cv::WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window database", save_img_dst);
  imshow( "Display window", imgDB_dst );
  //namedWindow( "CONCAT", cv::WINDOW_AUTOSIZE );
  //imshow( "CONCAT", dst );
  cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
  while (true) {

    frame = cv::Scalar(49, 52, 49);
    cvui::button(frame, 110, 80, "NO PASAS");
    namedWindow( "nopasas", cv::WINDOW_AUTOSIZE );
    imshow( "nopasas", frame);
    if (cv::waitKey(20) == 27) {
      cv::destroyWindow("Display window");
      cv::destroyWindow("Display window database");
        cv::destroyWindow("nopasas");
        break;
    }

 }

  if (cv::waitKey(20) == 27) { //ESC
      cv::destroyWindow("Display window");
      cv::destroyWindow("Display window database");
  }
}
void oneToMany(cv::Mat save_img) {
  namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", save_img);
  std::cout << "Verificando . . . ";
  //Verify();
  cv::Mat imgDB1 = cv::imread("/Users/brias5/Desktop/face_alignment/CVUI/Sampleimages/1.jpg"); //funcion que llama a 1 to 1, simulacion
  cv::Mat imgDB2 = cv::imread("/Users/brias5/Desktop/face_alignment/CVUI/Sampleimages/2.jpg");
  cv::Mat imgDB3 = cv::imread("/Users/brias5/Desktop/face_alignment/CVUI/Sampleimages/3.jpg");
  cv::Mat imgDB4 = cv::imread("/Users/brias5/Desktop/face_alignment/CVUI/Sampleimages/4.jpg");
  cv::Mat dst;
  cv::Mat save_img_dst;
  cv::Mat imgDB1_dst;
  cv::Mat imgDB2_dst;
  cv::Mat imgDB3_dst;
  cv::Mat imgDB4_dst;
  cv::Size size(150,150);
  resize(save_img,save_img_dst,size);
  resize(imgDB1,imgDB1_dst,size);
  resize(imgDB2,imgDB2_dst,size);
  resize(imgDB3,imgDB3_dst,size);
  resize(imgDB4,imgDB4_dst,size);
  //cv::hconcat(save_img_dst, imgDB, dst); // horizontal

//Identify();

  namedWindow( "Display window database", cv::WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window database", save_img_dst);
  imshow( "Display window", imgDB1_dst );
  namedWindow( "Display window 2", cv::WINDOW_AUTOSIZE );
  namedWindow( "Display window 3", cv::WINDOW_AUTOSIZE );
  namedWindow( "Display window 4", cv::WINDOW_AUTOSIZE );
  imshow( "Display window 2", imgDB2_dst );
  imshow( "Display window 3", imgDB3_dst );
  imshow( "Display window 4", imgDB4_dst );
  //namedWindow( "CONCAT", cv::WINDOW_AUTOSIZE );
  //imshow( "CONCAT", dst );
  cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
  while (true) {

    frame = cv::Scalar(49, 52, 49);
    cvui::button(frame, 110, 80, "NO PASAS");
    namedWindow( "nopasas", cv::WINDOW_AUTOSIZE );
    imshow( "nopasas", frame);
    if (cv::waitKey(20) == 27) {
      cv::destroyWindow("nopasas");
      cv::destroyWindow("Display window");cv::destroyWindow("Display window 2");cv::destroyWindow("Display window 3");cv::destroyWindow("Display window 4");
      cv::destroyWindow("Display window database");
        break;
    }

 }

  if (cv::waitKey(20) == 27) { //ESC
      cv::destroyWindow("Display window");
      cv::destroyWindow("Display window database");
  }
}
//User interface main
int main(int, char**) {
    //Initialize frame
    cv::Mat frame = cv::Mat(200, 500, CV_8UC3);

    // Init a OpenCV window and tell cvui to use it.
    cv::namedWindow(WINDOW_NAME);
    cvui::init(WINDOW_NAME);

    bool is_running = true;

    //While using the program
    while (is_running) {

      frame = cv::Scalar(49, 52, 49);
      cv::VideoCapture cap; //VIDEO
      cv::Mat save_img;
      int deviceID = 0;             // 0 = open default camera
      int apiID = cv::CAP_ANY;      // 0 = autodetect default API
      // open selected camera using selected API
      cap.open(deviceID + apiID);
      // check if we succeeded
      if (!cap.isOpened()) {
          std::cerr << "ERROR! Unable to open camera\n";
          return -1;
      }
      //---Loop to read frames
      for (;;){
          // wait for a new frame from camera and store it into 'frame'
          cap.read(frame);
          // check if we succeeded
          if (frame.empty()) {
              std::cerr << "ERROR! blank frame grabbed\n";
              break;
          }

          //Buttons
          if (cvui::button(frame, 110, 80, "1 to 1")) {
              // The button was clicked, so let's take a picture and call the corresponding function.
              cap >> frame;
              cap >> save_img;
              //imwrite("1to1.jpg", save_img);
              oneToOne(save_img);//Funcion de 1 a 1
          }
          if (cvui::button(frame, 200, 80, "1 to M")) {
            // The button was clicked, so let's take a picture and call the corresponding function.
            cap >> frame;
            cap >> save_img;
            //imwrite("1toM.jpg", save_img);
            oneToMany(save_img);//Funcion de 1 a M
          }
          if (cvui::button(frame, 290, 80, "Add users")) {
            // The button was clicked, so let's take a picture and call the corresponding function.
              cap >> frame;
              cap >> save_img;
              //imwrite("newuser.jpg", save_img);
              pedirDatos(save_img); //Funcion que pide datos
          }

          if (cvui::button(frame, 400, 80, "EXIT")) {
            // The button was clicked, so let's take a picture and call the corresponding function.
              is_running = false;
              break;
          }
          cvui::update();

          // Show everything on the screen
          cv::imshow(WINDOW_NAME, frame);

          // Check if ESC key was pressed
          if (cv::waitKey(20) == 27) {
              is_running = false;
              break;
          }
        } //close for
      } //close while
    return 0;
} //close main
