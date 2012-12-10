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
#ifndef CALA_RAYACCEL_H_
#define CALA_RAYACCEL_H_

#include "vmath/ray.h"
#include "surface.h"

namespace calacirya {

class RayAccel {
public:
	virtual ~RayAccel() = 0;
	virtual bool find_hit(const Ray &ray, SurfPoint *pt) const = 0;
};

}	// namespace calacirya

#endif	// CALA_RAYACCEL_H_
