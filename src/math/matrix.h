/*
Calacirya is a photorealistic 3D renderer.
Copyright (C) 2012 John Tsiombikas <nuclear@member.fsf.org>,
               and Nikos Papadopoulos <nikpapas@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CALA_MATRIX_H_
#define CALA_MATRIX_H_

#include <iostream>
#include "mathdef.h"

/* 3x3 matrix */
class Matrix3x3 {
private:
	scalar_t m[3][3];

public:

	static Matrix3x3 identity;

	Matrix3x3();
	Matrix3x3(	scalar_t m11, scalar_t m12, scalar_t m13,
				scalar_t m21, scalar_t m22, scalar_t m23,
				scalar_t m31, scalar_t m32, scalar_t m33);
	Matrix3x3(const Vector3 &ivec, const Vector3 &jvec, const Vector3 &kvec);

	Matrix3x3(const Matrix4x4 &mat4x4);

	/* binary operations matrix (op) matrix */
	friend Matrix3x3 operator +(const Matrix3x3 &m1, const Matrix3x3 &m2);
	friend Matrix3x3 operator -(const Matrix3x3 &m1, const Matrix3x3 &m2);
	friend Matrix3x3 operator *(const Matrix3x3 &m1, const Matrix3x3 &m2);

	friend void operator +=(Matrix3x3 &m1, const Matrix3x3 &m2);
	friend void operator -=(Matrix3x3 &m1, const Matrix3x3 &m2);
	friend void operator *=(Matrix3x3 &m1, const Matrix3x3 &m2);

	/* binary operations matrix (op) scalar and scalar (op) matrix */
	friend Matrix3x3 operator *(const Matrix3x3 &mat, scalar_t scalar);
	friend Matrix3x3 operator *(scalar_t scalar, const Matrix3x3 &mat);

	friend void operator *=(Matrix3x3 &mat, scalar_t scalar);

	inline scalar_t *operator [](int index);
	inline const scalar_t *operator [](int index) const;

	inline void reset_identity();

	void translate(const Vector2 &trans);
	void set_translation(const Vector2 &trans);

	void rotate(scalar_t angle);						/* 2d rotation */
	void rotate(const Vector3 &euler_angles);			/* 3d rotation with euler angles */
	void rotate(const Vector3 &axis, scalar_t angle);	/* 3d axis/angle rotation */
	void set_rotation(scalar_t angle);
	void set_rotation(const Vector3 &euler_angles);
	void set_rotation(const Vector3 &axis, scalar_t angle);

	void scale(const Vector3 &scale_vec);
	void set_scaling(const Vector3 &scale_vec);

	void set_column_vector(const Vector3 &vec, unsigned int col_index);
	void set_row_vector(const Vector3 &vec, unsigned int row_index);
	Vector3 get_column_vector(unsigned int col_index) const;
	Vector3 get_row_vector(unsigned int row_index) const;

	void transpose();
	Matrix3x3 transposed() const;
	scalar_t determinant() const;
	Matrix3x3 inverse() const;

	friend std::ostream &operator <<(std::ostream &out, const Matrix3x3 &mat);
};

/* binary operations matrix (op) matrix */
Matrix3x3 operator +(const Matrix3x3 &m1, const Matrix3x3 &m2);
Matrix3x3 operator -(const Matrix3x3 &m1, const Matrix3x3 &m2);
Matrix3x3 operator *(const Matrix3x3 &m1, const Matrix3x3 &m2);

void operator +=(Matrix3x3 &m1, const Matrix3x3 &m2);
void operator -=(Matrix3x3 &m1, const Matrix3x3 &m2);
void operator *=(Matrix3x3 &m1, const Matrix3x3 &m2);

/* binary operations matrix (op) scalar and scalar (op) matrix */
Matrix3x3 operator *(const Matrix3x3 &mat, scalar_t scalar);
Matrix3x3 operator *(scalar_t scalar, const Matrix3x3 &mat);

void operator *=(Matrix3x3 &mat, scalar_t scalar);

std::ostream &operator <<(std::ostream &out, const Matrix3x3 &mat);



/* 4x4 matrix */
class Matrix4x4 {
private:
	scalar_t m[4][4];

public:

	static Matrix4x4 identity;

	Matrix4x4();
	Matrix4x4(	scalar_t m11, scalar_t m12, scalar_t m13, scalar_t m14,
				scalar_t m21, scalar_t m22, scalar_t m23, scalar_t m24,
				scalar_t m31, scalar_t m32, scalar_t m33, scalar_t m34,
				scalar_t m41, scalar_t m42, scalar_t m43, scalar_t m44);

	Matrix4x4(const Matrix3x3 &mat3x3);

	/* binary operations matrix (op) matrix */
	friend Matrix4x4 operator +(const Matrix4x4 &m1, const Matrix4x4 &m2);
	friend Matrix4x4 operator -(const Matrix4x4 &m1, const Matrix4x4 &m2);
	friend Matrix4x4 operator *(const Matrix4x4 &m1, const Matrix4x4 &m2);

	friend void operator +=(Matrix4x4 &m1, const Matrix4x4 &m2);
	friend void operator -=(Matrix4x4 &m1, const Matrix4x4 &m2);
	friend inline void operator *=(Matrix4x4 &m1, const Matrix4x4 &m2);

	/* binary operations matrix (op) scalar and scalar (op) matrix */
	friend Matrix4x4 operator *(const Matrix4x4 &mat, scalar_t scalar);
	friend Matrix4x4 operator *(scalar_t scalar, const Matrix4x4 &mat);

	friend void operator *=(Matrix4x4 &mat, scalar_t scalar);

	inline scalar_t *operator [](int index);
	inline const scalar_t *operator [](int index) const;

	inline void reset_identity();

	void translate(const Vector3 &trans);
	void set_translation(const Vector3 &trans);

	void rotate(const Vector3 &euler_angles);			/* 3d rotation with euler angles */
	void rotate(const Vector3 &axis, scalar_t angle);	/* 3d axis/angle rotation */
	void set_rotation(const Vector3 &euler_angles);
	void set_rotation(const Vector3 &axis, scalar_t angle);

	void scale(const Vector4 &scale_vec);
	void set_scaling(const Vector4 &scale_vec);

	void set_column_vector(const Vector4 &vec, unsigned int col_index);
	void set_row_vector(const Vector4 &vec, unsigned int row_index);
	Vector4 get_column_vector(unsigned int col_index) const;
	Vector4 get_row_vector(unsigned int row_index) const;

	void transpose();
	Matrix4x4 transposed() const;
	scalar_t determinant() const;
	Matrix4x4 adjoint() const;
	Matrix4x4 inverse() const;

	friend std::ostream &operator <<(std::ostream &out, const Matrix4x4 &mat);
};

/* binary operations matrix (op) matrix */
Matrix4x4 operator +(const Matrix4x4 &m1, const Matrix4x4 &m2);
Matrix4x4 operator -(const Matrix4x4 &m1, const Matrix4x4 &m2);
Matrix4x4 operator *(const Matrix4x4 &m1, const Matrix4x4 &m2);

void operator +=(Matrix4x4 &m1, const Matrix4x4 &m2);
void operator -=(Matrix4x4 &m1, const Matrix4x4 &m2);
inline void operator *=(Matrix4x4 &m1, const Matrix4x4 &m2);

/* binary operations matrix (op) scalar and scalar (op) matrix */
Matrix4x4 operator *(const Matrix4x4 &mat, scalar_t scalar);
Matrix4x4 operator *(scalar_t scalar, const Matrix4x4 &mat);

void operator *=(Matrix4x4 &mat, scalar_t scalar);

std::ostream &operator <<(std::ostream &out, const Matrix4x4 &mat);

#include "matrix.inl"

#endif	/* CALA_MATRIX_H_ */
