#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat& reduceColor(Mat& originalImage, const uchar* const table);

int main(int argc, char** argv) {

    if (argc != 3) {
        printf("This tool requires an image path and divider parameter\n");
        return -1;
    }

    char* imagePath = argv[1];
    
    Mat originalImage;
    originalImage = imread(imagePath, 1);

    if (!originalImage.data) {
        printf("No image data could be found in the given file\n");
        return -1;
    }

    int divider = 0;
    std::stringstream rawDivider;
    rawDivider << argv[2];
    rawDivider >> divider;

    if (!rawDivider || !divider) {
        printf("Bad divider parameter was provided\n");
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; ++i) {
        table[i] = (uchar)(divider * (i/divider));
    }

    Mat modifiedImage = reduceColor(originalImage, table);
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", modifiedImage);    
    waitKey(0);
    
    return 0;
}

Mat& reduceColor(Mat& originalImage, const uchar* const table) {
    CV_Assert(originalImage.depth() == CV_8U);
    
    int channels = originalImage.channels();
    
    int rows = originalImage.rows;
    int columns = originalImage.cols * channels;
    
    if (originalImage.isContinuous()) {
        columns *= rows;
        rows = 1;
    }
    
    int rowIndex, columnIndex;
    uchar* rowPointer;
    
    for (rowIndex = 0; rowIndex < rows; ++rowIndex) {
        rowPointer = originalImage.ptr<uchar>(rowIndex);
        
        for (columnIndex = 0; columnIndex < columns; ++columnIndex) {
            rowPointer[columnIndex] = table[rowPointer[columnIndex]];
        }
    }
    return originalImage;
}

