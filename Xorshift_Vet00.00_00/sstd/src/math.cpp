﻿#include "typeDef.h"
#include "math.hpp"
#include <stdlib.h> // abs()
#include <cmath> // ceil(), floor()
#include <algorithm> // for std::sort

// 最近接偶数への丸め (round to the nearest even; RN)
float  sstd::round2even(float n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }
double sstd::round2even(double n){ return std::ceil((n - 0.5) / 2) + std::floor((n + 0.5) / 2); }

// 最近接奇数への丸め (round to the nearest odd; RO)
float  sstd::round2odd(float n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }
double sstd::round2odd(double n){ return std::ceil((n + 0.5) / 2) + std::floor((n - 0.5) / 2); }

// Kahan summation algorithm
// lhs = KahanSum(std::vector<Type>& rhs)
#define KAHAN_SUM_i(Type, lhs, rhs_i, rhs_len)\
	Type del=0;\
	for(uint i=0; i<rhs_len; i++){\
		Type r1=rhs_i-del;\
		Type r2=lhs+r1;\
		del=(r2-lhs)-r1;\
		lhs=r2;\
	}

float sstd::sum(const std::vector<float>& rhs){
	float lhs=0;
	KAHAN_SUM_i(float, lhs, rhs[i], rhs.size());
	return lhs;
}
float sstd::sum_abs(const std::vector<float>& rhs){
	float lhs=0;
	KAHAN_SUM_i(float, lhs, abs(rhs[i]), rhs.size());
	return lhs;
}
float sstd::ave(const std::vector<float>& rhs){
	return sstd::sum(rhs)/rhs.size();
}
float sstd::med(std::vector<float> rhs){ // copy rhs
	if(rhs.size()==0){ return (float)0.0; }
	std::sort(rhs.begin(), rhs.end());
	uint size_div2 = rhs.size() / 2;
	uint size_mod  = rhs.size() - 2*size_div2; // same as "rhs.size()%2"
	if(size_mod==0){ return (rhs[size_div2-1] + rhs[size_div2])/(float)2.0; // rhs.size() is even number
	}     else     { return rhs[size_div2]; }                               // rhs.size() is odd number
}
float sstd::max(const std::vector<float>& rhs){
	if(rhs.size()==0){ return 0.0; }
	float lhs=rhs[0];
	for(uint i=1; i<rhs.size(); i++){ if(lhs<rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
float sstd::max_abs(const std::vector<float>& rhs){
	if(rhs.size()==0){ return 0.0; }
	float lhs=rhs[0], buf=abs(rhs[0]);
	for(uint i=1; i<rhs.size(); i++){ if(buf<abs(rhs[i])){ lhs=rhs[i]; buf=abs(rhs[i]); } }
	return lhs;
}
float sstd::min(const std::vector<float>& rhs){
	if(rhs.size()==0){ return 0.0; }
	float lhs=rhs[0];
	for(uint i=1; i<rhs.size(); i++){ if(lhs>rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
float sstd::min_abs(const std::vector<float>& rhs){
	if(rhs.size()==0){ return 0.0; }
	float lhs=rhs[0], buf=abs(rhs[0]);
	for(uint i=1; i<rhs.size(); i++){ if(buf>abs(rhs[i])){ lhs=rhs[i]; buf=abs(rhs[i]); } }
	return lhs;
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
float sstd::var(const std::vector<float>& rhs){
	float a=sstd::ave(rhs);
	float lhs=0;
	KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(float)(rhs.size()-1);
	return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
float sstd::var_p(const std::vector<float>& rhs){
	float a=sstd::ave(rhs);
	float lhs=0;
	KAHAN_SUM_i(float, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(float)rhs.size();
	return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
float sstd::stdev(const std::vector<float>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
float sstd::stdev_p(const std::vector<float>& rhs){ return sqrt(sstd::var_p(rhs)); }


double sstd::sum(const std::vector<double>& rhs){
	double lhs=0;
	KAHAN_SUM_i(double, lhs, rhs[i], rhs.size());
	return lhs;
}
double sstd::sum_abs(const std::vector<double>& rhs){
	double lhs=0;
	KAHAN_SUM_i(double, lhs, abs(rhs[i]), rhs.size());
	return lhs;
}
double sstd::ave(const std::vector<double>& rhs){
	return sstd::sum(rhs)/rhs.size();
}
double sstd::med(std::vector<double> rhs){ // copy rhs
	if(rhs.size()==0){ return (double)0.0; }
	std::sort(rhs.begin(), rhs.end());
	uint size_div2 = rhs.size() / 2;
	uint size_mod  = rhs.size() - 2*size_div2; // same as "rhs.size()%2"
	if(size_mod==0){ return (rhs[size_div2-1] + rhs[size_div2])/(double)2.0; // rhs.size() is even number
	}     else     { return rhs[size_div2]; }                                // rhs.size() is odd number
}
double sstd::max(const std::vector<double>& rhs){
	if(rhs.size()==0){ return 0.0; }
	double lhs=rhs[0];
	for(uint i=1; i<rhs.size(); i++){ if(lhs<rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
double sstd::max_abs(const std::vector<double>& rhs){
	if(rhs.size()==0){ return 0.0; }
	double lhs=rhs[0], buf=abs(rhs[0]);
	for(uint i=1; i<rhs.size(); i++){ if(buf<abs(rhs[i])){ lhs=rhs[i]; buf=abs(rhs[i]); } }
	return lhs;
}
double sstd::min(const std::vector<double>& rhs){
	if(rhs.size()==0){ return 0.0; }
	double lhs=rhs[0];
	for(uint i=1; i<rhs.size(); i++){ if(lhs>rhs[i]){ lhs=rhs[i]; } }
	return lhs;
}
double sstd::min_abs(const std::vector<double>& rhs){
	if(rhs.size()==0){ return 0.0; }
	double lhs=rhs[0], buf=abs(rhs[0]);
	for(uint i=1; i<rhs.size(); i++){ if(buf>abs(rhs[i])){ lhs=rhs[i]; buf=abs(rhs[i]); } }
	return lhs;
}
// 不偏分散/標本分散 (variance): u^2 = (1/(n-1))*Σ(x_i-μ)^2
double sstd::var(const std::vector<double>& rhs){
	double a=sstd::ave(rhs);
	double lhs=0;
	KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(double)(rhs.size()-1);
	return lhs;
}
// 母分散 (variance population): σ^2 = (1/n)*Σ(x_i-μ)^2
double sstd::var_p(const std::vector<double>& rhs){
	double a=sstd::ave(rhs);
	double lhs=0;
	KAHAN_SUM_i(double, lhs, (rhs[i]-a)*(rhs[i]-a), rhs.size());
	lhs/=(double)rhs.size();
	return lhs;
}
// 標本標準偏差 (sample standard deviation): u = SQRT( (1/(n-1))*Σ(x_i-μ)^2 )
double sstd::stdev(const std::vector<double>& rhs){ return sqrt(sstd::var(rhs)); }
// 標準偏差 (standard deviation): σ = SQRT( (1/n)*Σ(x_i-μ)^2 )
double sstd::stdev_p(const std::vector<double>& rhs){ return sqrt(sstd::var_p(rhs)); }

// get a list of prime number under rhs.
std::vector<uint64> sstd::prime(uint64 rhs){
	
	uint64 ApproximationNumOfPrimes = (uint64)log((double)rhs); // depend on "Prime number theorem"
	std::vector<uint64> lhs(ApproximationNumOfPrimes); lhs.clear();

	std::vector<char> sieve(rhs, 0); // Sieve of Eratosthenes

	for(uint64 p=3; p<rhs; p+=2){
		for(uint64 q=p*p; q<rhs; q+=2*p){ // p*p mean smallest number that not sift through is multiple of own // adding 2*p to avoid multiple of 2
			sieve[q]=1;
		}
	}

	if(rhs>=2){ lhs.push_back(2); }
	for(uint64 i=3; i<rhs; i+=2){
		if(sieve[i]!=1){
			lhs.push_back(i);
		}
	}
	
	return lhs;
}

// get a list of prime factorization
std::vector<struct sstd::fact> sstd::factor(uint64 rhs){
	std::vector<struct sstd::fact> lhs;
	
//	std::vector<uint> primeList = sstd::prime((uint)(sqrt((double)rhs)+1)); // これは間違い factor(10) でコケる
	std::vector<uint64> primeList = sstd::prime(rhs/2+1);
	struct sstd::fact buf; buf.num = 0;
	for(uint64 i=0; i<primeList.size(); i++){
		buf.prime = primeList[i];
		while(1){
			uint64 prime_div = rhs / primeList[i];
			uint64 prime_mod = rhs - primeList[i]*prime_div; // same as "rhs % primeList[i];"
			if(prime_mod!=0){ break; }
			buf.num++;
			rhs = prime_div;
		}
		if(buf.num!=0){ lhs.push_back(buf); }
		if(rhs==1){ break; }
		buf.num = 0;
	}
	return lhs;
}

// get a list of all divisors
std::vector<uint64> sstd::divisor(uint64 rhs){
	std::vector<struct sstd::fact> factorList = sstd::factor(rhs);
	if(factorList.size()==0){ return std::vector<uint64>(0); } // ERROR check

	std::vector<std::vector<uint64>> expList(factorList.size());
	for(uint64 p=0; p<expList.size(); p++){
		expList[p].push_back(1);
		for(uint64 q=1; q<factorList[p].num+1; q++){
			expList[p].push_back(expList[p][q-1] * factorList[p].prime);
		}
	}

	uint64 size = expList[0].size(); for(uint64 i=1; i<expList.size(); i++){ size *= expList[i].size(); }
	std::vector<uint64> divList(size); divList.clear();
	std::vector<uint64> divList_buf(size); divList_buf.clear();

	for(uint64 i=0; i<expList[0].size(); i++){ divList.push_back( expList[0][i] ); }
	for(uint64 i=1; i<expList.size(); i++){
		for(uint64 p=0; p<divList.size(); p++){
			for(uint64 q=0; q<expList[i].size(); q++){
				divList_buf.push_back(divList[p] * expList[i][q]);
			}
		}
		std::swap(divList, divList_buf);
		divList_buf.clear();
	}

	std::sort(divList.begin(), divList.end());
	return divList;
}


// base ^ exponent
#define sstd_pow(type, base, exp)\
	if(exp==0){ return 1; }\
	type ret=base;\
	for(type i=1; i<exp; i++){ ret *= base; }\
	return ret

uint8  sstd::pow(uint8  base, uint8  exp){ sstd_pow(uint8,  base, exp); }
uint16 sstd::pow(uint16 base, uint16 exp){ sstd_pow(uint16, base, exp); }
uint32 sstd::pow(uint32 base, uint32 exp){ sstd_pow(uint32, base, exp); }
uint64 sstd::pow(uint64 base, uint64 exp){ sstd_pow(uint64, base, exp); }

