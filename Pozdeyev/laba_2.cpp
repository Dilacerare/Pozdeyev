#include "laba_2.h"

void laba_2::perform() {
    Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/Cat_col.jpg");
    //Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/noise.jpg");
    //Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/plane.jpg");

    Mat grayscaleImage;
    cvtColor(image, grayscaleImage, COLOR_BGR2GRAY);

    Mat binaryImage;
    threshold(grayscaleImage, binaryImage, 128, 255, THRESH_BINARY);

    imshow("Исходное", image);
    imshow("Однотонное изображение", grayscaleImage);
    imshow("Бинарное изображение", binaryImage);
    waitKey(0);
    destroyAllWindows();

    int command;
    bool check = true;
    bool binShow;
    bool monoShow;
    int apertureSize;

    Mat binResult = binaryImage.clone();
    Mat monoResult = grayscaleImage.clone();
    //Mat result(image.rows, image.cols, CV_8UC1);


    while (check)
    {
        cout << "Select a filter:\n 1) Binary Erosion\n 2) Binary Dilation\n 3) Binary Closing\n 4) Binary Opening\n 5) Halftone Erosion\n 6) Halftone Dilation\n 7) Halftone Closing\n 8) Halftone Opening\n 9) Contour Selection\n 10) Multiscale Morphological Gradient\n 0) Exit\n";
        cin >> command;

        switch (command)
        {
        case 1:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            bin_erode(binaryImage, binResult, apertureSize);
            binShow = true;
            monoShow = false;
            break;
        case 2:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            bin_dilate(binaryImage, binResult, apertureSize);
            binShow = true;
            monoShow = false;
            break;
        case 3:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            close(binaryImage, binResult, apertureSize, true);
            binShow = true;
            monoShow = false;
            break;
        case 4:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            open(binaryImage, binResult, apertureSize, true);
            binShow = true;
            monoShow = false;
            break;
        case 5:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            mono_erode(grayscaleImage, monoResult, apertureSize);
            binShow = false;
            monoShow = true;
            break;
        case 6:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            mono_dilate(grayscaleImage, monoResult, apertureSize);
            binShow = false;
            monoShow = true;
            break;
        case 7:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            close(grayscaleImage, monoResult, apertureSize, false);
            binShow = false;
            monoShow = true;
            break;
        case 8:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            open(grayscaleImage, monoResult, apertureSize, false);
            binShow = false;
            monoShow = true;
            break;
        case 9:
            contour_selection(grayscaleImage, monoResult);
            binShow = false;
            monoShow = true;
            break;
        case 10:
            gradient(grayscaleImage, monoResult);
            binShow = false;
            monoShow = true;
            break;
        case 0:
            check = false;
            binShow = false;
            monoShow = false;
            break;
        default:
            cout << "Wrong command!\n Try aganin\n";
            binShow = false;
            monoShow = false;
            break;
        }

        if (binShow)
        {
            imshow("Original", binaryImage);
            imshow("Filtered", binResult);
            waitKey(0);
            destroyAllWindows();
            imwrite("C:/Users/aidar/Downloads/result.jpg", binResult);
        }
        if (monoShow)
        {
            imshow("Original", grayscaleImage);
            imshow("Filtered", monoResult);
            waitKey(0);
            destroyAllWindows();
            imwrite("C:/Users/aidar/Downloads/result.jpg", monoResult);
        }
    }
}

void laba_2::bin_erode(const Mat& input_img, Mat& output_img, int aperture_size)
{
    Mat kernel = Mat::ones(aperture_size, aperture_size, CV_8U);
    int imageHeight = input_img.rows;
    int imageWidth = input_img.cols;
    int kernelRadius = aperture_size / 2;

    for (int y = kernelRadius; y < imageHeight - kernelRadius; ++y) {
        for (int x = kernelRadius; x < imageWidth - kernelRadius; ++x) {

            bool erode = true;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {

                    if (kernel.at<uchar>(ky + kernelRadius, kx + kernelRadius) == 1 &&
                        input_img.at<uchar>(y + ky, x + kx) != 255) {
                        erode = false;
                        break;
                    }
                }
                if (!erode) break;
            }
            output_img.at<uchar>(y, x) = erode ? 255 : 0;
        }
    }
}

void laba_2::bin_dilate(const Mat& input_img, Mat& output_img, int aperture_size)
{
    Mat kernel = Mat::ones(aperture_size, aperture_size, CV_8U);
    int imageHeight = input_img.rows;
    int imageWidth = input_img.cols;
    int kernelRadius = aperture_size / 2;

    for (int y = kernelRadius; y < imageHeight - kernelRadius; ++y) {
        for (int x = kernelRadius; x < imageWidth - kernelRadius; ++x) {

            bool dilate = false;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {

                    if (kernel.at<uchar>(ky + kernelRadius, kx + kernelRadius) == 1 &&
                        input_img.at<uchar>(y + ky, x + kx) == 255) {
                        dilate = true;
                        break;
                    }
                }
                if (dilate) break;
            }
            output_img.at<uchar>(y, x) = dilate ? 255 : 0;
        }
    }
}

void laba_2::mono_erode(const Mat& input_img, Mat& output_img, int aperture_size)
{
    int imageHeight = input_img.rows;
    int imageWidth = input_img.cols;
    int kernelRadius = aperture_size / 2;

    for (int y = kernelRadius; y < imageHeight - kernelRadius; ++y) {
        for (int x = kernelRadius; x < imageWidth - kernelRadius; ++x) {
            float minIntensity = 255.0;
            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                    float intensity = input_img.at<uchar>(y + ky, x + kx);
                    if (intensity < minIntensity) {
                        minIntensity = intensity;
                    }
                }
            }
            output_img.at<uchar>(y, x) = static_cast<uchar>(minIntensity);
        }
    }
}

void laba_2::mono_dilate(const Mat& input_img, Mat& output_img, int aperture_size)
{
    int imageHeight = input_img.rows;
    int imageWidth = input_img.cols;
    int kernelRadius = aperture_size / 2;

    for (int y = kernelRadius; y < imageHeight - kernelRadius; ++y) {
        for (int x = kernelRadius; x < imageWidth - kernelRadius; ++x) {

            uchar maxPixelValue = 0;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {

                    uchar pixelValue = input_img.at<uchar>(y + ky, x + kx);
                    if (pixelValue > maxPixelValue) {
                        maxPixelValue = pixelValue;
                    }
                }
            }
            output_img.at<uchar>(y, x) = maxPixelValue;
        }
    }
}

void laba_2::close(const Mat& input_img, Mat& output_img, int aperture_size, bool isBin)
{
    Mat tempImage = output_img.clone();

    if (isBin)
    {
        bin_erode(input_img, tempImage, aperture_size);
        bin_dilate(tempImage, output_img, aperture_size);
    }
    else
    {
        mono_erode(input_img, tempImage, aperture_size);
        mono_dilate(tempImage, output_img, aperture_size);
    }
}

void laba_2::open(const Mat& input_img, Mat& output_img, int aperture_size, bool isBin)
{
    Mat tempImage = output_img.clone();

    if (isBin)
    {
        bin_dilate(input_img, tempImage, aperture_size);
        bin_erode(tempImage, output_img, aperture_size);
    }
    else
    {
        mono_dilate(input_img, tempImage, aperture_size);
        mono_erode(tempImage, output_img, aperture_size);
    }
}

void laba_2::contour_selection(const Mat& input_img, Mat& output_img) {

    Mat gradientX = cv::Mat::zeros(input_img.size(), CV_32F);
    Mat gradientY = cv::Mat::zeros(input_img.size(), CV_32F);

    int imageHeight = input_img.rows;
    int imageWidth = input_img.cols;

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            if (x > 0 && x < imageWidth - 1) {
                gradientX.at<float>(y, x) = static_cast<float>(input_img.at<uchar>(y, x + 1)) - static_cast<float>(input_img.at<uchar>(y, x - 1));
            }
            if (y > 0 && y < imageHeight - 1) {
                gradientY.at<float>(y, x) = static_cast<float>(input_img.at<uchar>(y + 1, x)) - static_cast<float>(input_img.at<uchar>(y - 1, x));
            }
        }
    }

    cv::Mat gradientMagnitude = cv::Mat::zeros(input_img.size(), CV_32F);
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            float gx = gradientX.at<float>(y, x);
            float gy = gradientY.at<float>(y, x);
            gradientMagnitude.at<float>(y, x) = sqrt(gx * gx + gy * gy);
        }
    }

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            output_img.at<uchar>(y, x) = static_cast<uchar>(gradientMagnitude.at<float>(y, x));
        }
    }
}

void laba_2::gradient(const Mat& input_img, Mat& output_img)
{
    output_img.zeros(input_img.size(), CV_8U);

    int kernelSizes[] = {1, 3, 5, 7 };
    int numKernels = sizeof(kernelSizes) / sizeof(int);

    Mat tempDilateImage = output_img.clone();
    Mat tempErodeImage = output_img.clone();
    Mat tempGradientImage = output_img.clone();

    for (int i = 1; i < numKernels; ++i)
    {
        mono_dilate(input_img, tempDilateImage, kernelSizes[i]);
        mono_erode(input_img, tempErodeImage, kernelSizes[i]);
        Mat gradient = tempDilateImage - tempErodeImage;
        close(gradient, tempGradientImage, kernelSizes[i - 1], false);
        output_img += tempGradientImage;
    }

    //output_img *= 1/3;
}