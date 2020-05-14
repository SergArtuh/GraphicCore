#pragma once
#include "api.h"
#include "shmem.h"

#include <stdint.h>
#include <array>


template<class T, size_t S>
class Vector final {
public:
	using pT = T*;
	using InitArray = std::array<T, S>;

	Vector();

	Vector(InitArray&& initArray);

	Vector(pT ptr);

	Vector(pT ptr, shmem::Use);

	Vector(pT ptr, shmem::NotUse);

	//Vector(std::initializer_list<T>);



	Vector(const Vector& r);

	Vector(Vector&& r);

	~Vector();

	Vector& operator=(const Vector& r);

	T& operator[](size_t n) {
		return m_data[n];
	}

	const T& operator[](size_t n) const {
		return m_data[n];
	}

	static constexpr size_t SizeInBytes();

private:
	template <size_t D>
	class DotProduct {
	public:
		static T result(pT a, pT b) {
			return (*a) * (*b) + DotProduct<D - 1>::result(a + 1, b + 1);
		}
	};

	template <>
	class DotProduct<1> {
	public:
		static T result(pT a, pT b) {
			return (*a) * (*b);
		}
	};

	template <size_t D>
	class Normalize {
	public:
		static void result(pT a, T lendth) {
			(*a) /= lendth;
			Normalize<D - 1>::result(a + 1, lendth);
		}
	};

	template <>
	class Normalize<1> {
	public:
		static void result(pT a, T lendth) {
			(*a) /= lendth;
		}
	};

public:
	T dot(const Vector& r) const;

	T length() const;

	/*Vector cross(const Vector& r) const;*/

	void normalize();

	size_t size() const { return S; }

private:
	void Copy(Vector& l, const Vector& r);


	pT m_data = nullptr;
};

template<class T, size_t S>
inline Vector<T, S>::Vector(InitArray&& initArray) : Vector(initArray.data(), shmem::NotUse()) {}

template<class T, size_t S>
inline Vector<T, S>::Vector() : m_data{ reinterpret_cast<pT>(malloc(SizeInBytes())) } {}

template<class T, size_t S>
inline Vector<T, S>::Vector(pT ptr) : Vector(ptr, shmem::NotUse()) {}

template<class T, size_t S>
inline Vector<T, S>::Vector(pT ptr, shmem::Use) : m_data{ ptr } {
}

template<class T, size_t S>
inline Vector<T, S>::Vector(pT ptr, shmem::NotUse) : m_data{ reinterpret_cast<pT>(malloc(SizeInBytes())) } {
	memcpy(m_data, ptr, SizeInBytes());
}

/*template<class T, size_t S>
inline Vector<T, S>::Vector(std::initializer_list<T> fl) : m_data{ new T[S] } {
	uint16_t counter = 0;
	for (const T& e : fl) {
		m_data[counter++] = e;
	}
}*/

template<class T, size_t S>
inline Vector<T, S>::Vector(const Vector& r) : m_data{ reinterpret_cast<pT>(malloc(SizeInBytes())) } {
	Copy(*this, r);
}

template<class T, size_t S>
inline Vector<T, S>::Vector(Vector&& r) {
	m_data = r.m_data;
	r.m_data = nullptr;
}

template<class T, size_t S>
inline Vector<T, S>::~Vector()
{
	if (m_data) {
		// XXX: temporary disabled
		// Need alocator
		//delete[] m_data;
	}
}


template<class T, size_t S>
inline  Vector<T, S>& Vector<T, S>::operator=(const Vector& r) {
	Copy(*this, r);
	return *this;
}

template<class T, size_t S>
inline constexpr size_t Vector<T, S>::SizeInBytes()
{
	return sizeof(T) * S;
}

template<class T, size_t S>
inline void Vector<T, S>::Copy(Vector& l, const Vector& r) {
	memcpy(m_data, r.m_data, SizeInBytes());
}

template<class T, size_t S>
inline T Vector<T, S>::dot(const Vector& r) const {
	return DotProduct<S>::result(m_data, r.m_data);
}

template<class T, size_t S>
inline T Vector<T, S>::length() const {
	return sqrt(DotProduct<S>::result(m_data, m_data));
}

template<class T, size_t S>
inline void Vector<T, S>::normalize() {
	Normalize<S>::result(m_data, length());
}


using Vec4f = Vector<float, 4>;
using Vec3f = Vector<float, 3>;
using Vec2f = Vector<float, 2>;



namespace {
	template <class T, size_t S, size_t C>
	struct FillVector {
		static void result(Vector<T, S>& v, T value) {
			v[C] = value;
			FillVector<T, S, C - 1>::result(v, value);
		}
	};

	template <class T, size_t S>
	struct FillVector<T, S, 0> {
		static void result(Vector<T, S>& v, T value) {
			v[0] = value;
		}
	};
}

template<class T, size_t S>
constexpr void makeZeroVector(Vector< T, S>& v) {
	FillVector<T, S, S - 1>::result(v, T{ 0 });
}

template<class T, size_t S>
constexpr Vector< T, S> makeZeroVector() {
	Vector< T, S> v;
	makeZeroVector(v);
	return v;
}

template<class T, size_t S>
constexpr void makeOneVector(Vector< T, S>& v) {
	FillVector<T, S, S - 1>::result(v, T{ 1 });
}

template<class T, size_t S>
constexpr Vector< T, S> makeOneVector() {
	Vector< T, S> v;
	makeOneVector(v);
	return v;
}