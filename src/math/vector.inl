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

/* ----------- Vector2 ----------------- */

inline scalar_t &Vector2::operator [](int elem) {
	return elem ? y : x;
}

inline const scalar_t &Vector2::operator [](int elem) const {
	return elem ? y : x;
}

inline Vector2 operator -(const Vector2 &vec) {
	return Vector2(-vec.x, -vec.y);
}

inline scalar_t dot_product(const Vector2 &v1, const Vector2 &v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

inline Vector2 operator +(const Vector2 &v1, const Vector2 &v2) {
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

inline Vector2 operator -(const Vector2 &v1, const Vector2 &v2) {
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

inline Vector2 operator *(const Vector2 &v1, const Vector2 &v2) {
	return Vector2(v1.x * v2.x, v1.y * v2.y);
}

inline Vector2 operator /(const Vector2 &v1, const Vector2 &v2) {
	return Vector2(v1.x / v2.x, v1.y / v2.y);
}

inline bool operator ==(const Vector2 &v1, const Vector2 &v2) {
	return (fabs(v1.x - v2.x) < XSMALL_NUMBER) && (fabs(v1.y - v2.x) < XSMALL_NUMBER);
}

inline void operator +=(Vector2 &v1, const Vector2 &v2) {
	v1.x += v2.x;
	v1.y += v2.y;
}

inline void operator -=(Vector2 &v1, const Vector2 &v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
}

inline void operator *=(Vector2 &v1, const Vector2 &v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
}

inline void operator /=(Vector2 &v1, const Vector2 &v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
}

inline Vector2 operator +(const Vector2 &vec, scalar_t scalar) {
	return Vector2(vec.x + scalar, vec.y + scalar);
}

inline Vector2 operator +(scalar_t scalar, const Vector2 &vec) {
	return Vector2(vec.x + scalar, vec.y + scalar);
}

inline Vector2 operator -(scalar_t scalar, const Vector2 &vec) {
	return Vector2(vec.x - scalar, vec.y - scalar);
}

inline Vector2 operator *(const Vector2 &vec, scalar_t scalar) {
	return Vector2(vec.x * scalar, vec.y * scalar);
}

inline Vector2 operator *(scalar_t scalar, const Vector2 &vec) {
	return Vector2(vec.x * scalar, vec.y * scalar);
}

inline Vector2 operator /(const Vector2 &vec, scalar_t scalar) {
	return Vector2(vec.x / scalar, vec.y / scalar);
}

inline void operator +=(Vector2 &vec, scalar_t scalar) {
	vec.x += scalar;
	vec.y += scalar;
}

inline void operator -=(Vector2 &vec, scalar_t scalar) {
	vec.x -= scalar;
	vec.y -= scalar;
}

inline void operator *=(Vector2 &vec, scalar_t scalar) {
	vec.x *= scalar;
	vec.y *= scalar;
}

inline void operator /=(Vector2 &vec, scalar_t scalar) {
	vec.x /= scalar;
	vec.y /= scalar;
}

inline scalar_t Vector2::length() const {
	return sqrt(x*x + y*y);
}

inline scalar_t Vector2::length_sq() const {
	return x*x + y*y;
}

inline Vector2 lerp(const Vector2 &a, const Vector2 &b, scalar_t t)
{
	return a + (b - a) * t;
}

inline Vector2 catmull_rom_spline(const Vector2 &v0, const Vector2 &v1,
		const Vector2 &v2, const Vector2 &v3, scalar_t t)
{
	scalar_t spline(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t);
	scalar_t x = spline(v0.x, v1.x, v2.x, v3.x, t);
	scalar_t y = spline(v0.y, v1.y, v2.y, v3.y, t);
	return Vector2(x, y);
}


/* ------------- Vector3 -------------- */

inline scalar_t &Vector3::operator [](int elem) {
	return elem ? (elem == 1 ? y : z) : x;
}

inline const scalar_t &Vector3::operator [](int elem) const {
	return elem ? (elem == 1 ? y : z) : x;
}

/* unary operations */
inline Vector3 operator -(const Vector3 &vec) {
	return Vector3(-vec.x, -vec.y, -vec.z);
}

/* binary vector (op) vector operations */
inline scalar_t dot_product(const Vector3 &v1, const Vector3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 cross_product(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.y * v2.z - v1.z * v2.y,  v1.z * v2.x - v1.x * v2.z,  v1.x * v2.y - v1.y * v2.x);
}


inline Vector3 operator +(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator -(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3 operator *(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector3 operator /(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline bool operator ==(const Vector3 &v1, const Vector3 &v2) {
	return (fabs(v1.x - v2.x) < XSMALL_NUMBER) && (fabs(v1.y - v2.y) < XSMALL_NUMBER) && (fabs(v1.z - v2.z) < XSMALL_NUMBER);
}

inline void operator +=(Vector3 &v1, const Vector3 &v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}

inline void operator -=(Vector3 &v1, const Vector3 &v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}

inline void operator *=(Vector3 &v1, const Vector3 &v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
}

inline void operator /=(Vector3 &v1, const Vector3 &v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
}
/* binary vector (op) scalar and scalar (op) vector operations */
inline Vector3 operator +(const Vector3 &vec, scalar_t scalar) {
	return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline Vector3 operator +(scalar_t scalar, const Vector3 &vec) {
	return Vector3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

inline Vector3 operator -(const Vector3 &vec, scalar_t scalar) {
	return Vector3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

inline Vector3 operator *(const Vector3 &vec, scalar_t scalar) {
	return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vector3 operator *(scalar_t scalar, const Vector3 &vec) {
	return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline Vector3 operator /(const Vector3 &vec, scalar_t scalar) {
	return Vector3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline void operator +=(Vector3 &vec, scalar_t scalar) {
	vec.x += scalar;
	vec.y += scalar;
	vec.z += scalar;
}

inline void operator -=(Vector3 &vec, scalar_t scalar) {
	vec.x -= scalar;
	vec.y -= scalar;
	vec.z -= scalar;
}

inline void operator *=(Vector3 &vec, scalar_t scalar) {
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;
}

inline void operator /=(Vector3 &vec, scalar_t scalar) {
	vec.x /= scalar;
	vec.y /= scalar;
	vec.z /= scalar;
}

inline scalar_t Vector3::length() const {
	return sqrt(x*x + y*y + z*z);
}
inline scalar_t Vector3::length_sq() const {
	return x*x + y*y + z*z;
}

inline Vector3 lerp(const Vector3 &a, const Vector3 &b, scalar_t t) {
	return a + (b - a) * t;
}

inline Vector3 catmull_rom_spline(const Vector3 &v0, const Vector3 &v1,
		const Vector3 &v2, const Vector3 &v3, scalar_t t)
{
	scalar_t spline(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t);
	scalar_t x = spline(v0.x, v1.x, v2.x, v3.x, t);
	scalar_t y = spline(v0.y, v1.y, v2.y, v3.y, t);
	scalar_t z = spline(v0.z, v1.z, v2.z, v3.z, t);
	return Vector3(x, y, z);
}

/* ----------- Vector4 ----------------- */

inline scalar_t &Vector4::operator [](int elem) {
	return elem ? (elem == 1 ? y : (elem == 2 ? z : w)) : x;
}

inline const scalar_t &Vector4::operator [](int elem) const {
	return elem ? (elem == 1 ? y : (elem == 2 ? z : w)) : x;
}

inline Vector4 operator -(const Vector4 &vec) {
	return Vector4(-vec.x, -vec.y, -vec.z, -vec.w);
}

inline scalar_t dot_product(const Vector4 &v1, const Vector4 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline Vector4 cross_product(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3) {
	scalar_t a, b, c, d, e, f;       /* Intermediate Values */
    Vector4 result;

    /* Calculate intermediate values. */
    a = (v2.x * v3.y) - (v2.y * v3.x);
    b = (v2.x * v3.z) - (v2.z * v3.x);
    c = (v2.x * v3.w) - (v2.w * v3.x);
    d = (v2.y * v3.z) - (v2.z * v3.y);
    e = (v2.y * v3.w) - (v2.w * v3.y);
    f = (v2.z * v3.w) - (v2.w * v3.z);

    /* Calculate the result-vector components. */
    result.x =   (v1.y * f) - (v1.z * e) + (v1.w * d);
    result.y = - (v1.x * f) + (v1.z * c) - (v1.w * b);
    result.z =   (v1.x * e) - (v1.y * c) + (v1.w * a);
    result.w = - (v1.x * d) + (v1.y * b) - (v1.z * a);
    return result;
}

inline Vector4 operator +(const Vector4 &v1, const Vector4 &v2) {
	return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline Vector4 operator -(const Vector4 &v1, const Vector4 &v2) {
	return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline Vector4 operator *(const Vector4 &v1, const Vector4 &v2) {
	return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

inline Vector4 operator /(const Vector4 &v1, const Vector4 &v2) {
	return Vector4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

inline bool operator ==(const Vector4 &v1, const Vector4 &v2) {
	return	(fabs(v1.x - v2.x) < XSMALL_NUMBER) &&
			(fabs(v1.y - v2.y) < XSMALL_NUMBER) &&
			(fabs(v1.z - v2.z) < XSMALL_NUMBER) &&
			(fabs(v1.w - v2.w) < XSMALL_NUMBER);
}

inline void operator +=(Vector4 &v1, const Vector4 &v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
}

inline void operator -=(Vector4 &v1, const Vector4 &v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
}

inline void operator *=(Vector4 &v1, const Vector4 &v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	v1.w *= v2.w;
}

inline void operator /=(Vector4 &v1, const Vector4 &v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	v1.w /= v2.w;
}

/* binary vector (op) scalar and scalar (op) vector operations */
inline Vector4 operator +(const Vector4 &vec, scalar_t scalar) {
	return Vector4(vec.x + scalar, vec.y + scalar, vec.z + scalar, vec.w + scalar);
}

inline Vector4 operator +(scalar_t scalar, const Vector4 &vec) {
	return Vector4(vec.x + scalar, vec.y + scalar, vec.z + scalar, vec.w + scalar);
}

inline Vector4 operator -(const Vector4 &vec, scalar_t scalar) {
	return Vector4(vec.x - scalar, vec.y - scalar, vec.z - scalar, vec.w - scalar);
}

inline Vector4 operator *(const Vector4 &vec, scalar_t scalar) {
	return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

inline Vector4 operator *(scalar_t scalar, const Vector4 &vec) {
	return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

inline Vector4 operator /(const Vector4 &vec, scalar_t scalar) {
	return Vector4(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
}

inline void operator +=(Vector4 &vec, scalar_t scalar) {
	vec.x += scalar;
	vec.y += scalar;
	vec.z += scalar;
	vec.w += scalar;
}

inline void operator -=(Vector4 &vec, scalar_t scalar) {
	vec.x -= scalar;
	vec.y -= scalar;
	vec.z -= scalar;
	vec.w -= scalar;
}

inline void operator *=(Vector4 &vec, scalar_t scalar) {
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;
	vec.w *= scalar;
}

inline void operator /=(Vector4 &vec, scalar_t scalar) {
	vec.x /= scalar;
	vec.y /= scalar;
	vec.z /= scalar;
	vec.w /= scalar;
}

inline scalar_t Vector4::length() const {
	return sqrt(x*x + y*y + z*z + w*w);
}
inline scalar_t Vector4::length_sq() const {
	return x*x + y*y + z*z + w*w;
}

inline Vector4 lerp(const Vector4 &v0, const Vector4 &v1, scalar_t t)
{
	return v0 + (v1 - v0) * t;
}

inline Vector4 catmull_rom_spline(const Vector4 &v0, const Vector4 &v1,
		const Vector4 &v2, const Vector4 &v3, scalar_t t)
{
	scalar_t spline(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t);
	scalar_t x = spline(v0.x, v1.x, v2.x, v3.x, t);
	scalar_t y = spline(v0.y, v1.y, v2.y, v3.y, t);
	scalar_t z = spline(v0.z, v1.z, v2.z, v3.z, t);
	scalar_t w = spline(v0.w, v1.w, v2.w, v3.w, t);
	return Vector4(x, y, z, w);
}
