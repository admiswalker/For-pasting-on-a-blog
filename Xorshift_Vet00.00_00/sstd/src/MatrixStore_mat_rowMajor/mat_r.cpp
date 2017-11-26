#include "./mat_r.hpp"

// print 関数の定義．
#define sstd_mat_r_print(Mat, rows, cols, OPTION1, OPTION2)\
	for(uint p=0; p<rows; p++){\
		uint q=0;\
		printf(OPTION1, Mat(p, q));\
		for(q++; q<cols; q++){\
			printf(OPTION2, Mat(p, q));\
		}\
		printf("\n");\
	}


// "% d", "% lf" のように，マイナスのためにスペース1つ分空ける．(符号なし整数についても，位置を合わせるためスペースを空けておく)
void sstd::print(const class sstd::mat_r<  char>& Mat){
	sstd_mat_r_print(((class sstd::mat_r<  char>&)Mat),
					 ((class sstd::mat_r<  char>&)Mat).rows(),
					 ((class sstd::mat_r<  char>&)Mat).cols(), "% d", "\t % d");
}
void sstd::print(const class sstd::mat_r< uchar>& Mat){
	sstd_mat_r_print(((class sstd::mat_r< uchar>&)Mat),
					 ((class sstd::mat_r< uchar>&)Mat).rows(),
					 ((class sstd::mat_r< uchar>&)Mat).cols(), "%u", "\t %u");
}
void sstd::print(const class sstd::mat_r<   int>& Mat){
	sstd_mat_r_print(((class sstd::mat_r<   int>&)Mat),
					 ((class sstd::mat_r<   int>&)Mat).rows(),
					 ((class sstd::mat_r<   int>&)Mat).cols(), "% d", "\t % d");
}
void sstd::print(const class sstd::mat_r<  uint>& Mat){
	sstd_mat_r_print(((class sstd::mat_r<  uint>&)Mat),
					 ((class sstd::mat_r<  uint>&)Mat).rows(),
					 ((class sstd::mat_r<  uint>&)Mat).cols(), "%u", "\t %u"); // "%u" はエラーが出るので空けない．
}
void sstd::print(const class sstd::mat_r< float>& Mat){
	sstd_mat_r_print(((class sstd::mat_r< float>&)Mat),
					 ((class sstd::mat_r< float>&)Mat).rows(),
					 ((class sstd::mat_r< float>&)Mat).cols(), "% f", "\t % f");
}
void sstd::print(const class sstd::mat_r<double>& Mat){
	sstd_mat_r_print(((class sstd::mat_r<double>&)Mat),
					 ((class sstd::mat_r<double>&)Mat).rows(),
					 ((class sstd::mat_r<double>&)Mat).cols(), "% lf", "\t % lf");
}

// for sstd::printn(); and sstd::printn_all();.
void sstd::for_printn(const class sstd::mat_r  <char>& tMat){ printf(" = \n");sstd::print(tMat); }
void sstd::for_printn(const class sstd::mat_r <uchar>& tMat){ printf(" = \n");sstd::print(tMat); }
void sstd::for_printn(const class sstd::mat_r   <int>& tMat){ printf(" = \n");sstd::print(tMat); }
void sstd::for_printn(const class sstd::mat_r  <uint>& tMat){ printf(" = \n");sstd::print(tMat); }
void sstd::for_printn(const class sstd::mat_r <float>& tMat){ printf(" = \n");sstd::print(tMat); }
void sstd::for_printn(const class sstd::mat_r<double>& tMat){ printf(" = \n");sstd::print(tMat); }
