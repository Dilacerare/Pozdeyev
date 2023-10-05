#include <opencv2/opencv.hpp> 
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

class laba_2
{
public:
	void perform();
private:
	void bin_erode(const Mat&, Mat&, int);
	void bin_dilate(const Mat&, Mat&, int);
	void mono_erode(const Mat&, Mat&, int);
	void mono_dilate(const Mat&, Mat&, int);
	void close(const Mat&, Mat&, int, bool);
	void open(const Mat&, Mat&, int, bool);
	void contour_selection(const Mat&, Mat&);
	void gradient(const Mat&, Mat&);
};

