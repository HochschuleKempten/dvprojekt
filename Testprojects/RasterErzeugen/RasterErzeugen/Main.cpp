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
	cv::Point2f pt(len / 2., len / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

	cv::warpAffine(src, dst, r, cv::Size(len, len));
}

int main()
{
	string name = "LuftaufnahmeBumpLight";
	Mat img = imread(name + string(".jpg"));

	int rasterSize = 6;
	int height = img.rows / rasterSize;
	int width = img.cols / rasterSize;

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
			Mat rotMat = (Mat_<float>(2, 2) << 0, 1,
											   1, 0);
			rotateCenter(field, 180, field);	//CGeoCube needs to be rotated by 180°
			//Mat erg = rotMat * field;
			imwrite(name + to_string(rowIdx) + string("_") + to_string(colIdx) + string(".jpg"), field);
		}
	}

	std::cout << "Everything done" << std::endl;
}
