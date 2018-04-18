#pragma once


#include "mathUtil.h"

template <class T>
class Vec3 {
public: // methods
	Vec3() {}
	Vec3(T _x, T _y, T _z)
		:
		x(_x),
		y(_y),
		z(_z)
	{}

	// copy constructor
	Vec3(const Vec3 &vect)
		:
		Vec3(vect.x, vect.y, vect.z)
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
	Vec3& Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	// get the normalized vector
	Vec3 GetNormalized() const
	{
		Vec3 norm = *this;
		norm.Normalize();
		return norm;
	}

	// returns the cross product of two vectors
	static Vec3 CrossProduct(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		Vec3 temp;
		temp.x = (v1.y*v2.z) - (v1.z*v2.y);
		temp.y = (v1.z*v2.x) - (v1.x*v2.z);
		temp.z = (v1.x*v2.y) - (v1.y*v2.x);
		return temp;
	}

	/****************************************************************/


	/* OPERATORS *///////////////////////////////////////////////////////
				   //////////////////////////////////////////////////////

	// - operator negates vector
	Vec3 operator-() const
	{
		return Vec3(-x, -y, -z);
	}



	// = operator
	Vec3& operator=(const Vec3 &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	// += operator
	Vec3& operator+=(const Vec3 &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	// + operator
	Vec3 operator+(const Vec3 &other) const
	{
		return Vec3(*this) += other;
	}

	// -= operator
	Vec3& operator-=(const Vec3 &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	// - operator Vec3 - Vec3
	Vec3 operator-(const Vec3 &other) const
	{
		return Vec3(*this) -= other;
	}

	// * operator scalar * vector
	T operator*(const Vec3 &other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	// *= operator vector *= scalar
	Vec3& operator*=(const T &other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	// * operator vector * scalar
	Vec3 operator*(const T other) const
	{
		return Vec3(*this) *= other;
	}

	// /= operator vector /= scalar
	Vec3& operator/=(const T &other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	Vec3 operator/(const T &other)
	{
		return Vec3(*this) /= other;
	}

	bool operator==(const Vec3 &other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vec3 &other) const
	{
		return !(*this == other);
	}

	
public: // attributes
	T x;
	T y;
	T z;


};



