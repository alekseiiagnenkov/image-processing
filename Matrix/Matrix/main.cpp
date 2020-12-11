#include <opencv2/opencv.hpp>
#include <iostream>
#include "Editor.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Specify file name!" << std::endl;
		return -1;
	}

	cv::Mat image = cv::imread(argv[1]);
	cv::imshow("Original image", image);
	cv::waitKey(0);
	cv::Mat modifiedImage(image.rows, image.cols, CV_8UC3);

	std::vector<Matrix> Arr;
	Arr = load(Arr);

    do {
        srand(time(0));
        float noise = 0.1;
        int sizeImg = image.cols * image.rows;
        for (int i = 0; i < sizeImg * noise; i++) {
            int size = rand() % 4;
            int x=rand() % image.cols, y=rand() % image.rows;
            for (int j = 0; j < size; j++)
                image.data[index(x,y, image.cols) + j] = rand() % 256;
        }
        cv::imshow("Modified", image);
        cv::waitKey(0);

	Matrix M= modify_image(image.data, modifiedImage.data, image.cols, image.rows, Arr);

		if (M.arr1.size()==0)
			break;
		cv::imshow("Modified", modifiedImage);
		cv::waitKey(0);

		if (M.name.size() == 0) {
				Arr = add_matrix(Arr, M);
		}
	} while (1);

	save(Arr);

	return 0;
}