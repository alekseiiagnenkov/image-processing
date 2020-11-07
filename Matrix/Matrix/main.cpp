#include <opencv2/opencv.hpp>
#include <iostream>
#include "Editor.h"
#include "fstream"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Specify file name!" << std::endl;
		return -1;
	}

	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Original image", img);
	cv::waitKey(1);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);

	std::vector<Matrix*> ARR;
	ARR = LOAD(ARR);
	Matrix* M; 

	do {
		if (!(M = modifyImage(img.data, modifiedImage.data, img.cols, img.rows, ARR)))
			break;
		cv::imshow("Modified", modifiedImage);
		cv::waitKey(1);


		int i = 0;
		for (i = 0; i < ARR.size(); i++) {
			if (ARR[i]->name == M->name) {
				i = -1;
				break;
			}
		}
		if (i != -1)
			ARR = addMatrix(ARR, M);


	} while (1);

	SAVE(ARR);

	return 0;
}