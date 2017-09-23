#pragma once

#include <stdio.h>
#include <vector>

#define sstd_useTypeDef
#include "./sstd/sstd.hpp"

std::string c2py_str(const char* rhs);
std::string c2py_int(int rhs);
std::string c2py_double(double rhs);

std::string c2py_vecInt(std::vector<int>& rhs);
std::string c2py_vecDouble(std::vector<double>& rhs);

std::string c2py_vvecInt(std::vector<std::vector<int>>& rhs);
std::string c2py_vvecDouble(std::vector<std::vector<double>>& rhs);
