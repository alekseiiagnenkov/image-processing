#include "Editor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

const char *msgs[] = {"\n [0] Create filter",
                      " [1] Choose filter",
                      " [2] exit\n"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

Matrix (*functions[])(std::vector<Matrix> &) = {create_matrix, choose_matrix, exit};

Matrix dialog_choose(std::vector<Matrix> &ARR) {
    int rc = dialog(msgs, NMsgs);
    return functions[rc](ARR);
}

Matrix choose_matrix(std::vector<Matrix> &ARR) {
    Matrix M;
    int a = 0;
    if (ARR.size() == 0) {
        std::cout << "No filters!";
        return M;
    } else {
        for (int i = 0; i < ARR.size(); i++)
            std::cout << "[" << i << "] - " << ARR[i].name << std::endl;
        do {
            std::cout << "Your choise:";
            std::cin >> a;
        } while (a < 0 || a >= ARR.size());
        return ARR[a];
    }
}

Matrix create_matrix(std::vector<Matrix> &ARR) {

    double a;
    Matrix M;
    do {
        std::cout << "Enter the number of the first matrix:";
        std::cin >> M.height;
    } while (!(M.height % 2));

    for (int y = 0; y < M.height; y++) {
        std::cout << "Enter the [" << y + 1 << "] element of the matrix:";
        std::cin >> a;
        M.arr1.push_back(a);
    }

    do {
        std::cout << "Enter the number of the second matrix:";
        std::cin >> M.width;
    } while (!(M.width % 2));

    for (int x = 0; x < M.width; x++) {
        std::cout << "Enter the [" << x + 1 << "] element of the matrix:";
        std::cin >> a;
        M.arr2.push_back(a);
    }
    return M;
}

Matrix exit(std::vector<Matrix> &ARR) {
    Matrix M;
    return M;
}

Matrix
modify_image(std::uint8_t const *inputImage, std::uint8_t *outputImage, std::uint32_t width, std::uint32_t height,
             std::vector<Matrix> &ARR) {

    Matrix M = dialog_choose(ARR);
    if (!M.arr1.size() == 0) {


        cv::Mat bigImage(height + 2 * (M.height / 2), width + 2 * (M.width / 2), CV_8UC3);
        for (int y = (M.height / 2); y < height + (M.height / 2); y++)
            for (int x = (M.width / 2); x < width + (M.width / 2); x++) {
                int ind = index(x, y, width + 2 * (M.width / 2));
                int ind1 = index(x - (M.width / 2), y - (M.height / 2), width);
                for (int i = 0; i < 3; i++)
                    bigImage.data[ind + i] = inputImage[ind1 + i];
            }
        copy_edges(inputImage, bigImage.data, width, height, M);


        for (int y = (M.height / 2); y < height + (M.height / 2); y++)
            for (int x = (M.width / 2); x < width + (M.height / 2); x++) {
                int ind = index(x - (M.width / 2), y - (M.height / 2), width);
                for (int i = 0; i < 3; i++) {
                    int j = 0;
                    double r = 0;
                    outputImage[ind + i] = 0;
                    for (int n = x - (M.width / 2), j = 0; n <= x + (M.width / 2); n++, j++)
                        if ((index(n, y, width + 2 * (M.width / 2)) + i) <= 3*((width + 2 * (M.width / 2)) * (height + 2 * (M.height / 2))))
                            r += M.arr1[j] * bigImage.data[index(n, y, width + 2 * (M.width / 2)) + i];
                    for (int m = y - (M.height / 2), j = 0; m <= y + (M.height / 2); m++, j++)
                        if ((index(x, m, width + 2 * (M.width / 2)) + i) <= 3*((width + 2 * (M.width / 2)) * (height + 2 * (M.height / 2))))
                            r += M.arr2[j] * bigImage.data[index(x, m, width + 2 * (M.width / 2)) + i];
                    outputImage[ind + i] = clamp(r / 2);
                }
            }
    }
    return M;
}

std::vector<Matrix> add_matrix(std::vector<Matrix> &ARR, Matrix M) {
    int a, i;
    do {
        std::cout << "Do you want to save this filter?\n [Yes]-1   [No]-0\n Your choise:";
        std::cin >> a;
    } while (a < 0 || a > 1);
    if (a) {
        do {
            std::cout << "Enter name of filter:";
            std::cin >> M.name;
            for (i = 0; i < ARR.size(); i++)
                if (ARR[i].name == M.name) {
                    std::cout << "ERROR!  This filter already have created!\n";
                    i = -1;
                }
        } while (i == -1);
        ARR.push_back(M);
    }
    return ARR;
}

void copy_edges(std::uint8_t const *inputImage, std::uint8_t *outputImage, std::uint32_t width, std::uint32_t height,
                Matrix M) {

    for (int x = M.width / 2; x < width + (M.width / 2); x++) {
        int ind1 = index(x - (M.width / 2), 0, width);
        for (int y = 0; y < (M.height / 2); y++) {
            int ind = index(x, y, width + 2 * (M.width / 2));
            for (int i = 0; i < 3; i++)
                outputImage[ind + i] = inputImage[ind1 + i];
        }
    }

    for (int x = M.width / 2; x < width + M.width / 2; x++) {
        int ind1 = index(x - (M.width / 2), height - 1, width);
        for (int y = height + M.height / 2; y < height + 2 * (M.height / 2); y++) {
            int ind = index(x, y, width + 2 * (M.width / 2));
            for (int i = 0; i < 3; i++)
                outputImage[ind + i] = inputImage[ind1 + i];
        }
    }

    for (int y = M.height / 2; y < height + (M.height / 2); y++) {
        int ind1 = index(0, y - (M.height / 2), width);
        for (int x = 0; x < (M.width / 2); x++) {
            int ind = index(x, y, width + 2 * (M.height / 2));
            for (int i = 0; i < 3; i++)
                outputImage[ind + i] = inputImage[ind1 + i];
        }
    }

    for (int y = M.height / 2; y < height + M.height / 2; y++) {
        int ind1 = index(width - 1, y - (M.height / 2), width);
        for (int x = width + M.width / 2; x < width + 2 * (M.width / 2); x++) {
            int ind = index(x, y, width + 2 * (M.width / 2));
            for (int i = 0; i < 3; i++)
                outputImage[ind + i] = inputImage[ind1 + i];
        }
    }
}

int index(int x, int y, int width) {
    return ((x + y * width) * 3);
}

int dialog(const char *msgs[], int n) {
    std::string errmsg;
    int rc;
    do {
        std::cout << errmsg;
        errmsg = "You are wrong. Repeat, please\n";
        for (int j = 0; j < n; ++j)
            puts(msgs[j]);
        std::cout << "Make your choice:";

        if (get_natural_int(&rc) == 0) { rc = 0; }
    } while (rc < 0 || rc >= n);
    return rc;
}

int get_natural_int(int *a) {
    do {
        std::cin >> *a;
        if (*a < 0)
            return 0;
        if (*a < 0) {
            std::cout << "Error! Please, repeat your input: ";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    } while (*a < 0);
    return 1;
}

unsigned char clamp(double val) {
    if (val < 0)
        return 0;
    if (val > 255)
        return 255;
    return (unsigned char) val;
}

std::vector<Matrix> load(std::vector<Matrix> &ARR) {

    int i, j;
    std::ifstream data;
    data.open("../res/data.txt", std::ifstream::in);
    if (data.is_open()) {
        data.seekg(0, std::ios::beg);

        while (!data.eof()) {
            Matrix M;
            data >> M.name;
            if ((M.name.size() == 0))
                break;
            data >> M.height >> M.width;

            for (i = 0; i < M.height; i++) {
                data >> j;
                M.arr1.push_back(j);
            }
            for (i = 0; i < M.width; i++) {
                data >> j;
                M.arr2.push_back(j);
            }
            ARR.push_back(M);
        }
        data.close();
    }
    return ARR;
}

void save(std::vector<Matrix> &ARR) {
    std::ofstream data;
    data.open("../res/data.txt", std::ios_base::out | std::ios_base::trunc);
    if (data.is_open()) {
        for (int j = 0; j < ARR.size(); j++) {
            data << ARR[j].name << " " << ARR[j].height << " " << ARR[j].width << " " << std::endl;
            for (int i = 0; i < ARR[j].height; i++)
                data << ARR[j].arr1[i] << " ";
            data << std::endl;
            for (int i = 0; i < ARR[j].width; i++)
                data << ARR[j].arr2[i] << " ";
            data << std::endl;
        }
        data.close();
    }
}