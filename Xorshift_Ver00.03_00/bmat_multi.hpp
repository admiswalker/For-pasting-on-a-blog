#pragma once
#include <sstd/sstd.hpp>
#include <gmp.h>
#include <gmpxx.h> // for C++

namespace sstd{
//	pow_multi
	class sstd::bmat pow(class sstd::bmat base, mpz_class exponent); // base^{exponent}
	void pow_myself(class sstd::bmat& base, mpz_class exponent);
};

