#include <iostream>
#include <vector>
#include <stdlib.h>
#include "./sstd/sstd.hpp"
#include "c2py.hpp"


void vec2graph_1(const char* pWriteName, double interval, std::vector<double>& in1){

	std::string args;
	args  = c2py_str(pWriteName);
	args += c2py_double(interval);
	args += c2py_vecDouble(in1);

	system(sstd::ssprintf("python -u ./plot.py %s", args.c_str()).c_str());
	// 引数の与え方
	// [$ python -u ./plot.py writeName interval len1 vec1 len2 vec2 ... lenN vecN]
	//                0       1         2        3    4    5    6    ... 2*N  2*N+1
}
void vec2graph_2(const char* pWriteName, double interval, std::vector<double>& in1, std::vector<double>& in2){

	std::string args;
	args  = c2py_str(pWriteName);
	args += c2py_double(interval);
	args += c2py_vecDouble(in1);
	args += c2py_vecDouble(in2);

	system(sstd::ssprintf("python -u ./plot.py %s", args.c_str()).c_str());
}
void vec2graph_3(const char* pWriteName, double interval, std::vector<double>& in1, std::vector<double>& in2, std::vector<double>& in3){

	std::string args;
	args  = c2py_str(pWriteName);
	args += c2py_double(interval);
	args += c2py_vecDouble(in1);
	args += c2py_vecDouble(in2);
	args += c2py_vecDouble(in3);

	system(sstd::ssprintf("python -u ./plot.py %s", args.c_str()).c_str());
}

int main(){

	double freq2generate = 0.3; // 3 Hz sin wave
	double freq2sample = 10;    // 100 Hz sampling
	uint len=60*10 + 1;         // 1 sec
	std::vector<double> sin_wave = sstd::sinWave(freq2generate, freq2sample, len);
	std::vector<double> cos_wave = sstd::cosWave(freq2generate, freq2sample, len);
	std::vector<double> sin_2(len); for(uint i=0; i<len; i++){ sin_2[i]=2*sin_wave[i]; }
	
	vec2graph_1("./001.png", 1/freq2sample, sin_wave);
	vec2graph_2("./002.png", 1/freq2sample, sin_wave, cos_wave);
	vec2graph_3("./003.png", 1/freq2sample, sin_wave, cos_wave, sin_2);

	return 0;
}
