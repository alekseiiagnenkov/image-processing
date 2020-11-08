#include "StaticMatrix.h"
#include "DynamicMatrix.h"

#include <iostream>
#include <fstream>

#include <string>

int main(int argc, char** argv) {

	//staticmat::Matrix statMat;

	//std::cin >> statMat.name;
	//std::cin >> statMat.vertSize;
	//for(int i=0; i<statMat.vertSize; i++)
	//	std::cin >> statMat.vertMatr[i];
	//std::cin >> statMat.horSize;
	//for (int i = 0; i < statMat.horSize; i++)
	//	std::cin >> statMat.horMatr[i];
	//std::ofstream outFile("out.bin", std::ios::binary);
	//outFile.write((char*)&statMat, sizeof(statMat));
	//outFile.close();

	//staticmat::Matrix statMatNew;
	//std::ifstream inFile("out.bin", std::ios::binary);
	//inFile.read((char*)&statMatNew, sizeof(statMatNew));
	//inFile.close();

	dynamicmat::Matrix dynMat;
	std::string matrName;
	std::cin >> matrName;
	dynMat.nameSize = matrName.size() + 1;
	dynMat.name = new char[dynMat.nameSize];
	std::memcpy(dynMat.name, matrName.c_str(), dynMat.nameSize);
	std::cin >> dynMat.vertSize;
	dynMat.vertMatr = new double[dynMat.vertSize];
	for (int i = 0; i < dynMat.vertSize; i++)
		std::cin >> dynMat.vertMatr[i];
	std::cin >> dynMat.horSize;
	dynMat.horMatr = new double[dynMat.horSize];
	for (int i = 0; i < dynMat.horSize; i++)
		std::cin >> dynMat.horMatr[i];

	std::ofstream outDynFile("outDyn.bin", std::ios::binary);
	outDynFile.write((char*)&dynMat, sizeof(dynMat));
	outDynFile.write((char*)dynMat.name, dynMat.nameSize * sizeof(char));
	outDynFile.write((char*)dynMat.vertMatr, dynMat.vertSize * sizeof(double));
	outDynFile.write((char*)dynMat.horMatr, dynMat.horSize * sizeof(double));
	outDynFile.close();
	delete[] dynMat.name;
	delete[] dynMat.vertMatr;
	delete[] dynMat.horMatr;

	dynamicmat::Matrix dynMatNew;
	std::ifstream inDynFile("outDyn.bin", std::ios::binary);
	inDynFile.read((char*)&dynMatNew, sizeof(dynMatNew));
	dynMatNew.name = new char[dynMatNew.nameSize];
	dynMatNew.vertMatr = new double[dynMatNew.vertSize];
	dynMatNew.horMatr = new double[dynMatNew.horSize];
	inDynFile.read((char*)dynMatNew.name, dynMatNew.nameSize * sizeof(char));
	inDynFile.read((char*)dynMatNew.vertMatr, dynMatNew.vertSize * sizeof(double));
	inDynFile.read((char*)dynMatNew.horMatr, dynMatNew.horSize * sizeof(double));
	inDynFile.close();
	delete[] dynMatNew.name;
	delete[] dynMatNew.vertMatr;
	delete[] dynMatNew.horMatr;
}