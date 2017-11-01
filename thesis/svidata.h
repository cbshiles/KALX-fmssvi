#pragma once
#include <string>
#include <vector>

using namespace std;

class svidata
{
//private:
public:
	string fileName;
	vector<pair<double, double>> smile;
	vector<double> K;
//public:
	svidata(void);
	svidata(string&);
	//pair<string, string> getSmile () { return smile; };
	void readData();
	void strikes ();
	~svidata(void);
};

