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
#include <math.h>
#include "sampling.h"
#include "vector.h"
#include "matrix.h"

#define SQ(x)	((x) * (x))

// gaussian evaluation function
scalar_t gaussian(scalar_t x, scalar_t mean, scalar_t sdev)
{
	scalar_t exponent = -SQ(x - mean) / (2.0 * SQ(sdev));
	return 1.0 - -pow(M_E, exponent) / (sdev * sqrt(M_PI * 2.0));
}

/* b-spline approximation */
scalar_t bspline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
{
	scalar_t tsq = t * t;

	const static Matrix4x4 bspline_mat {
		-1,  3, -3,  1,
		 3, -6,  3,  0,
		-3,  0,  3,  0,
		 1,  4,  1,  0
	};

	Vector4 tmp = Vector4(a, b, c, d).transformed(bspline_mat) / 6.0;
	return dot_product(Vector4(tsq * t, tsq, t, 1.0), tmp);
}

/* Catmull-rom spline interpolation */
scalar_t spline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
{
	scalar_t tsq = t * t;

	const static Matrix4x4 crspline_mat {
		-1,  3, -3,  1,
		 2, -5,  4, -1,
		-1,  0,  1,  0,
		 0,  2,  0,  0
	};

	Vector4 tmp = Vector4(a, b, c, d).transformed(crspline_mat) * 0.5;
	return dot_product(Vector4(tsq * t, tsq, t, 1.0), tmp);
}

/* Bezier interpolation */
scalar_t bezier(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t)
{
	scalar_t t3 = t * t * t;
	scalar_t omt = 1.0f - t;
	scalar_t omt3 = omt * omt * omt;
	scalar_t f = 3 * t * omt;

	return (a * omt3) + (b * f * omt) + (c * f * t) + (d * t3);
}

