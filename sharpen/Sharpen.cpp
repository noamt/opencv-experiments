#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat& sharpenManually(Mat& originalImage, Mat& result);
Mat& sharpenWithCv(Mat& originalImage, Mat& result);

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("This tool requires an image path paramter\n");
        return -1;
    }

    char* imagePath = argv[1];
   
    Mat randomMat = Mat(4, 4, CV_8UC3);
    randu(randomMat, Scalar::all(0), Scalar::all(255));
    
    Mat result;
    sharpenManually(randomMat, result);
 
    Mat originalImage;
    originalImage = imread(imagePath, 1);

    if (!originalImage.data) {
        printf("No image data could be found in the given file\n");
        return -1;
    }
    
    sharpenWithCv(originalImage, result);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", result);    
    waitKey(0);
    
    return 0;
}

Mat& sharpenManually(Mat& originalImage, Mat& result) {
   cout << "Starting with = " << endl << " " << originalImage << endl << endl;
   
   CV_Assert(originalImage.depth() == CV_8U);
   
   result.create(originalImage.size(), originalImage.type());
   const int channels = originalImage.channels();

   cout << "Number of channels is " << channels << endl;
   
   for(int row = 1; row < (originalImage.rows -1); ++row) {

       cout << "Previous row is " << (row - 1) << endl;
       cout << "Current row is " << (row) << endl;
       cout << "Next row is " << (row + 1) << endl;

       const uchar* previousRow = originalImage.ptr<uchar>(row - 1);
       const uchar* currentRow = originalImage.ptr<uchar>(row);
       const uchar* nextRow = originalImage.ptr<uchar>(row + 1);

       uchar* outputRow = result.ptr<uchar>(row);
         
       for(int column = channels; column < (channels * (originalImage.cols -1)); ++column) {
           printf("5 * currentRow[column] = %u, currentRow[column - channels] = %u, currentRow[column + channels] = %u, previousRow[column] = %u, nextRow[column] = %u",
                  static_cast<unsigned>(5 * currentRow[column]), static_cast<unsigned>(currentRow[column - channels]),
                  static_cast<unsigned>(currentRow[column + channels]), static_cast<unsigned>(previousRow[column], nextRow[column]));
           *outputRow++ = saturate_cast<uchar>(5 * currentRow[column] - currentRow[column - channels] - currentRow[column + channels] - previousRow[column] - nextRow[column]);
            cout << "Now we're at = " << endl << " " << result << endl << endl;
       }
   }

   result.row(0).setTo(Scalar(0));
   result.row(result.rows - 1).setTo(Scalar(0));
   result.col(0).setTo(Scalar(0));
   result.col(result.cols - 1).setTo(Scalar(0));
}

Mat& sharpenWithCv(Mat& originalImage, Mat& result) {
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
                                      -1, 5, -1,
                                      0, -1, 0);
    filter2D(originalImage, result, originalImage.depth(), kernel);
}
