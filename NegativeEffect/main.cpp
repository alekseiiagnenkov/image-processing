#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>
#include <memory>

    //rgb24, bgr24, rgb32, rgba32, arbg32, yuv, nv12

void modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height) {

	//[b00 g00 r00 b10 g10 r10 b20 g20 r20 b01 g01 r01 b11 g11 r11 b21 g21 r21]
	//[0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17 ]

	// x=0 b=0 g=1 r=2
	// x=1 b=3 g=4 r=5
	// x=2 b=6 g=7 r=8
	//b(x)=x*3 g(x)=x*3+1 r(x)=x*3+2
	//b(0,0)=0
	//b(0,1)=9
	//b(0,2)=18
	//b(y)=y*width*3

	//b(x,y)=x*3+y*width*3=[(x+y*width)*3];

	int size = width * height * 3;
	for (int i = 0; i < size; i ++) {
		outputImage[i] = 255 - inputImage[i];
	}
}


int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Specify file name" << std::endl;
		return -1;
	}

	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Original image", img);
	cv::Mat negativeSample = cv::Scalar(255, 255, 255) - img;
	cv::imshow("Negative", negativeSample);
	cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);
	modifyImage(img.data, modifiedImage.data, img.cols, img.rows);
	cv::imshow("Modified", modifiedImage);
	cv::waitKey(0);
	return 0;
}