#include <opencv2/opencv.hpp>

struct Matrix {
	std::string name;
	double* arr1;
	double* arr2;
	int width;
	int height;
};

int index(int x, int y, int width, int height);
unsigned char clamp(double val);
Matrix* modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, std::vector<Matrix*>&);

Matrix* CreatMatrix(std::vector<Matrix*>& ARR);
Matrix* ChooseMatrix(std::vector<Matrix*>& ARR);
Matrix* Exit(std::vector<Matrix*>& ARR);
Matrix* (*functions[])(std::vector<Matrix*>& ARR);
Matrix* dialogChoose(std::vector<Matrix*>& ARR);


Matrix* copyEdges(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, Matrix* M);
int dialog(const char* msgs[], int N);
int getNaturalInt(int* a);
void SAVE(std::vector<Matrix*>& ARR);
std::vector<Matrix*> LOAD(std::vector<Matrix*>&);
std::vector<Matrix*> addMatrix(std::vector<Matrix*>& ARR, Matrix* M);