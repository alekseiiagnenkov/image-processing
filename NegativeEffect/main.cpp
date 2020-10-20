#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdint>

void modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height) {

}


int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Укажите имя изображения" << std::endl;
		return -1;
	}
	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Оригинальное изображение", img);
	cv::Mat negativeSample = cv::Scalar(255,255,255) - img;
	cv::imshow("Негатив", negativeSample);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);
	modifyImage(img.data, modifiedImage.data, img.cols, img.rows);
	cv::imshow("Измененное", modifiedImage);
	cv::waitKey(0);
}