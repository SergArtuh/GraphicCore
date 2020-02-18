#pragma once
#include "api.h"
#include <stdint.h>
#include <initializer_list>

template<class T, size_t S>
class Vector final {
public:
	using pT = T*;

	Vector();

	Vector(std::initializer_list<T>);

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
	void CopyConstructor(Vector& l, const Vector& r);


	pT m_data = nullptr;
};


template<class T, size_t S>
inline Vector<T, S>::Vector() : m_data{ new T[S] } {}

template<class T, size_t S>
inline Vector<T, S>::Vector(std::initializer_list<T> fl) : m_data{ new T[S] } {
	uint16_t counter = 0;
	for (const T& e : fl) {
		m_data[counter++] = e;
	}
}

template<class T, size_t S>
inline Vector<T, S>::Vector(const Vector& r) : m_data{ new T[S] } {
	CopyConstructor(*this, r);
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
		delete[] m_data;
	}
}


template<class T, size_t S>
inline  Vector<T, S>& Vector<T, S>::operator=(const Vector& r) {
	CopyConstructor(*this, r);
	return *this;
}

template<class T, size_t S>
inline void Vector<T, S>::CopyConstructor(Vector& l, const Vector& r) {
	constexpr const uint16_t sizeInBytes = sizeof(T) * S;
	memcpy(m_data, r.m_data, sizeInBytes);
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