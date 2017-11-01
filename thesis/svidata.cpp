#include "svidata.h"
#include <fstream>
#include <iostream>
#include "optimization.h"
#include "optimization_least_squares.h"
svidata::svidata(void) { }

svidata::svidata(string& str): fileName(str) {
	ifstream file(fileName);
	string line1;
	vector<string> temp;
	pair<double, double> point;
	while (!file.eof()) {
		getline(file, line1); 
		point.first = atof(line1.substr(0, line1.find('\t')).c_str());
		line1 = line1.substr(line1.find('\t') + 1);
		point.second = atof(line1.substr(0, line1.find('\t')).c_str());
		smile.push_back(point);
	}
};
void svidata::strikes() {};
svidata::~svidata(void)
{
}
