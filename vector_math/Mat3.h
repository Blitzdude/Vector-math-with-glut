#pragma once

#include "Vec3.h"
#include "Mat2.h"

template<class T>
class Mat3 {
public:

	// 
	Mat3() { *this = Mat3::identity(); }
	// 16 parameter constructor
	Mat3(T e11, T e12, T e13,
		T e21, T e22, T e23, 
		T e31, T e32, T e33 )
	{
		// row1
		elements[0][0] = e11;
		elements[0][1] = e12;
		elements[0][2] = e13;
		// row2
		elements[1][0] = e21;
		elements[1][1] = e22;
		elements[1][2] = e23;
		// row3
		elements[2][0] = e31;
		elements[2][1] = e32;
		elements[2][2] = e33;
	}

	// constructor using vectors
	Mat3(Vec3<T> v1,
		Vec3<T> v2,
		Vec3<T> v3)
	{
		// row1
		elements[0][0] = v1.x;
		elements[0][1] = v1.y;
		elements[0][2] = v1.z;
		// row2
		elements[1][0] = v2.x;
		elements[1][1] = v2.y;
		elements[1][2] = v2.z;
		// row3
		elements[2][0] = v3.x;
		elements[2][1] = v3.y;
		elements[2][2] = v3.z;
	}

	/* METHODS *///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

					 // Determinant calculation
T determinant()
{
	/*
	|00 01 02|00 01
	|10 11 12|10 11
	|20 21 22|20 21
	*/
		

	// calculate the six parts
	T sub1 = elements[0][0] * elements[1][1] * elements[2][2];
	T sub2 = elements[0][1] * elements[1][2] * elements[2][0];
	T sub3 = elements[0][2] * elements[1][0] * elements[2][1];
	T sub4 = elements[2][0] * elements[1][1] * elements[0][2];
	T sub5 = elements[2][1] * elements[1][2] * elements[0][0];
	T sub6 = elements[2][2] * elements[1][0] * elements[0][1];

	return sub1 + sub2 + sub3 - sub4 - sub5 - sub6;
}
// Transpose
Mat3 transpose()
{
	Mat3 result;
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = 0; i < 3; i++)
		{
			result.elements[i][j] = elements[j][i];
		}
	}
	return result;
}
// Inverse Operation

// Identity
static Mat3 identity()
{
	return {
		(T)1.0, (T)0.0, (T)0.0, 
		(T)0.0, (T)1.0, (T)0.0, 
		(T)0.0, (T)0.0, (T)1.0
	};
}
// Zeroes
static Mat3 zeroes()
{
	return {
		(T)0.0, (T)0.0, (T)0.0,
		(T)0.0, (T)0.0, (T)0.0,
		(T)0.0, (T)0.0, (T)0.0
	};
}
// scaling
static Mat3 scaling(T factor)
{
	return {
		factor, (T)0.0, (T)0.0,
		(T)0.0, factor, (T)0.0,
		(T)0.0, (T)0.0, (T)1.0
	};
}
// Translation
static Mat3 translation(const Vec3<T>& t)
{
	return {
		(T)1.0, (T)0.0, t.x,
		(T)0.0, (T)1.0, t.y,
		(T)0.0, (T)0.0, t.z
	};
}
// Rotation X
static Mat3 rotationZ(T theta)
{
	const T sinTheta = sin(theta);
	const T cosTheta = cos(theta);
	return {
		cosTheta, -sinTheta, (T)0.0,
		sinTheta, cosTheta,  (T)0.0,
		(T)0.0,	 (T)0.0,	 (T)1.0,
	};
}

// Rotation Y
static Mat3 rotationY(T theta)
{
	const T sinTheta = sin(theta);
	const T cosTheta = cos(theta);
	return {
		cosTheta, (T)0.0, -sinTheta,
		(T)0.0,   (T)1.0, (T)0.0,   
		sinTheta, (T)0.0, cosTheta, 
	};
}
// Rotation Z
static Mat3 rotationX(T theta)
{
	const T sinTheta = sin(theta);
	const T cosTheta = cos(theta);
	return {
		(T)1.0, (T)0.0, (T)0.0, 
		(T)0.0, cosTheta, -sinTheta, 
		(T)0.0, sinTheta, cosTheta
	};
}

/* OPERATORS *///////////////////////////////////////////////////////
			   //////////////////////////////////////////////////////

			   // copies elements
Mat3& operator= (const Mat3& other)
{
	memcpy(elements, other.elements, sizeof(elements));
	return *this;
}
// *= multplies matrix with scalar
Mat3& operator*=(T other)
{
	for (auto& row : elements)
	{
		for (T& e : row)
		{
			e *= other;
		}
	}
}

// * multiplies matrix with scalar
Mat3 operator* (T other) const
{
	Mat3 result = *this;
	return result *= other;
}

// *= multiplies with matrix
Mat3& operator*= (const Mat3& other)
{
	return *this = *this * other;
}

// * multiplies with matrix
Mat3 operator* (const Mat3& other) const
{
	Mat3 result;
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t k = 0; k < 3; k++)
		{
			T sum = (T)0.0;
			for (size_t i = 0; i < 3; i++)
			{
				sum += elements[j][i] * other.elements[i][k];
			}
			result.elements[j][k] = sum;
		}
	}
	return result;
}


public: // attributes
		//		[row][column]
	T elements[3][3];
};

// Vector4 = Mat3 - Vector4 product
template<typename T>
Vec3<T>& operator*=(Vec3<T>& lhs, const Mat3<T>& rhs)
{
	return lhs = lhs * rhs;
}

template<typename T>
Vec3<T> operator* (const Vec3<T>& lhs, const Mat3<T>& rhs)
{
	return {
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]
	};
}