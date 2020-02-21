#pragma once
#include "api.h"
#include "Vector.h"
#include <stdint.h>
#include <initializer_list>

template<class T, size_t M, size_t N>
class Matrix final {
public:
	using CT = const T;
	using pT = T*;
	using Vec = Vector<T, M>;
	using pVec = Vec *;
	using pMat = pVec *;

	Matrix();

	Matrix(std::initializer_list<T>);

	Matrix(const Matrix& r);

	Matrix(Matrix&& r);

	~Matrix();

	T& operator=(const Matrix& r);

	Vec& operator[](size_t n) {
		return m_data[n];
	}

	const Vec& operator[](size_t n) const {
		return m_data[n];
	}

	pVec GetVectorPtr(size_t n);

private:

public:


private:
	void CopyConstructor(Matrix& l, const Matrix& r);

	pVec m_data = nullptr;
};


using Mat4f = Matrix<float, 4, 4>;
using Mat3f = Matrix<float, 3, 3>;
using Mat2f = Matrix<float, 2, 2>;

using CMat2f = const Mat2f;
using CMat3f = const Mat3f;
using CMat4f = const Mat4f;

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix() : m_data(new Vec[N]) {}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(std::initializer_list<T> initList) : m_data(new Vec[N]) {
	size_t counterM = 0;
	size_t counterN = 0;
	for (CT & il : initList) {
		m_data[counterM++][counterN] = il;
		if (counterM == N) {
			counterM = 0;
			counterN++;
		}
	}
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(const Matrix& r) : m_data(new Vec[N]) {
	CopyConstructor(*this, r);
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(Matrix&& r) {
	m_data = r.m_data;
	r.m_data = nullptr;
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::~Matrix() {
	if (m_data) {
		delete[] m_data;
	}
}

template<class T, size_t M, size_t N>
inline T& Matrix<T, M, N>::operator=(const Matrix& r) {
	CopyConstructor(*this, r);
	return *this;
}

template<class T, size_t M, size_t N>
inline Vector<T, M>* Matrix<T, M, N>::GetVectorPtr(size_t n)
{
	return m_data + n;
}

template<class T, size_t M, size_t N>
inline void Matrix<T, M, N>::CopyConstructor(Matrix& l, const Matrix& r) {
	for (int i = 0; i < M; ++i) {
		l[i] = r[i];
	}
}
