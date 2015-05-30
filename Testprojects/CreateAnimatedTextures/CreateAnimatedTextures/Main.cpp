#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

int main()
{
	const int numberOfImages = 30;
	const int numberOfDigits = 5;
	const std::string totalName = "AniTest/strike_";

	std::stringstream stream;
	stream << totalName << std::setfill('0') << setw(numberOfDigits) << 0 << ".png";

	cv::Mat imgFirst = cv::imread(stream.str(), -1);
	cv::Mat imgTotal(imgFirst.rows * 2, imgFirst.cols * (numberOfImages / 2), imgFirst.type());

	for (int i = 0; i < numberOfImages; i++)
	{
		stream.str("");
		stream.clear();

		stream << totalName << std::setfill('0') << setw(numberOfDigits) << i << ".png";
		std::string imgName = stream.str();

		cv::Mat imgCurrent = cv::imread(imgName, -1);

		int rowOffset = 0;
		int colNumber = i;
		if (i >= numberOfImages / 2)
		{
			rowOffset = imgFirst.rows;
			colNumber = i - numberOfImages / 2;
		}

		//Copy image
		for (int rows = 0; rows < imgCurrent.rows; rows++)
		{
			for (int cols = 0; cols < imgCurrent.cols; cols++)
			{
				for (int channel = 0; channel < 4; channel++)
				{
					imgTotal.at<Vec4b>(rows + rowOffset, cols + colNumber*imgFirst.cols)[channel] = imgCurrent.at<Vec4b>(rows, cols)[channel];
				}
			}
		}
	}

	cv::imwrite(totalName + ".png", imgTotal);
	std::cout << "Everything done" << std::endl;
 	return 0;
}
