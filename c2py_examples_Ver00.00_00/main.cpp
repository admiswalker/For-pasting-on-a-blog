#ifdef _WIN32
	#include "./sstd/sstd.hpp"
#else
	#include <sstd/sstd.hpp>
#endif

void sample1(){
	// Sample1
	{
		sstd::c2py<int> plus_a_b("./tmpDir", "pyFunctions", "plus_a_b", "int, int, const int*");
		int a=1, b=2;
		int c=plus_a_b(a, &b);
		
		sstd::printn(c);
	}
	printf("\n");

	// Sample2
	//   int is treated as a int32. (uint is treated as a uint32.)
	{
		sstd::c2py<std::vector<int>> plus_vecA_vecB("./tmpDir", "pyFunctions", "plus_vecA_vecB", "vec<int>, const int*, len, const vec<int>*");
		int arrA[]={1,2,3};
		std::vector<int> vecB={4,5,6};
		std::vector<int> vecC=plus_vecA_vecB(arrA, 3, &vecB);
		
		sstd::printn(vecC);
	}
	printf("\n");

	// Sample3:
	//   writing back self multiplied value.
	{
		sstd::c2py<void> selfMult("./tmpDir", "pyFunctions", "selfMult", "void, int*, int*, len, vec<int>*");
		int a=2;
		int arrB[]={3,4,5};
		std::vector<int> vecC={6,7,8};
		selfMult(&a, arrB, 3, &vecC);
		
		sstd::printn(a);
		printf("arrB[3] = [ "); for(uint i=0; i<3; i++){ printf("%d ", arrB[i]); } printf("]\n");
		sstd::printn(vecC);
	}
	printf("\n");

	// Sample4:
	//   conversion types of Python side. Right of separator symbol "|" mean Python side. Right of "|" enable to take "*" or "~" and these order have no meaning. (There is no difference between "|*~" and "|~*".)
	//   *: type conversion to built-in type.
	//   ~: type conversion to a pseudo pointer type (self inclusion list).
	{
		sstd::c2py<void> checkTypes("./tmpDir", "pyFunctions", "checkTypes", "void, int, int|~, int|*, int|*~");
		checkTypes(0, 0, 0, 0);
	}
	printf("\n");

	// Sample5:
	//   writing back with changing the length of std::vector<T>.
	{
		sstd::c2py<void> changeLen("./tmpDir", "pyFunctions", "changeLen", "void, vec<int>*|*, vec<int>*|~");
		std::vector<int> vec1={1,2,3}, vec2={1,2,3};
		changeLen(&vec1, &vec2);
		
		sstd::printn(vec1);
		sstd::printn(vec2);
	}
	printf("\n");

	// Sample6:
	//   multiple return value in python side.
	{
		sstd::c2py<int> multiRet("./tmpDir", "pyFunctions", "multiRet", "int, ret int*, ret int*, len, ret vec<int>*");
		int ret0=0;
		int ret1=0;
		int ret2[]={0,0,0};
		std::vector<int> ret3;
		ret0 = multiRet(&ret1, &ret2, 3, &ret3);
		
		sstd::printn(ret0);
		sstd::printn(ret1);
		printf("ret2[3] = [ "); for(uint i=0; i<3; i++){ printf("%d ", ret2[i]); } printf("]\n");
		sstd::printn(ret3);
	}
	printf("\n");
}
void benchMark1(){
	time_m timem; sstd::measureTime_start(timem);
		
	sstd::c2py<void> emptyFunc("./tmpDir", "pyFunctions", "emptyFunc", "void");
	for(uint i=0; i<1000; i++){ emptyFunc(); }
		
	sstd::measureTime_stop_print(timem); sstd::pauseIfWin32();
//--------------------------------
//	 Execution time:   199. 535 sec
//--------------------------------
}
void benchMark2(){
	time_m timem; sstd::measureTime_start(timem);
		
	for(uint i=0; i<1000; i++){
		sstd::c2py<void> emptyFunc("./tmpDir", "pyFunctions", "emptyFunc", "void");
		emptyFunc();
	}
		
	sstd::measureTime_stop_print(timem); sstd::pauseIfWin32();
//--------------------------------
// Execution time:   200. 207 sec
//--------------------------------
}

void applicationSample1(){
	double freq2generate = 0.1; // 0.1 Hz sin wave
	double freq2sample = 10;    // 10 Hz sampling
	uint len=60*10 + 1;         // 60 sec
	std::vector<double> vecY = sstd::sinWave(freq2generate, freq2sample, len);
	std::vector<double> vecX(len); for(uint i=0; i<vecX.size(); i++){ vecX[i]=(double)i*(1/freq2sample); }
	
	sstd::c2py<void> vec2graph("./tmpDir", "pyFunctions", "vec2graph", "void, const char*, vec<double>*, vec<double>*");
	vec2graph("./sin.png", &vecX, &vecY);
}

void applicationSample2(){
	double freq_generate = 0.1; // 0.1 Hz sin wave
	double freq_sample = 10;    // 10 Hz sampling
	uint len=60*10 + 1;         // 60 sec
	std::vector<double> sinY = sstd::sinWave(freq_generate, freq_sample, len);
	std::vector<double> sinX(len); for(uint i=0; i<sinX.size(); i++){ sinX[i]=(double)i*(1/freq_sample); }
	
	std::vector<double> cosY = sstd::cosWave(freq_generate, freq_sample, len);
	std::vector<double> cosX(len); for(uint i=0; i<cosX.size(); i++){ cosX[i]=(double)i*(1/freq_sample); }
	
	std::vector<std::string> vLabel={"sin", "cos", "-cos"};
	std::vector<std::vector<double>> vvecX={sinX, cosX,    cosX};
	std::vector<std::vector<double>> vvecY={sinY, cosY, -1*cosY};
	
	sstd::c2py<void> vvec2graph("./tmpDir", "pyFunctions", "vvec2graph", "void, const char*, const vec<str>*, const vvec<double>*, const vvec<double>*");
	vvec2graph("./sin_cos.png", &vLabel, &vvecX, &vvecY);
}

void applicationSample3(){
	sstd::c2py<void> imgPath2mat_rRGB("./tmpDir", "pyFunctions", "imgPath2mat_rRGB", "void, ret mat_r<uint8>*, ret mat_r<uint8>*, ret mat_r<uint8>*, const char*");
	sstd::mat_r<uint8> imgR, imgG, imgB;
	imgPath2mat_rRGB(&imgR, &imgG, &imgB, "./sample.png");

	for(uint p=0; p<imgG.rows(); p++){
		for(uint q=0; q<imgG.cols(); q++){
			imgG(p, q) = sstd::round2even(0.5*((double)imgG(p, q)));
		}
	}
	
	sstd::c2py<void> mat_rRGB2img("./tmpDir", "pyFunctions", "mat_rRGB2img", "void, const char*, mat_r<uint8>*, mat_r<uint8>*, mat_r<uint8>*");
	mat_rRGB2img("./sample_reCombined.png", &imgR, &imgG, &imgB);
}

int main(){
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
	
	sample1();
//	benchMark1(); // Benchmarking is greatly affected by the number of import files on python side.
//	benchMark2(); // Benchmarking is greatly affected by the number of import files on python side.
	applicationSample1();
	applicationSample2();
	applicationSample3();
	
	printf("\n■ measureTime_stop----------------\n");
	sstd::measureTime_stop_print(timem);
	sstd::pauseIfWin32();
	return 0;
}







