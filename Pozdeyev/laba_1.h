#include <opencv2/opencv.hpp> 
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

class laba_1
{
public:
	void perform();
private:
	void gauss_kernel(Mat&, int, float);
	void gauss_bluray(const Mat&, Mat&, int, float);
	void gauss_contour(const Mat&, Mat&, int, float);
	void gauss_sharpness(const Mat&, Mat&, int, float, float);
	void difference_of_gaussians(const Mat&, Mat&);
	void sobel_contour(const Mat&, Mat&);
	void mosaic_filter(const Mat&, Mat&, int);
	void aperture_correction_filter(const Mat&, Mat&);
	void median_filter(const Mat&, Mat&, int);
};


