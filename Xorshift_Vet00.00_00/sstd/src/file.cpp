#include "file.hpp"


#ifdef _WIN32
	inline bool sstd_file_fopen_win32(FILE** fp, const char*& fileName, const char*& mode){
		return (fopen_s(fp, fileName, mode)==NULL);
	}
#else
	inline bool sstd_file_fopen_linux(FILE** fp, const char*& fileName, const char*& mode){
		*fp = fopen(fileName, mode);
		return (*fp!=NULL);
	}
#endif
bool sstd::file::fopen(const char* fileName, const char* mode){
	#ifdef _WIN32
		return sstd_file_fopen_win32(&fp, fileName, mode);
	#else
		return sstd_file_fopen_linux(&this->fp, fileName, mode);
	#endif
}
void sstd_file_fclose(FILE*& stream){ fclose(stream); }

inline size_t sstd_file_fread(void*& ptr, const size_t& size, const size_t& nmemb, FILE*& fp){ return fread(ptr, size, nmemb, fp); }
size_t sstd::file::fread(void* ptr, const size_t& size, const size_t& nmemb){ return sstd_file_fread(ptr, size, nmemb, this->fp); }

inline size_t sstd_file_fwrite(const void*& ptr, const size_t& size, const size_t& nmemb, FILE*& fp){ return fwrite(ptr, size, nmemb, fp); }
size_t sstd::file::fwrite(const void* ptr, const size_t& size, const size_t& nmemb){ return sstd_file_fwrite(ptr, size, nmemb, this->fp); }

long sstd_file_fseek(FILE*& fp, const long& offset, const int& whence){ return fseek(fp, offset, whence); }
int sstd::file::fseek(const long& offset, const int& whence){ return sstd_file_fseek(this->fp, offset, whence); }

long sstd_file_ftell(FILE*& fp){ return ftell(fp); }
long sstd::file::ftell(){ return sstd_file_ftell(this->fp); }


/*
 * How to use this.
 *
 * printf("■ fopen\n");
 *
 * FILE* fp;
 * const char* FileName = "./test_fopen.txt";
 *
 * if(!sstd::fopen(&fp, FileName, "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
 *     // falied
 *     printf("false\n\n");
 * }else{
 *     // success
 *     printf("example.txt was made.\n\n");
 *     fwrite("abc", 3, 1, fp);
 * }
 * fclose(fp);
 */
