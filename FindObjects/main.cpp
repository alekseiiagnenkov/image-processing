#include <opencv2/opencv.hpp>
#include <iostream>

struct Y1_Y2 {
    int y1 = -1;
    int y2 = -1;
};

struct X1_X2 {
    int x1 = -1;
    int x2 = -1;
};

struct Objects {
    std::vector<Y1_Y2> objectsY;
    std::vector<X1_X2> objectsX;
};

struct Detection {
    int x;
    int y;
    int width;
    int height;
};

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

    Objects objects;
    //std::vector<Detection> objects;

    int blue = 0, green = 0, red = 0;
    //std::cout << "Put color a object (blue[b] green[g] red[r]; (0 <= b,g,r <= 255)): bbb ggg rrr ---> ";
    //std::cin >> blue >> green >> red;
    bool flag_strX = false, flag_strY = false, flag_objX = false, flag_objY = false;
    std::vector<int> ourColorMin = {blue - 10, green - 10, red - 10};
    std::vector<int> ourColorMax = {blue + 10, green + 10, red + 10};
    int i;

    X1_X2 coordX;
    Y1_Y2 coordY;

    for (int y = 0; y < img.rows; y++) {
        if (!flag_objY && coordY.y1 != -1 && coordY.y2 != -1 && (coordY.y1 != coordY.y2)) {
            objects.objectsY.push_back(coordY);
            coordY.y1 = -1;
            coordY.y2 = -1;
        }
        flag_objY = false;
        for (int x = 0; x < img.cols; x++) {
            int ind = index(x, y, img.cols);
            for (i = 0; i < 3; i++) {
                if ((img.data[ind] + i) < ourColorMin[i] || (img.data[ind] + i) > ourColorMax[i]) {
                    break;
                }
            }

            ///   |
            ///   |
            ///   |
            ///  \/ y

            //если i=3, значит цвета похожи, если i<3, значит различны
            if (i == 3) {
                flag_objY = true;
                if (coordY.y1 == -1) {
                    coordY.y1 = y;
                } else
                    coordY.y2 = y;
            }
        }
    }
    for (int x = 0; x < img.cols; x++) {
        if (!flag_objX && coordX.x1 != -1 && coordX.x2 != -1 && (coordX.x1 != coordX.x2)) {
            objects.objectsX.push_back(coordX);
            coordX.x1 = -1;
            coordX.x2 = -1;
        }
        flag_objX = false;
        for (int y = 0; y < img.rows; y++) {
            int ind = index(x, y, img.cols);
            for (i = 0; i < 3; i++) {
                if ((img.data[ind] + i) < ourColorMin[i] || (img.data[ind] + i) > ourColorMax[i]) {
                    break;
                }
            }

            /// ------> x

            //если i=3, значит цвета похожи, если i<3, значит различны
            if (i == 3) {
                flag_objX = true;
                if (coordX.x1 == -1) {
                    coordX.x1 = x;
                } else
                    coordX.x2 = x;
            }
        }
    }

    for (int j = 0; j < objects.objectsY.size(); j++) {
        for (i = 0; i < objects.objectsX.size(); i++) {
            std::cout << objects.objectsX[i].x1 << ";" << objects.objectsY[j].y1 << std::endl;
            std::cout << "width = " << objects.objectsX[i].x2 - objects.objectsX[i].x1 << std::endl;
            std::cout << "height = " << objects.objectsY[j].y2 - objects.objectsY[j].y1 << std::endl;
        }
    }
    Detection res;
    return 0;
}