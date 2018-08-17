#include <sstd/sstd.hpp>

int main(){
	std::vector<double> a={1, 2, 3}, b={4, 5, 6};
	sstd::printn(a);
	a*=4;                 // same as "for(int i=0; i<a.size(); i++){ a[i]*=4; }"
	sstd::printn(a);
	printf("\n");
	
	a<<=b;                // same as "a.insert(a.end(), b.begin(), b.end());".
	sstd::printn(a);
	a<<=7.0;              // same as "a.push_back(7.0);".
	sstd::printn(a);
	sstd::printn(a<<8.0); // same as "{ std::vector<double> tmp(a.size()+1); for(uint p=0;p<a.size();p++){tmp[p]=a[p];} tmp[a.size()]=8.0; sstd::printn(tmp); }"
	
	return 0;
}

