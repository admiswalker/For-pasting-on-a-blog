#include "typeDef.h"
#include <string>
#include <vector>

namespace sstd{
	std::string              readAll(const char*        pReadFile);
	std::string              readAll(const std::string&  readFile);
	std::string              readAll_withoutBOM(const char*        pReadFile);
	std::string              readAll_withoutBOM(const std::string&  readFile);
	std::vector<std::string> splitByLine(const std::string& str);
	
	std::vector<std::string> split(const char*        str, const char X);
	std::vector<std::string> split(const std::string& str, const char X);
	
	std::string              removeHeadSpace(const uchar* str);
	void                     removeTailSpace(std::string& str);
	std::string              removeSpace_of_HeadAndTail(const uchar* str);
	std::vector<std::string> removeSpace_of_HeadAndTail(const std::vector<std::string>& vec);
	
	bool strcmp(const char*        str1, const char*        str2);
	bool strcmp(const char*        str1, const std::string& str2);
	bool strcmp(const std::string& str1, const char*        str2);
	bool strcmp(const std::string& str1, const std::string& str2);
}

