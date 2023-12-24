#include "laba_3.h"

using namespace cv;
using namespace std;

void laba_3::perform() {
	//Загрузка изображений с диска
	Mat img1 = imread("./Sampels/ponarama1.jpg");
	Mat img2 = imread("./Sampels/ponarama2.jpg");
	resize(img1, img1, Size(), 0.5, 0.5);
	resize(img2, img2, Size(), 0.5, 0.5);
	//Инициализация детектора, подготовка контейнеров для характерных точек и их дескрипторов
	Ptr<ORB> detector = ORB::create();
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;
	//Поиск характерных точек на сшиваемых изображениях и вычисление их дескрипторов
	detector->detect(img1, keypoints1);
	detector->detect(img2, keypoints2);
	detector->compute(img1, keypoints1, descriptor1);
	detector->compute(img2, keypoints2, descriptor2);
	//Отрисовка найденных характерных точек
	Mat keypoints1draw, keypoints2draw;
	drawKeypoints(img1, keypoints1, keypoints1draw);
	drawKeypoints(img2, keypoints2, keypoints2draw);
	imshow("keypoints1draw", keypoints1draw);
	imshow("keypoints2draw", keypoints2draw);
	waitKey();
	destroyAllWindows();

	BFMatcher matcher(NORM_HAMMING);
	vector<vector<DMatch>> matches;
	matcher.knnMatch(descriptor1, descriptor2, matches, 2);
	vector<KeyPoint> matched1, matched2;

	vector<DMatch> good_matches;

	float match_ratio = 0.5f;
	for (size_t i = 0; i < matches.size(); i++) 
	{
		DMatch first = matches[i][0];
		float dist1 = matches[i][0].distance;
		float dist2 = matches[i][1].distance;

		if (dist1 < match_ratio * dist2) 
		{
			int new_i = static_cast<int>(matched1.size());
			matched1.push_back(keypoints1[first.queryIdx]);
			matched2.push_back(keypoints2[first.trainIdx]);
			good_matches.push_back(DMatch(new_i, new_i, 0));
		}
	}
	Mat dMatches;
	drawMatches(img1, matched1, img2, matched2, good_matches, dMatches);
	imshow("Matches", dMatches);
	waitKey();
	destroyAllWindows();

	vector<Point2f> points1, points2;
	for (size_t i = 0; i < good_matches.size(); i++) {
		points1.push_back(matched1[good_matches[i].queryIdx].pt);
		points2.push_back(matched2[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(points2, points1, RANSAC);
	cout << "Матрица гомографии H:" << endl;
	cout << H << endl;

	// Размеры изображений
	Size img1_size = img1.size();
	Size img2_size = img2.size();

	// Создание изображения панорамы
	Mat panorama;

	cout << img2.size() << endl;
	cout << panorama.size() << endl;

	// Преобразование второго изображения на основе найденной матрицы гомографии
	warpPerspective(img2, panorama, H, Size(img1_size.width + img2_size.width - 360, img2_size.height));
	imshow("Panorama", panorama);
	waitKey();
	destroyAllWindows();
	Mat half(panorama, Rect(0, 0, img1.cols, img1.rows));
	img1.copyTo(half);

	// Отображение и сохранение панорамного изображения
	imshow("Panorama", panorama);
	waitKey();
	destroyAllWindows();
}