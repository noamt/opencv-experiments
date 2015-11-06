#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv) {

    if (argc != 2) {
        printf("This tool requires an image path parameter\n");
        return -1;
    }

    char* imagePath = argv[1];
    
    Mat originalImage;
    originalImage = imread(imagePath, 1);

    if (!originalImage.data) {
        printf("No image data could be found in the given file\n");
        return -1;
    }

    Mat grayImage;
    cvtColor(originalImage, grayImage, CV_BGR2GRAY);
    
    namedWindow(imagePath, CV_WINDOW_AUTOSIZE);
    namedWindow("Gray Version", CV_WINDOW_AUTOSIZE);

    imshow(imagePath, originalImage);
    imshow("Gray Version", grayImage);

    waitKey(0);

    return 0;
}
