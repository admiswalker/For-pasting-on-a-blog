#define use_sstd_measureTime

#include <sstd/sstd.hpp>

#include <gmp.h>
#include <gmpxx.h> // for C++
#include "bmat_multi.hpp"

//-------------------------------------------------------------------------
void get_prime_factor_Of_2_32m1(){
	uint64 fact_num = sstd::pow((uint64)2, (uint64)32) - (uint64)1;
	std::vector<struct sstd::fact> factList = sstd::factor(fact_num);
	sstd::print(factList);
	
// $ ./exe
// ■ measureTime_start---------------
// 
// 4294967295 = 3^1 + 5^1 + 17^1 + 257^1 + 65537^1 // 4294967295 = 2^32 -1
// 
// ■ measureTime_stop----------------
// --------------------------------
//  Execution time:    72. 871 sec
// --------------------------------
}
void cal_divsOf_2_64m1(){
	// calculating divisors of 2^64-1
	// >> 2^64 - 1 = 3 * 5 * 17 * 257 * 641 * 65537 * 6700417
	// struct fact{
	//     uint64 prime;
	//     uint64 num;
	// };
	std::vector<struct sstd::fact> factorList = {{3,1},{5,1},{17,1},{257,1},{641,1},{65537,1},{6700417,1}};
	std::vector<uint64> divs = sstd::divisor(factorList);
	printf("Divisors of 2^64-1 is \n"); sstd::print(divs);
}
//-------------------------------------------------------------------------
bool isFullPeriod(sstd::bmat& T, const sstd::bmat& I, std::vector<uint64>& divs){
	for(uint i=0; i<divs.size()-1; i++){
		sstd::bmat Tp = T^(divs[i]); // XORSHIFT
		if(Tp==I){ return false; }
	}
	sstd::bmat Tp = T^(divs[divs.size()-1]); // XORSHIFT
	if(Tp==I){ return true;
	}  else  { return false; }
}
bool isFullPeriod(sstd::bmat& T, const sstd::bmat& I, std::vector<mpz_class>& divs){
	for(uint i=0; i<divs.size()-1; i++){
		sstd::bmat Tp = sstd::pow(T, divs[i]); // XORSHIFT multi
		if(Tp==I){ return false; }
	}
	sstd::bmat Tp = sstd::pow(T, divs[divs.size()-1]); // XORSHIFT multi
	if(Tp==I){ return true;
	}  else  { return false; }
}
//-------------------------------------------------------------------------
bool isFullPeriod_LRL(std::vector<uint64>& divs, uint N, uint a, uint b, uint c){

	sstd::bmat I  = sstd::eye(N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Lc = sstd::LxShiftMat(N, c);
	sstd::bmat T = (I + La)*(I + Rb)*(I + Lc);
//	sstd::printn(T);

	return isFullPeriod(T, I, divs);
}
void T_LRL(std::vector<uint64>& divs, uint N){
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod_LRL(divs, N, a, b, c)){
//				if(isFullPeriod_LRL(divs, N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
bool isFullPeriod_LR(std::vector<uint64>& divs, uint N, uint a, uint b){
	sstd::bmat I  = sstd::eye(N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
//	sstd::bmat T = (I + Rb)*(I + La);
	sstd::bmat T = (I + La)*(I + Rb);
//	sstd::printn(T);
	
	return isFullPeriod(T, I, divs);
}
void T_LR(std::vector<uint64>& divs, uint N){
	uint num=0;
	printf("  a,  b\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			if(isFullPeriod_LR(divs, N, a, b)){
				printf("|%2u, %2u", a, b);
				num++;
				if(num%9==0){ printf("|\n"); }
			}
		}
	}
}
//-------------------------------------------------------------------------
bool isFullPeriod_64(std::vector<uint64>& divs, uint N, uint a, uint b, uint c){
	sstd::bmat Z  = sstd::zeros(N, N);
	sstd::bmat I  = sstd::eye  (N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Rc = sstd::RxShiftMat(N, c);
	sstd::bmat T = Z << (I + La)*(I + Rb) &&
		           I <<      (I + Rc)     ;
//	sstd::printn(T);
	
	return isFullPeriod(T, sstd::eye(64, 64), divs);
}
void matT_64(std::vector<uint64>& divs){
	uint N=32;
	
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod_64(divs, N, a, b, c)){
//				if(isFullPeriod_64(divs, N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
bool isFullPeriod_96(std::vector<mpz_class>& divs, uint N, uint a, uint b, uint c){
	sstd::bmat Z  = sstd::zeros(N, N);
	sstd::bmat I  = sstd::eye  (N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Rc = sstd::RxShiftMat(N, c);
	sstd::bmat T = Z << Z << (I + La)*(I + Rb) &&
		           I << Z <<         Z         &&
		           Z << I <<      (I + Rc)     ;
//	sstd::printn(T);
	
	return isFullPeriod(T, sstd::eye(96, 96), divs);
}
void matT_96(std::vector<mpz_class>& divs96){
	uint N=32;
	
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod_96(divs96, N, a, b, c)){
//				if(isFullPeriod_96(divs, N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
bool isFullPeriod_128(std::vector<mpz_class>& divs, uint N, uint a, uint b, uint c){
	sstd::bmat Z  = sstd::zeros(N, N);
	sstd::bmat I  = sstd::eye  (N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Rc = sstd::RxShiftMat(N, c);
	sstd::bmat T = Z << Z << Z << (I + La)*(I + Rb) &&
		           I << Z << Z <<         Z         &&
		           Z << I << Z <<         Z         &&
		           Z << Z << I <<      (I + Rc)     ;
//	sstd::printn(T);
	
	return isFullPeriod(T, sstd::eye(128, 128), divs);
}
void matT_128(std::vector<mpz_class>& divs){
	uint N=32;
	
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod_128(divs, N, a, b, c)){
//				if(isFullPeriod_128(divs, N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
bool isFullPeriod_160(std::vector<mpz_class>& divs, uint N, uint a, uint b, uint c){
	sstd::bmat Z  = sstd::zeros(N, N);
	sstd::bmat I  = sstd::eye  (N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Rc = sstd::RxShiftMat(N, c);
	sstd::bmat T = Z << Z << Z << Z << (I + La)*(I + Rb) &&
		           I << Z << Z << Z <<         Z         &&
		           Z << I << Z << Z <<         Z         &&
		           Z << Z << I << Z <<         Z         &&
		           Z << Z << Z << I <<      (I + Rc)     ;
//	sstd::printn(T);
	
	return isFullPeriod(T, sstd::eye(160, 160), divs);
}
void matT_160(std::vector<mpz_class>& divs){
	uint N=32;
	
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod_160(divs, N, a, b, c)){
//				if(isFullPeriod_160(divs, N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
void print_vecMulti(std::vector<mpz_class>& rhs){
	printf("[ ");
	for(uint i=0; i<rhs.size(); i++){ printf("%s ", rhs[i].get_str().c_str()); }
	printf("]\n");
}
//-------------------------------------------------------------------------
int main(){
//	printf("This code calculates the table of \"George Marsaglia [2003], Xorshift RNGs, page.2\".\n");
	
//	get_prime_factor_Of_2_32m1();
//	cal_divsOf_2_64m1(); // 2^64-1 の約数を全て計算する
	
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);

	// calculate divisors of 2^32-1.
//	std::vector<uint64> divs32 = sstd::divisor(4294967296-1); // Below line returns the same result of this line, but took a little time to run everytime and takes a little heavy memory (about 2 GByte).
//	std::vector<uint64> divs32 = {1, 3, 5, 15, 17, 51, 85, 255, 257, 771, 1285, 3855, 4369, 13107, 21845, 65535, 65537, 196611, 327685, 983055, 1114129, 3342387, 5570645, 16711935, 16843009, 50529027, 84215045, 252645135, 286331153, 858993459, 1431655765, 4294967295};
	std::vector<uint64> divs32 = {1ull*5ull*17ull*257ull*65537ull,
								  3ull*1ull*17ull*257ull*65537ull,
								  3ull*5ull* 1ull*257ull*65537ull,
								  3ull*5ull*17ull*  1ull*65537ull,
								  3ull*5ull*17ull*257ull*    1ull,
								  
								  3ull*5ull*17ull*257ull*65537ull};
	
	// calculate divisors of 2^64-1.
//	std::vector<uint64> divs64 = sstd::divisor(18446744073709551616-1); // impossible in this way // below is calculated by "void cal_divsOf_2_64m1();".
//	std::vector<uint64> divs64 = {1ull, 3ull, 5ull, 15ull, 17ull, 51ull, 85ull, 255ull, 257ull, 641ull, 771ull, 1285ull, 1923ull, 3205ull, 3855ull, 4369ull, 9615ull, 10897ull, 13107ull, 21845ull, 32691ull, 54485ull, 65535ull, 65537ull, 163455ull, 164737ull, 196611ull, 327685ull, 494211ull, 823685ull, 983055ull, 1114129ull, 2471055ull, 2800529ull, 3342387ull, 5570645ull, 6700417ull, 8401587ull, 14002645ull, 16711935ull, 16843009ull, 20101251ull, 33502085ull, 42007935ull, 42009217ull, 50529027ull, 84215045ull, 100506255ull, 113907089ull, 126027651ull, 210046085ull, 252645135ull, 286331153ull, 341721267ull, 569535445ull, 630138255ull, 714156689ull, 858993459ull, 1431655765ull, 1708606335ull, 1722007169ull, 2142470067ull, 3570783445ull, 4294967295ull, 4294967297ull, 5166021507ull, 8610035845ull, 10712350335ull, 10796368769ull, 12884901891ull, 21474836485ull, 25830107535ull, 29274121873ull, 32389106307ull, 53981843845ull, 64424509455ull, 73014444049ull, 87822365619ull, 146370609365ull, 161945531535ull, 183538269073ull, 219043332147ull, 365072220245ull, 439111828095ull, 439125228929ull, 550614807219ull, 917691345365ull, 1095216660735ull, 1103806595329ull, 1317375686787ull, 2195626144645ull, 2753074036095ull, 3311419785987ull, 5519032976645ull, 6586878433935ull, 7465128891793ull, 16557098929935ull, 18764712120593ull, 22395386675379ull, 37325644458965ull, 56294136361779ull, 93823560602965ull, 111976933376895ull, 112855183834753ull, 281470681808895ull, 281479271743489ull, 338565551504259ull, 564275919173765ull, 844437815230467ull, 1407396358717445ull, 1692827757521295ull, 1918538125190801ull, 4222189076152335ull, 4785147619639313ull, 5755614375572403ull, 9592690625954005ull, 14355442858917939ull, 23925738098196565ull, 28778071877862015ull, 71777214294589695ull, 72340172838076673ull, 217020518514230019ull, 361700864190383365ull, 1085102592571150095ull, 1229782938247303441ull, 3689348814741910323ull, 6148914691236517205ull, 18446744073709551615ull}; // Below line is able to get same result.
	std::vector<uint64> divs64 = {1ull*5ull*17ull*257ull*641ull*65537ull*6700417ull,
								  3ull*1ull*17ull*257ull*641ull*65537ull*6700417ull,
								  3ull*5ull* 1ull*257ull*641ull*65537ull*6700417ull,
								  3ull*5ull*17ull*  1ull*641ull*65537ull*6700417ull,
								  3ull*5ull*17ull*257ull*  1ull*65537ull*6700417ull,
								  3ull*5ull*17ull*257ull*641ull*    1ull*6700417ull,
								  3ull*5ull*17ull*257ull*641ull*65537ull*      1ull,
								  
								  3ull*5ull*17ull*257ull*641ull*65537ull*6700417ull};
	
	mpz_class forCast = 1;
	//$ factor 2^128-1 = 79228162514264337593543950336 - 1 = 79228162514264337593543950335 = 3x3x5x7x13x17x97x193x241x257x673x65537x22253377
	std::vector<mpz_class> divs96 = {forCast * 1*1*5*7*13*17*97*193*241*257*673*65537*22253377,
									 forCast * 3*1*5*7*13*17*97*193*241*257*673*65537*22253377,
									 forCast * 3*3*1*7*13*17*97*193*241*257*673*65537*22253377,
									 forCast * 3*3*5*1*13*17*97*193*241*257*673*65537*22253377,
									 forCast * 3*3*5*7* 1*17*97*193*241*257*673*65537*22253377,
									 forCast * 3*3*5*7*13* 1*97*193*241*257*673*65537*22253377,
									 forCast * 3*3*5*7*13*17* 1*193*241*257*673*65537*22253377,
									 forCast * 3*3*5*7*13*17*97*  1*241*257*673*65537*22253377,
									 forCast * 3*3*5*7*13*17*97*193*  1*257*673*65537*22253377,
									 forCast * 3*3*5*7*13*17*97*193*241*  1*673*65537*22253377,
									 forCast * 3*3*5*7*13*17*97*193*241*257*  1*65537*22253377,
									 forCast * 3*3*5*7*13*17*97*193*241*257*673*    1*22253377,
									 forCast * 3*3*5*7*13*17*97*193*241*257*673*65537*       1,
									 
									 forCast * 3*3*5*7*13*17*97*193*241*257*673*65537*22253377};
	
	// $ factor 2^128-1 = 340282366920938463463374607431768211456-1 = 340282366920938463463374607431768211455 = 3x5x17x257x641x65537x274177x6700417x67280421310721
	std::vector<mpz_class> divs128 = {forCast * 1*5*17*257*641*65537*274177*6700417*67280421310721,
									  forCast * 3*1*17*257*641*65537*274177*6700417*67280421310721,
									  forCast * 3*5* 1*257*641*65537*274177*6700417*67280421310721,
									  forCast * 3*5*17*  1*641*65537*274177*6700417*67280421310721,
									  forCast * 3*5*17*257*  1*65537*274177*6700417*67280421310721,
									  forCast * 3*5*17*257*641*    1*274177*6700417*67280421310721,
									  forCast * 3*5*17*257*641*65537*     1*6700417*67280421310721,
									  forCast * 3*5*17*257*641*65537*274177*      1*67280421310721,
									  forCast * 3*5*17*257*641*65537*274177*6700417*             1,
									  
									  forCast * 3*5*17*257*641*65537*274177*6700417*67280421310721};
	
	// $ factor 2^160-1 = 1461501637330902918203684832716283019655932542976-1 = 1461501637330902918203684832716283019655932542975 = 3x5x5x11x17x31x41x257x61681x65537x414721x4278255361x44479210368001
	std::vector<mpz_class> divs160 = {forCast * 1*5*5*11*17*31*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*1*1*11*17*31*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*1*11*17*31*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5* 1*17*31*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11* 1*31*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17* 1*41*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31* 1*257*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31*41*  1*61681*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31*41*257*    1*65537*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31*41*257*61681*    1*414721*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31*41*257*61681*65537*     1*4278255361*44479210368001,
									  forCast * 3*5*5*11*17*31*41*257*61681*65537*414721*         1*44479210368001,
									  forCast * 3*5*5*11*17*31*41*257*61681*65537*414721*4278255361*             1,
									  
									  forCast * 3*5*5*11*17*31*41*257*61681*65537*414721*4278255361*44479210368001};
	
	//*
	printf("□ calculate LR 32bits\n");
	T_LR(divs32, 32); printf("\n");
	//*/
	
	//*
	printf("□ calculate LR 64bits\n");
	T_LR(divs64, 64); printf("\n");
	//*/
	
	//*
	printf("□ calculate LRL 32bits\n");
	T_LRL(divs32, 32); printf("\n");
	//*/
	
	//*
	printf("□ calculate LRL 64bits\n");
	T_LRL(divs64, 64); printf("\n");
	//*/
	
	//*
	printf("□ calculate T = (0 << A) && (I << B)\n");
	matT_64(divs64); printf("\n");
	//*/

	//*
	printf("□ calculate T = Z << Z << (I + La)*(I + Rb)  &&  I << Z << Z  &&  Z << I << (I + Rc)\n");
	matT_96(divs96); printf("\n");
	//*/
	
	//*
	printf("□ calculate T = Z << Z << Z << (I + La)*(I + Rb)  &&  I << Z << Z << Z  &&  Z << I << Z << Z  &&  Z << Z << I << (I + Rc)\n");
	matT_128(divs128); printf("\n");
	//*/

	//*
	printf("□ calculate n=160\n");
	matT_160(divs160); printf("\n");
	//*/
	
	printf("\n■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem);
	return 0;
}


/*
void TEST_bmat(){
	// init test
	sstd::bmat bMat4x4(4, 4);
	sstd::eye(bMat4x4);   sstd::printn(bMat4x4);
	sstd::ones(bMat4x4);  sstd::printn(bMat4x4);
	sstd::zeros(bMat4x4); sstd::printn(bMat4x4);
	sstd::print(bMat4x4);     // for print debug
	sstd::print_all(bMat4x4); // for bmat debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

	sstd::bmat bonded8x8 = sstd::zeros(4, 4) << sstd::eye(4, 4) &&
                           sstd::ones(4, 4)  << sstd::eye(4, 4);
	sstd::printn(bonded8x8);
	
	sstd::bmat bMat8x9 = sstd::eye(8, 9);
	sstd::printn(bMat8x9);
	sstd::print_all(bMat8x9); // for debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

	sstd::printn(bMat8x9.rows());
	sstd::printn(bMat8x9.cols());
	printf("\n");

	// access to elements
	sstd::bmat M = sstd::zeros(4, 4);
	M(0, 1) = 1;
	M(1, 2) = 1;
	M(2, 3) = 1;
	M(3, 4) = 1;
	sstd::printn(M);
	sstd::printn(M*M); // multi

	// tranpose
	sstd:: bmat M_tr = M; // copy
	sstd::Tr_myself(M_tr);
	sstd::printn(M_tr);
	sstd::printn(sstd::Tr(M));

	// pow test
	sstd::bmat L1 = sstd::LxShiftMat(16, 1);
	sstd::printn(L1);
	sstd::bmat L7 = L1^((uint64)7); // この計算は後で確認して！！！
	sstd::printn(L7);

	uint N = 32;
	sstd::bmat I(N, N); sstd::eye(I);
	sstd::bmat L15 = sstd::LxShiftMat(N, 15);
	sstd::bmat R17 = sstd::RxShiftMat(N, 17);
	sstd::bmat L13 = sstd::LxShiftMat(N, 13);
	sstd::bmat T = (I + L15)*(I + R17)*(I + L13);
	sstd::printn(T);
	sstd::bmat Tp = T^(4294967296-1); // XORSHIFT
	sstd::printn(Tp);
	
	printf("Tp==I: "); if(Tp==I){ printf("true\n");  }else{ printf("false\n"); }
	printf("Tp!=I: "); if(Tp!=I){ printf("true\n");  }else{ printf("false\n"); }

	printf("I(0, 0): "); if(I(0, 0)){printf("true\n");}else{printf("false\n");}
	printf("I(1, 0): "); if(I(1, 0)){printf("true\n");}else{printf("false\n");}
	printf("I(0, 1): "); if(I(0, 1)){printf("true\n");}else{printf("false\n");}
	printf("I(1, 1): "); if(I(1, 1)){printf("true\n");}else{printf("false\n");}

	I = sstd::eye(4, 4);
	sstd::printn(I);
	I(0, 0) = false;
	I(1, 1) = false;
	I(0, 1) = 1;
	I(0, 2) = 1000;	// "I(0, 2) = 1000;" に同じ．

//	I(1, 0) = I(2, 0) = I(2, 2);
	I(1, 0) = I(2, 0) = I(2, 2) = true;

	sstd::printn(I);

	sstd::printn(I);
	I[0] = false;
	I[1] = true;

	I[2] = I[3] = I[15];
	I[4] = I[5] = true;

	I[6] = I[7] = I(2, 2);
	I(2, 2) = I[0];

	sstd::printn(I);
}
*/
