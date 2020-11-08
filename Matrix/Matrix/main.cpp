#include <opencv2/opencv.hpp>
#include <iostream>
#include "Editor.h"
#include <fstream>

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Specify file name!" << std::endl;
		return -1;
	}

	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Original image", img);
	cv::waitKey(1);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);

	std::vector<Matrix*> Arr;
	Arr = load(Arr);
	Matrix* M;

	do {
		if (!(M = modifyImage(img.data, modifiedImage.data, img.cols, img.rows, Arr)))
			break;
		cv::imshow("Modified", modifiedImage);
		cv::waitKey(1);

		if (M->name.size() == 0) {
				Arr = addMatrix(Arr, M);
		}
	} while (1);

	save(Arr);

	//for (int i = 0; i < ARR.size(); i++) {
	//	delete[] ARR[i]->arr1;
	//	delete[] ARR[i]->arr2;
	//	delete ARR[i];
	//}

	return 0;
}