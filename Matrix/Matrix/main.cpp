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
	cv::waitKey(0);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);

	std::vector<Matrix> Arr;
	Arr = load(Arr);

    do {
	Matrix M= modifyImage(img.data, modifiedImage.data, img.cols, img.rows, Arr);

		if (M.arr1.size()==0)
			break;
		cv::imshow("Modified", modifiedImage);
		cv::waitKey(0);

		if (M.name.size() == 0) {
				Arr = addMatrix(Arr, M);
		}
	} while (1);

	save(Arr);

	return 0;
}