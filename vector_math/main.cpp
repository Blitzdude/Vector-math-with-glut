#include <stdlib.h>
#include <glut/glut.h>
#include <iostream>

// vector libraries
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

void printVec4(const char* const name, const Vec4<float>& v)
{
	printf("%-12s = <%2.2f, %2.2f, %2.2f, %2.2f>\n", name, v.x, v.y, v.z, v.w);
}

void printVec3(const char* const name, const Vec3<float>& v)
{
	printf("%-12s = <%2.2f, %2.2f, %2.2f>\n", name, v.x, v.y, v.z);
}

void printVec2(const char* const name, const Vec2<float>& v)
{
	printf("%-12s = <%2.2f, %.2f>\n", name, v.x, v.y);
}

void printMat4(const char* const name, const Mat4<float>& m)
{
	printf("%-12s = \n", name);
	for (size_t j = 0; j < 4; j++)
	{
		printf("[ ");
		for (size_t i = 0; i < 4; i++)
		{
			printf(" %2.2f ", m.elements[j][i]);
		}
		printf("]\n");
	}

}

int main(int argc, char ** argv) {
	/* TODO implement glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Vector Demo");
	*/

	// Vector 3d Tests - TEHT�V�NANTO T�SS�!!!!
	/*
	printf("VECTOR3D\n");
	Vec3<float> v1(1, 2, 3);
	Vec3<float> v2(4, 4, 5);
	printVec3("v1", v1);
	printVec3("v2", v2);
	printVec3("v1 + v2", v1 + v2);
	printVec3("v1 - v2", v1 - v2);
	printVec3("v1 cross v2", Vec3<float>::CrossProduct(v1, v2));
	*/

	// Vector 2d Tests
	/*
	printf("\n\nVECTOR2D\n");
	Vec2<float> v2d_1(3.0f, 2.0f);
	Vec2<float> v2d_2(4.0f, 1.0f);
	printVec2("v2d_1", v2d_1);
	printVec2("v2d_2", v2d_2);
	printVec2("v2d_1 + v2d_2", v2d_1 + v2d_2);
	printVec2("v2d_1 - v2d_2", v2d_1 - v2d_2);
	printf("v1 cross v2    = %2.2f\n", Vec2<float>::CrossProduct(v2d_1, v2d_2));

	printf("length squared    = %2.2f\n", v2d_1.sqLength());
	printf("v1 length    = %2.2f\n", v2d_1.length());
	*/

	/*
	// Vector 4d Tests
	printf("\n\nVECTOR4D\n");
	Vec4<float> v4d_1(3.0f, 2.0f, 2.0f, 1.0f);
	Vec4<float> v4d_2(1.0f, 2.0f, 5.0f, 3.0f);
	printVec4("v4d_1", v4d_1);
	printVec4("v4d_2", v4d_2);
	printVec4("v1 + v2", v4d_1 + v4d_2);
	printVec4("v1 - v2", v4d_1 - v4d_2);
	printf("v1 is equal v2    = %d\n", v4d_1 == v4d_2 );
	v4d_2 = v4d_1;
	printf("v1 is equal v2    = %d\n", v4d_1 == v4d_2);
	*/

	Mat4<float> mat1(
		1.0f, 0.0f, 0.0f, 0.0f,
		2.0f, 2.0f, 2.0f, 2.0f,
		3.0f, 3.0f, 3.0f, 3.0f,
		4.0f, 4.0f, 4.0f, 4.0f);

	printMat4("matrix1", mat1);

	mat1 = mat1.transpose();

	printMat4("matrix1", mat1);
	
	Mat4<float> rotMatZ = Mat4<float>::rotationZ(toRadians(180.0f));
	printMat4("rotMatZ", rotMatZ);
	Vec4<float> res1 = Vec4<float>(1.0f, 2.0f, 2.0f, 3.0f) * mat1;
	
	printVec4("res1", res1);
	

	// ask for input to stop program from running
	int a;
	printf("Enter any char to exit >> ");
	std::cin >> a;

	return 0;
}