#include "Editor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

const char* msgs[] = { " [0] Create filter",
					   " [1] Blur ",
					   " [2] Copy ",
					   " [3] Negative ",
					   " [4] Exit\n"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

Matrix* (*functions[])(int, int) = { CreatMatrix, Blur, Copy, Negative, Exit };

Matrix* dialogChoose(int width, int height) {
	int rc = dialog(msgs, NMsgs);
	return functions[rc](width, height);
}


Matrix* Negative(int width, int heigth) {
	Matrix* M = new Matrix[1];
	M->height = 1;
	M->width = 1;
	M->arr = new double[]
	{-1};
	return M;
}

Matrix* Blur(int width, int heigth) {
	Matrix* M = new Matrix[1];
	M->height = 3;
	M->width = 3;
	M->arr = new double[]
	{ 0.0625, 0.125, 0.0625,
		0.125, 0.25, 0.125,
		0.0625, 0.125, 0.0625 };
	return M;
}

Matrix* Copy(int width, int heigth) {
	Matrix* M = new Matrix[1];
	M->height = 3;
	M->width = 3;
	M->arr = new double[]
	{ 0, 0, 0,
		0, 1, 0,
		0, 0, 0 };
	return M;
}

Matrix* CreatMatrix(int width, int height) {

	Matrix* M = new Matrix[1];
	do {
		std::cout << "Enter the number of lines:";
		std::cin >> M->height;
	} while (!(M->height % 2));
	do {
		std::cout << "Enter the number of rows:";
		std::cin >> M->width;
	} while (!(M->width % 2));

	M->arr = new double[(M->width * M->height)];
	for (int x = 0; x < M->width; x++) {
		for (int y = 0; y < M->height; y++) {
			std::cout << "Enter the [" << y + 1 << "," << x + 1 << "] element of the matrix:";
			std::cin >> M->arr[(x + y * M->width)];
		}
	}
	return M;
}

Matrix* Exit(int a, int b) {
	return nullptr;
}



int modifyImage(const std::uint8_t const* inputImage, std::uint8_t* outputImage, std::uint32_t width, std::uint32_t height) {

	int b = 1;

	Matrix* M;
	if (M = dialogChoose(width, height)) {

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++) {
				int ind = index(x, y, width, height, &b);
				for (int i = 0; i < 3; i++) {
					int j = 0;
					outputImage[ind + i] = 0;
					for (int m = y - (M->height / 2); m <= y + (M->height / 2); m++)
						for (int n = x - (M->width / 2); n <= x + (M->width / 2); n++, j++)
							outputImage[ind + i] += M->arr[j] * inputImage[index(n, m, width, height, &b) + i] * b;
				}
			}
		delete[] M->arr;
		delete[] M;
		return 1;
	}
	else {
		return 0;
	}
}



int index(int x, int y, int width, int height, int* b) {
	*b = 1;
	if (x < 0 || x > width || y < 0 || y > height)
		*b = 0;
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