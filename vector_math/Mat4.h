#pragma once

#include "Vec4.h"
#include "Mat3.h"

template<class T>
class Mat4 {
public:
	// Methods
	
	// default constructor, creates an identity matrix
	Mat4() 
	{ 
		*this = Mat4<T>::identity(); 
	};

	// 16 parameter constructor
	Mat4(T e11, T e12, T e13, T e14,
		 T e21, T e22, T e23, T e24,
		 T e31, T e32, T e33, T e34,
		 T e41, T e42, T e43, T e44)
	{
		// row1
		elements[0][0] = e11;
		elements[0][1] = e12;
		elements[0][2] = e13;
		elements[0][3] = e14;
		// row2
		elements[1][0] = e21;
		elements[1][1] = e22;
		elements[1][2] = e23;
		elements[1][3] = e24;
		// row3
		elements[2][0] = e31;
		elements[2][1] = e32;
		elements[2][2] = e33;
		elements[2][3] = e34;
		// row 4
		elements[3][0] = e41;
		elements[3][1] = e42;
		elements[3][2] = e43;
		elements[3][3] = e44;
	}

	// constructor using vectors
	Mat4(Vec4<T> v1,
		Vec4<T> v2,
		Vec4<T> v3,
		Vec4<T> v4)
	{
		// row1
		elements[0][0] = v1.x;
		elements[0][1] = v1.y;
		elements[0][2] = v1.z;
		elements[0][3] = v1.w;
		// row2
		elements[1][0] = v2.x;
		elements[1][1] = v2.y;
		elements[1][2] = v2.z;
		elements[1][3] = v2.w;
		// row3
		elements[2][0] = v3.x;
		elements[2][1] = v3.y;
		elements[2][2] = v3.z;
		elements[2][3] = v3.w;
		// row 4
		elements[3][0] = v4.x;
		elements[3][1] = v4.y;
		elements[3][2] = v4.z;
		elements[3][3] = v4.w;
	}
	

	/* METHODS *///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////

	

	// Determinant calculation
	T determinant()
	{
		/*
		|+ - + -|
		|- + - +|
		|+ - + -|
		|- + - +|
		*/

		// lambda function for lazyness
		auto e = [&](size_t a, size_t b) -> T {
			return elements[a][b];
		};

		// calculate the subMatrix 3x3 matrices
		Mat3<T> subMatrix1(
			e(1,1), e(1,2), e(1,3),
			e(2,1), e(2,2), e(2,3),
			e(3,1), e(3,2), e(3,3)
			);

		Mat3<T> subMatrix2(
			e(1,0), e(1,2), e(1,3),
			e(2,0), e(2,2), e(2,3),
			e(3,0), e(3,2), e(3,3)
			);

		Mat3<T> subMatrix3(
			e(1,0), e(1,1), e(1,3),
			e(2,0), e(2,1), e(2,3),
			e(3,0), e(3,1), e(3,3)
		);

		Mat3<T> subMatrix4(
			e(1,0), e(1,1), e(1,2),
			e(2,0), e(2,1), e(2,2),
			e(3,0), e(3,1), e(3,2)
		);

		// calculate the minors determinants
		T value1 = subMatrix1.determinant() * e(0,0);
		T value2 = subMatrix2.determinant() * e(0,1);
		T value3 = subMatrix3.determinant() * e(0,2);
		T value4 = subMatrix4.determinant() * e(0,3);

		// return the real determinant
		return value1 - value2 + value3 - value4;
	}
	// Transpose
	Mat4 transpose()
	{
		Mat4 result;
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t i = 0; i < 4; i++)
			{
				result.elements[i][j] = elements[j][i];
			}
		}
		return result;
	}
	// Inverse Operation
	
	Mat4 inverted() 
	{

		// calculate matrix minors
		/*
		| 00 01 02 03 |
		| 10 11 12 13 |
		| 20 21 22 23 |
		| 30 31 32 33 |
		*/
		
		// lambda function for lazyness
		auto e = [&](size_t a, size_t b) -> T {
			return elements[a][b];
		};

		// 1st row
		Mat3<T> minor00(
			e(1, 1), e(1, 2), e(1, 3),
			e(2, 1), e(2, 2), e(2, 3),
			e(3, 1), e(3, 2), e(3, 3)
		);
		Mat3<T> minor01(
			e(1, 0), e(1, 2), e(1, 3),
			e(2, 0), e(2, 2), e(2, 3),
			e(3, 0), e(3, 2), e(3, 3)
		);

		Mat3<T> minor02(
			e(1, 0), e(1, 1), e(1, 3),
			e(2, 0), e(2, 1), e(2, 3),
			e(3, 0), e(3, 1), e(3, 3)
		);
		Mat3<T> minor03(
			e(1, 0), e(1, 1), e(1, 2),
			e(2, 0), e(2, 1), e(2, 2),
			e(3, 0), e(3, 1), e(3, 2)
		);

		// 2nd row
		Mat3<T> minor10(
			e(0, 1), e(0, 2), e(0, 3),
			e(2, 1), e(2, 2), e(2, 3),
			e(3, 1), e(3, 2), e(3, 3)
		);
		Mat3<T> minor11(
			e(0, 0), e(0, 2), e(0, 3),
			e(2, 0), e(2, 2), e(2, 3),
			e(3, 0), e(3, 2), e(3, 3)
		);
		Mat3<T> minor12(
			e(0, 0), e(0, 1), e(0, 3),
			e(2, 0), e(2, 1), e(2, 3),
			e(3, 0), e(3, 1), e(3, 3)
		);
		Mat3<T> minor13(
			e(0, 0), e(0, 1), e(0, 2),
			e(2, 0), e(2, 1), e(2, 2),
			e(3, 0), e(3, 1), e(3, 2)
		);

		// 3rd row
		Mat3<T> minor20(
			e(0, 1), e(0, 2), e(0, 3),
			e(1, 1), e(1, 2), e(1, 3),
			e(3, 1), e(3, 2), e(3, 3)
		);
		Mat3<T> minor21(
			e(0, 0), e(0, 2), e(0, 3),
			e(1, 0), e(1, 2), e(1, 3),
			e(3, 0), e(3, 2), e(3, 3)
		);

		/*
		| 00 01 02 03 |
		| 10 11 12 13 |
		| 20 21 22 23 |
		| 30 31 32 33 |
		*/

		Mat3<T> minor22(
			e(0, 0), e(0, 1), e(0, 3),
			e(1, 0), e(1, 1), e(1, 3),
			e(3, 0), e(3, 1), e(3, 3)
		);
		Mat3<T> minor23(
			e(0, 0), e(0, 1), e(0, 2),
			e(1, 0), e(1, 1), e(1, 2),
			e(3, 0), e(3, 1), e(3, 2)
		);
		
		// 4th row
		Mat3<T> minor30(
			e(0, 1), e(0, 2), e(0, 3),
			e(1, 1), e(1, 2), e(1, 3),
			e(2, 1), e(2, 2), e(2, 3)
		);
		Mat3<T> minor31(
			e(0, 0), e(0, 2), e(0, 3),
			e(1, 0), e(1, 2), e(1, 3),
			e(2, 0), e(2, 2), e(2, 3)
		);

		Mat3<T> minor32(
			e(0, 0), e(0, 1), e(0, 3),
			e(1, 0), e(1, 1), e(1, 3),
			e(2, 0), e(2, 1), e(2, 3)
		);
		Mat3<T> minor33(
			e(0, 0), e(0, 1), e(0, 2),
			e(1, 0), e(1, 1), e(1, 2),
			e(2, 0), e(2, 1), e(2, 2)
		);

		// calculate cofactor using minors
		Mat4 cofactor(
			minor00.determinant(), -minor01.determinant(), minor02.determinant(), -minor03.determinant(),
			-minor10.determinant(), minor11.determinant(), -minor12.determinant(), minor13.determinant(),
			minor20.determinant(), -minor21.determinant(), minor22.determinant(), -minor23.determinant(),
			-minor30.determinant(), minor31.determinant(), -minor32.determinant(), minor33.determinant()
		);

		// transpose cofactor to find adjugate matrix
		// M_inv = 1/det(M) * adjugate(M)

		return cofactor.transpose() * (1.0 / this->determinant());
	}

	// Identity
	static Mat4 identity()
	{
		return {
			(T)1.0, (T)0.0, (T)0.0, (T)0.0,
			(T)0.0, (T)1.0, (T)0.0, (T)0.0,
			(T)0.0, (T)0.0, (T)1.0, (T)0.0,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0,
		};
	}
	// scaling
	static Mat4 scaling(T factor)
	{
		return {
			factor, (T)0.0, (T)0.0, (T)0.0,
			(T)0.0, factor, (T)0.0, (T)0.0,
			(T)0.0, (T)0.0, factor, (T)0.0,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0
		};
	}
	// Translation
	static Mat4 translation(const Vec4<T>& t)
	{
		return {
			(T)1.0, (T)0.0, (T)0.0, t.x,
			(T)0.0, (T)1.0, (T)0.0, t.y,
			(T)0.0, (T)0.0, (T)1.0, t.z,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0
		};
	}
	// Rotation X
	static Mat4 rotationZ(T theta)
	{
		const T sinTheta = sin(theta);
		const T cosTheta = cos(theta);
		return {
			cosTheta, -sinTheta, (T)0.0, (T)0.0,
			sinTheta, cosTheta,  (T)0.0, (T)0.0,
			(T)0.0,	 (T)0.0,	 (T)1.0, (T)0.0,
			(T)0.0,	 (T)0.0,	 (T)0.0, (T)1.0
		};
	}

	// Rotation Y
	static Mat4 rotationY(T theta)
	{
		const T sinTheta = sin(theta);
		const T cosTheta = cos(theta);
		return {
			cosTheta, (T)0.0, -sinTheta, (T)0.0,
			(T)0.0,   (T)1.0, (T)0.0,    (T)0.0,
			sinTheta, (T)0.0, cosTheta,  (T)0.0,
			(T)0.0,   (T)0.0, (T)0.0,    (T)1.0
		};
	}
	// Rotation Z
	static Mat4 rotationX(T theta)
	{
		const T sinTheta = sin(theta);
		const T cosTheta = cos(theta);
		return {
			(T)1.0, (T)0.0, (T)0.0, (T)0.0,
			(T)0.0, cosTheta, -sinTheta, (T)0.0,
			(T)0.0, sinTheta, cosTheta,  (T)0.0,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0
		};
	}

	/* OPERATORS *///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////

	// copies elements
	Mat4& operator= (const Mat4& other)
	{
		memcpy(elements, other.elements, sizeof(elements));
		return *this;
	}
	// *= multplies matrix with scalar
	Mat4& operator*=(T other)
	{
		for (auto& row : elements)
		{
			for (T& e : row)
			{
				e *= other;
			}
		}
		return *this;
	}

	// * multiplies matrix with scalar
	Mat4 operator* (T other) const
	{
		Mat4 result = *this;
		return result *= other;
	}

	// *= multiplies with matrix
	Mat4& operator*= (const Mat4& other)
	{
		return *this = *this * other;
	}
		
	// * multiplies with matrix
	Mat4 operator* (const Mat4& other) const
	{
		Mat4 result;
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				T sum = (T)0.0;
				for (size_t i = 0; i < 4; i++)
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
	T elements[4][4];
};

// Vector4 =  Mat4 * Vector4 product
template<typename T>
Vec4<T>& operator*=(const Mat4<T>& lhs, const Vec4<T>& rhs)
{
	return lhs = lhs * rhs;
}

template<typename T>
Vec4<T> operator* (const Mat4<T>& lhs, const Vec4<T>& rhs)
{
	/*
	| 00 01 02 03 |[x]
	| 10 11 12 13 |[y]
	| 20 21 22 23 |[z]
	| 30 31 32 33 |[w]
	*/
	return {
		rhs.x * lhs.elements[0][0] + rhs.y * lhs.elements[0][1] + rhs.z * lhs.elements[0][2] + rhs.w * lhs.elements[0][3],
		rhs.x * lhs.elements[1][0] + rhs.y * lhs.elements[1][1] + rhs.z * lhs.elements[1][2] + rhs.w * lhs.elements[1][3],
		rhs.x * lhs.elements[2][0] + rhs.y * lhs.elements[2][1] + rhs.z * lhs.elements[2][2] + rhs.w * lhs.elements[2][3],
		rhs.x * lhs.elements[3][0] + rhs.y * lhs.elements[3][1] + rhs.z * lhs.elements[3][2] + rhs.w * lhs.elements[3][3]
	};
}

/*
// TODO:: should vector - matrix product be defined? in that order
// if defined-> produces a matrix, not a vector

// Vector4 =  Vector4 product * Mat4 
template<typename T>
Vec4<T>& operator*=(Vec4<T>& lhs, const Mat4<T>& rhs)
{
	return lhs = lhs * rhs;
}

template<typename T> // TODO: is there vector matrix product
Vec4<T> operator* (const Vec4<T>& lhs, const Mat4<T>& rhs)
{
	
	//			  | 00 01 02 03 |
	//			  | 10 11 12 13 |
	//	<x y z w> | 20 21 22 23 |
	//			  | 30 31 32 33 |
	

	return {
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0] + lhs.w * rhs.elements[3][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1] + lhs.w * rhs.elements[3][1],
		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2] + lhs.w * rhs.elements[3][2],
		lhs.x * rhs.elements[0][3] + lhs.y * rhs.elements[1][3] + lhs.z * rhs.elements[2][3] + lhs.w * rhs.elements[3][3]
	};
}
*/


