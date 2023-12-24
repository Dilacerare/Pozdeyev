#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class laba_4
{
public:
	static const int B = 255;
	static const int M = 500;
	void perform();
	void MSICE(Mat&, Mat&);
	int out(Mat&, int, int, int);
	int S(Mat&, int, int, int);
	int get_A(int);
	uchar check_for_limit(int);
};
