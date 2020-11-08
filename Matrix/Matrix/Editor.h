#include <opencv2/opencv.hpp>

struct Matrix {
	std::string name;
	std::vector<double> arr1;
	std::vector<double> arr2;
	int width;
	int height;
};

int index(int x, int y, int width);
unsigned char clamp(double val);
Matrix* modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, std::vector<Matrix>&);

Matrix* CreatMatrix(std::vector<Matrix>& ARR);
Matrix* ChooseMatrix(std::vector<Matrix>& ARR);
Matrix* Exit(std::vector<Matrix>& ARR);
Matrix* (*functions[])(std::vector<Matrix>& ARR);
Matrix* dialogChoose(std::vector<Matrix>& ARR);


void copyEdges(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, Matrix* M);
int dialog(const char* msgs[], int N);
int getNaturalInt(int* a);
void save(std::vector<Matrix>& ARR);
std::vector<Matrix> load(std::vector<Matrix>&);
std::vector<Matrix> addMatrix(std::vector<Matrix>& ARR, Matrix* M);