/**
    * @brief makeCanvas Makes composite image from the given images
    * @param vecMat Vector of Images.
    * @param windowHeight The height of the new composite image to be formed.
    * @param nRows Number of rows of images. (Number of columns will be calculated
    *              depending on the value of total number of images).
    * @return new composite image.
    */
    #include <opencv2/opencv.hpp> //cvui
    #include <opencv2/core.hpp> //video
    #include <opencv2/videoio.hpp> //video
    #include <opencv2/highgui.hpp> //video

    #include <iostream>
    #include <stdio.h>
    using namespace cv;


   cv::Mat makeCanvas(std::vector<cv::Mat>& vecMat, int windowHeight, int nRows) {
           int N = vecMat.size();
           nRows  = nRows > N ? N : nRows;
           int edgeThickness = 10;
           int imagesPerRow = ceil(double(N) / nRows);
           int resizeHeight = floor(2.0 * ((floor(double(windowHeight - edgeThickness) / nRows)) / 2.0)) - edgeThickness;
           int maxRowLength = 0;

           std::vector<int> resizeWidth;
           for (int i = 0; i < N;) {
                   int thisRowLen = 0;
                   for (int k = 0; k < imagesPerRow; k++) {
                           double aspectRatio = double(vecMat[i].cols) / vecMat[i].rows;
                           int temp = int( ceil(resizeHeight * aspectRatio));
                           resizeWidth.push_back(temp);
                           thisRowLen += temp;
                           if (++i == N) break;
                   }
                   if ((thisRowLen + edgeThickness * (imagesPerRow + 1)) > maxRowLength) {
                           maxRowLength = thisRowLen + edgeThickness * (imagesPerRow + 1);
                   }
           }
           int windowWidth = maxRowLength;
           cv::Mat canvasImage(windowHeight, windowWidth, CV_8UC3, Scalar(0, 0, 0));

           for (int k = 0, i = 0; i < nRows; i++) {
                   int y = i * resizeHeight + (i + 1) * edgeThickness;
                   int x_end = edgeThickness;
                   for (int j = 0; j < imagesPerRow && k < N; k++, j++) {
                           int x = x_end;
                           cv::Rect roi(x, y, resizeWidth[k], resizeHeight);
                           cv::Size s = canvasImage(roi).size();
                           // change the number of channels to three
                           cv::Mat target_ROI(s, CV_8UC3);
                           if (vecMat[k].channels() != canvasImage.channels()) {
                               if (vecMat[k].channels() == 1) {
                                   cv::cvtColor(vecMat[k], target_ROI, COLOR_GRAY2BGR);
                               }
                           } else {
                               vecMat[k].copyTo(target_ROI);
                           }
                           cv::resize(target_ROI, target_ROI, s);
                           if (target_ROI.type() != canvasImage.type()) {
                               target_ROI.convertTo(target_ROI, canvasImage.type());
                           }
                           target_ROI.copyTo(canvasImage(roi));
                           x_end += resizeWidth[k] + edgeThickness;
                   }
           }
           return canvasImage;
   }

int main() {

Mat img1 = imread("/Sampleimages/1.jpg");
Mat img2 = imread("/Sampleimages/2.jpg");
Mat img3 = imread("/Sampleimages/3.jpg");
Mat img4 = imread("/Sampleimages/4.jpg");
Mat img5 = imread("/Sampleimages/5.jpg");
Mat img6 = imread("/Sampleimages/6.jpg");
Mat dst;
std::vector<cv::Mat> vecMat = {
            img1, img2, img3, img4, img5, img6
    };
makeCanvas(vecMat, 5000, 3);


return 0;


}
