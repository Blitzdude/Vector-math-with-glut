#pragma once

#include "Vec2.h"

template<class T>
class Mat2 {
public:
	// Methods

	Mat2() {}
	// 4 parameter constructor
	Mat2(T e11, T e12,
		T e21, T e22)
	{
		// row1
		elements[0][0] = e11;
		elements[0][1] = e12;
		// row2
		elements[1][0] = e21;
		elements[1][1] = e22;
	}

		// constructor using vectors
	Mat2(Vec2<T> v1,
		Vec2<T> v2)
	{
		// row1
		elements[0][0] = v1.x;
		elements[0][1] = v1.y;
		// row2
		elements[1][0] = v2.x;
		elements[1][1] = v2.y;
	}


	/* METHODS *///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	// Determinant calculation
	Mat2 determinant()
	{
		/*
		|+ -|
		|- +|
		*/

		// calculate the minor determinants
		return elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1];
	}
	// Transpose
	Mat2 transpose()
	{
		Mat2 result;
		for (size_t j = 0; j < 2; j++)
		{
			for (size_t i = 0; i < 2; i++)
			{
				result.elements[i][j] = elements[j][i];
			}
		}
		return result;
	}
	// Inverse Operation

	// Identity
	static Mat2 identity()
	{
		return {
			(T)1.0, (T)0.0,
			(T)0.0, (T)1.0,
		};
	}
	// scaling
	static Mat2 scaling(T factor)
	{
		return {
			factor, (T)0.0, 
			(T)0.0, factor
		};
	}
	
	
	// Rotation 
	static Mat2 rotation(T theta)
	{
		const T sinTheta = sin(theta);
		const T cosTheta = cos(theta);
		return {
			cosTheta, -sinTheta,
			sinTheta, cosTheta
		};
	}


	/* OPERATORS *///////////////////////////////////////////////////////
				   //////////////////////////////////////////////////////

				   // copies elements
	Mat2& operator= (const Mat2& other)
	{
		memcpy(elements, other.elements, sizeof(elements));
		return *this;
	}
	// *= multplies matrix with scalar
	Mat2& operator*=(T other)
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
	Mat2 operator* (T other) const
	{
		Mat2 result = *this;
		return result *= other;
	}

	// *= multiplies with matrix
	Mat2& operator*= (const Mat2& other)
	{
		return *this = *this * other;
	}

	// * multiplies with matrix
	Mat2 operator* (const Mat2& other) const
	{
		Mat2 result;
		for (size_t j = 0; j < 2; j++)
		{
			for (size_t k = 0; k < 2; k++)
			{
				T sum = (T)0.0;
				for (size_t i = 0; i < 2; i++)
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
	T elements[2][2];
};

// Vector2 = Mat2 - Vector2 product
template<typename T>
Vec2<T>& operator*=(Vec2<T>& lhs, const Mat2<T>& rhs)
{
	return lhs = lhs * rhs;
}

template<typename T>
Vec2<T> operator* (const Vec2<T>& lhs, const Mat2<T>& rhs)
{
	return {
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1]
	};
}