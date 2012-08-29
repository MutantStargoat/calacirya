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
#include <random>
#include <functional>
#include "mathdef.h"

// uniform random vector on the surface of the unit sphere
inline Vector3 sphrand()
{
	static std::uniform_real_distribution<scalar_t> dis{0.0, 1.0};
	static std::mt19937 mt;

	auto rnd = std::bind(dis, mt);

	scalar_t u = rnd();
	scalar_t v = rnd();

	scalar_t theta = 2.0 * M_PI * u;
	scalar_t phi = acos(2.0 * v - 1.0);

	return Vector3(cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi));
}

inline scalar_t lerp(scalar_t a, scalar_t b, scalar_t t)
{
	return a + (b - a) * t;
}
