#include "c2py.hpp"

std::string c2py_str(const char* rhs){ return sstd::ssprintf(" %s", rhs); }
std::string c2py_int(int rhs)        { return sstd::ssprintf(" %d", rhs); }
std::string c2py_double(double rhs)  { return sstd::ssprintf(" %lf", rhs); }

std::string c2py_vecInt(std::vector<int>& rhs){

	std::string lhs = sstd::ssprintf(" %d", rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		lhs += sstd::ssprintf(" %d", rhs[i]);
	}
	return lhs;
}
std::string c2py_vecDouble(std::vector<double>& rhs){

	std::string lhs = sstd::ssprintf(" %d", rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		lhs += sstd::ssprintf(" %lf", rhs[i]);
	}
	return lhs;
}

std::string c2py_vvecInt(std::vector<std::vector<int>>& rhs){

	std::string lhs = sstd::ssprintf(" %d", rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		lhs += sstd::ssprintf(" %d", rhs[i].size());
		for(uint i=0; i<rhs[i].size(); i++){
			lhs += sstd::ssprintf(" %d", rhs[i]);
		}
	}
	return lhs;
}
std::string c2py_vvecDouble(std::vector<std::vector<double>>& rhs){

	std::string lhs = sstd::ssprintf(" %d", rhs.size());
	for(uint p=0; p<rhs.size(); p++){
		lhs += sstd::ssprintf(" %d", rhs[p].size());
		for(uint q=0; q<rhs[p].size(); q++){
			lhs += sstd::ssprintf(" %lf", rhs[p][q]);
		}
	}
	return lhs;
}
