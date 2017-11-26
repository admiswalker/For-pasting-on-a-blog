#include "./mat.hpp"

// print 関数の定義．
#define sstd_mat_print(mat, rows, cols, OPTION1, OPTION2)\
	for(uint p=0; p<rows; p++){\
		uint q=0;\
		printf(OPTION1, mat(p, q));\
		for(q++; q<cols; q++){\
			printf(OPTION2, mat(p, q));\
		}\
		printf("\n");\
	}


// "% d", "% lf" のように，マイナスのためにスペース1つ分空ける．(符号なし整数についても，位置を合わせるためスペースを空けておく)
void sstd::print(const class sstd::mat<  char>& mat){
	sstd_mat_print(((class sstd::mat<  char>&)mat),
				   ((class sstd::mat<  char>&)mat).rows(),
				   ((class sstd::mat<  char>&)mat).cols(), "% d", "\t % d");
}
void sstd::print(const class sstd::mat< uchar>& mat){
	sstd_mat_print(((class sstd::mat< uchar>&)mat),
				   ((class sstd::mat< uchar>&)mat).rows(),
				   ((class sstd::mat< uchar>&)mat).cols(), "%u", "\t %u");
}
void sstd::print(const class sstd::mat<   int>& mat){
	sstd_mat_print(((class sstd::mat<   int>&)mat),
				   ((class sstd::mat<   int>&)mat).rows(),
				   ((class sstd::mat<   int>&)mat).cols(), "% d", "\t % d");
}
void sstd::print(const class sstd::mat<  uint>& mat){
	sstd_mat_print(((class sstd::mat<  uint>&)mat),
				   ((class sstd::mat<  uint>&)mat).rows(),
				   ((class sstd::mat<  uint>&)mat).cols(), "%u", "\t %u"); // "%u" はエラーが出るので空けない．
}
void sstd::print(const class sstd::mat< float>& mat){
	sstd_mat_print(((class sstd::mat< float>&)mat),
				   ((class sstd::mat< float>&)mat).rows(),
				   ((class sstd::mat< float>&)mat).cols(), "% f", "\t % f");
}
void sstd::print(const class sstd::mat<double>& mat){
	sstd_mat_print(((class sstd::mat<double>&)mat),
				   ((class sstd::mat<double>&)mat).rows(),
				   ((class sstd::mat<double>&)mat).cols(), "% lf", "\t % lf");
}

// for sstd::printn(); and sstd::printn_all();.
void sstd::for_printn(const class sstd::mat  <char>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat <uchar>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat   <int>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat  <uint>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat <float>& mat){ printf(" = \n");sstd::print(mat); }
void sstd::for_printn(const class sstd::mat<double>& mat){ printf(" = \n");sstd::print(mat); }
