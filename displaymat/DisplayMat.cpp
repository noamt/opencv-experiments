#include<stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main (int argc, char** argv) {

    Mat eyeMat = Mat::eye(256, 256, CV_8UC3);
    cout << "E = " << endl << " " << eyeMat << endl << endl;

    Mat customMat = Mat(256, 256, CV_8UC3, Scalar(255, 0, 0));

    namedWindow("Custom Mat" , WINDOW_AUTOSIZE);
    imshow("Custom Mat", customMat);

    Mat randomMat = Mat(256, 256, CV_8UC3);
    randu(randomMat, Scalar::all(0), Scalar::all(255));

    namedWindow("Random Mat" , WINDOW_AUTOSIZE);
    imshow("Random Mat", randomMat);

    waitKey(0);
    return 0;
}
