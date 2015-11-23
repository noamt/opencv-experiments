#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    double alpha = 0.5;
    double beta;
    double input;

    if (argc != 3) {
        printf("This tool requires to image paths\n");
        return -1;
    }

    char* imagePath1 = argv[1];
    Mat src1 = imread(imagePath1, 1);

    if (!src1.data) {
        printf("No image data could be found in the first given file\n");
        return -1;
    }

    char* imagePath2 = argv[2];
    Mat src2 = imread(imagePath2, 1);

    if (!src2.data) {
        printf("No image data could be found in the second given file\n");
        return -1;
    }

    cout << "Linear Blender Example" << endl;
    cout << "Please provide an alpha [0-1]" << endl;
    cin >> input;

    if (input >= 0.0 && input <= 1.0) {
        alpha = input;
    }

    namedWindow("Linear Blend", WINDOW_AUTOSIZE);
    beta = 1.0 - alpha;

    Mat result;

    addWeighted(src1, alpha, src2, beta, 0.0, result);

    imshow("Linear Blend", result);
    waitKey(0);

    return 0;
}
