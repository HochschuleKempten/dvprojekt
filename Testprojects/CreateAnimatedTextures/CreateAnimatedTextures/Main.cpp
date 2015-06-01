#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <iomanip>

int printUsuage()
{
	static int errorNumber = -1;

	std::cout << "CreateAnimatedTextures <path_before_numbers> <number_of_images>" << std::endl
		      << "For example CreateAnimatedTextures strike\\strike_ 30" << std::endl
			  << "Please note that only png images are supported" << std::endl;

	return errorNumber--;
}

int main(const int argc, const char** argv)
{
	std::cout << "This is CreateAnimatedTextures v1.0" << std::endl;

	//argc = 3;
	//char argv[3][20] = { "ASD", "strike\\strike_", "30" };

	if (argc != 3)
	{
		std::cerr << "Wrong number of arguments." << std::endl;
		return printUsuage();
	}

	const std::string totalName(argv[1]);
	const int numberOfImages = std::atoi(argv[2]);
	const int numberOfDigits = static_cast<int>(std::ceil(std::log10(numberOfImages)));

	if (numberOfImages % 2 != 0)
	{
		std::cerr << "The number of images is not divisible by 2, but this is required " << std::endl;
		return printUsuage();
	}

	if (numberOfDigits <= 0)
	{
		std::cerr << numberOfImages << " is a invalid number of images " << std::endl;
		return printUsuage();
	}

	std::stringstream stream;
	stream << totalName << std::setfill('0') << std::setw(numberOfDigits) << 0 << ".png";

	//Read the first image to get the total size and the right type
	const cv::Mat imgFirst = cv::imread(stream.str(), -1);
	if (imgFirst.empty())
	{
		std::cerr << "Can't read the first image. Please check if the file " << stream.str() << " really exists" << std::endl;
		return printUsuage();
	}

	cv::Mat imgTotal(imgFirst.rows * 2, imgFirst.cols * (numberOfImages / 2), imgFirst.type());

	for (int i = 0; i < numberOfImages; i++)
	{
		stream.str("");
		stream.clear();

		stream << totalName << std::setfill('0') << std::setw(numberOfDigits) << i << ".png";
		std::string imgName = stream.str();

		const cv::Mat imgCurrent = cv::imread(imgName, -1);
		if (imgCurrent.empty())
		{
			std::cerr << "Can't read the current image. Please check if the file " << stream.str() << " really exists" << std::endl;
			return printUsuage();
		}

		if (imgCurrent.size != imgFirst.size || imgCurrent.type() != imgFirst.type())
		{
			std::cerr << "The current image " << imgName << " has a different size or type as previous images" << std::endl;
			return printUsuage();
		}

		int rowOffset = 0;
		int colNumber = i;
		if (i >= numberOfImages / 2)
		{
			rowOffset = imgFirst.rows;
			colNumber = i - numberOfImages / 2;
		}

		//Copy image
		cv::Rect roi(cv::Point(colNumber*imgFirst.cols, rowOffset), cv::Size(imgCurrent.cols, imgCurrent.rows));
		cv::Mat imgTotalROI = imgTotal(roi);
		imgCurrent.copyTo(imgTotalROI);
	}

	std::cout << "Writing image... " << std::boolalpha << cv::imwrite(totalName + ".png", imgTotal) << std::endl
		      << "Everything done" << std::endl;
 	return 0;
}
