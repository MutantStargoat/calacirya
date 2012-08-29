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
#ifndef CALA_VECTOR_H_
#define CALA_VECTOR_H_

#include <iostream>
#include "mathdef.h"

class Vector3;
class Vector4;
class Matrix3x3;
class Matrix4x4;
class Quaternion;

class Vector2 {
public:
	scalar_t x, y;

	Vector2(scalar_t x = 0.0, scalar_t y = 0.0);
	Vector2(const Vector3 &vec);
	Vector2(const Vector4 &vec);

	inline scalar_t &operator [](int elem);
	inline const scalar_t &operator [](int elem) const;

	inline scalar_t length() const;
	inline scalar_t length_sq() const;
	void normalize();
	Vector2 normalized() const;

	void transform(const Matrix3x3 &mat);
	Vector2 transformed(const Matrix3x3 &mat) const;

	void rotate(scalar_t angle);
	Vector2 rotated(scalar_t angle) const;

	Vector2 reflection(const Vector2 &normal) const;
	Vector2 refraction(const Vector2 &normal, scalar_t src_ior, scalar_t dst_ior) const;
};

/* unary operations */
inline Vector2 operator -(const Vector2 &vec);

/* binary vector (op) vector operations */
inline scalar_t dot_product(const Vector2 &v1, const Vector2 &v2);

inline Vector2 operator +(const Vector2 &v1, const Vector2 &v2);
inline Vector2 operator -(const Vector2 &v1, const Vector2 &v2);
inline Vector2 operator *(const Vector2 &v1, const Vector2 &v2);
inline Vector2 operator /(const Vector2 &v1, const Vector2 &v2);
inline bool operator ==(const Vector2 &v1, const Vector2 &v2);

inline void operator +=(Vector2 &v1, const Vector2 &v2);
inline void operator -=(Vector2 &v1, const Vector2 &v2);
inline void operator *=(Vector2 &v1, const Vector2 &v2);
inline void operator /=(Vector2 &v1, const Vector2 &v2);

/* binary vector (op) scalar and scalar (op) vector operations */
inline Vector2 operator +(const Vector2 &vec, scalar_t scalar);
inline Vector2 operator +(scalar_t scalar, const Vector2 &vec);
inline Vector2 operator -(const Vector2 &vec, scalar_t scalar);
inline Vector2 operator *(const Vector2 &vec, scalar_t scalar);
inline Vector2 operator *(scalar_t scalar, const Vector2 &vec);
inline Vector2 operator /(const Vector2 &vec, scalar_t scalar);

inline void operator +=(Vector2 &vec, scalar_t scalar);
inline void operator -=(Vector2 &vec, scalar_t scalar);
inline void operator *=(Vector2 &vec, scalar_t scalar);
inline void operator /=(Vector2 &vec, scalar_t scalar);

std::ostream &operator <<(std::ostream &out, const Vector2 &vec);

inline Vector2 lerp(const Vector2 &a, const Vector2 &b, scalar_t t);
inline Vector2 catmull_rom_spline(const Vector2 &v0, const Vector2 &v1,
		const Vector2 &v2, const Vector2 &v3, scalar_t t);

/* 3D Vector */
class Vector3 {
public:
	scalar_t x, y, z;

	Vector3(scalar_t x = 0.0, scalar_t y = 0.0, scalar_t z = 0.0);
	Vector3(const Vector2 &vec);
	Vector3(const Vector4 &vec);

	inline scalar_t &operator [](int elem);
	inline const scalar_t &operator [](int elem) const;

	inline scalar_t length() const;
	inline scalar_t length_sq() const;
	void normalize();
	Vector3 normalized() const;

	void transform(const Matrix3x3 &mat);
	Vector3 transformed(const Matrix3x3 &mat) const;
	void transform(const Matrix4x4 &mat);
	Vector3 transformed(const Matrix4x4 &mat) const;
	void transform(const Quaternion &quat);
	Vector3 transformed(const Quaternion &quat) const;

	void rotate(const Vector3 &euler);
	Vector3 rotated(const Vector3 &euler) const;

	Vector3 reflection(const Vector3 &normal) const;
	Vector3 refraction(const Vector3 &normal, scalar_t src_ior, scalar_t dst_ior) const;
	Vector3 refraction(const Vector3 &normal, scalar_t ior) const;
};

/* unary operations */
inline Vector3 operator -(const Vector3 &vec);

/* binary vector (op) vector operations */
inline scalar_t dot_product(const Vector3 &v1, const Vector3 &v2);
inline Vector3 cross_product(const Vector3 &v1, const Vector3 &v2);

inline Vector3 operator +(const Vector3 &v1, const Vector3 &v2);
inline Vector3 operator -(const Vector3 &v1, const Vector3 &v2);
inline Vector3 operator *(const Vector3 &v1, const Vector3 &v2);
inline Vector3 operator /(const Vector3 &v1, const Vector3 &v2);
inline bool operator ==(const Vector3 &v1, const Vector3 &v2);

inline void operator +=(Vector3 &v1, const Vector3 &v2);
inline void operator -=(Vector3 &v1, const Vector3 &v2);
inline void operator *=(Vector3 &v1, const Vector3 &v2);
inline void operator /=(Vector3 &v1, const Vector3 &v2);

/* binary vector (op) scalar and scalar (op) vector operations */
inline Vector3 operator +(const Vector3 &vec, scalar_t scalar);
inline Vector3 operator +(scalar_t scalar, const Vector3 &vec);
inline Vector3 operator -(const Vector3 &vec, scalar_t scalar);
inline Vector3 operator *(const Vector3 &vec, scalar_t scalar);
inline Vector3 operator *(scalar_t scalar, const Vector3 &vec);
inline Vector3 operator /(const Vector3 &vec, scalar_t scalar);

inline void operator +=(Vector3 &vec, scalar_t scalar);
inline void operator -=(Vector3 &vec, scalar_t scalar);
inline void operator *=(Vector3 &vec, scalar_t scalar);
inline void operator /=(Vector3 &vec, scalar_t scalar);

std::ostream &operator <<(std::ostream &out, const Vector3 &vec);

inline Vector3 lerp(const Vector3 &a, const Vector3 &b, scalar_t t);
inline Vector3 catmull_rom_spline(const Vector3 &v0, const Vector3 &v1,
		const Vector3 &v2, const Vector3 &v3, scalar_t t);

/* 4D Vector */
class Vector4 {
public:
	scalar_t x, y, z, w;

	Vector4(scalar_t x = 0.0, scalar_t y = 0.0, scalar_t z = 0.0, scalar_t w = 0.0);
	Vector4(const Vector2 &vec);
	Vector4(const Vector3 &vec);

	inline scalar_t &operator [](int elem);
	inline const scalar_t &operator [](int elem) const;

	inline scalar_t length() const;
	inline scalar_t length_sq() const;
	void normalize();
	Vector4 normalized() const;

	void transform(const Matrix4x4 &mat);
	Vector4 transformed(const Matrix4x4 &mat) const;

	Vector4 reflection(const Vector4 &normal) const;
	Vector4 refraction(const Vector4 &normal, scalar_t src_ior, scalar_t dst_ior) const;
};


/* unary operations */
inline Vector4 operator -(const Vector4 &vec);

/* binary vector (op) vector operations */
inline scalar_t dot_product(const Vector4 &v1, const Vector4 &v2);
inline Vector4 cross_product(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3);

inline Vector4 operator +(const Vector4 &v1, const Vector4 &v2);
inline Vector4 operator -(const Vector4 &v1, const Vector4 &v2);
inline Vector4 operator *(const Vector4 &v1, const Vector4 &v2);
inline Vector4 operator /(const Vector4 &v1, const Vector4 &v2);
inline bool operator ==(const Vector4 &v1, const Vector4 &v2);

inline void operator +=(Vector4 &v1, const Vector4 &v2);
inline void operator -=(Vector4 &v1, const Vector4 &v2);
inline void operator *=(Vector4 &v1, const Vector4 &v2);
inline void operator /=(Vector4 &v1, const Vector4 &v2);

/* binary vector (op) scalar and scalar (op) vector operations */
inline Vector4 operator +(const Vector4 &vec, scalar_t scalar);
inline Vector4 operator +(scalar_t scalar, const Vector4 &vec);
inline Vector4 operator -(const Vector4 &vec, scalar_t scalar);
inline Vector4 operator *(const Vector4 &vec, scalar_t scalar);
inline Vector4 operator *(scalar_t scalar, const Vector4 &vec);
inline Vector4 operator /(const Vector4 &vec, scalar_t scalar);

inline void operator +=(Vector4 &vec, scalar_t scalar);
inline void operator -=(Vector4 &vec, scalar_t scalar);
inline void operator *=(Vector4 &vec, scalar_t scalar);
inline void operator /=(Vector4 &vec, scalar_t scalar);

std::ostream &operator <<(std::ostream &out, const Vector4 &vec);

inline Vector4 lerp(const Vector4 &v0, const Vector4 &v1, scalar_t t);
inline Vector4 catmull_rom_spline(const Vector4 &v0, const Vector4 &v1,
		const Vector4 &v2, const Vector4 &v3, scalar_t t);

#include "vector.inl"

#endif	/* CALA_VECTOR_H_ */
