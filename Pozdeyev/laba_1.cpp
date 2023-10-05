#include "laba_1.h"

void laba_1::perform()
{
    Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/Cat.jpg", IMREAD_GRAYSCALE);

    Mat DoG(image.rows, image.cols, CV_8SC1);
    Mat contour(image.rows, image.cols, CV_8UC1);
    Mat sobel = Mat::zeros(image.size(), CV_32F);

    Mat result(image.rows, image.cols, CV_8UC1);

    int command;
    bool check = true;
    bool show;
    int apertureSize;

    while (check)
    {
        cout << "Select a filter:\n 1) Gauss Bluray\n 2) Gauss Contour\n 3) Gauss Sharpness\n 4) Difference Of Gaussians\n 5) Canny\n 6) Sobel Contour\n 7) Mosaic\n 8) Aperture Correction\n 9) Median\n 0) Exit\n";
        cin >> command;

        switch (command)
        {
        case 1:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            gauss_bluray(image, result, apertureSize, 1.0);
            show = true;
            break;
        case 2:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            gauss_contour(image, result, apertureSize, 1.0);
            show = true;
            break;
        case 3:
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            gauss_sharpness(image, result, apertureSize, 1.0, 0.35);
            show = true;
            break;
        case 4:
            difference_of_gaussians(image, result);
            //result = DoG;
            show = true;
            break;
        case 5:
            Canny(image, result, 50, 200);
            show = true;
            break;
        case 6:
            sobel_contour(image, sobel);
            result = sobel;
            show = true;
            break;
        case 7:
            int blockSize;
            cout << "Enter mosaic block size: ";
            cin >> blockSize;
            mosaic_filter(image, result, blockSize);
            show = true;
            break;
        case 8:
            float correctionFactor;
            cout << "Enter aperture size: ";
            cin >> apertureSize;
            cout << "Enter correction factor: ";
            cin >> correctionFactor;
            aperture_correction_filter(image, result, apertureSize, correctionFactor);
            show = true;
            break;
        case 9:
            cout << "Enter median filter aperture size: ";
            cin >> apertureSize;
            median_filter(image, result, apertureSize);
            show = true;
            break;
        case 0:
            check = false;
            show = false;
            break;
        default:
            cout << "Wrong command!\n Try aganin\n";
            show = false;
            break;
        }

        if (show)
        {
            imshow("Original", image);
            imshow("Filtered", result);
            waitKey(0);
            destroyAllWindows();
            imwrite("C:/Users/aidar/Downloads/result.jpg", result);
        }
    }
}

void laba_1::gauss_kernel(Mat& kernel, int aperture_size, float sigma)
{
    float sum = 0.0;
    for (int i = 0; i < aperture_size; i++) {
        for (int j = 0; j < aperture_size; j++) {
            float x = i - aperture_size / 2.0;
            float y = j - aperture_size / 2.0;
            kernel.at<float>(i, j) = exp(-(x * x + y * y) / (2 * sigma * sigma));
            sum += kernel.at<float>(i, j);
        }
    }
    kernel /= sum;
}

void laba_1::gauss_bluray(const Mat& input_img, Mat& output_img, int aperture_size, float sigma)
{
    Mat kernel(aperture_size, aperture_size, CV_32F);
    gauss_kernel(kernel, aperture_size, sigma);

    for (int i = aperture_size / 2; i < input_img.rows - aperture_size / 2; i++) {
        for (int j = aperture_size / 2; j < input_img.cols - aperture_size / 2; j++) {

            float sum = 0.0;

            for (int x = -aperture_size / 2; x <= aperture_size / 2; x++) {
                for (int y = -aperture_size / 2; y <= aperture_size / 2; y++) {
                    sum += kernel.at<float>(x + aperture_size / 2, y + aperture_size / 2) * input_img.at<uchar>(i + x, j + y);
                }
            }

            output_img.at<uchar>(i, j) = sum;
        }
    }
}

void laba_1::gauss_contour(const Mat& input_img, Mat& output_img, int aperture_size, float sigma)
{
    Mat kernel(aperture_size, aperture_size, CV_32F);
    gauss_kernel(kernel, aperture_size, sigma);

    for (int i = aperture_size / 2; i < input_img.rows - aperture_size / 2; i++) {
        for (int j = aperture_size / 2; j < input_img.cols - aperture_size / 2; j++) {

            float sum_x = 0.0;
            float sum_y = 0.0;

            for (int x = -aperture_size / 2; x <= aperture_size / 2; x++) {
                for (int y = -aperture_size / 2; y <= aperture_size / 2; y++) {
                    sum_x += kernel.at<float>(x + aperture_size / 2, y + aperture_size / 2) * input_img.at<uchar>(i + x, j + y) * x;
                    sum_y += kernel.at<float>(x + aperture_size / 2, y + aperture_size / 2) * input_img.at<uchar>(i + x, j + y) * y;
                }
            }

            output_img.at<uchar>(i, j) = sqrt(sum_x * sum_x + sum_y * sum_y);
        }
    }
}

void laba_1::gauss_sharpness(const Mat& input_img, Mat& output_img, int aperture_size, float sigma, float amount)
{
    Mat kernel(aperture_size, aperture_size, CV_32F);
    gauss_kernel(kernel, aperture_size, sigma);

    for (int i = aperture_size / 2; i < input_img.rows - aperture_size / 2; i++) {
        for (int j = aperture_size / 2; j < input_img.cols - aperture_size / 2; j++) {

            float sum_x = 0.0;
            float sum_y = 0.0;

            for (int x = -aperture_size / 2; x <= aperture_size / 2; x++) {
                for (int y = -aperture_size / 2; y <= aperture_size / 2; y++) {
                    sum_x += kernel.at<float>(x + aperture_size / 2, y + aperture_size / 2) * input_img.at<uchar>(i + x, j + y) * x;
                    sum_y += kernel.at<float>(x + aperture_size / 2, y + aperture_size / 2) * input_img.at<uchar>(i + x, j + y) * y;
                }
            }

            float val = sqrt(sum_x * sum_x + sum_y * sum_y);

            int k = input_img.at<uchar>(i, j);
            int temp = k + amount * (k - val);
            if (temp > 255)
            {
                output_img.at<uchar>(i, j) = 255;
                continue;
            }
            if (temp < 0)
            {
                output_img.at<uchar>(i, j) = 0;
                continue;
            }

            output_img.at<uchar>(i, j) = input_img.at<uchar>(i, j) + amount * (input_img.at<uchar>(i, j) - val);
        }
    }
}

void laba_1::difference_of_gaussians(const Mat& input_img, Mat& output_img)
{
    Mat blurred_image3x3(input_img.rows, input_img.cols, CV_8UC1);
    Mat blurred_image5x5(input_img.rows, input_img.cols, CV_8UC1);

    gauss_bluray(input_img, blurred_image3x3, 3, 1.0);
    gauss_bluray(input_img, blurred_image5x5, 5, 3.0);

    for (int i = 0; i < input_img.rows; i++)
    {
        for (int j = 0; j < input_img.cols; j++)
        {
            int diff = blurred_image5x5.at<uchar>(i, j) - blurred_image3x3.at<uchar>(i, j);
            output_img.at<uchar>(i, j) = abs(diff);
        }
    }
}

void laba_1::sobel_contour(const Mat& input_img, Mat& output_img)
{
    Mat sobel_abs;
    float sobel_kernel[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };

    for (int i = 1; i < input_img.rows - 1; i++) {
        for (int j = 1; j < input_img.cols - 1; j++) {
            float pixel = 0.0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    pixel += input_img.at<uchar>(i + k, j + l) * sobel_kernel[k + 1][l + 1];
                }
            }
            output_img.at<float>(i, j) = pixel;
        }
    }
    convertScaleAbs(output_img, sobel_abs);
    sobel_abs.convertTo(output_img, CV_8U);
}

void laba_1::mosaic_filter(const Mat& input_img, Mat& output_img, int blockSize)
{
    for (int i = 0; i < input_img.rows; i += blockSize) {
        for (int j = 0; j < input_img.cols; j += blockSize) {
            int sum = 0;
            int count = 0;
            for (int x = 0; x < blockSize; x++) {
                for (int y = 0; y < blockSize; y++) {
                    int row = i + x;
                    int col = j + y;
                    if (row < input_img.rows && col < input_img.cols) {
                        sum += input_img.at<uchar>(row, col);
                        count++;
                    }
                }
            }
            int average = count > 0 ? sum / count : 0;
            for (int x = 0; x < blockSize; x++) {
                for (int y = 0; y < blockSize; y++) {
                    int row = i + x;
                    int col = j + y;
                    if (row < input_img.rows && col < input_img.cols) {
                        output_img.at<uchar>(row, col) = static_cast<uchar>(average);
                    }
                }
            }
        }
    }
}

void laba_1::aperture_correction_filter(const Mat& input_img, Mat& output_img, int aperture_size, float correction_factor)
{
    for (int i = aperture_size / 2; i < input_img.rows - aperture_size / 2; i++) {
        for (int j = aperture_size / 2; j < input_img.cols - aperture_size / 2; j++) {

            float sum = 0.0;

            for (int x = -aperture_size / 2; x <= aperture_size / 2; x++) {
                for (int y = -aperture_size / 2; y <= aperture_size / 2; y++) {
                    sum += input_img.at<uchar>(i + x, j + y);
                }
            }

            float average = sum / (aperture_size * aperture_size);

            output_img.at<uchar>(i, j) = static_cast<uchar>(average * correction_factor);
        }
    }
}

void laba_1::median_filter(const Mat& input_img, Mat& output_img, int aperture_size)
{
    vector<uchar> pixelValues;
    for (int i = aperture_size / 2; i < input_img.rows - aperture_size / 2; i++) {
        for (int j = aperture_size / 2; j < input_img.cols - aperture_size / 2; j++) {
            pixelValues.clear();

            for (int x = -aperture_size / 2; x <= aperture_size / 2; x++) {
                for (int y = -aperture_size / 2; y <= aperture_size / 2; y++) {
                    pixelValues.push_back(input_img.at<uchar>(i + x, j + y));
                }
            }

            sort(pixelValues.begin(), pixelValues.end());

            int medianIndex = pixelValues.size() / 2;
            uchar medianValue = pixelValues[medianIndex];

            output_img.at<uchar>(i, j) = medianValue;
        }
    }
}