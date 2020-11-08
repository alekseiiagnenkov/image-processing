#include "Editor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

const char* msgs[] = { "\n [0] Create filter",
					   " [1] Choose filter",
					   " [2] Exit\n"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

Matrix* (*functions[])(std::vector<Matrix*>&) = { CreatMatrix, ChooseMatrix, Exit };

Matrix* dialogChoose(std::vector<Matrix*>& ARR) {
	int rc = dialog(msgs, NMsgs);
	return functions[rc](ARR);
}

Matrix* ChooseMatrix(std::vector<Matrix*>& ARR) {
	Matrix* M = nullptr;
	int a = 0;
	if (ARR.size() == 0) {
		std::cout << "No filters!";
		return nullptr;
	}
	else {
		for (int i = 0; i < ARR.size(); i++)
			std::cout << "[" << i << "] - " << ARR[i]->name << std::endl;
		do {
			std::cout << "Your choise:";
			std::cin >> a;
		} while (a < 0 || a >= ARR.size());
		return ARR[a];
	}
}

Matrix* CreatMatrix(std::vector<Matrix*>& ARR) {

	Matrix* M = new Matrix;
	do {
		std::cout << "Enter the number of the first matrix:";
		std::cin >> M->height;
	} while (!(M->height % 2));

	M->arr1 = new double[M->height];
	for (int y = 0; y < M->height; y++) {
		std::cout << "Enter the [" << y + 1 << "] element of the matrix:";
		std::cin >> M->arr1[y];
	}

	do {
		std::cout << "Enter the number of the second matrix:";
		std::cin >> M->width;
	} while (!(M->width % 2));

	M->arr2 = new double[M->width];
	for (int x = 0; x < M->width; x++) {
		std::cout << "Enter the [" << x + 1 << "] element of the matrix:";
		std::cin >> M->arr2[x];
	}
	return M;
}

Matrix* Exit(std::vector<Matrix*>& ARR) {
	return nullptr;
}


Matrix* modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, std::vector<Matrix*>& ARR) {

	Matrix* M;
	if (M = dialogChoose(ARR)) {
		for (int y = (M->height / 2); y < height - (M->height / 2); y++)
			for (int x = (M->width / 2); x < width - (M->width / 2); x++) {
				int ind = index(x, y, width, height);
				for (int i = 0; i < 3; i++) {
					int j = 0;
					double r = 0;
					outputImage[ind + i] = 0;
					for (int n = x - (M->width / 2), j = 0; n <= x + (M->width / 2); n++, j++)
						r += M->arr1[j] * inputImage[index(n, y, width, height) + i];
					for (int m = y - (M->height / 2); m <= y + (M->height / 2); m++, j++)
						r += M->arr2[j] * inputImage[index(x, m, width, height) + i];
					outputImage[ind + i] = clamp(r / 2);
				}
			}
		M = copyEdges(inputImage, outputImage, width, height, M);
		return M;
	}
	else {
		return nullptr;
	}
}

std::vector<Matrix*> addMatrix(std::vector<Matrix*>& ARR, Matrix* M) {
	int a = 0, i;
	do {
		std::cout << "Do you want to save this filter?\n [Yes]-1   [No]-0\n Your choise:";
		std::cin >> a;
	} while (a < 0 || a>1);
	if (a) {
		do {
			std::cout << "Enter name of filter:";
			std::cin >> M->name;
			for (i = 0; i < ARR.size(); i++) {
				if (ARR[i]->name == M->name) {
					std::cout << "ERROR!  This filter already have created!\n";
					i=-1;
				}
			}
		} while (i==-1);
		ARR.push_back(M);
	}
	else {
		delete[] M->arr1;
		delete[] M->arr2;
		delete M;
	}
	return ARR;
}

Matrix* copyEdges(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height, Matrix* M) {

	for (int y = 0; y < M->height / 2; y++)
		for (int x = 0; x < width; x++) {
			int ind = index(x, y, width, height);
			for (int i = 0; i < 3; i++) {
				outputImage[ind + i] = inputImage[ind + i];
			}
		}

	for (int y = (height - M->height / 2); y < height; y++)
		for (int x = 0; x < width; x++) {
			int ind = index(x, y, width, height);
			for (int i = 0; i < 3; i++) {
				outputImage[ind + i] = inputImage[ind + i];
			}
		}

	for (int y = 0; y < height; y++)
		for (int x = 0; x < M->width / 2; x++) {
			int ind = index(x, y, width, height);
			for (int i = 0; i < 3; i++) {
				outputImage[ind + i] = inputImage[ind + i];
			}
		}

	for (int y = 0; y < height; y++)
		for (int x = width - M->width / 2; x < width; x++) {
			int ind = index(x, y, width, height);
			for (int i = 0; i < 3; i++) {
				outputImage[ind + i] = inputImage[ind + i];
			}
		}
	return M;
}

int index(int x, int y, int width, int height) {
	return ((x + y * width) * 3);
}

int dialog(const char* msgs[], int N) {
	std::string errmsg;
	int rc;
	do {
		std::cout << errmsg;
		errmsg = "You are wrong. Repeat, please\n";
		for (int j = 0; j < N; ++j)
			puts(msgs[j]);
		std::cout << "Make your choice:";

		if (getNaturalInt(&rc) == 0) { rc = 0; }
	} while (rc < 0 || rc >= N);
	return rc;
}

int getNaturalInt(int* a) {
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
	return (unsigned char)val;
}

std::vector<Matrix*> load(std::vector<Matrix*>& ARR) {

	std::ifstream data;
	data.open("data.txt", std::ifstream::in);
	if (data.is_open()) {
		data.seekg(0, std::ios::beg);

		while (!data.eof()) {
			Matrix* M = new Matrix;
			data >> M->name;
			if ((M->name.size() == 0))
				break;
			data >> M->height >> M->width;

			M->arr1 = new double[M->height];
			M->arr2 = new double[M->width];
			for (int i = 0; i < M->height; i++) {
				data >> M->arr1[i];
			}
			for (int i = 0; i < M->width; i++) {
				data >> M->arr2[i];
			}
			ARR.push_back(M);
		}
		data.close();
	}
	return ARR;
}

void save(std::vector<Matrix*>& ARR) {
	std::ofstream data;
	data.open("data.txt", std::ios_base::out | std::ios_base::trunc);
	if (data.is_open()) {
		data.seekp(0, std::ios::beg);
		for (int j = 0; j < ARR.size(); j++) {
			data << ARR[j]->name << " " << ARR[j]->height << " " << ARR[j]->width << " " << std::endl;
			for (int i = 0; i < ARR[j]->height; i++)
				data << ARR[j]->arr1[i] << " ";
			data << std::endl;
			for (int i = 0; i < ARR[j]->width; i++)
				data << ARR[j]->arr2[i] << " ";
			data << std::endl;
		}
		data.close();
	}
}