#include <opencv2/opencv.hpp>

struct Matrix {
	double* arr;
	int width;
	int height;
};

int index(int x, int y, int width, int height, int* b);
int modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height);

Matrix* CreatMatrix(int width, int height);
Matrix* Blur(int width, int heigth);
Matrix* Copy(int width, int heigth);
Matrix* Exit(int a, int b);

Matrix* (*functions[])(int, int);
Matrix* dialogChoose(int, int);
int dialog(const char* msgs[], int N);
int getNaturalInt(int* a);