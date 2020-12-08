#include <opencv2/opencv.hpp>
#include <iostream>

int index(int x, int y, int width) {
    return ((x + y * width) * 3);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Specify file name!" << std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(argv[1]);
    cv::imshow("Original image", image);
    cv::waitKey(0);
    cv::Mat modifiedImage(image.rows, image.cols, CV_8UC3);


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

    return 0;
}