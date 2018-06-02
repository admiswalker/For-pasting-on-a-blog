#include "bmat_multi.hpp"

void bmat_power_calculation(class sstd::bmat& base, mpz_class& exponent){

	for(; exponent>(mpz_class)0; exponent>>=1){
		if((exponent & (mpz_class)1)!=(mpz_class)0){
			if(exponent==(mpz_class)1){ return; }
			break;
		}
		base = sstd::mul(base, base);
	}
	sstd::bmat buf = base;
	buf = sstd::mul(buf, buf);
	exponent>>=1;

	for(;;exponent>>=1){
		if((exponent & (mpz_class)1)!=(mpz_class)0){
			base = sstd::mul(base, buf);
			if(exponent==(mpz_class)1){ return; }
		}
		buf = sstd::mul(buf, buf);
	}
}
class sstd::bmat sstd::pow(class sstd::bmat base, mpz_class exponent){

	if(exponent==(mpz_class)0){ return eye(base.rows(), base.cols()); }
	bmat_power_calculation(base, exponent);
	return base;
}
void sstd::pow_myself(class sstd::bmat& base, mpz_class exponent){

	if(exponent==(mpz_class)0){ base=eye(base.rows(), base.cols()); return; }
	bmat_power_calculation(base, exponent);
}

