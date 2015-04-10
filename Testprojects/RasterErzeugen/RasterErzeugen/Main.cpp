#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/**
 * Rotate an image
 */
void rotateCenter(cv::Mat& src, double angle, cv::Mat& dst)
{
	int len = std::max(src.cols, src.rows);
	cv::Point2f pt(len / 2. - 0.5, len / 2. - 0.5);
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

	cv::warpAffine(src, dst, r, cv::Size(len, len));
}

int main()
{
	//Settings
	string name = "LuftaufnahmeDiffuse";
	int rasterSize = 10;

	Mat img = imread(name + string(".jpg"));
	int height = img.rows / rasterSize;
	int width = img.cols / rasterSize;

	if (height != width) {
		cout << "The image needs to have an aspect ratio of 1:1, abort" << endl;
		return -1;
	}

	for (int rowIdx = 0; rowIdx < rasterSize; rowIdx++) {
		for (int colIdx = 0; colIdx < rasterSize; colIdx++) {
			/*
			 * #--------> x
			 * |
			 * |
			 * |
			 * y
			 */
			Mat field = img(Rect(colIdx * height, rowIdx * width, width, height)).clone();

			//CGeoCube needs to be rotated by 180°
			//rotateCenter(field, 180, field);
			flip(field, field, -1);

			imwrite(name + to_string(rowIdx) + string("_") + to_string(colIdx) + string(".jpg"), field);
		}
	}

	cout << "Everything done" << endl;
}
