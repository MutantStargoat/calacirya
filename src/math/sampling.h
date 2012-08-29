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
#ifndef CALA_SAMPLING_H_
#define CALA_SAMPLING_H_

#include "vector.h"
#include "mathdef.h"

inline Vector3 sphrand();

scalar_t gaussian(scalar_t x, scalar_t mean, scalar_t sdev);

inline scalar_t lerp(scalar_t a, scalar_t b, scalar_t t);

scalar_t bspline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);
scalar_t spline(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);
scalar_t bezier(scalar_t a, scalar_t b, scalar_t c, scalar_t d, scalar_t t);

#include "sampling.inl"

#endif	/* CALA_SAMPLING_H_ */
