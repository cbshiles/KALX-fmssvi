#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "optimization.h"
#include "optimization_least_squares.h"
using namespace dlib;
using namespace std;

namespace SVI {

	typedef matrix<double,1,1> input_vector;
	typedef matrix<double,5,1> parameter_vector;

	double sviModel(const input_vector& input, const parameter_vector& par) {
		double k = input(0); 
		double a = par(0); double b = par(1);double rho = par(2);double m = par(3); double sigma = par(4);
	return  ( a + b * ( rho * (k - m) + sqrt((k - m) * (k - m) + sigma * sigma ) ) );
	}
	/*
	******************************************************************************************
		Class for handling Data - We read a textfile and pair strike with implied variance
	******************************************************************************************
	*/
	class SVI_DATA {
		private:
			std::string fileName;
			
		public:
				//	Smile
			std::vector< pair<double, double> > smile;
			std::vector<double> params;
			SVI_DATA(string& str): fileName(str) {
				ifstream file(fileName);
				string line1;
				std::vector<string> temp;
				pair<double, double> point;
					while (!file.eof()) {
						getline(file, line1); 
						// strikes
						point.first = log(atof(line1.substr(0, line1.find('\t')).c_str()));
						line1 = line1.substr(line1.find('\t') + 1);
						// Convert to implied variance 
						point.second = pow(atof(line1.substr(0, line1.find('\t')).c_str()) / 100, 2);
						// build smile using pairs of strike, variance data
						smile.push_back(point);
					}	
			}
	/*
	**************************************************************************
		This member function prints the set of strikes and variances in smile
	**************************************************************************
	*/
			void printData() {
				std::vector<pair<double,double> >::const_iterator iter;
				for( iter = smile.begin(); iter!= smile.end(); iter++) {
					cout<<iter->first<<'\t'<<iter->second<<endl;
				}
			}
	};
	/* 
	*************************************************************************
		Calculates residuals given a single strike and parameter set
	*************************************************************************
	*/
	double residual ( const std::pair<input_vector, double>& data, const parameter_vector& params) {
	return sviModel(data.first, params) - data.second;
	}

	parameter_vector optSvi(SVI_DATA data, parameter_vector par) {
		std::vector<std::pair<input_vector, double> > data_samples;
		input_vector input;
			for (int i = 0; i < data.smile.size(); ++i) {
				input(0) = data.smile[i].first;
				const double output = data.smile[i].second;
				data_samples.push_back(make_pair(input, output));
			}
	parameter_vector x;
	x = 1;
	solve_least_squares_lm(objective_delta_stop_strategy(1e-7).be_verbose(), 
							&residual, derivative(&residual), data_samples, x);

	cout<<"inferred parameters: "<<trans(x)<<endl;
	return x;
	}
}