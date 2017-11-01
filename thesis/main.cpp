
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "svi.h"
using namespace std;

int main() { 
	int x; 

	using namespace SVI;
	double a = -2; 
	double b = 12;
	double sigma = 0.2;
	double rho = 0.1;
	double m = 0;
	double myNums [] = {a, b, rho, m, sigma};
	std::vector<double> params(myNums, myNums + sizeof(myNums)/sizeof(double));
	string str = "smileData.txt";
	SVI_DATA svi(str);
	parameter_vector vec;
	vec(0) = a; vec(1) = b; vec(2) = rho; vec(3) = m; vec(4) = sigma;
	optSvi(svi, vec);
	
	std::cin >> x;
return 0;
}