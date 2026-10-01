#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("../src/lenna.bmp");

    if (image.empty())
    {
        cout << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    Mat binary;
    threshold(gray, binary, 127, 255, THRESH_BINARY);

    imshow("Original", image);
    imshow("Gray", gray);
    imshow("Binary", binary);

    waitKey(0);

    return 0;
}
