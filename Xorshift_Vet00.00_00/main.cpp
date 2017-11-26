#define use_sstd_measureTime
#include <sstd/sstd.hpp>

bool isFullPeriod(uint N, uint a, uint b, uint c){

	//std::vector<uint64> divs = sstd::divisor(4294967296-1); // Below line returns the same result of this line, but took a little time to run everytime and takes a little heavy memory (about 2 GByte).
	std::vector<uint64> divs = {1, 3, 5, 15, 17, 51, 85, 255, 257, 771, 1285, 3855, 4369, 13107, 21845, 65535, 65537, 196611, 327685, 983055, 1114129, 3342387, 5570645, 16711935, 16843009, 50529027, 84215045, 252645135, 286331153, 858993459, 1431655765, 4294967295};

	sstd::bmat I  = sstd::eye(N, N);
	sstd::bmat La = sstd::LxShiftMat(N, a);
	sstd::bmat Rb = sstd::RxShiftMat(N, b);
	sstd::bmat Lc = sstd::LxShiftMat(N, c);
	sstd::bmat T = (I + La)*(I + Rb)*(I + Lc);
//	sstd::printn(T);
	
	for(uint i=0; i<divs.size()-1; i++){
		sstd::bmat Tp = T^(divs[i]); // XORSHIFT
		if(Tp==I){ return false; }
	}
	sstd::bmat Tp = T^(divs[divs.size()-1]); // XORSHIFT
	if(Tp==I){ return true;
	}  else  { return false; }
}
int main(){
	printf("This code calculates the table of \"George Marsaglia [2003], Xorshift RNGs, page.2\".\n");
	
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);

	uint N = 32;
	uint num=0;
	printf("  a,  b,  c\n");
	for(uint a=0; a<N; a++){
		for(uint b=0; b<N; b++){
			for(uint c=0; c<N; c++){
				if(a<c && isFullPeriod(N, a, b, c)){
					printf("|%2u, %2u, %2u", a, b, c);
					num++;
					if(num%9==0){ printf("|\n"); }
				}
			}
		}
	}
	printf("\n");

	printf("■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem);
	return 0;
}

/*
$ ./exe
This code calculates the table of "George Marsaglia [2003], Xorshift RNGs, page.2".
■ measureTime_start---------------

  a,  b,  c
| 1,  3, 10| 1,  5, 16| 1,  5, 19| 1,  9, 29| 1, 11,  6| 1, 11, 16| 1, 19,  3| 1, 21, 20| 1, 27, 27|
| 2,  5, 15| 2,  5, 21| 2,  7,  7| 2,  7,  9| 2,  7, 25| 2,  9, 15| 2, 15, 17| 2, 15, 25| 2, 21,  9|
| 3,  1, 14| 3,  3, 26| 3,  3, 28| 3,  3, 29| 3,  5, 20| 3,  5, 22| 3,  5, 25| 3,  7, 29| 3, 13,  7|
| 3, 23, 25| 3, 25, 24| 3, 27, 11| 4,  3, 17| 4,  3, 27| 4,  5, 15| 5,  3, 21| 5,  7, 22| 5,  9,  7|
| 5,  9, 28| 5,  9, 31| 5, 13,  6| 5, 15, 17| 5, 17, 13| 5, 21, 12| 5, 27,  8| 5, 27, 21| 5, 27, 25|
| 5, 27, 28| 6,  1, 11| 6,  3, 17| 6, 17,  9| 6, 21,  7| 6, 21, 13| 7,  1,  9| 7,  1, 18| 7,  1, 25|
| 7, 13, 25| 7, 17, 21| 7, 25, 12| 7, 25, 20| 8,  7, 23| 8,  9, 23| 9,  5, 14| 9,  5, 25| 9, 11, 19|
| 9, 21, 16|10,  9, 21|10,  9, 25|11,  7, 12|11,  7, 16|11, 17, 13|11, 21, 13|12,  9, 23|13,  3, 17|
|13,  3, 27|13,  5, 19|13, 17, 15|14,  1, 15|14, 13, 15|15,  1, 29|17, 15, 20|17, 15, 23|17, 15, 26|

■ measureTime_stop----------------
--------------------------------
 Execution time:     9. 465 sec
--------------------------------
*/


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
