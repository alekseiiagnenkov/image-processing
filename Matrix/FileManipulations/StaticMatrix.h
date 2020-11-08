#pragma once

namespace staticmat {

	constexpr int MAX_NAME_SIZE = 255 ;
	constexpr int MAX_MATR_SIZE = 100;


	struct Matrix {
		char name[MAX_NAME_SIZE];
		int vertSize;
		double vertMatr[MAX_MATR_SIZE];
		int horSize;
		double horMatr[MAX_MATR_SIZE];
	};

}