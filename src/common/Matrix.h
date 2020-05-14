#pragma once
#include "api.h"
#include "Vector.h"

#include "shmem.h"

#include <stdint.h>
#include <array>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <new>

#define _USE_MATH_DEFINES
#include <math.h>


template<class T, size_t M, size_t N>
class Matrix final {
public:
	using CT = const T;
	using pT = T*;
	using Vec = Vector<T, M>;
	using pVec = Vec*;
	using pMat = pVec*;
	using InitArray = std::array<T, M * N>;


	Matrix();

	Matrix(InitArray&& initArray);

	Matrix(pT ptr);

	Matrix(pT ptr, shmem::Use);

	Matrix(pT ptr, shmem::NotUse);

	Matrix(const Matrix& r);

	Matrix(Matrix&& r);

	~Matrix();

	Matrix<T, M, N>& operator=(const Matrix& r);

	Vec& operator[](size_t n) {
		return m_data[n];
	}

	const Vec& operator[](size_t n) const {
		return m_data[n];
	}

	pVec GetVectorPtr(size_t n);

	static constexpr size_t SizeInBytes();

private:
	template<int VN>
	void Copy(pVec src, pVec dest) {
		(*src) = (*dest);
		Copy<VN - 1>(++src, ++dest);
	}

	template<>
	void Copy<1>(pVec src, pVec dest) {
		(*src) = (*dest);
	}

	template<int VN, class ShMem = shmem::NotUse>
	void CopyFromSrc(pVec src, pT destData) {
		pVec v = new (src) Vec(destData, ShMem());
		CopyFromSrc<VN - 1, ShMem>(++src, destData + M);
	}

	template<>
	void CopyFromSrc<1, shmem::Use>(pVec src, pT destData) {
		pVec v = new (src) Vec(destData, shmem::Use());
	}

	template<>
	void CopyFromSrc<1, shmem::NotUse>(pVec src, pT destData) {
		pVec v = new (src) Vec(destData, shmem::NotUse());
	}

	pVec m_data = nullptr;
};


using Mat4f = Matrix<float, 4, 4>;
using Mat3f = Matrix<float, 3, 3>;
using Mat2f = Matrix<float, 2, 2>;

using CMat2f = const Mat2f;
using CMat3f = const Mat3f;
using CMat4f = const Mat4f;

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix() : m_data{ new Vec[N] } {}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(const Matrix& r) : m_data{ new Vec[N] } {
	Copy<N>(m_data, r.m_data);
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(Matrix&& r) {
	m_data = r.m_data;
	r.m_data = nullptr;
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(InitArray&& initArray) : Matrix(initArray.data(), shmem::NotUse()) {}


template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(pT ptr) : Matrix(ptr, shmem::NotUse()) {}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(pT ptr, shmem::Use) : m_data{ reinterpret_cast<pVec>(malloc(sizeof(Vec)* N)) } {
	CopyFromSrc<N, shmem::Use>(m_data, ptr);
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(pT ptr, shmem::NotUse) : m_data{ new Vec[N] } {
	CopyFromSrc<N, shmem::NotUse>(m_data, ptr);
}


template<class T, size_t M, size_t N>
inline Matrix<T, M, N>::~Matrix() {
	if (m_data) {
		// XXX: temporary disabled
		// Need alocator
		//delete[] m_data;
	}
}

template<class T, size_t M, size_t N>
inline Matrix<T, M, N>& Matrix<T, M, N>::operator=(const Matrix& r) {
	Copy<N>(m_data, r.m_data);
	return *this;
}

template<class T, size_t M, size_t N>
inline Vector<T, M>* Matrix<T, M, N>::GetVectorPtr(size_t n)
{
	return m_data + n;
}

template<class T, size_t M, size_t N>
inline constexpr size_t Matrix<T, M, N>::SizeInBytes() {
	return sizeof(T) * M * N;
}


// Matrix helpers

template<class T, size_t N, size_t M>
inline void makeZeroMatrix(Matrix<T, N, M>& m) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			m[i][j] = T{ 0 };
		}
	}
}

template<class T, size_t N, size_t M>
inline  Matrix<T, N, M> makeZeroMatrix() {
	Matrix<T, N, M> m;
	makeZeroMatrix(m);
	return m;
}

template<class T, size_t N>
inline void makeIdentityMatrix(Matrix<T, N, N>& m) {
	makeZeroMatrix<T, N, N>(m);
	for (int i = 0; i < N; ++i) {
		m[i][i] = T{ 1 };
	}
}

template<class T, size_t N>
inline  Matrix<T, N, N> makeIdentityMatrix() {
	Matrix<T, N, N> m;
	makeIdentityMatrix(m);
	return m;
}

inline void makeProjectionMatrix(float fov, float aspect, float near, float far, Mat4f& m) {
	auto scale = static_cast<float>(1. / tan(fov * 0.5 * M_PI / 180.));
	makeZeroMatrix<float, 4, 4>(m);
	m[0][0] = scale; // scale the x coordinates of the projected point 
	m[1][1] = scale * aspect; // scale the y coordinates of the projected point 
	m[2][2] = -far / (far - near); // used to remap z to [0,1] 
	m[3][3] = 0;
	m[3][2] = -far * near / (far - near); // used to remap z [0,1] 
	m[2][3] = -1; // set w = -z 
}

inline  Mat4f makeProjectionMatrix(float fov, float aspect, float near, float far) {
	Mat4f m = makeZeroMatrix<float, 4, 4>();
	makeProjectionMatrix(fov, aspect, near, far, m);
	return m;
}