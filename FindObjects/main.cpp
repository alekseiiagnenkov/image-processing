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

    cv::Mat img = cv::imread(argv[1]);
    cv::imshow("Original image", img);
    cv::waitKey(0);
    cv::Mat modifiedImage(img.rows, img.cols, CV_8UC3);


    int blue, green, red;
    std::cout << "Put color a object (blue[b] green[g] red[r]; (0 <= b,g,r <= 255)): bbb ggg rrr ---> ";
    std::cin >> blue >> green >> red;
    int blueMin = blue - 10, greenMin = green - 10, redMin = red - 10, blueMax = blue + 10, greenMax = green + 10, redMax = red + 10;
    std::vector<int> ourColorMin = {blueMin, greenMin, redMin};
    std::vector<int> ourColorMax = {blueMax, greenMax, redMax};
    std::vector<int> thisColor;
    int x1_flag = -1, y1_flag = -1, x2_flag = -1, y2_flag = -1, i;
    for (int y = 0; y < img.rows; y++)
        for (int x = 0; x < img.cols; x++) {
            int ind = index(x, y, img.cols);
            for (i = 0; i < 3; i++) {
                if ((img.data[ind] + i) < ourColorMin[i] || (img.data[ind] + i) > ourColorMax[i]) {
                    break;
                }
            }
            //если i=3, значит цвета похожи, если i<3, значит различны
            if (i == 3) {
                if (y1_flag == -1) {
                    y1_flag = y;
                    x1_flag = x;
                    x2_flag = x;
                } else
                    y2_flag = y;

                if (x1_flag > x)
                    x1_flag = x;
                if (x2_flag < x)
                    x2_flag = x;
            }
        }

    std::cout << "(x;y) = (" << y1_flag << ";" << x1_flag << ")" << std::endl;
    std::cout << "width = " << x2_flag - x1_flag << std::endl;
    std::cout << "height = " << y2_flag - y1_flag << std::endl;

    return 0;
}