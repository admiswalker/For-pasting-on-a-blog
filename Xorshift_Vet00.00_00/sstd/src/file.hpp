#pragma once

#include <stdio.h>


void sstd_file_fclose(FILE*& stream);


namespace sstd{ class file; }
class sstd::file{
private:
public:
	FILE* fp;
	file(){ fp=0; }
//	file(const char*& fileName, const char*& mode){ fopen(&fp, fileName, mode); } // コンストラクタでは，fopen の失敗を検知できないので，これは実装しないように!!!
	~file(){ if(fp!=0){ sstd_file_fclose(fp); } }
	
	bool fopen(const char* fileName, const char* mode);
	size_t fread(void* ptr, const size_t& size, const size_t& nmemb);
	size_t fwrite(const void* ptr, const size_t& size, const size_t& nmemb);
	int fseek(const long& offset, const int& whence);
	long ftell();
};



/*
namespace sstd{
	bool fopen(FILE** fp, const char* FileName, const char* mode);
}
*/

/*
 * How to use this.
 * 
 * FILE* fp;
 * const char* FileName = "./example.txt";
 * if(!sstd::fopen(&fp, FileName, "wb")){ // Enable to open file by the same code between VSC++ and GCC.
 *     // falied
 *     printf("false\n\n");
 * }else{
 *     // success
 *     printf("example.txt was made.\n\n");
 *     fwrite("abc", 3, 1, fp);
 * }
 * fclose(fp);
 */
