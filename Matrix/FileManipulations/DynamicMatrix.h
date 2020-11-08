#pragma once

namespace dynamicmat {


	struct Matrix {
		char* name;
		int nameSize;
		int vertSize;
		double* vertMatr;
		int horSize;
		double* horMatr;
	};

}