#pragma once

#include <vector>

namespace sstd{
	// 最近接偶数への丸め (round to the nearest even; RN)
	float  round2even(float n);
	double round2even(double n);

	// 最近接奇数への丸め (round to the nearest odd; RO)
	float  round2odd(float n);
	double round2odd(double n);

	float  sum    (const std::vector<float>& rhs);
	float  sum_abs(const std::vector<float>& rhs);
	float  ave    (const std::vector<float>& rhs); // 平均値: average
	float  med    (      std::vector<float>  rhs); // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	float  mod    (const std::vector<float>& rhs); // 最頻値: mode
	float  max    (const std::vector<float>& rhs);
	float  max_abs(const std::vector<float>& rhs);
	float  min    (const std::vector<float>& rhs);
	float  min_abs(const std::vector<float>& rhs);
	float  var    (const std::vector<float>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	float  var_p  (const std::vector<float>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	float  stdev  (const std::vector<float>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	float  stdev_p(const std::vector<float>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	double sum    (const std::vector<double>& rhs);
	double sum_abs(const std::vector<double>& rhs);
	double ave    (const std::vector<double>& rhs); // 平均値: average
	double med    (      std::vector<double>  rhs); // 中央値: median // copy rhs // If rhs.size () is even, average of the two median values is returned.
//	double mod    (const std::vector<double>& rhs); // 最頻値: mode
	double max    (const std::vector<double>& rhs);
	double max_abs(const std::vector<double>& rhs);
	double min    (const std::vector<double>& rhs);
	double min_abs(const std::vector<double>& rhs);
	double var    (const std::vector<double>& rhs); // 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
	double var_p  (const std::vector<double>& rhs); // 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
	double stdev  (const std::vector<double>& rhs); // 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
	double stdev_p(const std::vector<double>& rhs); // 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )

	// get a list of prime number under rhs.
	std::vector<uint64> prime(uint64 rhs);
	struct fact{
		uint64 prime;
		uint64 num;
	};
	std::vector<struct fact> factor(uint64 rhs); // prime factorization
	std::vector<uint64> divisor(uint64 rhs);       // get a list of all of the divisors.

	uint8  pow(uint8  base, uint8  exp);
	uint16 pow(uint16 base, uint16 exp);
	uint32 pow(uint32 base, uint32 exp);
	uint64 pow(uint64 base, uint64 exp);
}
