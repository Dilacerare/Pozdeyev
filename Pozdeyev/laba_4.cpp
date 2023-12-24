#include "laba_4.h"

using namespace cv;
using namespace std;

void laba_4::perform() {
	//Загрузка изображений с диска
	//Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/Cat_col.jpg");
	Mat image = imread("D:/My files/Codes/C++/Pozdeyev/Pozdeyev/Sampels/test2.jpg");

    Mat channels[3];
    split(image, channels);

	imshow("Origin", image);
	waitKey();
	destroyAllWindows();

    Mat channelResult = channels[1].clone();

    MSICE(channels[1], channelResult);

    channels[1] = channelResult;

    //Ptr<CLAHE> clahe = createCLAHE(50, Size(8, 8));
    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(4);

    Mat processed_channels[3];
    for (int i = 0; i < 3; ++i) {
        clahe->apply(channels[i], processed_channels[i]);
    }

    Mat processed_image1;
    merge(channels, 3, processed_image1);

    imshow("Processed Image", processed_image1);
    waitKey(0);
    destroyAllWindows();

    Mat processed_image;
    merge(processed_channels, 3, processed_image);

    imshow("Processed Image", processed_image);
    waitKey(0);
    destroyAllWindows();
}

void laba_4::MSICE(Mat& imput_chan, Mat& output_chan)
{
    int result;

    int dK_1 = (imput_chan.rows * imput_chan.cols) / 7085;
    int dK_2 = dK_1 / 2;
    int dK_3 = dK_2 / 2;

    for (int i = 0; i < imput_chan.rows; i++)
    {
        for (int j = 0; j < imput_chan.cols; j++)
        {
            result = out(imput_chan, i, j, dK_1) + out(imput_chan, i, j, dK_2) + out(imput_chan, i, j, dK_3);
            result = result / 3;
            output_chan.at<uchar>(i, j) = check_for_limit(result);
        }
    }
}

int laba_4::out(Mat& imput_chan, int i, int j, int dK)
{
    int result;

    int y = imput_chan.at<uchar>(i, j);
    int s = S(imput_chan, i, j, dK);

    if (y >= s)
        result = ((B + get_A(y - s)) * y) / (get_A(y - s) + y);
    else
        result = (get_A(y - s) * y) / (get_A(s - y) + B - y);

    //return check_for_limit(result);
    return result;
}

int laba_4::S(Mat& imput_chan, int i, int j, int dK)
{
    int result = 0;

    int x_start = 0, y_start = 0;
    int x_end = imput_chan.cols, y_end = imput_chan.rows;

    if (j - dK >= 0)
        x_start = j - dK;

    if (i - dK >= 0)
        y_start = i - dK;

    if (j + dK <= imput_chan.cols)
        x_end = j + dK;

    if (i + dK <= imput_chan.rows)
        y_end = i + dK;

    for (int y = y_start; y < y_end; y++)
    {
        for (int x = x_start; x < x_end; x++)
        {
            result += imput_chan.at<uchar>(y, x);
        }
    }

    result = result / ((2 * dK + 1) * (2 * dK + 1));

    //return check_for_limit(result);
    return result;
}

int laba_4::get_A(int x)
{
    if (1 <= x and x <= B)
    {
        return M / x;
    }
    else
    {
        return M;
    }
}

uchar laba_4::check_for_limit(int x)
{
    if (x > 255)
    {
        return 255;
    }
    else
    {
        if (x < 0)
        {
            return 0;
        }
        else
        {
            return x;
        }
    }
}