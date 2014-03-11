////////////////////////////////////////////////////////////////////
// FILE:        vec3.hpp
//
// AUTHOR:      Martin Bertram
//
// DESCRIPTION:	a vector class to represent 3-D points and vectors
////////////////////////////////////////////////////////////////////

#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants ///////////////////////////////////////////////////////

#define	VEC_DIM	3
#define VEC_INF 1.0e9
#define VEC_EPS 1.0e-9

#define Null3 Vec3(0.0, 0.0, 0.0)
#define XVec3 Vec3(1.0, 0.0, 0.0)
#define YVec3 Vec3(0.0, 1.0, 0.0)
#define ZVec3 Vec3(0.0, 0.0, 1.0)


// 3D points and vectors /////////////////////////////////////////////
class Vec3 {
public:
	double	p[VEC_DIM];

	Vec3();
	Vec3(const Vec3 &a);
	~Vec3();
	explicit Vec3(const double* x);
	explicit Vec3(FILE *fp);
	Vec3(double x, double y, double z);

	Vec3& operator=(const Vec3& a);

	// scalar-vector arithmetics //////////////////////////////
	Vec3& operator+=(const Vec3& a);
	inline friend Vec3 operator+(Vec3 a, const Vec3& b) {
		return a += b;
	}

	Vec3& operator-=(const Vec3& a);
	inline friend Vec3 operator-(Vec3 a, const Vec3& b) {
		return a -= b;
	}

	inline friend Vec3 operator-(Vec3 a) {
		Vec3 c;
		for( int i=0; i<VEC_DIM; i++)
			c.p[i] = -a.p[i];
		return c;
	}

	Vec3& operator*=(double sc);
	inline friend Vec3 operator*(double sc, Vec3 a) {
		return a *= sc;
	}

	inline friend Vec3 operator*(Vec3 a, double sc) {
		return a *= sc;
	}

	Vec3& operator/=(double sc);
	inline friend Vec3 operator/(Vec3 a, double sc) {
		return a /= sc;
	}

	// dot product ////////////////////////////////////////////////
	double operator*=(const Vec3& b);
	inline friend double operator*(Vec3 a, const Vec3& b) {
		return a *= b;
	}

	// cross product //////////////////////////////////////////////
	inline friend Vec3 operator%(const Vec3& a, const Vec3& b) {
		Vec3 ret;

		ret.p[0] = a.p[1] * b.p[2] - a.p[2] * b.p[1];
		ret.p[1] = a.p[2] * b.p[0] - a.p[0] * b.p[2];
		ret.p[2] = a.p[0] * b.p[1] - a.p[1] * b.p[0];

		return ret;
	}

	double Length() const;
	double Length2() const;
	double LengthXY() const;
	double LengthXY2() const;
	double DotXY(const Vec3& a) const;
	double CrossXY(const Vec3& a) const;
	void MinMaxExpand(Vec3& min, Vec3& max) const;
	void Normalize();
	void Print(char *c) const;
	void FScan(FILE *fp);
	void FPrint(FILE *fp) const;
};
#endif
