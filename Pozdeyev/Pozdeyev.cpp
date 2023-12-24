#include <opencv2/opencv.hpp> 
#include <cmath>
#include <iostream>
#include "laba_1.h"
#include "laba_2.h"
#include "laba_3.h"
#include "laba_4.h"

using namespace cv; 
using namespace std;


int main() { 
    laba_1 laba1;
    laba_2 laba2;
    laba_3 laba3;
    laba_4 laba4;

    //laba1.perform();

    //laba2.perform();
    
    //laba3.perform();
    
    laba4.perform();

    if (false)
    {
        Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/Cat_col.jpg");

        Mat grayscaleImage;
        cvtColor(image, grayscaleImage, COLOR_BGR2GRAY);

        Mat binaryImage;
        threshold(grayscaleImage, binaryImage, 128, 255, THRESH_BINARY);

        imshow("Исходное", image);
        imshow("Однотонное изображение", grayscaleImage);
        imshow("Бинарное изображение", binaryImage);
        waitKey(0);
        destroyAllWindows();

        Mat result = grayscaleImage.clone();

        Canny(image, result, 0, 255);

        imshow("Исходное", binaryImage);
        imshow("Бинарное изображение", result);
        waitKey(0);
        destroyAllWindows();
    }

    return 0; 
} 