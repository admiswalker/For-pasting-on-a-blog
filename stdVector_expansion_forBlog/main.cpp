#include <sstd/sstd.hpp>

int main(){
	std::vector<double> a={1, 2, 3};
	sstd::printn(a);
	a*=4;
	sstd::printn(a);
	
	return 0;
}

