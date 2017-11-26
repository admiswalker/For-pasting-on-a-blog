#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../pdbg.hpp"
#include "../typeDef.h"

//--------------------------------------------------------------------------------------------------------

namespace sstd{
	template <typename T> class mat;
	template <typename T> void copy(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs);
	template <typename T> void move(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs);
	template <typename T> void swap(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs);

	template <typename T> void zeros(class sstd::mat<T>& Mat);
	template <typename T> class sstd::mat<T> Tr(class sstd::mat<T>& rhs); // lhs = Transpose(rhs)
	template <typename T> void        Tr_myself(class sstd::mat<T>& rhs); // Transpose(rhs)
	template <typename T> class sstd::mat<T>* copyRect(class sstd::mat<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd);
	
	void print(const class sstd::mat  <char>& Mat);
	void print(const class sstd::mat <uchar>& Mat);
	void print(const class sstd::mat   <int>& Mat);
	void print(const class sstd::mat  <uint>& Mat);
	void print(const class sstd::mat <float>& Mat);
	void print(const class sstd::mat<double>& Mat);
	
	// for sstd::printn(); and sstd::printn_all();.
	void for_printn(const class sstd::mat  <char>& mat);
	void for_printn(const class sstd::mat <uchar>& mat);
	void for_printn(const class sstd::mat   <int>& mat);
	void for_printn(const class sstd::mat  <uint>& mat);
	void for_printn(const class sstd::mat <float>& mat);
	void for_printn(const class sstd::mat<double>& mat);
}

//--------------------------------------------------------------------------------------------------------

#include "CopyRow.hpp"	// "namespace mat{};" の後で include すること!!!
#include "CopyCol.hpp"	// "namespace mat{};" の後で include すること!!!

//--------------------------------------------------------------------------------------------------------

// type matrix: tmat
template <typename T>
class sstd::mat{
private:
	T* MatX;
	uint rowNum;	// 行数
	uint colNum;	// 列数
	uint length;

public:
	inline mat(){ rowNum=0; colNum=0; length=0; MatX=0; }
	inline mat(class mat&  rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::copy<T>(*this, rhs); } // called by "sstd::mat_r buf1(N, N); sstd::mat_r buf2(buf1);"
	inline mat(class mat&& rhs){ rowNum=0; colNum=0; length=0; MatX=0; sstd::move<T>(*this, rhs); }	// called by "return std::move(rhs);" or "std::swap(buf1, buf2)".
	// std::move(lhs, rhs): "move to uninitalized object" will be called.
	// std::swap(lhs, rhs): "move to uninitalized object" -> "copy to lhs or rhs" -> "copy to lhs or rhs" will be called.
	inline mat(const uint& row, const uint& col){
		rowNum = row;
		colNum = col;
		length = row * col;
		MatX = (T*)malloc(sizeof(T)*length);
		sstd::pdbg_if_stop_exit(MatX==0, "ERROR: This pointer is not allocated.\n");
	}
	inline ~mat(){ free(MatX); }

	// R: read only
	inline const uint& rows() const { return rowNum; }
	inline const uint& cols() const { return colNum; }
	inline const uint& len () const { return length; }

	// RW: read and write
	inline T*& pMat_RW(){ return MatX; }
	inline uint&  rows_RW(){ return rowNum; }
	inline uint&  cols_RW(){ return colNum; }
	inline uint&  len_RW (){ return length; }

	class mat& operator=(const class mat& rhs){ sstd::copy<T>(*this, (class mat&)rhs); return *this; }	// called by "lhs = mat::mat(3, 3);".

	T& operator[](const uint& p){ return MatX[      p]; }
	T& operator[](const  int& p){ return MatX[(uint)p]; }

	T& operator()(const uint& p, const uint& q){ return MatX[      p + rowNum*      q]; }
	T& operator()(const  int& p, const uint& q){ return MatX[(uint)p + rowNum*      q]; }
	T& operator()(const uint& p, const  int& q){ return MatX[      p + rowNum*(uint)q]; }
	T& operator()(const  int& p, const  int& q){ return MatX[(uint)p + rowNum*(uint)q]; }

	class CopyRow<T> operator()(const uint& p, const char& c_dummy){ return OpCopyRow<T>(this, p, c_dummy); }
	class CopyRow<T> operator()(const  int& p, const char& c_dummy){ return OpCopyRow<T>(this, p, c_dummy); }

	class CopyCol<T> operator()(const char& c_dummy, const uint& q){ return OpCopyCol<T>(this, c_dummy, q); }
	class CopyCol<T> operator()(const char& c_dummy, const  int& q){ return OpCopyCol<T>(this, c_dummy, q); }
};

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::zeros(class sstd::mat<T>& Mat){
	for(uint q=0; q<Mat.cols(); q++){
		for(uint p=0; p<Mat.rows(); p++){
			Mat(p, q) = (T)0;
		}
	}
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void copy_withoutAllocate(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs){
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(p, q) = rhs(p, q);
		}
	}
}
template <typename T>
inline void sstd::copy(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs){

	if(lhs.len() != rhs.len()){
		free(lhs.pMat_RW()); lhs.pMat_RW() = 0;
		if(rhs.len()!=0){ lhs.pMat_RW() = (T*)malloc(sizeof(T) * rhs.len()); }
	}

	lhs.rows_RW() = rhs.rows();
	lhs.cols_RW() = rhs.cols();
	lhs.len_RW()  = rhs.len();

	copy_withoutAllocate<T>(lhs, rhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline void sstd::move(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs){

	lhs.rows_RW() = rhs.rows(); rhs.rows_RW() = 0;
	lhs.cols_RW() = rhs.cols(); rhs.cols_RW() = 0;
	lhs.len_RW()  = rhs.len();  rhs.len_RW()  = 0;

	free(lhs.pMat_RW());
	lhs.pMat_RW() = rhs.pMat_RW();
	rhs.pMat_RW() = 0;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
void swap(class sstd::mat<T>& lhs, class sstd::mat<T>& rhs){

	uint rowsBuf=lhs.rows(); lhs.rows_RW()=rhs.rows(); rhs.rows_RW()=rowsBuf;
	uint colsBuf=lhs.cols(); lhs.cols_RW()=rhs.cols(); rhs.cols_RW()=colsBuf;
	uint lenBuf=lhs.len(); lhs.len_RW()=rhs.len(); rhs.len_RW()=lenBuf;
	
	T* pMatBuf=lhs.pMat(); lhs.pMat_RW()=rhs.pMat(); rhs.pMat_RW()=pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
class sstd::mat<T> sstd::Tr(class sstd::mat<T>& rhs){
	class sstd::mat<T> lhs(rhs.cols(), rhs.rows());
	for(uint q=0; q<rhs.cols(); q++){
		for(uint p=0; p<rhs.rows(); p++){
			lhs(q, p) = rhs(p, q);
		}
	}
	return lhs;
}
template <typename T>
void sstd::Tr_myself(class sstd::mat<T>& rhs){
	class sstd::mat<T> lhs = sstd::Tr(rhs);
	sstd::move(rhs, lhs);
}

//--------------------------------------------------------------------------------------------------------

template <typename T>
inline class sstd::mat<T>* sstd::copyRect(class sstd::mat<T>*& pMat, const uint& rowStart, const uint& rowEnd, const uint& colStart, const uint& colEnd){

	class sstd::mat<T>* pMatBuf = new sstd::mat<T>(rowEnd-rowStart, colEnd-colStart);

	for(uint q=0; q<(colEnd-colStart); q++){
		for(uint p=0; p<(rowEnd-rowStart); p++){
			(*pMatBuf)(p, q) = (*pMat)(p+rowStart, q+colStart);
		}
	}

	return pMatBuf;
}

//--------------------------------------------------------------------------------------------------------

