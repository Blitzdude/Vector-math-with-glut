#pragma once

#include "mathUtil.h"

template <class T>
class Vec4 {
public: // methods
	Vec4() {}
	Vec4(T _x, T _y, T _z, T _w)
		:
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{}

	// copy constructor
	Vec4(const Vec4 &vect)
		:
		Vec4(vect.x, vect.y, vect.z, vect.w)
	{}

	/* METHODS *///////////////////////////////////////////////////////
				 ///////////////////////////////////////////////////////////////////

				 // return length squared
	T sqLength() const
	{
		return square(*this);
	}

	// return the vector length
	T length() const
	{
		return sqrt(sqLength());
	}

	// Normalize the vector
	Vec4& Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
		return *this;
	}

	// get the normalized vector
	Vec4 GetNormalized() const
	{
		Vec4 norm = *this;
		norm.Normalize();
		return norm;
	}

	// Cross product is not defined to return a vector3 value in 4-dimensions
	/*
	static Vec4 CrossProduct(const Vec4<T> &v1, const Vec4<T> &v2)
	{
		NOT DEFINED
		return temp;
	}
	*/

	/****************************************************************/


	/* OPERATORS *///////////////////////////////////////////////////////
				   //////////////////////////////////////////////////////

				   // - operator negates vector
	Vec4 operator-() const
	{
		return Vec4(-x, -y, -z, -w);
	}



	// = operator
	Vec4& operator=(const Vec4 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	// += operator
	Vec4& operator+=(const Vec4 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	// + operator
	Vec4 operator+(const Vec4 &other) const
	{
		return Vec4(*this) += other;
	}

	// -= operator
	Vec4& operator-=(const Vec4 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	// - operator Vec4 - Vec4
	Vec4 operator-(const Vec4 &other) const
	{
		return Vec4(*this) -= other;
	}

	// * operator scalar * vector
	T operator*(const Vec4 &other) const
	{
		return x * other.x + y * other.y + z * other.z + other.w * w;
	}

	// *= operator vector *= scalar
	Vec4& operator*=(const T &other)
	{
		x *= other;
		y *= other;
		z *= other;
		w *= other;

		return *this;
	}

	// * operator vector * scalar
	Vec4 operator*(const T other) const
	{
		return Vec4(*this) *= other;
	}

	// /= operator vector /= scalar
	Vec4& operator/=(const T &other)
	{
		x /= other;
		y /= other;
		z /= other;
		w /= other;
		return *this;
	}

	Vec4 operator/(const T &other)
	{
		return Vec4(*this) /= other;
	}

	bool operator==(const Vec4 &other) const
	{
		return x == other.x && y == other.y 
			&& z == other.z && w == other.w;
	}

	bool operator!=(const Vec4 &other) const
	{
		return !(*this == other);
	}

public: // attributes
	T x;
	T y;
	T z;
	T w;
};

