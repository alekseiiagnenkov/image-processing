#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv) {
	if (argc != 2)
		return -1;
	ifstream textFile(argv[1]);
	string text;
	textFile >> text;
	cout << text << endl;
	string a;
	cin >> a;
}