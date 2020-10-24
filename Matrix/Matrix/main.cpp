#include <opencv2/opencv.hpp>
#include <iostream>
#include "Editor.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Specify file name!" << std::endl;
		return -1;
	}

	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Original image", img);
	cv::waitKey(1);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);
	do {
		if (!modifyImage(img.data, modifiedImage.data, img.cols, img.rows))
			break;
		cv::imshow("Modified", modifiedImage);
		std::cout << "Press any key."<< std::endl;
		cv::waitKey(1);
	} while (1);
	return 0;
}